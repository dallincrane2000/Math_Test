/* -----------------------------------------------------------------------------
FILENAME:          Math_Testor.cpp
DESCRIPTION:       Quizes the user with two random numbers and they choose if they
			       Add, Subtract, Multiply, or divide these two random numbers
COMPILER:          MinGW  C++ compiler
NOTES:             
MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Dallin Gomez       2021-10-20         1.0  Create the menus and all the functions
									       for the math.
Dallin Gomez	   2021-10-23		  2.0  Created a function that gives two random numbers
Dallin Gomez	   2021-10-24		  3.0  Fixed RNG being called multiple times making
										   the answers wrong
Dallin Gomez	   2021-11-02		  4.0  Created multiple choice choice function
Dallin Gomez	   2021-11-07		  5.0  Made a counter for score and for how many problems
									       have been completed
Dallin Gomez	   2021-11-08	      6.0  Created the export file 
Dallin Gomez	   2021-11-11		  7.0  Made all the necessary data export to a .txt
----------------------------------------------------------------------------- */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

// Prototypes
int Difficulty();
char Get_Choice();
void RNG(long &r1, long &r2, int &d_level);
void Addition(int &d_level, char &choice, ofstream &fout);
void Subtraction(int &d_level, char &choice, ofstream &fout);
void Multiplication(int &d_level, char &choice, ofstream &fout);
void Division(int &d_level, char &choice, ofstream &fout);
char Multi_Choice(int &answer, int &d_level, ofstream &fout);
void format(int &d_level, char &choice, long &r1, long &r2, ostream &out);
void start(string &fname, string &lname, unsigned &seed, int &d_level, ostream &out);
void problem_num(ofstream &fout);
void display_multi(int (&m)[5], ostream &out);
void answer_valid(char &m_choice_a, char &m_choice, long &answer, int &c_tries, int &tries, bool &tf, int &max_tries, ofstream &fout);

// Global Constants
const string PROGRAMMER_NAME = "Dallin Gomez";

/*-----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:       driver for the program
RETURNS:           0
NOTES:             
------------------------------------------------------------------------------- */

