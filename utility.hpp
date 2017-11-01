#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <iomanip>
using namespace std;

enum Error_code { SUCCESS, FAIL, OVERFLOW, UNDERFLOW };

void initializeTest1(int &end_time,int &queue_limit,
				double &arrival_rate,double &departure_rate,bool flag);

void run_idle(int time);

#endif
