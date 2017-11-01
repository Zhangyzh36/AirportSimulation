#ifndef PLANE_HPP
#define PLANE_HPP 

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int MAX_FUEL = 10;

enum Plane_status {NUL,ARRIVING,DEPARTING};

class Plane
{
	public:
		Plane();
		Plane(int flt,int time_,Plane_status status);
		void refuse() const;
		void land(int time) const;
		void fly(int time) const;
		int started() const;
		int getFuel() const;
		int getFlyNum() const;
		void setFuel(int value);
	private:
		int flt_num;
		int clock_start;
		int fuel;
		Plane_status state;
}; 

#endif

