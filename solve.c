
#include "green_house.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i = 0;
	time_t t;
	
	// init rand
	srand((unsigned) time(&t));

	// init bins
	int num_bins = 10000;
	int bins[num_bins];
	double bin_size = .0001;
	int store = 0;
	for (i = 0; i < num_bins; i++)
	{
		bins[i] = 0;
	}



	// init greenhouse system
	int trys = 150000;

	double threshold = 0.0;
	int pump_run_time = 0;
	int frequency_spray = 0;
	int spray_length = 0;
	double max_fittness = 1000.0;
	
	double max_threshold = 1.0;
	int max_pump_run_time = 1;
	int max_frequency_spray = 1;
	int max_spray_length = 1;

	green_house * gh = green_house_create(86400, 1.0, 3.0, 1.0, 10.0, 2.0, .01, .08, 3.0, .3, .0002, .16, .2);

	for(i = 0; i < trys; i++)
	{
		threshold = 5*((double)rand() / (double)RAND_MAX);
		pump_run_time = (rand() % 120) + 1;
		frequency_spray = (rand() % 360) + 1;
		spray_length = (rand() % 20) +1;
		green_house_run(gh, threshold, pump_run_time, frequency_spray, spray_length);
		store = (int)(gh->total_fittness / bin_size);
		if(gh->total_fittness < max_fittness)
		{
			max_fittness = gh->total_fittness;
			printf("new min at %lf \n", gh->total_fittness);
			max_threshold = threshold;
			max_pump_run_time = pump_run_time;
			max_frequency_spray = frequency_spray;
			max_spray_length = spray_length;
		}
		if (store < num_bins)
		{
			bins[store] = bins[store] + 1;
		}

	}	

	green_house_run(gh, max_threshold, max_pump_run_time, max_frequency_spray, max_spray_length);
	printf("threshold %lf \n", max_threshold);
	printf("pump_run_time %i \n", max_pump_run_time);
	printf("frequency spray %i \n", max_frequency_spray);
	printf("spray length %i \n", max_spray_length);
	print_double_array("moisture.txt", gh->plant_moisture, gh->run_time);
	print_double_array("mass.txt", gh->mass_air_tank, gh->run_time);
	print_double_array("fittness.txt", gh->fittness, gh->run_time);
	print_double_array("mist_control.txt", gh->mist_control, gh->run_time);
	print_double_array("pump_control.txt", gh->pump_control, gh->run_time);
	print_int_array("bins.txt", bins, num_bins);
	return 0;
}

