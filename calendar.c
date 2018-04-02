#include <stdio.h>
#include "time.h"
time_t rawtime;
struct tm * timeinfo;
struct tm when;
const char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
				"Thursday", "Friday", "Saturday"};
				
int dow(int y, int m, int d) {
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= m < 3;
	return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int LastDay (int iMonth, int iYear)
{
    //struct tm when;
    time_t lastday;

    // Set up current month
    when.tm_hour = 0;
    when.tm_min = 0;
    when.tm_sec = 0;
    when.tm_mday = 1;

    // Next month 0=Jan
    if (iMonth == 12)
    {
        when.tm_mon = 0;
        when.tm_year = iYear - 1900 + 1;
    }
    else
    {
        when.tm_mon = iMonth;
        when.tm_year = iYear - 1900;
    }
    // Get the first day of the next month
    lastday = mktime (&when);

    // Subtract 1 day
    lastday -= 86400;

    // Convert back to date and time
    when = *localtime (&lastday);

    return when.tm_mday;
}

int main(void) {
time (&rawtime);
timeinfo = localtime (&rawtime);
int day = timeinfo->tm_mday;
int mon = timeinfo->tm_mon +1;
int yea = timeinfo->tm_year +1900;
int wday = timeinfo->tm_wday;
int lastday = LastDay(mon,yea);
printf("%d %d %d %d \t",day,mon,yea,wday);
printf("%s\n\n", days[dow(yea,mon, day)]);
for(int i = 1; i<= lastday; i++){
if ((i == day ) && (dow(yea,mon,i) != 0)) { printf("[%d]\t" , i); }
else if ((i == day ) && (dow(yea,mon,i) == 0)) { printf("[%d] \n" , i); }
else if ((i != day ) && (dow(yea,mon,i) != 0)){ printf("%d\t",i);}
else if ((i != day ) && (dow(yea,mon,i) == 0)){ printf("%d \n",i);}

 }
	return 0;
}