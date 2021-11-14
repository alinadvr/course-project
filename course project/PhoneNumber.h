#pragma once
#include <string>
#include <fstream>

#define N 3

class PhoneNumber
{
private:
	int num, operatorN, first, last = 0, sumOne = 0, randOperator;
	string name, surname, patronymic, cellOperator, numberStr;
	ifstream fName, fSurname, fPatronymic, fcellOperator;
	int kyivstar[N] = { 68, 98, 97 };
	int vodafon[N] = { 95, 99, 66 };
	int life[N] = { 63, 93, 73 };

public:
	PhoneNumber* next = 0, * previous = 0;
	static int sumAll;

private:
	int funcRandOperator(int mas[], int operatorN);
	void sumOneNumb();

public:
	PhoneNumber();
	void print();
	void newNumber();
	string printInFile();
	string getName();
	string getSurname();
	string getPatronymic();
	string getCellOperator();

};
