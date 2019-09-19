#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <sys/time.h>

#include <cutils/log.h>
#include <cutils/properties.h>





#define BLUETOOTH_TTY_TEST 1

int uart_fd = -1;
struct termios termios;
unsigned char  buffer[1024];
int ttytestResult= -1;
unsigned char hci_reset[] = { 0x01, 0x03, 0x0c, 0x00 };
unsigned char hci_rtksyc[] = { 0xc0, 0x00, 0x2f, 0x00,0xd0, 0x01,0x7e,0xc0};


void
init_uart_brcm()
{
	tcflush(uart_fd, TCIOFLUSH);
	int n = tcgetattr(uart_fd, &termios);
	printf("tcgetattr %d\n",n);

#ifndef __CYGWIN__
	cfmakeraw(&termios);
#else
	termios.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                | INLCR | IGNCR | ICRNL | IXON);
	termios.c_oflag &= ~OPOST;
	termios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	termios.c_cflag &= ~(CSIZE | PARENB);
	termios.c_cflag |= CS8;
#endif

	//termios.c_cflag |= CRTSCTS;
	tcsetattr(uart_fd, TCSANOW, &termios);
	tcflush(uart_fd, TCIOFLUSH);
	tcsetattr(uart_fd, TCSANOW, &termios);
	tcflush(uart_fd, TCIOFLUSH);
	tcflush(uart_fd, TCIOFLUSH);
	cfsetospeed(&termios, B115200);
	cfsetispeed(&termios, B115200);
	tcsetattr(uart_fd, TCSANOW, &termios);
}


void
init_uart_rtk()
{
	tcflush(uart_fd, TCIOFLUSH);
	int n = tcgetattr(uart_fd, &termios);
	printf("tcgetattr %d\n",n);

#ifndef __CYGWIN__
	cfmakeraw(&termios);
#else
	termios.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                | INLCR | IGNCR | ICRNL | IXON);
	termios.c_oflag &= ~OPOST;
	termios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	termios.c_cflag &= ~(CSIZE | PARENB);
	termios.c_cflag |= CS8;
#endif
		termios.c_cflag &= ~CRTSCTS;

	termios.c_cflag |= PARENB;

	//termios.c_cflag |= CRTSCTS;
	tcsetattr(uart_fd, TCSANOW, &termios);
	tcflush(uart_fd, TCIOFLUSH);
	tcsetattr(uart_fd, TCSANOW, &termios);
	tcflush(uart_fd, TCIOFLUSH);
	tcflush(uart_fd, TCIOFLUSH);
	cfsetospeed(&termios, B115200);
	cfsetispeed(&termios, B115200);
	tcsetattr(uart_fd, TCSANOW, &termios);
}

void
dump(unsigned char *out, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (i && !(i % 16)) {
			printf("\n");
		}

		printf("%02x ", out[i]);
	}

	printf("\n");
}


#define READTTY_TIMEOUT  30//3s
int readttyLen(int fd,unsigned char *buffer,int len)
{
	int count;
	int i= 0;
	int timeout=0;
	while(len){
		count = read(fd,&buffer[i],1);
		if(count == 1){
			i += count;
			len -= count;
		}
		else{
			usleep(100000);//100ms
			timeout ++;
			//printf("timeout %d\n", timeout);
			if(timeout >= READTTY_TIMEOUT)
				return -1;
		}
		printf("received %d\n", i);
		dump(buffer, i);
		
	}
	return i;
}
void readBrcmTty(int fd, unsigned char  *buffer)
{
	int i=0;
	int count;
	int len;
	count = readttyLen(fd,buffer,3);
	printf("readBrcmTty count11 %d\n", count);
	if(count < 3)
		return;
	i += count;
	len = buffer[2];
	
	count = readttyLen(fd,&buffer[i],len);
	if(count<len)
		return;
	i += count;

	//if (debug)
	{

		printf("readBrcmTty received %d\n", i);
		dump(buffer, i);
	}
	
	ttytestResult = 0;
	printf("bt ttytest read_event succ\n");
}

