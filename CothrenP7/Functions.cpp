//A. Noel Cothren
//acothren1@cnm.edu

//File: Functions.cpp

#include "Functions.h"

#include <iostream>		//needed for cout
#include <string>		//needed for string
#include <fstream>		//for ifstream and ofstream
#include <iomanip>		//for setw()
using namespace std;


void WriteHeader()
{
	cout << "\n A. Noel Cothren"
		<< "\n acothren1@cnm.edu"
		<< "\n\n STEM Degrees, Race, and Gender from 2008 - 2016 school years."
		<< "\n\n The National Center for Education Statistics (NCES) is the primary federal entity for collecting and analyzing data related to education in the U.S. and other nations. \n NCES is located within the U.S. Department of Education and the Institute of Education Sciences.";
}

bool ReadData(Dataset& totals, Dataset& males, Dataset& females)
{
	//declare some variables
	string trash;
	string filename = "Data.txt";
	ifstream dataInput;		//input object 

	//open the file
	dataInput.open(filename.c_str());

	//check that we've got the file open
	if (!dataInput)
	{
		cout << "\n Error: Can't find " << filename;
		return false;
	}

	int totalRows = 0;
	do 
	{
		//trash the header
		while (totalRows < 8)
		{
			getline(dataInput, trash);
			totalRows++;
			//this is just to make sure the trash looks right, for dev only
			//cout << "\nHeader: " << trash;
			//cout << "\nTotal Rows: " << totalRows;
		}

		ProcessSection(dataInput, totals, totalRows);
		ProcessSection(dataInput, males, totalRows);
		ProcessSection(dataInput, females, totalRows);
		
	} while (totalRows < 35); //only read the totals all degree types

	//all done reading, close the file
	dataInput.close();

	return true;
}

void ProcessSection(ifstream& dataInput, Dataset& data, int& totalRows)
{
	string trash, temp;
	char comma = ',';
	//fill arrays with nested loops
	for (int row = 0; row < 5; row++)
	{
		//first we want to store the years
		dataInput >> data.years[row];

		//ignore the extra and trash the rest up to comma
		dataInput.ignore();
		getline(dataInput, trash, comma);

		//Debugging/watch the fun
		//cout << "\n Row # " << row << " YEAR: " << data.years[row];

		// next we want the related data columns...
		for (int col = 0; col < 18; ++col)
		{
			//read up to the comma into a temporary string, then save & convert to int
			getline(dataInput, temp, comma);
			data.degrees[row][col] = atoi(temp.c_str());

			//debugging/watch the fun
			//cout << "\n          Col # " << setw(2) << col << "  : " << setw(6) << data.degrees[row][col] << "  Temp: " << setw(6) << temp;
		}
		getline(dataInput, trash);
		totalRows++;
		
	}
	dataInput >> trash;
	dataInput.ignore();
	for (int rowsB = 0; rowsB < 4; rowsB++)
	{
		//save the data, add 5 to row num because we already saved 4 rows above
		dataInput >> data.years[rowsB+5];

		//ignore the extra and trash the rest up to comma
		dataInput.ignore();
		getline(dataInput, trash, comma);

		//Debugging/watch the fun
		//cout << "\n Row # " << rowsB+5 << " YEAR: " << data.years[rowsB+5];
		//cout << "\n [years] trash = " << trash;

		// next we want the related data columns...
		for (int col = 0; col < 18; ++col)
		{
			//read up to the comma into a temporary string, then save & convert to int
			getline(dataInput, temp, comma);
			data.degrees[rowsB+5][col] = atoi(temp.c_str());

			//debugging/watch the fun
			//cout << "\n          Col # " << setw(2) << col << "  : " << setw(6) << data.degrees[rowsB+5][col] << "  Temp: " << setw(6) << temp;
		}
		getline(dataInput, trash);
		totalRows++;
	}
	dataInput >> trash;
	dataInput >> trash;
	cout << "\n";
	dataInput.ignore();

	return;
}

