//
//  main.cpp
//  PPCA-Week1
//
//  Created by 陈天垚 on 7/6/15.
//  Copyright (c) 2015 陈天垚. All rights reserved.
//

#include <iostream>
#include <set>
#include <map>
using namespace std;

typedef int _T;

int main(int argc, const char * argv[]) {
	set<int> S;
	for(int i = 0; i < 10; ++i){
		S.insert(i);
	}
	set<int>::iterator it = S.lower_bound(-5);
	printf("%s %d", it == S.begin() ? "Yes" : "No", *it);
	return 0;
}
