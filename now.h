#ifndef NOW_H
#define NOW_H
#include <sys/time.h>
double now(){
    struct timeval tim;
    gettimeofday(&tim, NULL);
    return tim.tv_sec + tim.tv_usec/1000000.0;
}

#endif // NOW_H