string CalcTotalDifference(Dataset& totals, Dataset& males, Dataset& females)
{
	//vars
	int degreesMale08 = males.degrees[0][0], degreesFemale08 = females.degrees[0][0], degreesTotal08 = totals.degrees[0][0];
	int degreesMale16 = males.degrees[8][0], degreesFemale16 = females.degrees[8][0], degreesTotal16 = totals.degrees[8][0];
	double percentMale08, percentMale16, percentFemale08, percentFemale16, percentDiff08, percentDiff16;
	
	
	//calculate the difference in 2008-09 year
	percentMale08 = ( degreesMale08 / degreesTotal08 ) / 100; //should be 69.7163862
	percentFemale08 = (degreesFemale08 / degreesTotal08 ) / 100; //should be 30.2836138
	percentDiff08 = percentMale08 - percentFemale08;

	//calculate the difference in 2016-17 school year
	percentMale16 = (degreesMale16 / degreesTotal16) / 100; //should be 69.7163862
	percentFemale16 = (degreesFemale16 / degreesTotal16) / 100; //should be 30.2836138
	percentDiff16 = percentMale16 - percentFemale16;

	//create a stringstream to summarize the info
	stringstream ss;
	ss.precision(2);
	ss.setf(ios::fixed || ios::showpoint);

	//print the results 2008-09
	ss << "\n TOTAL DEGREES 2008-09"
	 << "\n Overall total: " << totals.degrees[0][0]
	 << "\n Males: " << males.degrees[0][0]
	 << "\n Females: " << females.degrees[0][0]
	 << "\n\n PERCENTAGE OF TOTAL DEGREES BY GENDER 2008-09"
	 << "\n Males: " << percentMale08 << "%"
	 << "\n Females: " << percentFemale08 << "%"
	 << "\n Percent Difference: " << percentDiff08 << "%";

	//print the results 2016-17
	ss << "\n\n TOTAL DEGREES 2016-17"
		<< "\n Overall total: " << totals.degrees[8][0]
		<< "\n Males: " << males.degrees[8][0]
		<< "\n Females: " << females.degrees[8][0]
		<< "\n\n PERCENTAGE OF TOTAL DEGREES BY GENDER 2016-17"
		<< "\n Males: " << percentMale16 << "%"
		<< "\n Females: " << percentFemale16 << "%"
		<< "\n Percent Difference: " << percentDiff16 << "%";

	//convert ss to a string, cout string, return it
	string report = ss.str();
	cout << report;
	return report;
}

string CalcRaceDifferences(Dataset& totals, Dataset& males, Dataset& females)
{
	//	3. What differences can be observed by race / ethnicity in regards to the gender gap in STEM ?
	//	Same as above, but for each year and each ethnicity, cout Gender + Race + % .Determine which is the max difference and min difference, and show those.  ASC order of %

	return string();
}

bool WriteReport(Dataset& totals, Dataset& males, Dataset& females)
{
	//string filename;
	//ofstream output;
	//output.open((filename).c_str());
	//if (!output) return false;
	//output << "\n Thanks for trying our mortgage calculator.\n Here are the details of your mortgage: \n\n" << result;
	////close output file
	//output.close();
	//cout << "\nTOTAL " << setw(10) << " YEARS " << setw(10) << "Degrees Total" << endl;
	//cout << "\n      " << setw(10) << " totals.years[0] " << setw(10) << totals.degrees[0][0] << endl;
	//cout << "\n          Col # " << setw(2) << col << "  : " << setw(6) << data.degrees[rowsB+5][col] << "  Temp: " << setw(6) << temp;
	cout << "\n\n REPORT";
	cout << "\n Totals: " << totals.degrees[0][0];
	cout << "\n Males: " << males.degrees[0][0];
	cout << "\n Females: " << females.degrees[0][0];
	//string openfile = "notepad.exe " + filename;
	//system(openfile.c_str());
	return true;
}