void readRtkTty(int fd, unsigned char  *buffer)
{
	int i=0;
	int count;
	int len;
	
	count = readttyLen(fd,buffer,16);
	if(count < 16){
		printf("received count %d\n", count);
		return;
	}
	i += count;

	//if (debug)
	{

		printf("received %d\n", i);
		dump(buffer, i);
	}

	ttytestResult = 0;
	printf("bt ttytest read_event succ\n");
}


void
hci_send_cmd(unsigned char *buf, int len)
{
	//if (debug) 
	{
		printf("writing\n");
		dump(buf, len);
	}

	int writelen=write(uart_fd, buf, len);
	printf("writelen %d\n",writelen);
}


void
expired(int sig)
{
    ttytestResult = -1;
	printf("bt ttytest expired\n");
}

void
proc_reset()
{
	signal(SIGALRM, expired);

	printf( "proc_reset");
	alarm(8);

	hci_send_buf(hci_reset, sizeof(hci_reset));

	read_event(uart_fd, buffer);

	alarm(0);
}

#define CONF_COMMENT '#'
#define CONF_DELIMITERS " =\n\r\t"
#define CONF_VALUES_DELIMITERS "=\n\r\t"
#define CONF_MAX_LINE_LEN 255
void get_tty_conf(const char *p_path,char *ttyPort)
{
    FILE    *p_file;
    char    *p_name;
    char    *p_value;
    char    line[CONF_MAX_LINE_LEN+1]; /* add 1 for \0 char */

    printf( "Attempt to load conf from %s", p_path);

    if ((p_file = fopen(p_path, "r")) != NULL)
    {
        /* read line by line */
        while (fgets(line, CONF_MAX_LINE_LEN+1, p_file) != NULL)
        {
            if (line[0] == CONF_COMMENT)
                continue;

            p_name = strtok(line, CONF_DELIMITERS);

            if (NULL == p_name)
            {
                continue;
            }

            p_value = strtok(NULL, CONF_DELIMITERS);

            if (NULL == p_value)
            {
                printf( "vnd_load_conf: missing value for name: %s", p_name);
                continue;
            }

            if (strcmp("UartPort", (const char *)p_name) == 0){
				printf("get ttyPort %s", p_value);
				strcpy(ttyPort,p_value);
				fclose(p_file);
				return;
            }
			
        }

        fclose(p_file);
    }
    else
    {
        printf( "vnd_load_conf file >%s< not found", p_path);
    }
	strcpy(ttyPort,"/dev/ttyS0");
}

int test_rtktty()
{
	init_uart_rtk();
	hci_send_cmd(hci_rtksyc, sizeof(hci_rtksyc));
	readRtkTty(uart_fd, buffer);
	return ttytestResult;
}
int test_brcmtty()
{
	init_uart_brcm();
	hci_send_cmd(hci_reset, sizeof(hci_reset));
	readBrcmTty(uart_fd, buffer);
	return ttytestResult;
}

static void ttytestThread(void *param)
{
	char ttyPort[30]={0};
   system("echo 1 > /sys/class/rfkill/rfkill0/state");
	sleep(1);
    get_tty_conf("/vendor/etc/bluetooth/bt_vendor.conf",ttyPort);
	if ((uart_fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NONBLOCK)) == -1) {
		printf( "port could not be opened, error %d\n", errno);
	}

	int i;
	for(i=0;i<3;i++){
	 if(test_brcmtty()>=0)
	 	return;
	 //if(test_rtktty()>=0)
	 //	return;
	}

}

int bluetoothtty_test()
{
    int i;
	
	pthread_t thread_id;
	pthread_create(&thread_id, NULL,(void*)ttytestThread, NULL);
	for(i=10;i>0;i--){
		sleep(1);
		if(ttytestResult == 0)
			return 0;
	}
	return -1;	

}

int
main (int argc, char **argv)

{

	bluetoothtty_test();
	return 0;

}



