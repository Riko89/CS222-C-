//Eric Davey
//Palomar ID # 007467548
// 4/24/2018
// CS 222  			Cinema Project Lab with operator overloading

#include <iostream>
#include "Cinema.h"
#include <string>
#include <list>
#include <map>

using namespace std;

void deletePointers(list<int> *time_available, list<int> *show_time)
{
	delete show_time;
	delete time_available;
}

int main() 
{


	Cinema AMC_Theatre;	

	string name = "Planet of the Apes"; // first movie
	Movie *mov = new Movie(name, 7, 6, 2010);
	list<int> *show_time = new list<int>;
	show_time->push_back(2100);
	show_time->push_back(1100);
	show_time->push_back(1530);
	show_time->push_back(930);
	AMC_Theatre.addMovie(mov, *show_time);


	name = "Kill Bill Volume : 2";
	mov = new Movie(name, 4, 16, 2004);
	show_time = new list<int>;
	show_time->push_back(1200);
	show_time->push_back(1300);
	show_time->push_back(1530);
	show_time->push_back(830);
	AMC_Theatre.addMovie(mov, *show_time);

	name = "Avatar";
	mov = new Movie(name, 12, 18, 2009);
	Movie temp1 = *mov;
	temp1++;
	mov = &temp1;
	//mov++;   // increment by 1

	show_time = new list<int>;
	show_time->push_back(730);
	show_time->push_back(1230);
	show_time->push_back(1700);
	show_time->push_back(1730);
	show_time->push_back(1800);
	show_time->push_back(1400);
	show_time->push_back(1900);
	show_time->push_back(2100);
	AMC_Theatre.addMovie(mov, *show_time);

	name = "Star Wars: A New Hope";
	mov = new Movie(name, 5, 25, 1977);
	show_time = new list<int>;
	show_time->push_back(1000);
	show_time->push_back(1100);
	show_time->push_back(1830);
	show_time->push_back(2130);
	AMC_Theatre.addMovie(mov, *show_time);

	name = "Indiana Jones: Raiders of The Lost Ark";
	mov = new Movie(name, 6, 12, 1981);
	show_time = new list<int>;
	show_time->push_back(1030);
	show_time->push_back(1230);
	show_time->push_back(1400);
	show_time->push_back(1500);
	AMC_Theatre.addMovie(mov, *show_time);
	
	//
	//			Finish adding movies
	cout << AMC_Theatre;
	//
	//
	name = "Avatar";

	Movie* i_want_watch = new Movie(name, 12, 18, 2009); // I want to see Avatar
	Movie temp2 = *i_want_watch;
	temp2++;
	i_want_watch = &temp2;

	list<int> *time_avaiable = new list<int>; //looking for times between 4 and 7
	time_avaiable->push_back(1600);
	time_avaiable->push_back(1630);
	time_avaiable->push_back(1700);
	time_avaiable->push_back(1730);
	time_avaiable->push_back(1800);
	time_avaiable->push_back(1830);
	time_avaiable->push_back(1900);
	
	AMC_Theatre.movieRunningAt(*i_want_watch, *time_avaiable);
	
	

	deletePointers(show_time, time_avaiable);  // delete the pointers,

	return 0;
}