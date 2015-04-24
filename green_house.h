


#ifndef _lsms_H_
#define _lsms_H_


typedef struct {
	double * mass_air_tank;
	double * plant_moisture;
	double * pump_control;
	double * mist_control;
	double * fittness;
	double * pump_on_off;
	double pump_on_cost;
	double pump_threshold;
	double plant_moisture_optimal;
	double mist_setting;
	double pipe_setting; // coeficiant of mass loss from mister
	double pump_setting;
	double volume_air_tank;
	double evaporation_rate;
	double max_moisture; // the max moisture the plant can have
	double energy_value; // how much the energy should effect the fittness
	double growth_value; // how much the deviation from optimal plant moisture will effect fittness
	double total_fittness; // total fittness store
	double time_divitions; // probably 1 sec each
	int run_time;
} green_house;

green_house * green_house_create(int run_time, double time_divitions, double energy_value, double growth_value, double volume_air_tank, double pump_setting, double mist_setting, double plant_moisture_optimal, double pump_on_cost, double pipe_setting, double evaporation_rate, double max_moisture, double pump_threshold);
void green_house_calc_total_fittness(green_house * gh);
void print_double_array(char filename[], double * data, int size);
void green_house_run(green_house * gh, double pump_threshold, int pump_time, int mist_frequency, int mist_time);

#endif	







