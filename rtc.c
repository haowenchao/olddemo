#include "rtc.h"
#include "lib/printf.h"

#ifndef BIG_ENDIAN

#define RTCCON   (*((volatile unsigned char *)0x57000040))
#define TICNT    (*((volatile unsigned char *)0x57000044))
#define RTCALM   (*((volatile unsigned char *)0x57000050))
#define ALMSEC   (*((volatile unsigned char *)0x57000054))
#define ALMMIN   (*((volatile unsigned char *)0x57000058))
#define ALMHOUR  (*((volatile unsigned char *)0x5700005C))
#define ALMDATE  (*((volatile unsigned char *)0x57000060))
#define ALMMON   (*((volatile unsigned char *)0x57000064))
#define ALMYEAR  (*((volatile unsigned char *)0x57000068))
#define BCDSEC   (*((volatile unsigned char *)0x57000070))
#define BCDMIN   (*((volatile unsigned char *)0x57000074))
#define BCDHOUR  (*((volatile unsigned char *)0x57000078))
#define BCDDATE  (*((volatile unsigned char *)0x5700007C))
#define BCDDAY   (*((volatile unsigned char *)0x57000080))
#define BCDMON   (*((volatile unsigned char *)0x57000084))
#define BCDYEAR  (*((volatile unsigned char *)0x57000088))

#else

#define RTCCON   (*((volatile unsigned char *)0x57000043))
#define TICNT    (*((volatile unsigned char *)0x57000047))
#define RTCALM   (*((volatile unsigned char *)0x57000053))
#define ALMSEC   (*((volatile unsigned char *)0x57000057))
#define ALMMIN   (*((volatile unsigned char *)0x5700005B))
#define ALMHOUR  (*((volatile unsigned char *)0x5700005F))
#define ALMDATE  (*((volatile unsigned char *)0x57000063))
#define ALMMON   (*((volatile unsigned char *)0x57000067))
#define ALMYEAR  (*((volatile unsigned char *)0x5700006B))
#define BCDSEC   (*((volatile unsigned char *)0x57000073))
#define BCDMIN   (*((volatile unsigned char *)0x57000077))
#define BCDHOUR  (*((volatile unsigned char *)0x5700007B))
#define BCDDATE  (*((volatile unsigned char *)0x5700007F))
#define BCDDAY   (*((volatile unsigned char *)0x57000083))
#define BCDMON   (*((volatile unsigned char *)0x57000087))
#define BCDYEAR  (*((volatile unsigned char *)0x5700008B))

#endif

void rtc_get(struct time_desc* time)
{
	unsigned char val;

	RTCCON |= (unsigned char)0x01;

	val = BCDSEC;
	time->sec = (val & 0xf) + (((val >> 4) & 0x7) * 10);

	val = BCDMIN;
	time->min = (val & 0xf) + (((val >> 4) & 0x7) * 10);

	val = BCDHOUR;
	time->hour = (val & 0xf) + (((val >> 4) & 0x3) * 10);

	val = BCDDATE;
	time->date = (val & 0xf) + (((val >> 4) & 0x3) * 10);

	val = BCDDAY;
	time->day = val & 0x7;

	val = BCDMON;
	time->month = (val & 0xf) + (((val >> 4) & 0x1) * 10);

	val = BCDYEAR;
	time->year = val;

	RTCCON &= (unsigned char)~0x1;
}

void rtc_set(struct time_desc* time)
{ 
	unsigned char val;

	//assert
	if(time->sec > 60 || time->min > 60 || time->hour > 24 \
		|| time->day > 7 || time->date > 31 \
		|| time->month > 12) {
		printf("\n\rparameters unvalid\n\r");
		return;
	}

	RTCCON |= (unsigned char)0x1;

	val = time->sec % 10 ;
	val |= (unsigned char)((time->sec / 10) << 4);
	BCDSEC = val;

	val = time->min % 10 ;
	val |= (unsigned char)((time->min / 10) << 4);
	BCDMIN = val;

	val = time->hour % 10;
	val |= (unsigned char)((time->hour / 10) << 4);
	BCDHOUR = val;

	val = time->day;
	BCDDAY = val;

	val = time->date % 10;
	val |= (unsigned char)((time->date / 10) << 4);
	BCDDATE = val;

	val = time->month % 10;
	val |= (unsigned char)((time->month / 10) << 4);
	BCDMON = val;

	val = time->year;
	BCDYEAR = val;

	RTCCON &= (unsigned char)~0x1;
}

void rtc_enable_alarm(enum alarm source)
{
	RTCCON |= 0x1;

	RTCALM |= 1 << 6;

	RTCALM |= 1 << source;

	RTCCON &= ~0x1;
} 

void rtc_disable_alarm(enum alarm source)
{
	RTCALM &= ~(1 << source);
}

void rtc_set_alarm_time(struct time_desc *time)
{
	unsigned char val;

	//assert
	if(time->sec > 60 || time->min > 60 || time->hour > 24 \
		|| time->day > 7 || time->date > 31 \
		|| time->month > 12) {
		printf("\n\rparameters unvalid\n\r");
		return;
	}

	RTCCON |= (unsigned char)0x1;

	val = time->sec % 10 ;
	val |= (unsigned char)((time->sec / 10) << 4);
	ALMSEC = val;

	val = time->min % 10 ;
	val |= (unsigned char)((time->min / 10) << 4);
	ALMMIN = val;

	val = time->hour % 10;
	val |= (unsigned char)((time->hour / 10) << 4);
	ALMHOUR = val;

	val = time->date % 10;
	val |= (unsigned char)((time->date / 10) << 4);
	ALMDATE = val;

	val = time->month % 10;
	val |= (unsigned char)((time->month / 10) << 4);
	ALMMON = val;

	val = time->year;
	ALMYEAR = val;

	RTCCON &= (unsigned char)~0x1;
}

int rtc_alarm_valid(enum alarm source)
{
	switch(source)
	{
	case secen:
	break;

	case minen:
	break;

	case houren:
	break;

	case dateen:
	break;

	case monen:
	break;

	case yearen:
	break;
	}
}

void rtc_enable_tick(unsigned char period)
{
	period |= 0x80;

	TICNT = period;
}

void rtc_disable_tick(void)
{
	TICNT &= ~0x80;
}

int rtc_tick_valid(void)
{
	return TICNT & 0x7f;
}

