#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SNOTIFY "notify-send"
int main(int argc, char const *argv[]){
	time_t mytime;
    mytime = time(NULL);

    int i;
    i = 0;

    while(i < 5) {
	    ctime(&mytime);
	    char *system_call;
	    struct tm * timeinfo;
	    timeinfo = localtime (&mytime);
	    sprintf(system_call, "%s \"It's %d:%d\"", SNOTIFY, timeinfo->tm_hour, timeinfo->tm_min);

	    printf("\a");
	    system(system_call);

	    usleep(1000 * 1000 * 5);

	    i++;
    }
	return 0;
}