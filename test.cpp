#include "test.hpp"
void input_arrivals(int &value)
{
	cout << "please enter the number of arrivals:" ;
	cin >> value;
}
void input_departures(int &value)
{
	cout << "please enter the number of departures:" ;
	cin >> value;
}
void test1(bool flag)
{
	int end_time;
	int queue_limit;
	int flight_number = 0;
	double arrival_rate,departure_rate;
	initializeTest1(end_time,queue_limit,arrival_rate,departure_rate,flag);
	Random variable;
	Runway small_airport(queue_limit);
	for(int current_time = 0;current_time < end_time; current_time++)
	{
		int number_arrivals = variable.poisson(arrival_rate);
		if(flag) input_arrivals(number_arrivals);
		
		for(int i=0;i < number_arrivals;i++)
		{
			Plane current_plane(flight_number++,current_time,ARRIVING);
			if(small_airport.can_land(current_plane) != SUCCESS)
				current_plane.refuse();
		}
		int number_departures = variable.poisson(departure_rate);
		if(flag) input_departures(number_departures);
		for(int j=0;j < number_departures;j++)
		{
			Plane current_plane(flight_number++,current_time,DEPARTING);
			if(small_airport.can_depart(current_plane) != SUCCESS)
				current_plane.refuse();
		}
		Plane moving_plane;
		switch (small_airport.activity(current_time,moving_plane))
		{
			case LAND:
				moving_plane.land(current_time);
				break;
			case TAKEOFF:
				moving_plane.fly(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;
				
		}
	}
	small_airport.shut_down(end_time);
}

void test2(bool flag)
{
	int end_time;
	int queue_limit_one;
	int queue_limit_two;
	int flight_number = 0;
	double arrival_rate,departure_rate;
	initializeTest2(end_time,queue_limit_one,queue_limit_two, arrival_rate, departure_rate,flag);
	Random variable;
	Runway runwayOne(queue_limit_one);
	Runway runwayTwo(queue_limit_two);
	for(int current_time = 0;current_time < end_time; current_time++)
	{		
		int number_arrivals = variable.poisson(arrival_rate);
		if(flag) input_arrivals(number_arrivals);
		for(int i=0;i < number_arrivals;i++)
		{
			Plane current_plane(flight_number++,current_time,ARRIVING);
			if(runwayOne.can_land(current_plane) != SUCCESS)
				current_plane.refuse();
		}
		int number_departures = variable.poisson(departure_rate);
		if(flag) input_departures(number_departures);
		for(int j=0;j < number_departures;j++)
		{
			Plane current_plane(flight_number++,current_time,DEPARTING);
			if(runwayTwo.can_depart(current_plane) != SUCCESS)
				current_plane.refuse();
		}
		Plane moving_plane;
		cout << "  Runway 1:" << endl;
		switch (runwayOne.activity(current_time,moving_plane))
		{
			case LAND:
				moving_plane.land(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;	
		}
		cout << "  Runway 2:" << endl;
		switch (runwayTwo.activity(current_time,moving_plane))
		{
			case TAKEOFF:
				moving_plane.fly(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;	
		}
	}
	cout << "\nRunway 1:" << endl;
	runwayOne.shut_down(end_time);

	cout << "\nRunway 2:" << endl;
	runwayTwo.shut_down(end_time);	
}

void initializeTest2(int &end_time,int &queue_limit_one, int &queue_limit_two,
					double &arrival_rate,double &departure_rate,bool flag)
{
	cout << "\nThis program simulates an airport with two runway." << endl
		 << "The first runway is reserved for landing, " << endl
		 << "the second runway is reserved for takeoff." << endl;
	cout << "Up to what number of planes can be waiting to land "
	 	 << "on the first runway at any time? " << flush;
	cin  >> queue_limit_one;
	cout << "Up to what number of planes can be waiting to take off "
	 	 << "on the second runway at any time? " << flush;
	cin  >> queue_limit_two;	
	cout << "How many units of time will the simulation run? " << flush;
	cin  >> end_time;
	if(flag) return;
	bool acceptable;
	do {
		cout << "Expected number of arrivals per unit time? " << flush;
		cin  >> arrival_rate;
		cout << "Expected number of departures per unit time? " << flush;
		cin  >> departure_rate;
		if(arrival_rate < 0.0 || departure_rate < 0.0)
			cerr << "These rates must be nonnegative." << endl;
		else
			acceptable = true;
		if(acceptable && arrival_rate + departure_rate > 1.0)
			cerr << "Safety Warning: This airport will become saturated." << endl;			
	}while(!acceptable);
}
void test3(bool flag)
{
	int end_time;
	int queue_limit_one;
	int queue_limit_two;
	int flight_number = 0;
	double arrival_rate,departure_rate;
	initializeTest3(end_time,queue_limit_one,queue_limit_two, arrival_rate, departure_rate,flag);
	Random variable;
	Runway runwayOne(queue_limit_one);
	Runway runwayTwo(queue_limit_two);
	for(int current_time = 0;current_time < end_time; current_time++)
	{		
		int number_arrivals = variable.poisson(arrival_rate);
		if(flag) input_arrivals(number_arrivals);
		for(int i=0;i < number_arrivals;i++)
		{
			Plane current_plane(flight_number++,current_time,ARRIVING);
			if(runwayOne.can_land(current_plane) != SUCCESS)
			{
				if(runwayTwo.can_land(current_plane) != SUCCESS)
					current_plane.refuse();
			}
				
		}
		int number_departures = variable.poisson(departure_rate);
		if(flag) input_departures(number_departures);
		for(int j=0;j < number_departures;j++)
		{
			Plane current_plane(flight_number++,current_time,DEPARTING);
			if(runwayTwo.can_depart(current_plane) != SUCCESS)
			{
				if(runwayOne.isLandingEmpty())
				{
					runwayOne.can_depart(current_plane);
				}
				else current_plane.refuse();
			}
				
		}
		Plane moving_plane;
		cout << "  Runway 1:" << endl;
		switch (runwayOne.activity(current_time,moving_plane))
		{
			case LAND:
				moving_plane.land(current_time);
				break;
			case TAKEOFF:
				moving_plane.fly(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;	
		}
		cout << "  Runway 2:" << endl;
		switch (runwayTwo.activity(current_time,moving_plane))
		{
			case LAND:
				moving_plane.land(current_time);
				break;
			case TAKEOFF:
				moving_plane.fly(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;	
		}
	}
	cout << "\nRunway 1:" << endl;
	runwayOne.shut_down(end_time);

	cout << "\nRunway 2:" << endl;
	runwayTwo.shut_down(end_time);
}

void initializeTest3(int &end_time,int &queue_limit_one, int &queue_limit_two,
					double &arrival_rate,double &departure_rate,bool flag)
{
	cout << "\nThis program simulates an airport with two runway." << endl
		 << "The first runway is reserved for landing, " << endl
		 << "the second runway is reserved for takeoff." << endl;
	cout << "If one of the queues is empty, then both runways can be used for the other queue." << endl
		 << "If landing queue is full, other landing plane will use takeoff queue." << endl;
	cout << "Up to what number of planes can be waiting to land "
	 	 << "on the first runway at any time? " << flush;
	cin  >> queue_limit_one;
	cout << "Up to what number of planes can be waiting to take off "
	 	 << "on the second runway at any time? " << flush;
	cin  >> queue_limit_two;	
	cout << "How many units of time will the simulation run? " << flush;
	cin  >> end_time;
	if(flag) return;
	bool acceptable;
	do {
		cout << "Expected number of arrivals per unit time? " << flush;
		cin  >> arrival_rate;
		cout << "Expected number of departures per unit time? " << flush;
		cin  >> departure_rate;
		if(arrival_rate < 0.0 || departure_rate < 0.0)
			cerr << "These rates must be nonnegative." << endl;
		else
			acceptable = true;
		if(acceptable && arrival_rate + departure_rate > 1.0)
			cerr << "Safety Warning: This airport will become saturated." << endl;			
	}while(!acceptable);
}					

void test4(bool flag)
{	
	int end_time;
	int flight_number = 0;
	int queue_limit_one;
	int queue_limit_two;
	int queue_limit_three;
	double arrival_rate,departure_rate;
	initializeTest4(end_time, queue_limit_one, queue_limit_two, queue_limit_three, arrival_rate, departure_rate,flag);
	Random variable;
	Runway runwayOne(queue_limit_one);
	Runway runwayTwo(queue_limit_two);
	Runway runwayThree(queue_limit_three);

	for(int current_time = 0;current_time < end_time; current_time++)
	{
		int number_arrivals = variable.poisson(arrival_rate);
		if(flag) input_arrivals(number_arrivals);
		for(int i=0;i < number_arrivals;i++)
		{
			Plane current_plane(flight_number++,current_time,ARRIVING);
			if(runwayOne.can_land(current_plane) != SUCCESS && runwayThree.can_land(current_plane) != SUCCESS)
				current_plane.refuse();
		}

		int number_departures = variable.poisson(departure_rate);
		if(flag) input_departures(number_departures);
		for(int j=0;j < number_departures;j++)
		{
			Plane current_plane(flight_number++,current_time,DEPARTING);
			if( runwayTwo.can_depart(current_plane) != SUCCESS && 
			    !(runwayThree.isLandingEmpty() && runwayThree.can_depart(current_plane) == SUCCESS))
				current_plane.refuse();
		}
		Plane moving_plane;
		cout << "  Runway 1:" << endl;
		switch (runwayOne.activity(current_time,moving_plane))
		{
			case LAND:
				moving_plane.land(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;	
		}
		cout << "  Runway 2:" << endl;
		switch (runwayTwo.activity(current_time,moving_plane))
		{
			case TAKEOFF:
				moving_plane.fly(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;	
		}
		cout << "  Runway 3:" << endl;
		switch (runwayThree.activity(current_time,moving_plane))
		{
			case LAND:
				moving_plane.land(current_time);
				break;
			case TAKEOFF:
				moving_plane.fly(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;
		}
	}

	cout << "\nRunway 1:" << endl;
	runwayOne.shut_down(end_time);

	cout << "\nRunway 2:" << endl;
	runwayTwo.shut_down(end_time);

	cout << "\nRunway 3:" << endl;
	runwayThree.shut_down(end_time);
}

void initializeTest4(int &end_time,int &queue_limit_one, int &queue_limit_two, int &queue_limit_three,
					double &arrival_rate,double &departure_rate,bool flag)
{
	cout << "\nThis program simulates an airport with three runways." << endl
		 << "The first runway is reserved for landing, the second runway is " << endl
		 << "reserved for takeoff, and the third is used for landing unless the landing " << endl
		 << "queue is empty, in which case it can be used for takeoffs." << endl;
	cout << "Up to what number of planes can be waiting to land "
	 	 << "on the first runway at any time? " << flush;
	cin  >> queue_limit_one;
	cout << "Up to what number of planes can be waiting to take off "
	 	 << "on the second runway at any time? " << flush;
	cin  >> queue_limit_two;
	cout << "Up to what number of planes can be waiting to land or "
	 	 << "take off on the third runway at any time? " << flush;
	cin  >> queue_limit_three;

	cout << "How many units of time will the simulation run? " << flush;
	cin  >> end_time;
	if(flag) return;
	bool acceptable;
	do {
		cout << "Expected number of arrivals per unit time? " << flush;
		cin  >> arrival_rate;
		cout << "Expected number of departures per unit time? " << flush;
		cin  >> departure_rate;
		if(arrival_rate < 0.0 || departure_rate < 0.0)
			cerr << "These rates must be nonnegative." << endl;
		else
			acceptable = true;
		//if(acceptable && arrival_rate + departure_rate > 1.0)
		//	cerr << "Safety Warning: This airport will become saturated." << endl;			
	}while(!acceptable);
}

void test5(bool flag)
{
	int end_time;
	int queue_limit;
	int flight_number = 0;
	double arrival_rate,departure_rate;
	initializeTest5(end_time,queue_limit,arrival_rate,departure_rate,flag);
	Random variable;
	Runway small_airport(queue_limit);
	for(int current_time = 0;current_time < end_time; current_time++)
	{
		int number_arrivals = variable.poisson(arrival_rate);
		if(flag) input_arrivals(number_arrivals);
		for(int i=0;i < number_arrivals;i++)
		{
			Plane current_plane(flight_number++,current_time,ARRIVING);
			if(small_airport.can_land(current_plane) != SUCCESS)
				current_plane.refuse();
		}

		Plane temp = small_airport.jump_queue();
		if (temp.getFuel() == 1)
			cout << "     Plane number " << temp.getFlyNum() << " with 1 unit fuel jump to the front of landing queue." << endl;

			
		int number_departures = variable.poisson(departure_rate);
		if(flag) input_departures(number_departures);
		for(int j=0;j < number_departures;j++)
		{
			Plane current_plane(flight_number++,current_time,DEPARTING);
			if(small_airport.can_depart(current_plane) != SUCCESS)
				current_plane.refuse();
		}
		
		Plane moving_plane;
		switch (small_airport.activity(current_time,moving_plane))
		{
			case LAND:
				moving_plane.land(current_time);
				break;
			case TAKEOFF:
				moving_plane.fly(current_time);
				break;
			case IDLE:
				run_idle(current_time);
				break;
				
		}

		int crash;
		if ( (crash = small_airport.decrease_fuel()) != -1)
		{
			cout << "\n\n     Plane number " << crash << " with 0 unit fuel will crash!!!\n" << endl;
			end_time = current_time;
			break;
		}
	}
	small_airport.shut_down(end_time);
}

void initializeTest5(int &end_time,int &queue_limit,
				     double &arrival_rate,double &departure_rate,bool flag)
{
	cout << "\nThis program simulates an airport with only one runway." << endl
		 << "When each plane arrives tp land, it will have a fuel level" << endl
		 << ",measured in units of time remaining. If the plane does not " << endl
		 << "have enough fuel to wait in the queue, it is allowed to land" << endl
		 << "immediately." << endl;
	cout << "Up to what number of planes can be waiting to land "
	 	 << "or take off at any time? " << flush;
	cin  >> queue_limit;
	cout << "How many units of time will the simulation run? " << flush;
	cin  >> end_time;
	if(flag) return;
	bool acceptable;
	do {
		cout << "Expected number of arrivals per unit time? " << flush;
		cin  >> arrival_rate;
		cout << "Expected number of departures per unit time? " << flush;
		cin  >> departure_rate;
		if(arrival_rate < 0.0 || departure_rate < 0.0)
			cerr << "These rates must be nonnegative." << endl;
		else
			acceptable = true;
		//if(acceptable && arrival_rate + departure_rate > 1.0)
		//	cerr << "Safety Warning: This airport will become saturated." << endl;			
	}while(!acceptable);
}


