#include "timer.h"
#include "xtime_l.h"


static XTime start_time, end_time;
static u8 timer_started_flag = FALSE;


void timer_start()
{
	XTime_GetTime(&start_time);
	timer_started_flag = TRUE;
}


double timer_stop()
{
	double time_elapsed_ms = 0;

	if (timer_started_flag == TRUE)
	{
		XTime_GetTime(&end_time);
		time_elapsed_ms = 1000.0 * (end_time - start_time) / COUNTS_PER_SECOND;
		timer_started_flag = FALSE;
	}

	return time_elapsed_ms;
}
