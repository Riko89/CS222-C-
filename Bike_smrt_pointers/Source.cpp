//Eric Davey
//CS222  C++ Sverdlov
//Palomar ID # 007467548
// BIKE LAB with list STL
// 4/10/2018

#include <iostream>
#include <fstream>
#include <list>
#include <iomanip> 
#include <memory>

using namespace std;

struct Bike;
typedef shared_ptr<Bike> UBike;
typedef list<shared_ptr<Bike> > myList;

enum status { NO_STATUS, NOT_RENTED, RENTED, ALL };
enum order { NO_ORDER, ID, MANUF };


struct Bike
{
	char manufact[25];
	int id_num;
	status rented_code; //RENTED/NOT_RENTED 
	char to_whom[25];   //to whom bike is rented 
	int size;
	float cost_per_day;
	bool deleted; //to mark bike as deleted in the list. 
	Bike *next_manuf; //pointer to next node in the 
					  //manufacturers list 
	Bike *next_id; //pointer to the next node 
				   //in the list by ID 
	Bike *next; //pointer to the next node in the general list 
};

void readBike(ifstream &in, myList &list1);
void printBikes(myList list1, order, status);
bool comp_id(UBike b1, UBike b2);
bool comp_manuf(UBike b1, UBike b2);
void do_transact(ifstream &inFile, myList &list1, status s);
void del_id_bike(ifstream &inFile, myList &list1);
void del_manuf(ifstream &inFile, myList &list1);

int main() 
{
	ifstream inFile;

	myList list1;

	inFile.open("prog_5_dat_file.txt"); // inFile is ifstream
	if (!inFile.good())
	{
		cout << "Problem with text file, exiting.." << endl;
		return 0;
	}

	while (inFile.good())
	{
		int code = 0;
		inFile >> code; // reads code for switch statement

		switch (code)
		{
		case 1:
			cout << "reading in bike . . ." << endl;
			readBike(inFile, list1);
			break;
		case 2:
			cout << "PRINTING GENERAL LIST OF ALL BIKES" << endl;
			printBikes(list1, NO_ORDER, ALL);
			break;
		case 3:
			cout << "PRINTING LIST OF ALL BIKES SORTED BY ID" << endl;
			printBikes(list1, ID, ALL);
			break;
		case 4:
			cout << "PRINTING LIST OF ALL BIKES SORTED BY MANUFACTURER NAME" << endl;
			printBikes(list1, MANUF, ALL);
			break;
		case 5:
			cout << "PRINTING LIST OF ALL BIKES AVAILABLE FOR RENT" << endl;
			printBikes(list1, NO_ORDER, NOT_RENTED);
			break;
		case 6: 
			cout << "PRINTING LIST OF ALL BIKES CURRENTLY RENTED" << endl;
			printBikes(list1, NO_ORDER, RENTED);
			break;
		case 7:
			cout << "ATTEMPTING TO RENT" << endl;
			do_transact(inFile, list1, NOT_RENTED);
			break;
		case 8:
			cout << "ATTEMPTING TO RETURN" << endl;
			do_transact(inFile, list1, RENTED);
			break;
		case 9: 
			del_id_bike(inFile, list1);
			break;
		case 10:
			del_manuf(inFile, list1);
		default:
			break;
		}
	}
	inFile.close();
	
	cout << "END" << endl;
	return 0;
}


void readBike(ifstream &inFile, myList &list1) // reads bikes into general list
{
	UBike ptr;
	ptr.reset(new Bike);

	ptr->rented_code = NOT_RENTED;
	inFile >> ptr->id_num;
	inFile >> ptr->size;
	inFile >> ptr->cost_per_day;
	inFile >> ptr->manufact;
	ptr->deleted = false;

	list1.push_back(move(ptr)); // add new bike
}

bool comp_id(UBike b1, UBike b2) {
	return  b1->id_num < b2->id_num;
}

bool comp_manuf(UBike b1, UBike b2) {
	return (strcmp(b1->manufact, b2->manufact) < 0);
}

void printBikes(myList list1, order o, status s)
{

	if(o == ID)
		list1.sort(comp_id);

	if (o == MANUF)
		list1.sort(comp_manuf);

	for (auto & i : list1) {
		if (i->rented_code == s || s == ALL)  // if printing all or rented code is what is asked for
		{
			if (!i->deleted)
			{
				cout << "ID NUM " << i->id_num;
				cout << "  SIZE " << i->size;
				cout << "  COST PER DAY $" << setw(6) << left << i->cost_per_day;
				cout << setw(3) << right << "  MANUFACTURER " << i->manufact << endl;
			}
		}
	}
	cout << endl;
}

void do_transact(ifstream &inFile, myList &list1, status rental_status)
{
	int id_num, num_days; // read in id and number of days rented
	float cost;
	char name[25];

	inFile >> id_num;
	inFile >> num_days;

	if (rental_status == NOT_RENTED) {
		for (auto & renting : list1) //check for ID 
		{
			if (renting->id_num == id_num && renting->rented_code == NOT_RENTED)
			{
				renting->rented_code = RENTED;
				inFile.ignore();
				inFile.getline(name, 25);
				strcpy_s(renting->to_whom, name);
				cost = num_days * renting->cost_per_day;
				cout << "Renting #" << renting->id_num << " bike to " << renting->to_whom << endl;
				cout << "Cost is $" << cost << endl << endl;
				return;
			}
			else if (renting->id_num == id_num && renting->rented_code == RENTED)
				cout << "BIKE ID NUM " << renting->id_num << " is already rented." << endl << endl;
		}
	}
	
	if (rental_status == RENTED)  // if we are trying to return a bike then
	{
		for (auto & returning : list1) //check for ID 
		{
			if (returning->id_num == id_num && returning->rented_code == RENTED)  // change status to not rented, return bike
			{
				returning->rented_code = NOT_RENTED;
				cout << "Bike ID NUM " << returning->id_num << " Was returned by " << returning->to_whom << " after ";
				cout << num_days << " days" << endl << endl;
			}
			else if(returning->id_num == id_num && returning->rented_code == RENTED)
				cout << "BIKE ID NUM " << returning->id_num << " cannot be returned because it was never rented." << endl << endl;
		}
	}
}
void del_id_bike(ifstream &inFile, myList &list1) // delete specific list by id
{
	int id_num;
	inFile >> id_num;
	cout << "Deleting num #" << id_num << endl << endl;
	for(auto & i : list1)
	{
		if (i->id_num == id_num)
		{
			i->deleted = true;
			break;
		}
	}
}
void del_manuf(ifstream &inFile, myList &list1) // finds manufacturer and deletes
{
	char manufact[25];
	inFile >> manufact, 25;
	cout << "Deleting manufacturer: " << manufact << endl << endl;

	for (auto & i : list1) {
		if (strcmp(manufact, i->manufact) == 0)
		{
			i->deleted = true;
			break;
		}
	}
}