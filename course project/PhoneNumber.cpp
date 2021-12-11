#include "PhoneNumber.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

PhoneNumber::PhoneNumber() {
	fName.open("name.txt");
	fSurname.open("surname.txt");
	fPatronymic.open("patronymic.txt");
	fcellOperator.open("cellOperator.txt");

	name = randValueFromFile(fName);
	surname = randValueFromFile(fSurname);
	patronymic = randValueFromFile(fPatronymic);

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
	createNumber();

	fName.close();
	fSurname.close();
	fPatronymic.close();
	fcellOperator.close();

	sumOneNumb();
}

void PhoneNumber::print() {
	cout << num << ". " << surname << " " << name << " " << patronymic << endl
		<< cellOperator << endl
		<< "0" << operatorN << first << last << endl
		<< "Сумма номера: " << sumOne << "\n\n";
}

void PhoneNumber::newNumber() {
	if (previous == 0)
	{
		num = 1;
	}
	else {
		num = previous->num + 1;
	}
}

string PhoneNumber::printInFile() {
	return to_string(num) + ". " + surname + " " + name + " " + patronymic + "\n"
		+ cellOperator + "\n"
		+ "0" + to_string(operatorN) + to_string(first) + to_string(last) + "\n"
		+ "Сумма номера: " + to_string(sumOne) + "\n";
}

string PhoneNumber::getName() {
	return name;
}

void PhoneNumber::setName(string value) {
	name = value;
}

string PhoneNumber::getSurname() {
	return surname;
}

void PhoneNumber::setSurname(string value) {
	surname = value;
}

string PhoneNumber::getPatronymic() {
	return patronymic;
}

void PhoneNumber::setPatronymic(string value) {
	patronymic = value;
}

string PhoneNumber::getCellOperator() {
	return cellOperator;
}

int PhoneNumber::getNumber() {
	return num;
}

int PhoneNumber::getSumOne() {
	return sumOne;
}

int PhoneNumber::funcRandOperator(int mas[], int operatorN) {
	int randChs = rand() % 3;
	for (int i = 0; i <= randChs; i++) {
		operatorN = mas[i];
	}
	return operatorN;
}

void PhoneNumber::sumOneNumb() {
	numberStr = to_string(operatorN) + to_string(first) + to_string(last);
	for (int i = 0; i < numberStr.length(); i++) {
		sumOne += numberStr.at(i) - '0';
	}
}

void PhoneNumber::aboutAuthor() {
	cout << "Автор курсового проекта: Дворянникова Алина Александровна\nСтудентка группы ОПК - 319\n\n";
}

void PhoneNumber::setCellOperator(string newCellOperator)
{
	cellOperator = newCellOperator;
}

void PhoneNumber::setOperatorNumber(int chsOperator)
{
	switch (chsOperator) {
	case 0:
		operatorN = funcRandOperator(kyivstar, operatorN);
		break;
	case 1:
		operatorN = funcRandOperator(vodafon, operatorN);
		break;
	case 2:
		operatorN = funcRandOperator(life, operatorN);
		break;
	}
}

void PhoneNumber::createNumber() {
	first = rand() % 900 + 100;
	int i = 1000;
	while (i >= 1) {
		last += rand() % 10 * i;
		i /= 10;
	}
}

void PhoneNumber::setSumOneNumber()
{
	sumOne = 0;
	sumOneNumb();
}

string PhoneNumber::randValueFromFile(ifstream &fValue) {
	string value;
	int randValue = rand() % 20 + 1;
	for (int i = 0; i < randValue; i++)
	{
		fValue >> value;
	}
	return value;
}
