#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ioctl.h>

#define MCP_MAGIC       'M'
#define SHUTDWN_NO      0x01
#define MCP_SHUTDWN     _IO(MCP_MAGIC,SHUTDWN_NO)
#define WAKEUP_NO	0x02
#define MCP_WKEUP	_IO(MCP_MAGIC,WAKEUP_NO)

int main(void)
{
    int file;
    char filename[] = "/dev/mcp9808";
    char temp[2],ch;

    file = open(filename,O_RDWR);
    if(file < 0){
	printf("Coudn't open /dev/mcp9808\n");
	exit(0);
    }

    ioctl(file,MCP_WKEUP);
    do
    {
	memset(temp,0,2);
	if(read(file,temp,2) != 2){
	    printf("Read fail\n");
	}
	printf("Temperature value = %d.%d\n",temp[0],temp[1]);
	printf("Press y|Y to read another value = ");	
	scanf("%c",&ch);
	getchar();
    }while(ch == 'y' || ch == 'Y');

    ioctl(file,MCP_SHUTDWN);
    close(file);
    return 0;
}


