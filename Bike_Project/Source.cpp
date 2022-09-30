//Eric Davey
//CS222  C++ Sverdlov
//Palomar ID # 007467548
// BIKE LAB
// 3/29/2018    I requested an extension.

#include <iostream>
#include "Bikes.h"
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;

void readBike(ifstream &in, Bike*& head, Bike*& manuf, Bike*& id);
void init(Bike*& head, Bike*& manuf, Bike*& id);
Bike* addbike(Bike* head, Bike* genList);
Bike* addbike(Bike* head_id, Bike* new_bike, order);
Bike* addbike(Bike* head_manufacturer, Bike* new_bike, order, int);
void printBikes(Bike* head, order, status);
void do_transact(ifstream &inFile, Bike* head, status s);
void del_id_bike(ifstream &inFile, Bike* id);
void del_manuf(ifstream &inFile, Bike* manuf);
void deleteBikes(Bike *head);

int main() 
{
	ifstream inFile;
	Bike *head, *manuf, *id;
	init(head, manuf, id); //initializes the lists;
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
			readBike(inFile, head, manuf, id);
			break;
		case 2:
			cout << "PRINTING GENERAL LIST OF ALL BIKES" << endl;
			printBikes(head, NO_ORDER, ALL);
			break;
		case 3:
			cout << "PRINTING LIST OF ALL BIKES SORTED BY ID" << endl;
			printBikes(id, ID, ALL);
			break;
		case 4:
			cout << "PRINTING LIST OF ALL BIKES SORTED BY MANUFACTURER NAME" << endl;
			printBikes(manuf, MANUF, ALL);
			break;
		case 5:
			cout << "PRINTING LIST OF ALL BIKES AVAILABLE FOR RENT" << endl;
			printBikes(head, NO_ORDER, NOT_RENTED);
			break;
		case 6: 
			cout << "PRINTING LIST OF ALL BIKES CURRENTLY RENTED" << endl;
			printBikes(head, NO_ORDER, RENTED);
			break;
		case 7:
			cout << "ATTEMPTING TO RENT" << endl;
			do_transact(inFile, head, NOT_RENTED);
			break;
		case 8:
			cout << "ATTEMPTING TO RETURN" << endl;
			do_transact(inFile, head, RENTED);
			break;
		case 9: 
			del_id_bike(inFile, id);
			break;
		case 10:
			del_manuf(inFile, manuf);
		default:
			break;
		}
	}
	inFile.close();
	deleteBikes(head); // delete all bikes
	
	cout << "END" << endl;
	return 0;
}

void init(Bike*& head, Bike*& manuf, Bike*& id) // initializes all pointers to NULL
{
	head = NULL;
	id = NULL;
	manuf = NULL;
}

void readBike(ifstream &inFile, Bike*& head, Bike*& manuf, Bike*& id) // reads bikes into general list
{
	//General List
	Bike *genList = new Bike;
	
	genList->rented_code = NOT_RENTED;
	inFile >> genList->id_num;
	inFile >> genList->size;
	inFile >> genList->cost_per_day;
	inFile >> genList->manufact;
	genList->deleted = false;

	head = addbike(head, genList); // addbike to general list
	id = addbike(id, genList, ID);  // addbike sorted by id
	manuf = addbike(manuf, genList, MANUF, 1);  //add bike sorted by manufacturer
	
}

Bike* addbike(Bike* head, Bike* new_bike) // add bike to general list
{
	Bike *pointer; // temp variable pointer

	if (head == NULL) // if this is the first in list
	{
		head = new_bike;
		head->next = NULL;
		return head;
	}
	//else add new list
	pointer = head; 
	while (pointer->next != NULL)
	{
		pointer = pointer->next;
	}
	pointer->next = new_bike;
	new_bike->next = NULL;

	return head;
}

Bike* addbike(Bike* head_id, Bike* new_bike, order) // add to list and sort by id;
{
	Bike *previous = head_id;
	Bike *temp = head_id;
	
	if (head_id == NULL) // if there is no list, make this the head
	{
		new_bike->next_id = NULL;
		head_id = new_bike;
		return head_id;
	}
	//else 
	//else if new bike is before head make new bike the head
	if (head_id->id_num > new_bike->id_num)
	{
		new_bike->next_id = head_id;
		head_id = new_bike;
		return head_id;
	}
	while (temp != NULL)  // traverse list for insertion point
	{
		if (temp->id_num > new_bike->id_num)
		{
			previous->next_id = new_bike;
			new_bike->next_id = temp;
			return head_id;
		}
		previous = temp;
		temp = temp->next_id;
	}
		// if new_bike is the largest
	previous->next_id = new_bike;
	new_bike->next_id = NULL;
	return head_id;
}

