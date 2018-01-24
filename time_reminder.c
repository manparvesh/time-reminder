#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SNOTIFY "notify-send"
#define ONE_SECOND_IN_MILLISECONDS 1000000
// #define DEBUG

void notification_sound(){
    printf("\a\n");
}

void update_current_time(time_t mytime, struct tm ** timeinfo){
    mytime = time(NULL);
    ctime(&mytime);
    *timeinfo = localtime (&mytime);
}

void sleep_for_one_second(){
    usleep(ONE_SECOND_IN_MILLISECONDS);
}

void sleep_for_n_seconds(int n){
	int i;
	i = 0;
	while(i < n){
		sleep_for_one_second();
		i++;
	}
}

int main(int argc, char const *argv[]){
    int time_in_minutes;
	time_in_minutes = 30;

    int time_in_seconds;
#ifdef DEBUG
    time_in_seconds = 1;
#else
    time_in_seconds = time_in_minutes * 60;
#endif

	time_t mytime;

	// waiting for time to reach :00 or :30
    while(1) {
		struct tm * timeinfo;

	    update_current_time(mytime, &timeinfo);
	    sleep_for_one_second();
#ifdef DEBUG
	    printf("%d:%d:%d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	    // stops after 2 mins
	    if (timeinfo->tm_min % 2 == 0) {
	    	break;
	    }
#else
	    if (timeinfo->tm_min % 30 == 0) {
	    	break;
	    }
#endif
	    // free(timeinfo);
    }

    // start alerting user after every 30 minutes from now
    while(1) {
    	notification_sound();

    	char *system_call;
		struct tm * timeinfo;

	    update_current_time(mytime, &timeinfo);
	    sprintf(system_call, "%s \"It's %d:%d\"", SNOTIFY, timeinfo->tm_hour, timeinfo->tm_min);

	    system(system_call);

	    // wait for the specified time
	    sleep_for_n_seconds(time_in_seconds);
    }
	return 0;
}