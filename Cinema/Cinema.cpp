#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include "Cinema.h"


using namespace std;

/**
//		OSTREAM FUNCTIONS

**/
ostream & operator<<(ostream &output, Movie &movie)
{
	Date temp = movie.getReleaseDate();
	output << movie.name << ":  " << endl << temp;
	output << "Rating: " << movie.rating << endl;
	return output;
}

ostream & operator<<(ostream &output, Date &date) {
	output << "Release Date:  " << date.getMonth() << "/" << date.getDay() << "/" << date.getYear() << endl;
	return output;
}

ostream & operator<<(ostream &output, Cinema &cinema)
{
	output << "Printing All Show Times: " << endl << endl;
	for (map<Movie*, list<int>>::iterator it = cinema.movie_times.begin(); it != cinema.movie_times.end(); it++)
	{
		output << "Movie: " << *it->first;
		output << "Show Times: ";
		for (auto &i : it->second) { output << i << ",   "; }
		output << endl << endl;
	}
	return output;
}

/**
//		DATE CLASS
**/

Date::Date(){}
Date::Date(int d, int m, int y)//const int format
{
	day = d;
	month = m;
	year = y;
}
Date::~Date(){}
bool Date::operator==(Date &date)
{
	if ((*this).day == date.day && (*this).month == date.month && (*this).year == date.year)
		return true;
	else
		return false;
}

int Date::getDay()const{return day;}
int Date::getMonth()const{return month;}
int Date::getYear()const{return year;}

/**
             MOVIE CLASS
**/

Movie::Movie(string & n, int mm, int dd, int yyyy) : releaseDate(dd, mm, yyyy) // passed string
{
	name = n;
	rating = 0;
}
Movie::~Movie() {}  // destructor
Date & Movie::getReleaseDate() // return temp date since releasedate is const
{
	Date temp = releaseDate;
	return temp;
}

bool Movie::operator== (Movie &movie)
{ 
	Date a = (*this).getReleaseDate();
	Date b = movie.getReleaseDate();
	
	if (a == b)
		return (*this).rating == movie.rating;
	else
		return false;
}

Movie & Movie::operator++(int)
{
	this->rating++;
	return (*this);
}

string Movie::getName() { return name; }

/////////
/**
//            CINEMA CLASS
**/
Cinema::Cinema() { }
Cinema::Cinema(Cinema &){ }

void Cinema::addMovie(Movie *movie, list<int> &p)
{
	running_movies.push_back(movie); 
	p.sort();
	movie_times.insert(pair<Movie*, list<int>>(movie, p));
}

Cinema::~Cinema()
{
	movie_times.clear();
	running_movies.clear();
}

void Cinema::movieRunningAt(Movie &movie, list<int> &times_available) // checks if your movie is running at the times you want
{
	cout << "All available showings for your movie at times you are available: " << endl;
	auto it = movie_times.begin();
	for(; it != movie_times.end(); it++)  // find the list that matches the show time
	{
		if (*it->first == movie)
			break;
	}
	if (it == movie_times.end())  
	{
		cout << "No Movie available" << endl;
		return;
	}

	//convert found list to vector for binary search
	vector <int> timesAvail;
	for (auto & i : times_available)
	{
		timesAvail.push_back(i);
	}

	for (int t : it->second)
	{
		if(binary_search(timesAvail.begin(), timesAvail.end(), t))
		{
			cout << "Showing at : " << t << endl;
			printShowTime(it->first); // print the movie at times available
		}
	}
}

void Cinema::printShowTime(Movie * movie) // print the movie name and release date
{
	cout << *movie;
}
