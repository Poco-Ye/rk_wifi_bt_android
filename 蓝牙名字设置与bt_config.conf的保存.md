```
diff --git a/btif/src/btif_core.c b/btif/src/btif_core.c
index 9c23f0b1..5c028849 100755
--- a/btif/src/btif_core.c
+++ b/btif/src/btif_core.c
@@ -1188,6 +1188,8 @@ bt_status_t btif_set_adapter_property(const bt_property_t *property)
                 BTA_DmSetDeviceName((char *)bd_name);

                 storage_req_id = BTIF_CORE_STORAGE_ADAPTER_WRITE;
+               btif_config_set_str("Adapter", "Name",(char *)bd_name);
+               btif_config_flush();
             }
             break;

```

这个patch是针对改完名字，关掉蓝牙（shut_down）才会写进去，data/misc/bluedroid/bt_config.conf

上层往下调，接口到这里，然后可以再到btm


```
rk322x_box:/data/misc/bluedroid # cat bt_config.conf
[Info]
FileSource = Backup
TimeCreated = 1970-01-01 00:00:16

[Adapter]
Address = cc:b8:a8:84:dd:8d
LE_LOCAL_KEY_IRK = 64d123036294e8bd4be03637080a643d
LE_LOCAL_KEY_IR = 9af845e6d3c2bacf05714a5524866da3
LE_LOCAL_KEY_DHK = 6791e2afb07bba233acdb634daced595
LE_LOCAL_KEY_ER = 38b5aa4ae9412e2b4ee8e333d5842e8d
ScanMode = 2
DiscoveryTimeout = 120
Name = rk322xheheuuyyppuuyyuuuuuuuuu
```

bt_config.conf

btif_config_set_str将key 和value加入链表

```
bool btif_config_set_str(const char *section, const char *key, const char *value) {
  assert(config != NULL);
  assert(section != NULL);
  assert(key != NULL);
  assert(value != NULL);

  pthread_mutex_lock(&lock);
  config_set_string(config, section, key, value); //here
  pthread_mutex_unlock(&lock);

  return true;  
}
```

系统是放在list上面去的，组合方式就是section, key, value
```
void config_set_string(config_t *config, const char *section, const char *key, const char *value) {
  section_t *sec = section_find(config, section);
  if (!sec) {
    sec = section_new(section);
    list_append(config->sections, sec);
  }

  for (const list_node_t *node = list_begin(sec->entries); node != list_end(sec->entries); node = list_next(node)) {   //here
    entry_t *entry = list_node(node);
    if (!strcmp(entry->key, key)) {
      osi_free(entry->value);
      entry->value = osi_strdup(value);
      return;
    }
  }

  entry_t *entry = entry_new(key, value);
  list_append(sec->entries, entry);
}
```

btif_config_flush()将链表保存进去/data/misc/bluedroid/bt_config.conf
```
void btif_config_flush(void) {
  assert(config != NULL);
  assert(config_timer != NULL);

  alarm_cancel(config_timer); 
  btif_config_write(0, NULL); //here
}
```

```

static void btif_config_write(UNUSED_ATTR UINT16 event, UNUSED_ATTR char *p_param) {
  assert(config != NULL);
  assert(config_timer != NULL);

  pthread_mutex_lock(&lock);
  rename(CONFIG_FILE_PATH, CONFIG_BACKUP_PATH);
  config_t *config_paired = config_new_clone(config);
  btif_config_remove_unpaired(config_paired);
  config_save(config_paired, CONFIG_FILE_PATH);  //here
  config_free(config_paired);
  pthread_mutex_unlock(&lock);
}
```


