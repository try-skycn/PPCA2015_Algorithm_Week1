//
//  main.cpp
//  PPCA-Week1
//
//  Created by 陈天垚 on 7/6/15.
//  Copyright (c) 2015 陈天垚. All rights reserved.
//

#include <cstdio>
#include <queue>
#include <memory>
#include <string>
#include <map>
#include <cstdlib>
#include <unistd.h>
#include "constant.h"
#include "random.h"
using namespace std;

template<int _mod>
struct modint{
	int x;
	modint(int _x) : x(_x){
		while(x < 0) x += _mod;
		while(x >= _mod) x -= _mod;
	}
	operator int(){
		return x;
	}
	void operator++(int){
		++x;
		if(x >= _mod) x -= _mod;
	}
	void operator--(int){
		--x;
		if(x < 0) x += _mod;
	}
	void operator+=(int del){
		x += del;
		while(x >= _mod) x -= _mod;
		while(x < 0) x += _mod;
	}
	modint<_mod> operator+(int del){
		return modint<_mod>(x + del);
	}
	modint<_mod> operator-(int del){
		return modint<_mod>(x - del);
	}
	bool operator==(const modint& r) const{
		return x == r.x;
	}
	bool operator!=(const modint& r) const{
		return x != r.x;
	}
};

typedef modint<total_cells> mint;
typedef pair<int, mint> POS;

enum vehicle_type{
	none = 0,
	car = 1,
	bus = 2,
	truck = 3
};

vehicle_type rand_type(){
	int p1 = portion_of_car;
	int p2 = portion_of_bus + p1;
	int ret = rand_under(total_probability);
	if(ret < p1) return car;
	else if(ret < p2) return bus;
	else return truck;
}

char switchToChar(vehicle_type type){
	switch(type){
		case car:
			return 'C';
		case bus:
			return 'B';
		case truck:
			return 'T';
		default:
			return ' ';
	}
}

struct vehicle{
	
	vehicle_type type;
	int speed;
	
	vehicle(vehicle_type _type = none, int _speed = 0) : type(_type), speed(_speed){
	}
	void make_empty(){
		type = none;
		speed = 0;
	}
	int speed_limit(){
		switch(type){
			case car:
				return speed_of_car;
			case bus:
				return speed_of_bus;
			case truck:
				return speed_of_truck;
			default:
				return 0;
		}
	}
	int expect_speed(){
		return speed_limit();
	}
};

typedef pair<vehicle, POS> STATE;

struct freeway{
	vehicle cells[total_lanes][total_cells];
	void clear(){
		for(int i = 0; i < total_lanes; ++i)
			for(int j = 0; j < total_cells; ++j)
				cells[i][j].make_empty();
	}
	vehicle &getCell(POS pos){
		return cells[pos.first][pos.second.x];
	}
	bool occupied(int _lane, mint pos){
		return cells[_lane][pos.x].type != none;
	}
	int frontGap(POS pos){
		for(int i = 1; i <= max_speed; ++i){
			if(occupied(pos.first, pos.second + i)){
				return i - 1;
			}
		}
		return out_of_sight;
	}
	int backGap(POS pos, int &bv){
		for(int i = 0; i <= max_speed; ++i){
			if(occupied(pos.first, pos.second - i)){
				bv = cells[pos.first][pos.second - i].speed;
				return i - 1;
			}
		}
		bv = 0;
		return out_of_sight;
	}
	STATE move_forward(POS opos){
		vehicle v = getCell(opos);
		if(v.speed < v.expect_speed())
			v.speed++;
		if(v.speed > 0 && rand_bool(p_slow))
			v.speed--;
		int front_gap = frontGap(opos);
		if(v.speed >= front_gap)
			v.speed = front_gap;
		POS npos(opos.first, opos.second + v.speed);
		return STATE(v, npos);
	}
	bool canMoveLeft(STATE ostate){
		vehicle &v = ostate.first;
		POS &pos = ostate.second;
		if(pos.first == 0) return false;
		
		int front_gap = frontGap(pos);
		if(v.expect_speed() <= front_gap) return false;
		
		int lf_gap = frontGap(POS(pos.first - 1, pos.second));
		if(front_gap == out_of_sight || front_gap >= lf_gap) return false;
		
		int lb_gap = out_of_sight, lbv = 0;
		lb_gap = backGap(POS(pos.first - 1, pos.second), lbv);
		if(lb_gap <= lbv) return false;
		
		return true;
	}
	bool canMoveRight(STATE ostate){
		vehicle &v = ostate.first;
		POS &pos = ostate.second;
		if(pos.first == total_lanes - 1) return false;
		
		int rf_gap = frontGap(POS(pos.first + 1, pos.second));
		if(rf_gap <= v.speed) return false;
		
		int rb_gap = out_of_sight, rbv = 0;
		rb_gap = backGap(POS(pos.first + 1, pos.second), rbv);
		if(rb_gap <= rbv) return false;
		
		return true;
	}
	STATE process(POS opos){
		STATE ostate(getCell(opos), opos);
		STATE nstate = move_forward(opos);
		if(canMoveLeft(ostate) && rand_bool(p_left)){
			nstate.second.first--;
		}else if(canMoveRight(ostate) && rand_bool(p_right)){
			nstate.second.first++;
		}
		return nstate;
	}
	
	void process(queue<STATE> &Q){
		for(int i = 0; i < total_lanes; ++i){
			for(int j = 0; j < total_cells; ++j){
				if(occupied(i, j)){
					STATE ret = process(POS(i, j));
					if(ret.second.second < total_cells)
						Q.push(ret);
				}
			}
		}
	}
	
	void reset(queue<STATE> &Q){
		clear();
		while(!Q.empty()){
			STATE s = Q.front();
			Q.pop();
			cells[s.second.first][s.second.second] = s.first;
		}
	}
	
	void init(){
		queue<STATE> Q;
		for(int i = init_st_lane; i < init_ed_lane; ++i){
			for(int j = init_st_cell; j < init_ed_cell; ++j){
				bool ret = rand_bool(occupation);
				if(ret){
					STATE input = STATE(vehicle(rand_type()), POS(i, j));
					Q.push(input);
				}
			}
		}
		reset(Q);
	}
	
	void print(mint l, mint r){
		for(int i = 0; i < total_lanes; ++i){
			if(l == r){
				printf("%c", switchToChar(cells[i][l].type));
				l++;
			}
			for(mint j = l; j != r; j++){
				printf("%c", switchToChar(cells[i][j].type));
			}
			printf("\n");
		}
		for(mint j = l; j != mint(r); j++)
			printf("-");
		printf("\n");
	}
	
	void print(){
		static mint stpos(0);
		int rows = total_cells / width_of_screen;
		for(int r = 0; r < rows; ++r){
			print(stpos + r * width_of_screen, stpos + (r + 1) * width_of_screen);
		}
		if(total_cells % width_of_screen){
			print(stpos + rows * width_of_screen, stpos + total_cells);
		}
		stpos += float_speed;
	}
};

freeway F[2];

int main(int argc, const char * argv[]) {
	F[0].init();
	F[0].print();
	printf("LINK START!\n\n");
	char tmp; scanf("%c", &tmp);
	queue<STATE> Q;
	for(int t = 1; t <= total_time; t^=1){
		F[~t&1].process(Q);
		F[t&1].reset(Q);
		if(1){
			system("clear");
			F[t&1].print();
			usleep(sleep_time * 1000);
		}
	}
	return 0;
}
