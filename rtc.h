#ifndef _RTC_H_
#define _RTC_H_

struct time_desc {
	unsigned char sec, min, hour;
	unsigned char day, date, month, year;
};

enum alarm {
	secen  = 0,
	minen  = 1,
	houren = 2,
	dateen = 3,
	monen  = 4,
	yearen = 5,
};

void rtc_get(struct time_desc* time);
void rtc_set(struct time_desc* time);
void rtc_enable_alarm(enum alarm source);
void rtc_disable_alarm(enum alarm source);
void rtc_set_alarm_time(struct time_desc *alm_time);
int rtc_alarm_valid(enum alarm source);
void rtc_enable_tick(unsigned char period);
void rtc_disable_tick(void);
int rtc_tick_valid(void);
#endif

