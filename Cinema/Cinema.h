#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <list>
#include <map>

class Date {
public:
	Date();
	Date(int, int, int);
	~Date();
	int getDay()const;
	int getMonth()const;
	int getYear()const;
	bool operator==(Date &);
	friend std::ostream & operator<<(std::ostream &, Date &);
private:
	int day, month, year;
};

class Movie
{
public:
	Movie(std::string &, int, int, int);
	~Movie();
	Date & getReleaseDate();
	bool operator== (Movie &);
	Movie & operator++(int);
	friend std::ostream & operator<<(std::ostream &, Movie &);
	std::string getName();
private:
	Movie();
	const Date releaseDate;
	std::string name;
	int rating;
};

class Cinema
{
public:
	Cinema();
	Cinema(Cinema &);
	~Cinema();
	void addMovie(Movie *, std::list<int> &);
	void movieRunningAt(Movie &, std::list<int> &);
	void printShowTime(Movie *);

	friend std::ostream & operator<<(std::ostream &, Cinema &);
private:
	std::list<Movie*> running_movies;
	std::map<Movie*, std::list<int> > movie_times;
};

#endif // CINEMA_H