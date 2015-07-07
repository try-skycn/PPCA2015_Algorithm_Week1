//
//  vehicle.cpp
//  PPCA-Week1
//
//  Created by 陈天垚 on 7/6/15.
//  Copyright (c) 2015 陈天垚. All rights reserved.
//

#include "vehicle.h"
#include "random.h"

vehicle::vehicle(vehicle_type _type, int _position, int _speed, int _lane) :
type(_type),
position(_position),
speed(_speed),
lane(_lane)
{
}

vehicle::vehicle_type vehicle::get_type() const{
	return type;
}

int vehicle::speed_limit() const{
	switch(type){
		case CAR:
			return 6;
		case BUS:
			return 5;
		case TRUCK:
			return 3;
	}
}

int vehicle::get_speed() const{
	return speed;
}

int vehicle::get_position() const{
	return position;
}

void vehicle::move_ahead(){
	position += speed;
}

void vehicle::accelerate(int delta_v){
	speed += delta_v;
}

void vehicle::decelerate(int delta_mv){
	speed -= delta_mv;
}

void vehicle::limit_speed(int speed_limit){
	if(speed > speed_limit)
		speed = speed_limit;
}

void vehicle::set_speed(int _speed){
	speed = _speed;
}

vehicle::vehicle_type vehicle::rand_type(){
	int result = rand_between(0, 100);
	if(result < portion_of_car)
		return CAR;
	else if(result < portion_of_car + portion_of_bus)
		return BUS;
	else return TRUCK;
}

bool vehicle::is_leftmost() const{
	return lane == 0;
}

bool vehicle::is_rightmost() const{
	return lane == total_lanes - 1;
}

void vehicle::move_left(){
	--lane;
}

void vehicle::move_right(){
	++lane;
}
