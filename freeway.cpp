//
//  freeway.cpp
//  PPCA-Week1
//
//  Created by 陈天垚 on 7/6/15.
//  Copyright (c) 2015 陈天垚. All rights reserved.
//

#include "freeway.h"

vehicle_lane::vehicle_lane(int _lane_index) : lane_index(_lane_index){
}

void vehicle_lane::vehicle_enqueue(std::priority_queue<vehicle_pointer> &vehicle_queue){
	for(container::iterator it = vehicles.begin(); it != vehicles.end(); ++it){
		vehicle_queue.push(*it);
	}
}

void vehicle_lane::reposition(vehicle_pointer prev, vehicle_pointer nxt){
	vehicles.erase(prev);
	vehicles.insert(nxt);
}

void vehicle_lane::remove(vehicle_pointer out_vehicle){
	vehicles.erase(out_vehicle);
}

void vehicle_lane::push(vehicle_pointer en_vehicle){
	vehicles.insert(en_vehicle);
}



/*freeway::freeway(){
}*/
