#include "green_house.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	green_house * gh = green_house_create(86400, 1.0, 3.0, 1.0, 10.0, 2.0, .01, .08, 3.0, .3, .0002, .16, .2);

	green_house_run(gh, 3.69, 2, 150, 5);
	print_double_array("test_moisture.txt", gh->plant_moisture, gh->run_time);
	print_double_array("test_mass.txt", gh->mass_air_tank, gh->run_time);
	print_double_array("test_fittness.txt", gh->fittness, gh->run_time);
	print_double_array("test_mist_control.txt", gh->mist_control, gh->run_time);
	print_double_array("test_pump_control.txt", gh->pump_control, gh->run_time);


	return 0;
}

