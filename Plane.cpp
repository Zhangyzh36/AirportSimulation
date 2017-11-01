#include "Plane.hpp"

Plane::Plane(int flt,int time_,Plane_status status)
{
	srand(time(NULL));
	flt_num = flt;
	clock_start = time_;
	fuel = rand() % MAX_FUEL + 1;
	state = status;
	cout << "     Plane number " << flt << " ready to ";
	if(status == ARRIVING) cout << "land." << endl;
	else cout << "take off." << endl;
	
}

Plane::Plane()
{
	flt_num = -1;
	clock_start = -1;
	fuel = 0;
	state = NUL;
}

void Plane::refuse() const
{
	cout << "     Plane number " << flt_num;
	if(state == ARRIVING) cout << " directed to another airport" << endl;
	else cout << " told to try to takeoff again later" << endl;
}

void Plane::land(int time) const
{
	int wait = time - clock_start;
	cout << setw(4) << time << ":Plane number " << flt_num << " landed after "
		 << wait << " time unit" << ((wait == 1)?"":"s")
		 << " in the takeoff queue." << endl;
}
void Plane::fly(int time) const
{
	int wait = time - clock_start;
	cout << setw(4)<< time << ":Plane number " << flt_num << " took off after "
		 << wait << " time unit" << ((wait == 1)?"":"s")
		 << " in the takeoff queue." << endl;
}
int Plane::started() const
{
	return clock_start;
}

int Plane::getFuel() const
{
	return fuel;
}

int Plane::getFlyNum() const
{
	return flt_num;
}

void Plane::setFuel(int value)
{
	fuel = value;
}
