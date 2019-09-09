#define LOG_TAG "RTKBT_API"
#ifdef BLUETOOTH_RTK_API
#include <string.h>
#include <hardware/bluetooth.h>
#include "hardware/bt_rtkbt.h"
#include "bt_target.h"
#include "bt_trace.h"
#include "btif_common.h"
#include "rtkbt_api.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


/*
    a sample of rtkbt_plugin_{id}.conf

    A=123
    B=4567 876
    C=11:22:33:44:55:66

    [GA]
    A=111
    B=4444 555
    C=11:11:11:11:11:11
    D=22:22:22:22:22:22

    [GB]
    A=333
    B=777 999
    C=66:66:66:66:66:66

    [GC]
    A=333
    B=777 999
    D=CCCCCCCC

*/
static char * contents[RTKBT_MAX_ID] = {0};
struct config_entry
{
    struct config_entry * next;
    char * group;
    char * item;
    char * val;
} * configs[RTKBT_MAX_ID] = {0};
/*
    rtkbt_conf_getline - internal funciton
    get a new line from head,return a pointer to the line header.
    left while return  (pointer of end of new line +1)
*/
static char * rtkbt_conf_getline(char * head, char ** left)
{
    char * next;
    if(*head == 0)
        return NULL;
    while((*head == '\r')||(*head == '\n'))
        head++;
    if(*head == 0)
        return NULL;
    next = head;
    while((*next != '\r')&&(*next != '\n')&&(*next != 0))
        next++;
    if(*next != 0)
        *next++ = 0;
    *left = next;
    return head;
}
/*
    rtkbt_conf_parse_config - internal funciton
    Parse config item from content and store all config item in items
    return: id of plugin
*/
static int rtkbt_conf_parse_config(struct config_entry **items, char *content)
{
    char * group = NULL;
    char * item = NULL;
    char * val = NULL;
    char * line = NULL;
    int id = -1;
    struct config_entry * entry, * head, *end;

    char * p;

    head = NULL;
    end = NULL;

    ALOGD("rtkbt_conf_parse_config\n");
    while((line = rtkbt_conf_getline(content, &content)) != NULL)
    {
        ALOGD("rtkbt_conf_parse_config line:%s\n", line);
        switch(line[0])
        {
            case '[':
            {
                p = strstr(line,"]");
                if(p)
                {
                    *p = 0;
                    group = &(line[1]);
                    ALOGI("rtkbt_conf_parse_config Find Group[%s]\n", group);
                }else{
                    ALOGW("rtkbt_conf_parse_config Expected ']' end of Group(%s)!\n", line);
                }
                break;
            }
            case '{':
            {
                p = strstr(line,"}");
                if(p)
                {
                    *p = 0;
                    id = strtol((&(line[1])), NULL, 0);
                    ALOGI("rtkbt_conf_parse_config Find PluginID[%d]\n", id);
                }else{
                    ALOGW("rtkbt_conf_parse_config Expected '}' end of PluginID(%s)!\n", line);
                }
                break;
            }
            case '#':
            {
                break;
            }
            default:
            {
                p = strstr(line,"=");
                if(p)
                {
                    *p++ = 0;
                    item = line;
                    val = p;
                    if((item[0]==0)||(val[0]==0))
                    {
                        ALOGI("rtkbt_conf_parse_config ignore(item:%s val:%s)\n", item[0]?item:"(null)", val[0]?val:"(null)");
                        break;
                    }
                    ALOGI("rtkbt_conf_parse_config Find Item[%s:%s=%s]\n", group, item, val);
                    entry = malloc(sizeof(struct config_entry));
                    if(entry)
                    {
                        entry->next = NULL;
                        entry->group = group;
                        entry->item = item;
                        entry->val = val;
                        if(end)
                        {
                            end->next = entry;
                            end = entry;
                        }else
                            end = entry;
                        if(head == NULL)
                            head = entry;
                    }
                }
            }
        }
    }
    *items = head;
    return id;
}
#if 0
int rtkbt_loadconfig()
{
    int i,res,fd;
    struct stat st;
    char path[1024];
    memset(config, 0, sizeof(config));
    memset(configs, 0, sizeof(configs));
    for(i = 0;i < RTKBT_MAX_ID; i++)
    {
        memset(path, 0, sizeof(path));
        sprintf(path, "%s/rtkbt_plugin_%d.conf", RTKBT_CONF_DIR, i);
        ALOGI("load_plugin_configs(%s) load!\n", path);
        fd = open(path, O_RDONLY);
        if(fd < 0)
        {
            ALOGW("load_plugin_configs(%s) open fail!\n", path);
            continue;
        }
        res = fstat(fd, &st);
        if(res)
        {
            ALOGW("load_plugin_configs(%s) stat fail! reason=%d\n", path, res);
            continue;
        }
        if(st.st_size <= 0)
        {
            ALOGW("load_plugin_configs(%s) size fail! size=%d\n", path, (int)st.st_size);
            continue;
        }
        ALOGI("load_plugin_configs(%s) size=%d!\n", path, (int)st.st_size);
        config[i] = malloc(st.st_size+1);
        if(config[i] == NULL)
        {
            ALOGW("load_plugin_configs(%s) malloc fail!\n", path);
            continue;
        }
        res = read(fd, config[i], st.st_size);
        if(res <= 0)
        {
            ALOGW("load_plugin_configs(%s) read fail! res=%d\n", path, res);
            continue;
        }
        config[i][res] = 0;
        res = rtkbt_conf_parse_config(&configs[i], config[i]);
        if(res <= 0)
        {
            ALOGW("load_plugin_configs(%s) rtkbt_conf_parse_config fail! res=%d\n", path, res);
            continue;
        }
    }
    return 0;
}
#else
int rtkbt_loadconfig(char * path)
{
    int res,fd;
    struct stat st;
    char * content = NULL;
    struct config_entry * config = NULL;

    ALOGI("rtkbt_loadconfig(%s) load!\n", path);
    fd = open(path, O_RDONLY);
    if(fd < 0)
    {
        ALOGW("rtkbt_loadconfig(%s) open fail!\n", path);
        return -1;
    }
    res = fstat(fd, &st);
    if(res)
    {
        ALOGW("rtkbt_loadconfig(%s) stat fail! reason=%d\n", path, res);
        return -1;
    }
    if(st.st_size <= 0)
    {
        ALOGW("rtkbt_loadconfig(%s) size fail! size=%d\n", path, (int)st.st_size);
        return -1;
    }
    ALOGI("rtkbt_loadconfig(%s) size=%d!\n", path, (int)st.st_size);
    content = malloc(st.st_size+1);
    if(content == NULL)
    {
        ALOGW("rtkbt_loadconfig(%s) malloc fail!\n", path);
        return -1;
    }
    res = read(fd, content, st.st_size);
    if(res <= 0)
    {
        ALOGW("rtkbt_loadconfig(%s) read fail! res=%d\n", path, res);
        return -1;
    }
    content[res] = 0;
    res = rtkbt_conf_parse_config(&config, content);
    if((res < 0)||(res >= RTKBT_MAX_ID))
    {
        ALOGW("rtkbt_loadconfig(%s) rtkbt_conf_parse_config fail! res=%d\n", path, res);
        return -1;
    }
    configs[res] = config;
    contents[res] = content;
    return 0;
}
#endif
int rtkbt_conf_init()
{
    memset(contents, 0, sizeof(contents));
    memset(configs, 0, sizeof(configs));
    return 0;
}
int rtkbt_conf_exit()
{
    struct config_entry *item, *p;
    int i;

    for(i = 0;i < RTKBT_MAX_ID; i++)
    {
        item = configs[i];
        while(item)
        {
            p = item;
            item = item->next;
            free(p);
        }
        if(contents[i])
            free(contents[i]);
    }
    return 0;
}
/*
    rtkbt_api_GetConfig
    used by plugin or bluedroid.
    id: PluginID
    group: config group
    item: config item

    return: config item val,it's a string.
*/
char * rtkbt_api_GetConfig(int id, char * group, char * item)
{
    struct config_entry * entry;

    if(item == NULL)
        return NULL;
    entry = configs[id];
    while(entry)
    {
        if(group&&(entry->group)&&(strcmp(entry->group, group)==0)&&(strcmp(entry->item, item)==0))
            return entry->val;
        if((group==NULL)&&(entry->group==NULL)&&(strcmp(entry->item, item)==0))
            return entry->val;

        entry = entry->next;
    }
    return NULL;
}
#endif