```
bool config_save(const config_t *config, const char *filename) {
  assert(config != NULL);
  assert(filename != NULL);
  assert(*filename != '\0');

  // Steps to ensure content of config file gets to disk:
  //
  // 1) Open and write to temp file (e.g. bt_config.conf.new).
  // 2) Sync the temp file to disk with fsync().
  // 3) Rename temp file to actual config file (e.g. bt_config.conf).
  //    This ensures atomic update.
  // 4) Sync directory that has the conf file with fsync().
  //    This ensures directory entries are up-to-date.
  int dir_fd = -1;
  FILE *fp = NULL;

  // Build temp config file based on config file (e.g. bt_config.conf.new).
  static const char *temp_file_ext = ".new";
  const int filename_len = strlen(filename);
  const int temp_filename_len = filename_len + strlen(temp_file_ext) + 1;
  char *temp_filename = osi_calloc(temp_filename_len);
  snprintf(temp_filename, temp_filename_len, "%s%s", filename, temp_file_ext);

  // Extract directory from file path (e.g. /data/misc/bluedroid).
  char *temp_dirname = osi_strdup(filename);
  const char *directoryname = dirname(temp_dirname);
  if (!directoryname) {
    LOG_ERROR(LOG_TAG, "%s error extracting directory from '%s': %s", __func__, filename, strerror(errno));
    goto error;
  }

  dir_fd = open(directoryname, O_RDONLY);
  if (dir_fd < 0) {
    LOG_ERROR(LOG_TAG, "%s unable to open dir '%s': %s", __func__, directoryname, strerror(errno));
    goto error;
  }

  fp = fopen(temp_filename, "wt");
  if (!fp) {
    LOG_ERROR(LOG_TAG, "%s unable to write file '%s': %s", __func__, temp_filename, strerror(errno));
    goto error;
  }

  for (const list_node_t *node = list_begin(config->sections); node != list_end(config->sections); node = list_next(node)) { //here 一个一个section 写 比如[info][adapter]
    const section_t *section = (const section_t *)list_node(node);
    if (fprintf(fp, "[%s]\n", section->name) < 0) {
      LOG_ERROR(LOG_TAG, "%s unable to write to file '%s': %s", __func__, temp_filename, strerror(errno));
      goto error;
    }

    for (const list_node_t *enode = list_begin(section->entries); enode != list_end(section->entries); enode = list_next(enode)) {
      const entry_t *entry = (const entry_t *)list_node(enode);
      if (fprintf(fp, "%s = %s\n", entry->key, entry->value) < 0) {
        LOG_ERROR(LOG_TAG, "%s unable to write to file '%s': %s", __func__, temp_filename, strerror(errno));
        goto error;
      }
    }

    // Only add a separating newline if there are more sections.
    if (list_next(node) != list_end(config->sections)) {
      if (fputc('\n', fp) == EOF) {
        LOG_ERROR(LOG_TAG, "%s unable to write to file '%s': %s", __func__, temp_filename, strerror(errno));
        goto error;
      }
    }
  }

  // Sync written temp file out to disk. fsync() is blocking until data makes it to disk.
  if (fsync(fileno(fp)) < 0) {
    LOG_WARN(LOG_TAG, "%s unable to fsync file '%s': %s", __func__, temp_filename, strerror(errno));
  }

  if (fclose(fp) == EOF) {
    LOG_ERROR(LOG_TAG, "%s unable to close file '%s': %s", __func__, temp_filename, strerror(errno));
    goto error;
  }
  fp = NULL;

  // Change the file's permissions to Read/Write by User and Group
  if (chmod(temp_filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) == -1) {
    LOG_ERROR(LOG_TAG, "%s unable to change file permissions '%s': %s", __func__, filename, strerror(errno));
    goto error;
  }

  // Rename written temp file to the actual config file.
  if (rename(temp_filename, filename) == -1) {
    LOG_ERROR(LOG_TAG, "%s unable to commit file '%s': %s", __func__, filename, strerror(errno));
    goto error;
  }

  // This should ensure the directory is updated as well.
  if (fsync(dir_fd) < 0) {
    LOG_WARN(LOG_TAG, "%s unable to fsync dir '%s': %s", __func__, directoryname, strerror(errno));
  }

  if (close(dir_fd) < 0) {
    LOG_ERROR(LOG_TAG, "%s unable to close dir '%s': %s", __func__, directoryname, strerror(errno));
    goto error;
  }

  osi_free(temp_filename);
  osi_free(temp_dirname);
  return true;

error:
  // This indicates there is a write issue.  Unlink as partial data is not acceptable.
  unlink(temp_filename);
  if (fp)
    fclose(fp);
  if (dir_fd != -1)
    close(dir_fd);
  osi_free(temp_filename);
  osi_free(temp_dirname);
  return false;
}
```


