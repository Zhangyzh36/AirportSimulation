#ifndef RUNWAY_HPP
#define RUNWAY_HPP

#include <queue>
#include "Plane.hpp"
#include "utility.hpp"
#include "Queue.hpp"
using namespace std;

enum Runway_activity {
	IDLE, LAND, TAKEOFF
};

class Runway {
public:
	Runway(int limit);
	Error_code can_land(const Plane &current);
	Error_code can_depart(const Plane &current);
	Runway_activity activity(int time, Plane &moving);
	int decrease_fuel();
	Plane jump_queue();
	bool isLandingEmpty();
	bool isTakeoffEmpty();
	void shut_down(int time) const;
private:
	Queue landing;
	Queue takeoff;
	int queue_limit;
	int num_land_requests;
	int num_takeoff_requests;
	int num_landings;
	int num_takeoffs;
	int num_land_accepted;
	int num_takeoff_accepted;
	int num_land_refused;
	int num_takeoff_refused;
	int land_wait;
	int takeoff_wait;
	int idle_time;
};


#endif 
