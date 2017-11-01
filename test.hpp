#ifndef TEST_HPP
#define TEST_HPP

#include "utility.hpp"
#include "Runway.hpp"
#include "Plane.hpp"
#include "Random.hpp"
void initializeTest2(int &end_time,int &queue_limit_one, int &queue_limit_two,
					double &arrival_rate,double &departure_rate,bool flag);
void initializeTest3(int &end_time,int &queue_limit_one, int &queue_limit_two,
					double &arrival_rate,double &departure_rate,bool flag);					
void initializeTest4(int &end_time,int &queue_limit_one, int &queue_limit_two, int &queue_limit_three,
				     double &arrival_rate,double &departure_rate,bool flag);
void initializeTest5(int &end_time,int &queue_limit,
				     double &arrival_rate,double &departure_rate,bool flag);


void test1(bool flag);
void test2(bool flag);
void test3(bool flag);
void test4(bool flag);
void test5(bool flag);

#endif
