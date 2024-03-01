#ifndef _ALARM_H_
#define _ALARM_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int get_hourDiff();
int get_minsDiff();
long get_timeDiff_sec();
void buzz();
void set_alarm();
void display();

#endif