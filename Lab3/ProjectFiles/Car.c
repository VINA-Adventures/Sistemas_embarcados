#include "Car.h"

Car *new_car(uint32_t runway_x_position, uint32_t runway_y_position, uint32_t runway_distance, uint32_t speed, uint32_t color, enum Car_size size) {

	Car* new_car = (Car*)malloc(sizeof(Car));
	new_car->runway_x_position = runway_x_position;
	new_car->runway_y_position = runway_y_position;
	new_car->runway_distance = runway_distance;
	new_car->speed = speed;
	new_car->color = color;
	new_car->accelerating = false;
	new_car->direction = STRAIGHT;
	new_car->max_speed = MAX_CAR_SPEED;
	new_car->collision_correction_direction = COLLISION_FRONT;
	new_car->collision_correction_position = 0;
	new_car->collision_correction_speed = 0;
	new_car->collision_detected = false;
	new_car->inverted = false;
	new_car->inversion_counter = 0;
	
	switch(size) {
		case CAR_VERY_SMALL:
			new_car->image = new_image((const int*) CAR_VERY_SMALL_ARRAY, 2, 5);
		break;
		case CAR_SMALL:
			new_car->image = new_image((const int*) CAR_SMALL_ARRAY, 6, 10);
		break;
		case CAR_MEDIUM:
			new_car->image = new_image((const int*) CAR_MEDIUM_ARRAY, 8, 15);
		break;
		default:
			new_car->image = new_image((const int*) CAR_BIG_ARRAY, 10, 20);
		break;
	}

	return new_car;
}

void delete_car(Car* car) {
	free(car);
	return;
}

const int CAR_VERY_SMALL_ARRAY[] = {
	0x6d,0xb6,0xff,0xb6,0x6d
	,0x6d,0xdb,0xff,0xdb,0x92
};

const int CAR_SMALL_ARRAY[] = {
	0x00,0xb6,0xdb,0x92,0xff,0xff,0x92,0xdb,0xb6,0x00
	,0x49,0x92,0xb6,0xb6,0xff,0xff,0xb6,0xdb,0xb6,0x00
	,0x6d,0x92,0xb6,0xdb,0xff,0xff,0xdb,0xb6,0x6d,0x92
	,0x6d,0x92,0xb6,0xff,0xff,0xff,0xff,0xb6,0x6d,0x92
	,0x6d,0x92,0xb6,0xff,0xff,0xff,0xff,0xb6,0x6d,0x92
	,0x6d,0x92,0x6d,0x92,0xff,0xff,0x92,0x6d,0x6d,0x92
};

const int CAR_MEDIUM_ARRAY[] = {
	0x00,0x00,0xff,0xdb,0x49,0x92,0xff,0xff,0xff,0x92,0x49,0xdb,0xff,0x00,0x00
	,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00
	,0xb6,0xb6,0x49,0x49,0x49,0x92,0xff,0xff,0xff,0x92,0x49,0xdb,0xff,0x24,0x00
	,0x6d,0x6d,0x92,0xb6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x6d,0x92,0x92
	,0x6d,0x6d,0x92,0xb6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x6d,0x92,0x92
	,0xb6,0xb6,0x49,0x6d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xb6,0xb6,0x49,0x49
	,0x92,0x92,0x6d,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xb6,0x92,0x6d,0x6d
	,0x49,0x49,0xb6,0x92,0x49,0x92,0xff,0xff,0xff,0x92,0x49,0x49,0x49,0xb6,0xb6
};

const int CAR_BIG_ARRAY[] = {
	0x00,0x00,0x6d,0xff,0xff,0x24,0x24,0x92,0xff,0xff,0xff,0xff,0x92,0x24,0x24,0xff,0xff,0x6d,0x00,0x00
	,0x00,0x00,0x6d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x6d,0x00,0x00
	,0x24,0x24,0x6d,0xdb,0xdb,0xdb,0xdb,0xdb,0xff,0xff,0xff,0xff,0xdb,0xdb,0xdb,0xff,0xff,0x6d,0x00,0x00
	,0x92,0x92,0x92,0x6d,0x6d,0x6d,0x6d,0xb6,0xff,0xff,0xff,0xff,0xb6,0x6d,0x6d,0x92,0x92,0x6d,0x6d,0x6d
	,0x92,0x92,0x6d,0x6d,0x6d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x92,0x6d,0x6d,0x6d
	,0x92,0x92,0x6d,0x6d,0x6d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x92,0x6d,0x6d,0x6d
	,0x92,0x92,0x92,0x6d,0x6d,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x92,0x6d,0x6d,0x6d
	,0x24,0x24,0x6d,0xdb,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x24,0x24,0x92,0xdb,0xdb
	,0xff,0xff,0x92,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x6d,0x00,0x00
	,0x24,0x24,0x6d,0xdb,0xdb,0x24,0x24,0x92,0xff,0xff,0xff,0xff,0x92,0x24,0x24,0x24,0x24,0x92,0xdb,0xdb

};