Bike* addbike(Bike* head_manufacturer, Bike* new_bike, order, int)
{
	Bike *previous = head_manufacturer;
	Bike *temp = head_manufacturer;

	if (head_manufacturer == NULL) // if there is no list, make this the head
	{
		new_bike->next_manuf = NULL;
		head_manufacturer = new_bike;
		return head_manufacturer;
	}
	//else if new bike is before head make new bike the head
	if (strcmp(head_manufacturer->manufact, new_bike->manufact) > 0)
	{
		new_bike->next_manuf = head_manufacturer;
		head_manufacturer = new_bike;
		return head_manufacturer;
	}
	while (temp != NULL)  // traverse list for insertion point
	{
		if (strcmp(temp->manufact, new_bike->manufact) > 0)
		{
			previous->next_manuf = new_bike;
			new_bike->next_manuf = temp;
			return head_manufacturer;
		}
		previous = temp;
		temp = temp->next_manuf;
	}
	// if new_bike is the largest
	previous->next_manuf = new_bike;
	new_bike->next_manuf = NULL;
	return head_manufacturer;
}

void printBikes(Bike* head, order o, status s)
{
	while (head != NULL)  //traverses
		{
			if (head->rented_code == s || s == ALL)  // if printing all or rented code is what is asked for
			{
				if (!head->deleted)
				{
					cout << "ID NUM " << head->id_num;
					cout << "  SIZE " << head->size;
					cout << "  COST PER DAY $" << setw(6) << left << head->cost_per_day;
					cout << setw(3) << right << "  MANUFACTURER " << head->manufact << endl;
				}
			}
			if(o == NO_ORDER)
				head = head->next;
			if(o == ID)
				head = head->next_id;
			if (o == MANUF)
				head = head->next_manuf;
		}
	cout << endl;
}

void do_transact(ifstream &inFile, Bike* head, status rental_status)
{
	Bike *temp = head;
	int id_num, num_days; // read in id and number of days rented
	float cost;
	char name[25];

	inFile >> id_num;
	inFile >> num_days;
	while (temp != NULL) //check for ID 
	{
		if (temp->id_num == id_num)
		{
			break;
		}
		temp = temp->next;
	}
	if (rental_status == NOT_RENTED)  // if we are trying to rent a bike then
	{
		if (temp->rented_code == NOT_RENTED)  // if not rented read in name  and change status to rented
		{
			temp->rented_code = RENTED;
			inFile.ignore();
			inFile.getline(name, 25);
			strcpy_s(temp->to_whom, name);
			cost = num_days * temp->cost_per_day;
			cout << "Renting #" << temp->id_num << " bike to " << temp->to_whom << endl << "Cost is $" << cost << endl << endl;
		}
		else
			cout << "BIKE ID NUM " << temp->id_num << " is already rented." << endl << endl;
	}
	
	if (rental_status == RENTED)  // if we are trying to return a bike then
	{ 
		if (temp->rented_code == RENTED)  // change status to not rented, return bike
		{
			temp->rented_code = NOT_RENTED;
			cout << "Bike ID NUM " << temp->id_num << " Was returned by " << temp->to_whom << " after ";
			cout << num_days << " days" << endl << endl;
		}
		else
			cout << "BIKE ID NUM " << temp->id_num << " cannot be returned because it was never rented." << endl << endl;
	}
}
void del_id_bike(ifstream &inFile, Bike* id) // delete specific list by id
{
	int id_num;
	inFile >> id_num;
	cout << "Deleting num #" << id_num << endl << endl;
	while (id != NULL)
	{
		if (id->id_num == id_num)
		{
			id->deleted = true;
			break;
		}
		id = id->next_id;
	}
}
void del_manuf(ifstream &inFile, Bike* manuf) // finds manufacturer and deletes
{
	char manufact[25];
	inFile.ignore();
	inFile.getline(manufact, 25);
	cout << "Deleting manufacturer: " << manufact << endl << endl;
	while (manuf != NULL)
	{
		if (strcmp(manufact, manuf->manufact) == 0)
		{
			manuf->deleted = true;
			break;
		}
		manuf = manuf->next_manuf;
	}
}
void deleteBikes(Bike *head) // deletes all nodes 
{
	Bike *previous;

	while (head != NULL)
	{
		cout << "Deleting " << head->manufact << endl;
		previous = head;
		head->deleted = true;
		head = head->next;
		delete previous;
	}
}