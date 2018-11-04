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

void rtc_get(struct time_desc* time);
void rtc_set(struct time_desc* time);
void rtc_enable_alarm(enum alarm source);
void rtc_disable_alarm(enum alarm source);
int rtc_alarm_valid(enum alarm source);
void rtc_enable_tick(unsigned char period);
void rtc_disable_tick(void);
int rtc_tick_valid(void);
#endif

