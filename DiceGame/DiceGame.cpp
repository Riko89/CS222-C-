// Programmer: Eric Davey
// Purpose: take in input from user as guess for the sum of a 6 sided dice rolled 3 times, randomly generate the rolls of the dice
// and calculate the sum, create a computer guess for the sum and calculate which guess is closer, if the user is about to win 3 times in
// a row the program cheats and gives the user a guess of 1000.
// Class: CS222
//Assignment # 2

#include <iostream>
#include <cstdlib>
#include <ctime>

void cheater(int &userGuess);			//function declarations
void rollDice(int &sum, int &pcGuess);
void deviation(int userGuess, int pcGuess, int sum, int &cheatCounter, int &winner);

using namespace std;

int main() 
{
	int userGuess = 0, pcGuess = 0, sum = 0, winner =0, userWins = 0, pcWins = 0, cheatCounter = 1; // variable declarations
	
	cout << "Input your guess for the sum of 3 dice rolls, input -1 to quit" << endl;
	do {  // do while, ending condition is a break, triggered if user inputs -1
		sum = 0; // resets sum
		cout << endl << "User Guess: ";
		cin >> userGuess;   // asking for user guess

		if (!cin.good() || userGuess < -1) // error checking for user input
		{
			cout << "Bad input" << endl;
			cin.clear();
			cin.ignore();
			continue;
		}

		if (userGuess == -1)  // ending condition for while loop
			break;
		
		rollDice(sum, pcGuess); // function call to rollDice

		cout << "Sum: " << sum << endl; 
		
		deviation(userGuess, pcGuess, sum, cheatCounter, winner); // function call to determine deviation
		if (winner == 0) //conditions for user win, winner == 0, incriment userwin counter, and cheater counter
		{
			userWins++;
			cheatCounter++;
		}
		else  // if not, computer wins, incriment pc win counter
			pcWins++;
		
		cout << "Score: User " << userWins << " Pc " << pcWins << endl;
	} while (true);
}

void rollDice(int &sum, int &pcGuess)  // function for rolling the dice and assigning sum to the value stored at sum.
{
	const int SIZE = 3;
	int diceArr[SIZE]; // array for storing rolls
	srand(time(0));  // setting random number generator to clock
	
	pcGuess = 1 + (rand() % 18);   // getting value for PC's guess, 1 - 18
	cout << "Pc guess: " << pcGuess << endl;

	for (int i = 0; i < 3; i++)
	{
		diceArr[i] = 1 + (rand() % 6); // 1 - 6
		cout << "roll... " << diceArr[i] << "    ";
		sum += diceArr[i]; // calculating sum
	}
	cout << endl;
}

void deviation(int userGuess, int pcGuess, int sum, int &cheatCounter, int &winner) // calculates the deviation of both guesses
{
	userGuess -= sum; 
	pcGuess -= sum;
	if (userGuess < 0) // if the deviation yeilds a negative number, multiply by -1 to assign a positive one
		userGuess *= -1;
	if (pcGuess < 0)
		pcGuess *= -1;

	if ((cheatCounter % 3) == 0 && userGuess < pcGuess)  // call to cheater function if winCounter is divisible by 3
	{
		cheater(userGuess);
		cheatCounter++; 
	}
	cout << "User Deviation: " << userGuess << endl << "Pc Deviation: " << pcGuess << endl;

	if (pcGuess <= userGuess)  // calculating win conditions, whosever number is smaller wins
	{
		cout << "Computer wins" << endl;
		winner = 1;
	}
	else
	{
		cout << "User wins" << endl;
		winner = 0;
	}
}

void cheater(int &userGuess) // computer cheats by setting userGuess to 1000
{
	cout << "Computer Cheats!" << endl; 
	userGuess = 1000;
}