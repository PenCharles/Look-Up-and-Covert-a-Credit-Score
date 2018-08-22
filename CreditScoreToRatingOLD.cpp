#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>
//need to fix the enum array situation
using namespace std;

//global constants
const int MAX = 1001;
const int LOW_AGE = 25;
const int HIGH_AGE = 60;
const int ARRAY_MAX = 1000;
const int AGE_MIN = 25;
const int AGE_MAX = 60;
const int LENGTH = 11;					//length of SSN
const string EXIT = "X";				//used to exit program
const string EXIT1 = "x";				//used to exit program
const int IDX2 = 3;						//used in error checks
const int IDX5 = 6;						//used in error checks
const char DASH = '-';					//used in error checks

//fucntion prototypes
void OpenAndCheckFile (ifstream& input);
void ReadAndProcess (ifstream& inFile, string ssn[], int number[], int& customerCount);
void SelectionSortTwoArrays (string info[], int number[], int count);
string ContinueOrExit ();
void WriteDataToFile (string info[], int number[], ofstream& outFile, 
					  int count);
void DisplaySSN (string info[], int count);
void binarySearch (string info[], int number[], int customerCount,
				   string userInput);
string ErrorCheck ();
void displayResults (bool found, int mid, string info[], int number[],
					 string userInput);
void binarySearch (string info[], int number[], int customerCount,
				   string userInput);



int main ()
{
	//local variables
	int customerCount = 0;				  //holds the count of customer in array
    //enum creditScore {EXCELLENT, GOOD, AVERAGE, FAIR, POOR, BAD}; //credit rating
	string inFilename = "CREDIT.txt";	  //name of file for reading data
	string outFilename = "SORTED.txt";    //name of file for sorted arrays
	string customerChoice;				  //var used to hold cont or exit choice
	ifstream inFile;					  //var used to read in data from file
	ofstream outFile;					  //var used to write data to a file
	string ssn[ARRAY_MAX];				  //array holds cust socials
	int rating[ARRAY_MAX];
	
	//execution
	inFile.open(inFilename.c_str());		//open file for reading in data
	outFile.open(outFilename.c_str());		//open file for data ouput
		 
	OpenAndCheckFile (inFile);			//check file and issue error if nonexist
	
	ReadAndProcess (inFile, ssn, rating, customerCount); //read data into arrays
	
	SelectionSortTwoArrays (ssn, rating, customerCount); //sort both arrays
	
	WriteDataToFile (ssn, rating, outFile, customerCount); //write data to file
	
	DisplaySSN (ssn, customerCount);	//display list of SSNs on file
	
	//based on choice will exit or search for credit score
	do
	{
		customerChoice = ErrorCheck(); //returns valid customer input
		
		if (customerChoice == "x" || customerChoice == "X")
			cout << endl << " Exiting Program" << endl;
		else
			binarySearch (ssn, rating, customerCount, customerChoice);
			
	} while (customerChoice != "x" && customerChoice != "X");

	inFile.close();		//close file
	outFile.close();	//close file
	
 	cout << endl << endl;
 	return 0;
}

//function definitions
void OpenAndCheckFile (ifstream& input)
{
	if (!input)			//tests to see if file exists
	{
		cout << endl << "This file does not exist. "
		   	         << "The program terminates.";
	}
}

void ReadAndProcess (ifstream& inFile, string info[], int number[],
					 int& count)
{
	string ssn;	 		//ssn of customer
	int age;			//age of customer
	int rating; 		//credit rating of customer
	enum credit {EXCELLENT, GOOD, AVERAGE, FAIR, POOR, BAD};
	credit score;
	
	inFile >> ssn >> age >> rating; 	//read in first line
	
	if (age > AGE_MIN && age < AGE_MAX) //if age in range add data to pos 0
		{
			info[count] = ssn;
			
			if (rating >= 750)
			{
				score = EXCELLENT;
			}
			else if (rating >= 720)
			{
				score = GOOD;
			}
			else if (rating >= 660)
			{
				score = AVERAGE;
			}
			else if (rating >= 620)
			{
				score = FAIR;
			}
			else if (rating >= 600)
			{
				score = POOR;
			}
			else
			{
				score = BAD;
			}
			number[count] = score;
			//cout << info[count] << " " << number[count] << endl;
		}
		
	//the while loop below will check for data and array bounds, next it will
	//read in data for file and check for age range, next it will increment 
	//count variable and check for array bounds, next if array has room data will
	//be placed inside array, if array becomes full it will no longer accept data
	//and an error will be issued warning the user that it is full
	while (inFile && count <= ARRAY_MAX)	//loop until eof or count >= ARRAY_MAX
	{
		inFile >> ssn >> age >> rating;		//read into var to check age range
		
		if (age >= AGE_MIN && age <= AGE_MAX) //if age in in range increment array
		{
			count++;						//incr loc in array
			
			if (count <= ARRAY_MAX)
			{
				info[count] = ssn;
				
				if (rating >= 750)
				{
					score = EXCELLENT;
				}
				else if (rating >= 720)
				{
					score = GOOD;
				}
				else if (rating >= 660)
				{
					score = AVERAGE;
				}
				else if (rating >= 620)
				{
					score = FAIR;
				}
				else if (rating >= 600)
				{
					score = POOR;
				}
				else
				{
					score = BAD;
				}
				number[count] = score;
				//cout << info[count] << " " << number[count] << endl;
			}
		}	 
	}	
	if (count > ARRAY_MAX)
	{
		cout << endl << endl << "The data file is to large. Only 1000 users have "
							 << "been loaded into the new file." << endl;
	}
}

