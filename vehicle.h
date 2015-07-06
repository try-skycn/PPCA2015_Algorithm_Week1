//
//  vehicle.h
//  PPCA-Week1
//
//  Created by 陈天垚 on 7/6/15.
//  Copyright (c) 2015 陈天垚. All rights reserved.
//

#ifndef __PPCA_Week1__vehicle__
#define __PPCA_Week1__vehicle__

#include "constant.h"

class vehicle{
public:
	enum vehicle_type{
		CAR		=	0,
		BUS		=	1,
		TRUCK	=	2
	};
	
private:
	vehicle_type type;
	int position;
	int speed;
	int lane;
	
public:
	vehicle(vehicle_type, int, int, int _lane = total_lane - 1);
	
	vehicle_type get_type() const;
	int speed_limit() const;
	int get_speed() const;
	int get_position() const;
	
	void move_ahead();
	void accelerate(int delta_v = 1);
	void decelerate(int delta_mv = 1);
	void limit_speed(int);
	void set_speed(int);
	
public:
	static vehicle_type rand_type();
	friend class vehicle_pointer;
	
	bool is_leftmost() const;
	bool is_rightmost() const;
	void move_left();
	void move_right();
};

class vehicle_pointer{
private:
	vehicle *p_vehicle;
public:
	vehicle_pointer() = delete;
	vehicle_pointer(vehicle *);
	bool operator<(const vehicle_pointer &) const;
	vehicle *operator->();
};

#endif /* defined(__PPCA_Week1__vehicle__) */
