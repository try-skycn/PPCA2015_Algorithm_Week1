//
//  constant.h
//  PPCA-Week1
//
//  Created by 陈天垚 on 7/6/15.
//  Copyright (c) 2015 陈天垚. All rights reserved.
//

#ifndef __PPCA_Week1__constant__
#define __PPCA_Week1__constant__

#include <algorithm>

const int total_probability = 100;

const int portion_of_car = 0;
const int portion_of_bus = 0;
const int portion_of_truck = total_probability - portion_of_bus - portion_of_car;

const int speed_of_car = 9;
const int speed_of_bus = 5;
const int speed_of_truck = 1;

//const int float_speed = 1;

const int p_slow = 0;
const int p_left = 0;
const int p_right = 100;

const int total_lanes = 36;
const int total_cells = 181;

const int init_st_lane = 0;
const int init_ed_lane = total_lanes;
const int init_st_cell = 0;
const int init_ed_cell = total_cells;

const int max_speed = std::max(speed_of_car, std::max(speed_of_bus, speed_of_truck));
const int out_of_sight = max_speed + 3;

const int occupation = 10;

const int total_time = 300;
const int display_time = 100;

const int width_of_screen = 181;
const int sleep_time = 100;

#endif /* defined(__PPCA_Week1__constant__) */
