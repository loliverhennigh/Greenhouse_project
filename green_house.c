#include <stdio.h>
#include <malloc.h>
#include <math.h>

#include "green_house.h"

green_house * green_house_create(int run_time, double time_divitions, double energy_value, double growth_value, double volume_air_tank, double pump_setting, double mist_setting, double plant_moisture_optimal, double pump_on_cost, double pipe_setting, double evaporation_rate, double max_moisture, double pump_threshold)
{
	green_house * gh = (green_house *)malloc(sizeof(green_house));
	gh->mass_air_tank = (double *)malloc(sizeof(double) * run_time);
	gh->plant_moisture = (double *)malloc(sizeof(double) * run_time);
	gh->mist_control = (double *)malloc(sizeof(double) * run_time);
	gh->pump_control = (double *)malloc(sizeof(double) * run_time);
	gh->pump_on_off = (double *)malloc(sizeof(double) * run_time);
	gh->fittness = (double *)malloc(sizeof(double) * run_time);
	gh->mist_setting = mist_setting;
	gh->pump_setting = pump_setting;
	gh->volume_air_tank = volume_air_tank;
	gh->energy_value = energy_value;
	gh->growth_value = growth_value;
	gh->run_time = run_time;
	gh->time_divitions = time_divitions;
	gh->total_fittness = -1;
	gh->plant_moisture_optimal = plant_moisture_optimal;
	gh->pump_on_cost = pump_on_cost;
	gh->pipe_setting = pipe_setting;
	gh->evaporation_rate = evaporation_rate;
	gh->max_moisture = max_moisture;
	gh->pump_threshold = pump_threshold;
	
	return gh;
}

void green_house_calc_total_fittness(green_house * gh)
{
	int i = 0;
	gh->total_fittness = 0.0;
	for(i = 0; i < gh->run_time; i++)
	{
		gh->total_fittness = gh->total_fittness + gh->fittness[i];
	}
	gh->total_fittness = gh->total_fittness / (double) gh->run_time;
}

void green_house_run(green_house * gh, double pump_threshold, int pump_time, int mist_frequency, int mist_time)
{
	int i = 0;
	// zero it
	for (i=0; i <gh->run_time; i++)
	{
		gh->mass_air_tank[i] = 0.0;
		gh->plant_moisture[i] = 0.0;
		gh->pump_control[i] = 0.0;
		gh->mist_control[i] = 0.0;
		gh->fittness[i] = 0.0;
		gh->pump_on_off[i] = 0.0;	

	}

	// start run
	gh->mass_air_tank[0] = gh->pump_threshold;
	gh->plant_moisture[0] = gh->plant_moisture_optimal;
	gh->pump_control[0] = 0.0;
	gh->mist_control[0] = 0.0;
	gh->fittness[0] = 0.0;
	gh->pump_on_off[0] = 0.0;	
	int store = 0;
	int store_mist = 0;
	int store_pump = 0;

	// initilize mist control
	for (i = 1; i < gh->run_time; i++)
	{
		store = i % mist_frequency;
		if(store == 0)
		{
			store_mist = mist_time;
		}
		if(store_mist > 0)
		{
			gh->mist_control[i] = 1.0;
		}
		store_mist--;
	}

	// main loop for simulating greenhouse behavior
	for (i = 1; i < gh->run_time; i++)
	{
		// update the mass of air in tank. -(loss from mister) + (pump intake)
		gh->mass_air_tank[i] = - gh->pipe_setting * gh->mist_control[i-1] * (gh->mass_air_tank[i-1] / gh->volume_air_tank) * gh->mist_control[i-1] + gh->pump_setting * gh->pump_control[i-1] + gh->mass_air_tank[i-1];
		// update plant moisture keeping below max moisture. -(evaporation) + (mister) 
		gh->plant_moisture[i] = gh->plant_moisture[i-1] + (gh->mist_control[i-1] * gh->mist_setting * (gh->mass_air_tank[i-1] / gh->volume_air_tank)) - (gh->evaporation_rate);
		if(gh->plant_moisture[i] > gh->max_moisture)
			{ gh->plant_moisture[i] = gh->max_moisture; }
		if(gh->plant_moisture[i] < 0.0)	
			{ gh->plant_moisture[i] = 0.0; }
		// update pump_control (trigger on and hold on)
		if(gh->mass_air_tank[i-1] < pump_threshold)
		{
			gh->pump_on_off[i] = 1.0;
			store_pump = pump_time;
		}
		if(store_pump > 0)
		{
			gh->pump_control[i] = 1.0;
		}
		store_pump--;
		// update fittness coef(plant moisture - optimal) + coef(pump + onoff cost)
		gh->fittness[i] = fabs(gh->growth_value * (gh->plant_moisture[i] - gh->plant_moisture_optimal)) + gh->energy_value * fabs((gh->pump_control[i] + gh->pump_on_off[i] * gh->pump_on_cost));
	}
	// calc total fittness
	green_house_calc_total_fittness(gh);
}


void print_double_array(char filename[], double * data, int size)
{
	int i = 0;
	FILE * fp;
	fp = fopen(filename, "w");
	for(i = 0; i < size; i++)
	{
		fprintf(fp, "%lf \n", data[i]);
	}
}






