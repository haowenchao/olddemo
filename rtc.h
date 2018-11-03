#ifndef _RTC_H_
#define _RTC_H_

struct time_desc {
	unsigned char sec, min, hour;
	unsigned char day, date, month, year;
};

enum alarm {
	secen  = 1 << 0,
	minen  = 1 << 1,
	houren = 1 << 2,
	dateen = 1 << 3,
	monen  = 1 << 4,
	yearen = 1 << 5,
};

#endif

