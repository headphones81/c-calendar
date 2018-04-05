#include <stdio.h>
#include "time.h"
time_t rawtime;
struct tm * timeinfo;
struct tm when;
const char *days[] = {"Sun", "Mon", "Tue", "Wed",
                "Thu", "Fri", "Sat"};

int a[6][7];

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
printf("\t\t%d %d %d \t\n",day,mon,yea);
for(int i = 0; i <= 6; i++){printf("%s\t",days[(i+1) % 7]);}
printf("\n");


/*
for ( int i = 1; i <= lastday; ++i){
if ((i == day ) && (dow(yea,mon,i) != 0)) { printf("[%d]\t" , i); }
else if ((i == day ) && (dow(yea,mon,i) == 0)) { printf("[%d] \n" , i); }
else if ((i != day ) && (dow(yea,mon,i) != 0)){ printf("%d\t",i);}
else if ((i != day ) && (dow(yea,mon,i) == 0)){ printf("%d \n",i);}
}

*/

for (int wday = 0; wday <= 6; wday++){
    for (int i =1; i<= lastday; ++i){
        if (wday == dow(yea,mon,i)){a[1+(i+dow(yea,mon,1)-1)/7][wday-1] = i;}
    
    }

    
}

 for ( int row = 0; row <= 6; ++row){
        for (int col = 0; col < 7; ++col ){
         if (a[row][col] != 0 && a[row][col] != day) {printf("%2d\t",a[row][col]);}
         else if (a[row][col] != 0 && a[row][col] == day) {printf("[%d]\t",a[row][col]);}
         else {printf("\t");}
        }
    
     printf("\n");
 }    
    return 0;
}