
#include "green_house.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i = 0;
	time_t t;
	
	// init rand
	srand((unsigned) time(&t));

	int trys = 100000;

	double threshold = 0.0;
	int pump_run_time = 0;
	int frequency_spray = 0;
	int spray_length = 0;
	double max_fittness = 1000.0;
	
	double max_threshold = 1.0;
	int max_pump_run_time = 1;
	int max_frequency_spray = 1;
	int max_spray_length = 1;

	green_house * gh = green_house_create(10000, 1.0, 1.0, 3.0, 10.0, 2.0, .1, .08, 3.0, .3, .002, .16, .2);

	for(i = 0; i < trys; i++)
	{
		threshold = 5*((double)rand() / (double)RAND_MAX);
		pump_run_time = (rand() % 120) + 1;
		frequency_spray = (rand() % 360) + 1;
		spray_length = (rand() % 20) +1;
		green_house_run(gh, threshold, pump_run_time, frequency_spray, spray_length);
		if(gh->total_fittness < max_fittness)
		{
			max_fittness = gh->total_fittness;
			printf("new min at %lf \n", gh->total_fittness);
			max_threshold = threshold;
			max_pump_run_time = pump_run_time;
			max_frequency_spray = frequency_spray;
			max_spray_length = spray_length;
		}
	

	}	

	green_house_run(gh, max_threshold, max_pump_run_time, max_frequency_spray, max_spray_length);
	print_double_array("moisture.txt", gh->plant_moisture, gh->run_time);
	print_double_array("mass.txt", gh->mass_air_tank, gh->run_time);
	print_double_array("fittness.txt", gh->fittness, gh->run_time);
	print_double_array("mist_control.txt", gh->mist_control, gh->run_time);
	return 0;
}

