#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

#ifdef PHONENUMBER_HPP
#endif // PHONENUMBER_HPP
#define PHONENUMBER_HPP

using namespace std; 

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

public:
	PhoneNumber();
	void print();
	void newNumber();
	string printInFile();
	string getName();
	string getSurname();
	string getPatronymic();
	string getCellOperator();

private:
	int funcRandOperator(int mas[], int operatorN);
	void sumOneNumb();

};

