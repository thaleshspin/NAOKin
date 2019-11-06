#include "Timer.h"
#include <unistd.h>

using namespace std;

Timer::Timer()
{
    Restart();
}

void Timer::Restart()
{
    clock_gettime(CLOCK_REALTIME, &start);
}

/* return elapsed time in seconds */
float Timer::Seconds() 
{
    return Millis() / 1000.0f;
}

uint32_t Timer::Millis() 
{
    return Micros() / 1000.0f;
}

uint32_t Timer::Micros() 
{
    clock_gettime(CLOCK_REALTIME, &end);
    float value = ((end.tv_sec - start.tv_sec) * 1000000.0f + (end.tv_nsec - start.tv_nsec) / 1000.0f);
    return value;
}

/* return estimated maximum value for elapsed() */
float Timer::SecondsMax() 
{
    /* Portability warning: elapsed_max() may return too high a value on systems
    * where std::clock_t overflows or resets at surprising values.
    */
    return Seconds();
}

/* return minimum value for elapsed() */
float Timer::SecondsMin() 
{
    return Seconds();
}

void Timer::Wait(int ms)
{
    usleep( 1000 * ms );
}