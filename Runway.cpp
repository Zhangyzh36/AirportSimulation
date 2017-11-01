#include "Runway.hpp"
#include <iomanip>
using namespace std;

Runway::Runway(int limit) : landing(limit), takeoff(limit)
{
	queue_limit = limit;
	num_land_requests = num_takeoff_requests = 0;
	num_landings = num_takeoffs = 0;
	num_land_accepted = num_takeoff_accepted = 0;
	num_land_refused = num_takeoff_refused = 0;
	land_wait = takeoff_wait = idle_time = 0;
}

Error_code Runway::can_land(const Plane &current)
{
	Error_code result;
	if (landing.size() < queue_limit)
		result = landing.inque(current);
	else
		result = FAIL;
	num_land_requests++;

	if (result != SUCCESS)
		num_land_refused++;
	else
		num_land_accepted++;

	return result;
}

Error_code Runway::can_depart(const Plane &current)
{
	Error_code result;
	if (takeoff.size() < queue_limit)
		result = takeoff.inque(current);
	else
		result = FAIL;
	num_takeoff_requests++;

	if (result != SUCCESS)
		num_takeoff_refused++;
	else
		num_takeoff_accepted++;

	return result;
}

bool Runway::isLandingEmpty()
{
	return landing.empty();
}

bool Runway::isTakeoffEmpty()
{
	return takeoff.empty();
}

Runway_activity Runway::activity(int time, Plane &moving)
{
	Runway_activity in_progress;
	
	if (!landing.empty()) {
		landing.retrieve(moving);
		land_wait += time - moving.started();
		num_landings++;
		in_progress = LAND;
		landing.deque();

	}
	else if (!takeoff.empty()) {
		takeoff.retrieve(moving);
		takeoff_wait += time - moving.started();
		num_takeoffs++;
		in_progress = TAKEOFF;
		takeoff.deque();
	}
	else {
		idle_time++;
		in_progress = IDLE;
	}

	return in_progress;
}


//if succeed, return -1;
//else return the crashed plane's fly_num
int Runway::decrease_fuel()
{
	for (int i = 0; i < landing.size(); ++i)
	{
		if (landing[i].getFuel() == 0)
			return landing[i].getFlyNum();
		else
			landing[i].setFuel(landing[i].getFuel() - 1);
	}

	return -1;
}

Plane Runway::jump_queue()
{	
	Plane temp;
	for (int i = 1; i < landing.size(); ++i)
	{
		if (landing[i].getFuel() == 1)
		{
			temp = landing[i];
			for (int j = i; j >= 1; --j)
				landing[i] = landing[i - 1];
			landing[0] = temp;
			break;
		}
	}

	return temp;
}

void Runway::shut_down(int time) const
{
	cout << "\n\tSimulatiuon has concluded after " << time << " time units." << endl;
	cout << left << setw(55) << "\tTotal number of planes processed" << (num_land_requests + num_takeoff_requests) << endl;
	cout << left << setw(55) << "\tTotal number of planes asking to land" << num_land_requests << endl;
	cout << left << setw(55) << "\tTotal number of planes asking to take off" << num_takeoff_requests << endl;
	cout << left << setw(55) << "\tTotal number of planes accepted for landing" << num_land_accepted << endl;
	cout << left << setw(55) << "\tTotal number of planes accepted for takeoff" << num_takeoff_accepted << endl;
	cout << left << setw(55) << "\tTotal number of planes refused for landing" << num_land_refused << endl;
	cout << left << setw(55) << "\tTotal number of planes refused for takeoff" << num_takeoff_refused << endl;
	cout << left << setw(55) << "\tTotal number of planes that landed" << num_landings << endl;
	cout << left << setw(55) << "\tTotal number of planes that took off" << num_takeoffs << endl;
	//                                                                              here!!!!!!!!!!!!!!
	cout << left << setw(55) << "\tTotal number of planes left in landing queue" << (num_land_accepted - num_landings) << endl;
	cout << left << setw(55) << "\tTotal number of planes left in takeoff queue" << (num_takeoff_accepted - num_takeoffs) << endl;
	//                                                                              here!!!!!!!!!!!!!!!!!
	cout << left << setw(55) << "\tPercentage of time runway idle" << fixed << setprecision(1) << ((double)idle_time * 100/time) << " %" << endl;
	cout << left << setw(55) << "\tAverage wait in landing queue" << fixed << setprecision(5) << ((double)land_wait/num_land_accepted) << " time units" << endl;
	cout << left << setw(55) << "\tAverage wait in takeoff queue" << fixed << setprecision(5) << ((double)takeoff_wait/num_takeoff_accepted) << " time units" << endl;
	cout << left << setw(55) << "\tAverage observed rate of planes wanting to land" << fixed << setprecision(3) << ((double)num_land_requests/time) << " time units" << endl;
	cout << left << setw(55) << "\tAverage observed rate of planes wanting to take off" << fixed << setprecision(3) << ((double)num_takeoff_requests/time) << " time units\n" << endl;

}
