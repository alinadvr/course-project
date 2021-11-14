#pragma once
#include <iostream>
#include <string>
#include <fstream>

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

private:
	int funcRandOperator(int mas[], int operatorN) {
		int randChs;
		randChs = rand() % 3;
		for (int i = 0; i <= randChs; i++) {
			operatorN = mas[i];
		}
		return operatorN;
	}

	void sumOneNumb() {
		numberStr = to_string(operatorN) + to_string(first) + to_string(last);
		for (int i = 0; i < numberStr.length(); i++) {
			sumOne += numberStr.at(i) - '0';
		}
	}

public:
	PhoneNumber() {
		fName.open("name.txt");
		fSurname.open("surname.txt");
		fPatronymic.open("patronymic.txt");
		fcellOperator.open("cellOperator.txt");

		int randName = rand() % 20 + 1;
		for (int i = 0; i < randName; i++)
		{
			fName >> name;
		}
		int randSurname = rand() % 20 + 1;
		for (int i = 0; i < randSurname; i++)
		{
			fSurname >> surname;
		}
		int randPatronymic = rand() % 20 + 1;
		for (int i = 0; i < randPatronymic; i++)
		{
			fPatronymic >> patronymic;
		}

		randOperator = (rand() % 10) % 3 + 1;
		for (int i = 0; i < randOperator; i++) {
			fcellOperator >> cellOperator;
		}

		switch (randOperator) {
		case 1: operatorN = funcRandOperator(kyivstar, operatorN);
			break;
		case 2: operatorN = funcRandOperator(vodafon, operatorN);
			break;
		case 3: operatorN = funcRandOperator(life, operatorN);
			break;
		}
		first = rand() % 900 + 100;
		int i = 1000;
		while (i >= 1) {
			last += rand() % 10 * i;
			i /= 10;
		}

		fName.close();
		fSurname.close();
		fPatronymic.close();
		fcellOperator.close();

		sumOneNumb();
	}

	void print() {
		cout << num << ". " << surname << " " << name << " " << patronymic << endl
			<< cellOperator << endl
			<< "0" << operatorN << first << last << endl
			<< "Сумма номера: " << sumOne << "\n\n";
	}

	void newNumber() {
		if (previous == 0)
		{
			num = 1;
		}
		else {
			num = previous->num + 1;
		}
	}

	string printInFile() {
		return to_string(num) + ". " + surname + " " + name + " " + patronymic + "\n"
			+ cellOperator + "\n"
			+ "0" + to_string(operatorN) + to_string(first) + to_string(last) + "\n"
			+ "Сумма номера: " + to_string(sumOne);
	}

	string getName() {
		return name;
	}

	string getSurname() {
		return surname;
	}

	string getPatronymic() {
		return patronymic;
	}

	string getCellOperator() {
		return cellOperator;
	}
};

