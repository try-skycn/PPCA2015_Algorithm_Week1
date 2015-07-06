//
//  random.cpp
//  PPCA-Week1
//
//  Created by 陈天垚 on 7/6/15.
//  Copyright (c) 2015 陈天垚. All rights reserved.
//

#include "random.h"
#include <cstdlib>
#include <ctime>

bool have_inited = false;

int rand_between(int lower, int upper){
	if (!have_inited){
		srand((unsigned int)time(0));
		have_inited = true;
	}
	return lower + rand() % (upper - lower);
}
