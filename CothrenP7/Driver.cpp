//A. Noel Cothren
//acothren1@cnm.edu

//File: Driver.cpp

#include <iostream>
#include <string>
#include <iomanip>		//for setw()
using namespace std;

#include "Functions.h"

int main()
{
	string raceHeader[8] = { "Total","White","Black","Hispanic","Asian / Pacific Islander","American Indian / Alaska Native","Two or more races","Non-resident alien" };
	string goOn;
	Dataset totals, males, females;
	WriteHeader();
	do
	{
		bool bRead = ReadData(totals, males, females);

		//call analyze functions & pass data to them
		string totalsCalc = CalcTotalDifference(totals, males, females);
		//call write function
		//bool bWritten = WriteReport(totals, males, females);
		cout << "\nWanna see it again? Type y or n     ";
		cin >> goOn;
	} while (goOn == "y");
	
	cout << "\nGoodbye!";

	return 0;
}