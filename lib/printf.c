#include "vsprintf.h"
#include "string.h"

unsigned char outbuf[1024];
unsigned char inbuf[1024];

extern char getc(void);
extern void putc(char);

int printf(const char* fmt,...)
{
	unsigned int i;
	va_list args;
	va_start(args,fmt);  //fmt转化为变参列表
	vsprintf((char*)outbuf,fmt,args); // 变参列表转化为字符串
	va_end(); //转化结束

	for(i=0;i<strlen((const char*)outbuf);i++)
	{
		putc(outbuf[i]);

	}
	return i;
}

int scanf(const char* fmt, ...)
{
	unsigned char c;
	int i = 0;
	va_list args;


	while (1)
	{

		c = getc();	
		if ((c==0x0d) || (c==0x0a))
		{
			inbuf[i] = '\n';
			break;
		}
		else
		{
			inbuf[i++] = c;	
		}
	}

	va_start(args, fmt);
	vsscanf((char *)inbuf,fmt,args);
	va_end(args);

	return i;
}
