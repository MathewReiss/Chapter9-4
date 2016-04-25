#include <pebble.h>
#include "main.h"

TextLayer *textlayer1, *textlayer2, *textlayer3;

void update_compass(){
	text_layer_set_text(textlayer1, get_compass());
}

void update_accel(){
	text_layer_set_text(textlayer2, get_accelerometer());
}

void update_light(){
	text_layer_set_text(textlayer3, get_light());
}

void init(){
	window = window_create();
	
	Layer *root = window_get_root_layer(window);
	
	GRect bounds = layer_get_bounds(root);
	
	textlayer1 = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h/3));
	text_layer_set_text_alignment(textlayer1, GTextAlignmentCenter);
	
	textlayer2 = text_layer_create(GRect(0, bounds.size.h/3, bounds.size.w, bounds.size.h/3));
	text_layer_set_text_alignment(textlayer2, GTextAlignmentCenter);
	
	textlayer3 = text_layer_create(GRect(0, 2*bounds.size.h/3, bounds.size.w, bounds.size.h/3));
	text_layer_set_text_alignment(textlayer3, GTextAlignmentCenter);
	
	layer_add_child(root, text_layer_get_layer(textlayer1));
	layer_add_child(root, text_layer_get_layer(textlayer2));
	layer_add_child(root, text_layer_get_layer(textlayer3));
	
	window_stack_push(window, true);
	
	init_helper_functions();
}

void deinit(){
	text_layer_destroy(textlayer1);
	text_layer_destroy(textlayer2);
	text_layer_destroy(textlayer3);
	window_destroy(window);
	
	deinit_helper_functions();
}

int main(void){
	init();
	app_event_loop();
	deinit();
}