void SelectionSortTwoArrays (string info[], int number[], int count)
{
	int index;			//loop condition number
	int biggestIndex;	//element loc of biggest value in unsorted array
	int location;		//second element loc in unsorted array
	string tempSSN;		//holds biggest value in sorted array
	int tempCreditScore;//holds biggest value in parallel array

	for (index = 0; index <= count - 1; index++)
	{
		biggestIndex = index;		//assume biggest num is in element 0
		
		for (location = index + 1; location <= count; location++) //cycle through list
			if (info[location] > info[biggestIndex])	//test for which is bigger
				biggestIndex = location;				//swap for biggest value
				
		tempSSN = info[biggestIndex];			//insert biggest value in 1st array
		tempCreditScore = number[biggestIndex];	//insert parallel element into paralell array
		info[biggestIndex] = info[index];		//provides starting loc for portion of unsorted array
		number[biggestIndex] = number[index];	//provides starting loc for portion of unsorted array
		info[index] = tempSSN;					//store current biggest value into sorted array
		number[index] = tempCreditScore;		//store parallel value in parallel array
	}
}

void WriteDataToFile (string info[], int number[], ofstream& outFile, 
					  int count)
{
	int index;		//loop condition number
	
	//loop through each array and store the sorted contents into the ouput file
	for(index = 0; index <= count; index++)
	{
		outFile << info[index] << " " << number[index] << endl;
	}
}

void DisplaySSN (string info[], int count)
{
	int index;	//loop condition number
	
	cout << "Social Security Numbers on file are:" << endl;
	
	for(index = 0; index <= count; index++)
	{
		cout << info[index] << "  ";
		if(index == 5)
			cout << endl;
	}
}

string ContinueOrExit ()
{
	string input;
	
	cout << endl << "Enter SSN to find (or X to exit): ";
	cin >> input;
	
	return input;
}

string ErrorCheck ()
{
	int numberLen;		//stores amount of characters in user entered SSN
	int count;      	//proper lenghth of ssn including dashes
	string userInput;
	bool invalidNumber;
	
	do
	{	
		cout << endl << endl << " Enter SSN to find (or X to exit):";
		invalidNumber = false;
		cin >> userInput;
		
		if (userInput != EXIT && userInput != EXIT1)
		{
			numberLen = userInput.length();
					
			if (numberLen < LENGTH || numberLen > LENGTH) 
				invalidNumber = true;
									
			if (userInput[IDX2] != DASH || (userInput[IDX5] != DASH))
				invalidNumber = true;	
				
			for (count = 0; count < LENGTH; count++)
			{
				if (isprint(userInput[count]));
				else
				{
					invalidNumber = true;
				}
			}
			
			if (invalidNumber)
			{
				cout << " Customer input " << userInput << " is formatted incorrectly."
				     << endl << " SSN must be exactly 11 characters long, formatted as: "
				     << "###-##-###" << endl;
			}
			else
			{
				cout << " You entered a good ssn" << endl;
			}
		}
	}
	while (invalidNumber);
	
	return userInput;
}

void binarySearch (string info[], int number[], int customerCount,
				  string userInput)
{
	int first = 0;					//holds the first position in the array
	int last = customerCount;	//holds last position in array
	int mid;						//holds the middle position in the array
	bool found = false;				//indicates when search is successful or not
	
	while (first <= last && !found)
	{
		mid = (first + last) / 2;
		
		if(info[mid] == userInput)
			found = true;
		else if (info[mid] < userInput)
			last = mid - 1;
		else
			first = mid + 1;
	}
	
	displayResults(found, mid, info, number, userInput);
}

void displayResults (bool found, int mid, string info[], int number[],
					 string userInput)
{	
	if (found)
	{
		cout << " The customer with SSN " << info[mid] << " has ";
		
		switch (number[mid])
		{
			case 0:
				cout << "an Excellent credit rating." << endl << endl;
				break;
			case 1:
				cout << "a Good credit rating." << endl << endl;
				break;
			case 2:
				cout << "an Average credit rating." << endl << endl;
				break;
			case 3:
				cout << "a Fair credit rating." << endl << endl;
				break;
			case 4:
				cout << "a Poor credit rating." << endl << endl;
				break;
			case 5:
				cout << "a Bad credit rating." << endl << endl;
		}
	}
	else
		cout << "No customer with " << userInput << " was found." << endl << endl;		
}
//cant find ssn 111-11-1111
