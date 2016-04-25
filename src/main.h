#pragma once
#include "pebble.h"

char compass_buffer[32];
char accel_buffer[32];
char light_buffer[32];

Window *window;

char *get_compass(){
	return compass_buffer;
}

char *get_accelerometer(){
	return accel_buffer;
}

char *get_light(){
	return light_buffer;
}

void update_compass();
void update_accel();
void update_light();

void compass(CompassHeadingData data){
	snprintf(compass_buffer, sizeof(compass_buffer), "Heading: %d˚", (int)data.true_heading);
	update_compass();
}

void accel(AccelData *data, uint32_t num_samples){
	snprintf(accel_buffer, sizeof(accel_buffer), "X: %d, Y: %d, Z: %d", data[0].x, data[0].y, data[0].z);
	update_accel();
}

void light(){
	static HealthMinuteData *data;
	health_service_get_minute_history(data, 1, (time_t*)(time(NULL)-5*60*1000), (time_t*)(time(NULL)));
	AmbientLightLevel level = data[0].light;
	switch(level){
		case AmbientLightLevelDark: snprintf(light_buffer, sizeof(light_buffer), "Light: Dark");
		case AmbientLightLevelLight: snprintf(light_buffer, sizeof(light_buffer), "Light: Light");
		case AmbientLightLevelUnknown: snprintf(light_buffer, sizeof(light_buffer), "Light: Unknown");
		case AmbientLightLevelVeryDark: snprintf(light_buffer, sizeof(light_buffer), "Light: Very Dark");
		case AmbientLightLevelVeryLight: snprintf(light_buffer, sizeof(light_buffer), "Light: Very Light");
	}
	update_light();
}

void init_helper_functions(){
	compass_service_subscribe(compass);
	accel_data_service_subscribe(1, accel);
	light();
}

void deinit_helper_functions(){
	compass_service_unsubscribe();
	accel_data_service_unsubscribe();
}