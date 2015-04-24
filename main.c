
#include "green_house.h"
#include <stdio.h>


int main()
{
	green_house * gh = green_house_create(1000, 1.0, 1.0, 100.0, 10.0, .02, .02, .08, .05, .1, .002, .16, .2);
	green_house_run(gh, 2, 100, 5, 1);
	green_house_run(gh, 2, 1, 5, 1);
	print_double_array("test.txt", gh->mass_air_tank, gh->run_time);
	print_double_array("fittness.txt", gh->fittness, gh->run_time);
	return 0;
}