int main()
{
	string fname, lname;
	bool tf = true;
	char choice;
	unsigned seed = time(0);
	int d_level;
	ofstream fout;
	time_t now;
	time(&now);

	srand (time(NULL));		// Sets the seed of random using the time

	cout << "What is your First and last name ? ";
	cin >> fname;		// Takes in first name
	cin >> lname;		// Takes in last name

	string filename = fname + "_" + lname + "_results" + ".txt";
	fout.open(filename);

	start(fname,lname,seed,d_level,fout);		// outputs the start function to .txt
	start(fname,lname,seed,d_level,cout);		// Displays start function
	d_level = Difficulty();		// Runs the function Difficulty and stores the output as d_level

	fout << "Difficulty  #: " << d_level << endl << endl;		// outputs difficulty level to .txt
	cout << "Difficulty  #: " << d_level << endl;		// Displays difficulty level


	// Start menu displayed only once
	cout << "          ARITHMETIC PRACTICE PROGRAM\n";
	cout << "Welcome to the Math Skills Practice Program.\n";
	cout << "This Program allows you to practice your math skills.\n";
	cout << "Choose what to practice in the menu shown below.\n";

	while(tf)				// Loops while tf = true breaks out if false
	{
		choice = Get_Choice();	// runs Get_Choice function and stores the output as choice

		switch (choice)		// Checks the choice variable and runs the appropriate function
		{
			case 'a':		
				Addition(d_level, choice, fout);		// Takes the values of d_level and choice
				break;				

			case 'b':
				Subtraction(d_level, choice, fout);		// Takes the values of d_level and choice
				break;

			case 'c':
				Multiplication(d_level, choice, fout);		// Takes the values of d_level and choice
				break;

			case 'd':
				Division(d_level, choice, fout);		// Takes the values of d_level and choice
				break;

			case 'q':
				tf = false;		// Breaks the loop and quits the program
				break;
		}
	}

	fout << "program ended: " << ctime(&now);
	fout.close();
	
	cout << "Thank you for using Math Tutor.\n" << endl;
	cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
	cout << __DATE__ << "  " __TIME__ << endl;
	cout << endl;

	system("pause");

	return 0;
}
/*-----------------------------------------------------------------------------
FUNCTION:          start()
DESCRIPTION:       outputs the required data to .txt and to console
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void start(string &fname, string &lname, unsigned &seed, int &d_level, ostream &out)
{
	time_t now;
	time(&now);

	seed = time(0);
	out << endl << "Student  name: " << fname << " " << lname << endl;	// Displays first and last name
	out << "Program start: " << ctime(&now);		// Displays when program is ran 
	out << "Random   Seed: " << seed << endl;		// Displays the random seed
}
/*-----------------------------------------------------------------------------
FUNCTION:          Get_Choice()
DESCRIPTION:       shows the menu and takes the users choice
RETURNS:           choice
NOTES:             
------------------------------------------------------------------------------- */
char Get_Choice()
{
	char choice;

	cout << "---------------------------------------------------------\n";
	cout << "               ARITHMETIC PRACTICE PROGRAM\n";
	cout << "                       MAIN MENU\n";
	cout << "---------------------------------------------------------\n";
	cout << "               a.   Addition problem\n";
	cout << "               b.   Subtraction problem\n";
	cout << "               c.   Multiplication problem\n";
	cout << "               d.   Division problem\n";
	cout << "               q.   Quit this program\n";
	cout << "---------------------------------------------------------\n";
	cout << "     Enter your choice [ a b c d q ]: ";
	cin >> choice;		// Takes the users choice
	cout << "---------------------------------------------------------\n";
	choice = tolower(choice);

	return choice;		// Returns the choice value once ran
}
/*-----------------------------------------------------------------------------
FUNCTION:          Difficulty()
DESCRIPTION:       shows the menu and takes the users choice
RETURNS:           choice
NOTES:             
------------------------------------------------------------------------------- */
int Difficulty() 
{
	int d_level;

	cout << "Please select difficulty level:\n";
	cout << "1. 1 digit\n";
	cout << "2. 2 digits\n";
	cout << "3. 3 digits\n";
	cout << "4. 4 digits\n";
	cout << "5. 5 digits\n";
	cout << "Please enter 1-5 only: ";
	cin >> d_level;		// Takes in the selected difficulty level

	return d_level;		// Returns the value of d_level once ran
}
/*-----------------------------------------------------------------------------
FUNCTION:          RNG()
DESCRIPTION:       Creates two random numbers using the difficulty selected
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void RNG(long &r1, long &r2, int &d_level)
{
	int min;
	int max;

	min = pow(10, d_level - 1);
	max = pow(10, d_level);

	r1 = min + rand() % (max - min);
	r2 = min + rand() % (max - min);

	// Set array of a b c d and e and randomize the order

}
/*-----------------------------------------------------------------------------
FUNCTION:          Multi_Choice()
DESCRIPTION:       Formats Multiple Choice
RETURNS:           m_choice
NOTES:             random_shuffle is appart of the algorithm library 
					http://www.cplusplus.com/reference/algorithm/random_shuffle/
------------------------------------------------------------------------------- */
char Multi_Choice(long &answer, int &d_level, ofstream &fout){
	int m[5], random, min, max, a, add_or_sub;
	char m_choice, m_choice_a;
	bool tf = true;
	static int c_tries = 0, tries = 0, max_tries = 1;	// Makes the variable save its value even when the function has completed
	double percent;

	min = 1;
	max = pow(10, d_level);

	for (int i = 1; i < 5; i++)
	{
		// Random number based off of d_level
		random = min + rand() % (max - min);

		add_or_sub = rand() % 1000 + 0;
		if(add_or_sub <= 500){		// if the random number generated by add_or_sub is less than 500 than it makes the random value
			random = (random * -1);	// A negative number 
		} 

		m[i] = (random + answer);		// Makes all of the values of the array equal to random numbers + the answer to make it close

		if (m[i] < 0){		// If value is negative then it takes the absolute value of the number making it positive
			m[i] = abs(i);
		}
	}

		m[0] = answer;		// Makes sure the answer is in the array before it is shuffled

	random_shuffle(begin(m), end(m));		// Shuffles the array

	while(tf){
		display_multi(m, cout);
		display_multi(m, fout);
		cout << "Choice: ";
		cin >> m_choice;		// Takes in the answer for the multiple choice
		fout << "You chose: " << m_choice << endl;

	// Finds what the correct multiple choice value is and sets it equal to m_choice_a
	for (int n = 0; n < 5; n++)	// Runs for each value in the array
	{
		if (answer == m[n])	// If the answer is equal the variable in the array this runs
		{
			a = 97;		// Starts at 97 for 'a'
			a = (a + n);	// adds the n value to bring the char value up to the correct letter
			m_choice_a = char(a);	// makes m_choice_a = to the char of the value of a which would be the correct letter
		}
	}
		answer_valid(m_choice_a,m_choice,answer,c_tries,tries,tf, max_tries, fout);

	}

	percent = (((double)c_tries / (double)tries)*100);		// Gives the percentage of correct tries and none correct tries

	
	cout << "Your score: " << c_tries << " / " << tries << " = " << percent << "%";
	fout << "\nYour score: " << c_tries << " / " << tries << " = " << percent << "%\n";

	return m_choice;		// When ran gives out the value of m_choice
}
/*-----------------------------------------------------------------------------
FUNCTION:          display_multi()
DESCRIPTION:       displays multiple choice to .txt and console
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void display_multi(int (&m)[5], ostream &out)
{
		out << endl;
		out << "(a)   " << m[0] << endl;		// Displays the array item in slot 1
		out << "(b)   " << m[1] << endl;		// Displays the array item in slot 2
		out << "(c)   " << m[2] << endl;		// Displays the array item in slot 3
		out << "(d)   " << m[3] << endl;		// Displays the array item in slot 4
		out << "(e)   " << "NONE OF THE ABOVE" << endl;		// Doesn't display an array item
}
/*-----------------------------------------------------------------------------
FUNCTION:          answer_valid()
DESCRIPTION:       checks if the answer is valid and makes the maximum tries 3
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void answer_valid(char &m_choice_a, char &m_choice, long &answer, int &c_tries, int &tries, bool &tf, int &max_tries, ofstream &fout)
{
// Checks if the correct answer has been choosen
	if (m_choice_a == m_choice){		// If answer is correct
		cout << "Congratulations!\n" << answer << " is the correct answer.\n";
		fout << "Congratulations!\n" << answer << " is the correct answer.\n";
		c_tries++;	//Adds one to correct tries
		tries++;	// Adds one to tries
		tf = false;
	} else if (!(m_choice_a == m_choice)){		// If answer is wrong
		cout << "Sorry, try again...";
		fout << "Sorry, try again...";
		tries++;	// Adds one to tries
	}

	// Makes the max tries = 3
	if (max_tries == 3){
		max_tries = 1;
		tf = false;
	} else{
		max_tries++;
	}
}
/*-----------------------------------------------------------------------------
FUNCTION:          problem_num()
DESCRIPTION:       displays the problem number to .txt and console
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void problem_num(ofstream &fout)
{
	static int p_number = 1;
	time_t now;
	time(&now);
	fout << "Problem No. " << p_number << ": " << ctime(&now) << endl;
	cout << "Problem No. " << p_number << ": " << ctime(&now) << endl;
	p_number++;
}
/*-----------------------------------------------------------------------------
FUNCTION:          format()
DESCRIPTION:       outputs the numbers in a consistent format
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void format(int &d_level, char &choice, long &r1, long &r2, ostream &out){
	string math;

	if (choice == 'a'){	// If a was selected in Get_choice function it makes math = +
		math = "+";
	} else if (choice == 'b'){ // If b was selected in Get_choice function it makes math = -
		math = "-";
	} else if (choice == 'c'){ // If c was selected in Get_choice function it makes math = *
		math = "*";
	} else if (choice == 'd'){ // If d was selected in Get_choice function it makes math = /
		math = "/";
	}

	if (!(choice == 'd')){		// If the choice was not d this is ran
		out << setw(d_level+2) << right << r1 << endl;
		out << math << setw(d_level+1) << right << r2 << endl;
		out << setfill ('-') << setw (d_level+2) << '-' << endl;
		out << setfill (' ');
	} else if (choice == 'd'){		// if choice is equal to d this is ran
		out << (r1*r2) << " " << math << " " << r1;
	}
}
/*-----------------------------------------------------------------------------
FUNCTION:          Addition()
DESCRIPTION:       Tests user with two numbers to add
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void Addition(int &d_level, char &choice, ofstream &fout)
{
	long r1, r2, answer, m_choice;

	RNG(r1, r2, d_level);		// Takes the values of r1 and r2 and d_level from RNG function
	
	cout << endl << endl;
	problem_num(fout);
	
	format(d_level, choice, r1, r2, cout);		// Passes the values of d_level,choice,r1 and r2 to format function
	format(d_level, choice, r1, r2, fout);		// Passes the values of d_level,choice,r1 and r2 to format function

	answer = (r1 + r2);	// adds r1 and r2 and sets it equal to answer variable

	m_choice = Multi_Choice(answer, d_level, fout);	// Gives multiple choice function answer and sets the functions output to m_choice

	cout << endl << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          Subtraction()
DESCRIPTION:       Tests user with two numbers to subtract
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void Subtraction(int &d_level, char &choice, ofstream &fout)
{
	long r1, r2, answer, m_choice, temp;

	RNG(r1, r2, d_level);		// Takes the values of r1 and r2 and d_level from RNG function

	cout << endl << endl;

	if (r1 < r2) {		// switches the values of r1 and r2 if r1 is less than r2
		temp = r1;
		r1 = r2;
		r2 = temp;
	}

	problem_num(fout);

	format(d_level, choice, r1, r2, cout);		// Passes the values of d_level,choice,r1 and r2 to format function
	format(d_level, choice, r1, r2, fout);		// Passes the values of d_level,choice,r1 and r2 to format function

	answer = (r1 - r2);					// Subtracts r1 and r2

	m_choice = Multi_Choice(answer, d_level, fout);	// Gives multiple choice function answer and sets the functions output to m_choice

	cout << endl << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          Multiplication()
DESCRIPTION:       Tests user with two numbers to multiply
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void Multiplication(int &d_level, char &choice, ofstream &fout)
{
	long r1, r2, answer, m_choice;

	RNG(r1, r2, d_level);		// Takes the values of r1 and r2 and d_level from RNG function

	cout << endl << endl;

	problem_num(fout);

	format(d_level, choice, r1, r2, cout);		// Passes the values of d_level,choice,r1 and r2 to format function
	format(d_level, choice, r1, r2, fout);		// Passes the values of d_level,choice,r1 and r2 to format function

	answer = (r1 * r2);	// Multiplies r1 and r2

	m_choice = Multi_Choice(answer, d_level, fout);	// Gives multiple choice function answer and sets the functions output to m_choice

	cout << endl << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION:          Division()
DESCRIPTION:       Tests user with two numbers to divide
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */
void Division(int &d_level, char &choice, ofstream &fout)
{
	long r1, r2, answer, m_choice;

	RNG(r1, r2, d_level);	// Takes the values of r1 and r2 and d_level from RNG function

	cout << endl << endl;

	problem_num(fout);

	format(d_level, choice, r1, r2, cout);		// Passes the values of d_level,choice,r1 and r2 to format function
	format(d_level, choice, r1, r2, fout);		// Passes the values of d_level,choice,r1 and r2 to format function

	answer = r2;		// r2 equals the division of the random numbers

	m_choice = Multi_Choice(answer, d_level, fout);	// Gives multiple choice function answer and sets the functions output to m_choice

	cout << endl << endl;
}