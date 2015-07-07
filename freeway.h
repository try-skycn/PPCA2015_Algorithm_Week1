//
//  freeway.h
//  PPCA-Week1
//
//  Created by 陈天垚 on 7/6/15.
//  Copyright (c) 2015 陈天垚. All rights reserved.
//

#ifndef __PPCA_Week1__freeway__
#define __PPCA_Week1__freeway__

#include <set>
#include <queue>
#include "vehicle.h"
#include "constant.h"

class vehicle_lane{
private:
	int lane_index;
	typedef std::set<vehicle_pointer> container;
	container vehicles;
	
public:
	vehicle_lane(int);
	void vehicle_enqueue(std::priority_queue<vehicle_pointer> &);
	void reposition(vehicle_pointer, vehicle_pointer);
	void remove(vehicle_pointer);
	void push(vehicle_pointer);
};

class freeway{
private:
	vehicle_lane lanes[total_lanes];
	
private:
	bool can_turn_left();
	bool can_turn_right();
	
public:
	freeway();
	
public:
	void push_new_vehicle();
	void process_time();
};

#endif /* defined(__PPCA_Week1__freeway__) */
