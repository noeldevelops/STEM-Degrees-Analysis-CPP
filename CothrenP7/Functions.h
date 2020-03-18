//A. Noel Cothren
//acothren1@cnm.edu

//File: Functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>	//needed here for string
#include <sstream>
using namespace std;

//Data Struct
//2D arrays: dataType arrayName [num rows][num col]
struct Dataset 
{
	int degrees[20][50];
	string years[20];
};

//Function Prototypes
void WriteHeader();
bool ReadData(Dataset& totals, Dataset& males, Dataset& females);
void ProcessSection(ifstream& dataInput, Dataset& data, int& totalRows);
string CalcTotalDifference(Dataset& totals, Dataset& males, Dataset& females);
string CalcRaceDifferences(Dataset& totals, Dataset& males, Dataset& females);
bool WriteReport(Dataset& totals, Dataset& males, Dataset& females);

#endif