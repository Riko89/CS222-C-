// Programmer: Eric Davey
// Purpose: Take in one integer input and return it's position in the fibonacci sequence using recursion, 
//then to take in another integer to determine if it is a number in the fibonacci sequence.
// Class: CS222
//Asignment # 2 
#include <iostream>

using namespace std;

 void fibonacci(int fArr[], int j, int numCycles) // recusive function, calls itself calculating the next fibonacci number
{
	if (j < numCycles) // if statement to continue recursion, when j becomes larger than numCycles recursion ends 
	{
		fArr[j] = fArr[j - 1] + fArr[j - 2]; 
		fibonacci(fArr, ++j, numCycles); // recursion call
	}
}

 bool fibCheck(int fArr[], int Num2, int i)  // boolean function, checks for value at i if = to Num2
 {
	 if (Num2 == fArr[i])
		 return true;
	 else
		 return false;
 }

int main()
{
	const int SIZE = 100; // SIZE is the default size of the array.
	int numCycles = 0, Num2 = 0, fArr[SIZE]; // num cycles is the amount of times the fib sequence will repeat, Num2 is the number asked for to check if it's a part of the sequeunce, fArr[] is the array of fibonacci numbers
	
	fArr[0] = 0, fArr[1] = 1;  // first two numbers of the Fibonacci sequence.

	cout << "Enter the number you wish to see in the Fibonacci sequence:  " << endl;
	do  // do ask for amount of cycles  While the cycles are not less than 1 or more than SIZE (100)
	{
		cin >> numCycles; //  number of cycles to repeat
		if (numCycles > SIZE) // do not want to exceed the size of the array 
			cout << "Too high, enter another" << endl; 
		if (numCycles < 1) //do not want to encounter out of bounds error
			cout << "Too low, enter another" << endl;
	} while (numCycles > SIZE | numCycles < 1);	 

	int j = 2; // j is index passed to recursive function
	fibonacci(fArr, j, numCycles); // recursive function call, fArr, j, and numCycles passed as arguments


	cout << "Output: " << fArr[numCycles-1] << endl;     
	cout << "Enter a number equal to or lower than the output: " << endl;
	cin >> Num2;  // asking for second number that needs to be lower than the output
	for (int i = 0; i < numCycles; i++)
	{
		if (fibCheck(fArr, Num2, i))  // passes elements to boolean algorithm, returns true or false
		{
			cout << Num2 << " is a Fibonacci number." << endl; // if true print if fib number, then return 0 to end program
			return 0; 
		}
	}
 
	
	cout << Num2 << " is not a Fibonacci number." << endl;  // if number wasn't confirmed, print is not and end program

	return 0;
}	