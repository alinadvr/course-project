#include "PhoneNumber.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

int PhoneNumber::sumAll = 0;

void checkAvailability(int availabilityValue) {
	if (availabilityValue == 0) {
		cout << "Ошибка: Такого элемента не существует";
	}
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int quantity = 0, availabilityValue = 0;
	char chsMenu, chsFiltr;
	string userFiltr;
	ofstream fillObj;
	COORD coordinate;
	PhoneNumber* head = 0, * now = 0, * last = 0, * nextToNow = 0;

	do {
		cout << "Введите количество экземпляров: ";
		cin >> quantity;
	} while (quantity > 20 || quantity < 0);
	system("cls");

	for (int i = 0; i < quantity; i++) {
		PhoneNumber* new_obj = new PhoneNumber();

		if (head == 0) head = new_obj;
		else {
			last->next = new_obj;
			new_obj->previous = last;
		}
		last = new_obj;
		last->newNumber();
		PhoneNumber::sumAll += last->getSumOne();
	}

	do {
		cout << "1 - Вывод всех экземпляров по порядку\n2 - Вывод всех экземпляров в обратном порядке\n3 - Вывод одного экземпляра по номеру\n"
			<< "4 - Вывод всех экземпляров по алфавиту\n5 - Вывод экземпляра по фильтру\n6 - Запись информации обо всех экземпляров в файл\n"
			<< "7 - Добавить экземпляр\n8 - Удалить экземпляр\n9 - Узнать информацию об авторе\n0 - Выход из программмы\n";
		chsMenu = _getch();
		
		switch (chsMenu) {
		case 72: 
			//up
			coordinate.Y++;
			break;
		case 80:
			//down
			coordinate.Y--;
			break;
		case 13: 
			//enter
			break;
		case '1':
			system("cls");
			now = head;
			while (now) {
				now->print();
				now = now->next;
			}
			break;
		case '2':
			system("cls");
			now = last;
			while (now) {
				now->print();
				now = now->previous;
			}
			break;
		case '3':
			system("cls");
			now = head;
			int numElement;
			cout << "Какой элемент вывести?(всего " << quantity << ")\n";
			cin >> numElement;
			system("cls");
			if (numElement <= quantity && numElement > 0) {
				for (int i = 1; i < numElement; i++) {
					now = now->next;
				}
				now->print();
			}
			else {
				cout << "Ошибка: Такого элемента не существует";
			}
			break;
		case '4': {
			system("cls");
			int num;
			string* names = new string[quantity];
			int* numbers = new int[quantity];

			now = head;
			for (int i = 0; i < quantity; i++) {
				names[i] = now->getSurname() + " " + now->getName() + " " + now->getPatronymic();
				numbers[i] = now->getNumber();
				now = now->next;
			}

			for (int i = 0; i < quantity - 1; i++) {
				for (int j = 0; j < quantity - 1; j++)
				{
					int result = names[j].compare(names[j + 1]);
					if (result == 1) {
						string temp = names[j];
						names[j] = names[j + 1];
						names[j + 1] = temp;

						int num = numbers[j];
						numbers[j] = numbers[j + 1];
						numbers[j + 1] = num;
					}
				}
			}

			for (int i = 0; i < quantity; i++) {
				now = head;
				while (now) {
					if (now->getNumber() == numbers[i]) {
						now->print();
					}
					now = now->next;
				}
			}
			break;
		}
		case '5':
			system("cls");
			cout << "1 - имя\n2 - фамилия\n3 - отчество\n4 - оператор\n";
			chsFiltr = _getch();
			system("cls");
			switch (chsFiltr) {
			case '1': 
				cout << "Введите имя: ";
				cin >> userFiltr;
				system("cls");
				now = head;
				while (now)
				{
					if (now->getName() == userFiltr)
					{
						now->print();
						availabilityValue++;
					}
					now = now->next;
				}
				checkAvailability(availabilityValue);
				break;
			case '2':
				cout << "Введите фамилию: ";
				cin >> userFiltr;
				system("cls");
				now = head;
				while (now)
				{
					if (now->getSurname() == userFiltr)
					{
						now->print();
						availabilityValue++;
					}
					now = now->next;
				}
				checkAvailability(availabilityValue);
				break;
			case '3':
				cout << "Введите отчество: ";
				cin >> userFiltr;
				system("cls");
				now = head;
				while (now)
				{
					if (now->getPatronymic() == userFiltr)
					{
						now->print();
						availabilityValue++;
					}
					now = now->next;
				}
				checkAvailability(availabilityValue);
				break;
			case '4':
				cout << "Введите оператор(Kyivstar, Vodafon, Life): ";
				cin >> userFiltr;
				system("cls");
				now = head;
				while (now)
				{
					if (now->getCellOperator() == userFiltr)
					{
						now->print();
						availabilityValue++;
					}
					now = now->next;
				}
				checkAvailability(availabilityValue);
				break;
			}
			break;
		case '6':
			system("cls");
			fillObj.open("objects.txt");

			now = head;
			while (now)
			{
				fillObj << now->printInFile();
				fillObj << "\n";
				now = now->next;
			}
			cout << "Елементы успешно записаны в файл";

			fillObj.close();
			break;
		case '7': 
			system("cls");
			now = head;
			cout << "На какое место вставить элемент?(всего " << quantity << ")\n";
			cin >> numElement;
			if (numElement < 1 || numElement > quantity + 1)
			{
				cout << "Ошибка: Вы вышли за пределы списка";
				break;
			}
			if (numElement == 1) {
				PhoneNumber* new_obj = new PhoneNumber();
				PhoneNumber::sumAll += new_obj->getSumOne();
				new_obj->next = head;
				head->previous = new_obj;
				head = new_obj;
			}
			else if (numElement == quantity + 1) {
				PhoneNumber* new_obj = new PhoneNumber();
				PhoneNumber::sumAll += new_obj->getSumOne();
				last->next = new_obj;
				new_obj->previous = last;
				last = new_obj;
			}
			else {
				PhoneNumber* new_obj = new PhoneNumber();
				PhoneNumber::sumAll += new_obj->getSumOne();
				for (int i = 1; i < numElement - 1; i++) {
					now = now->next;
				}
				nextToNow = now->next;

				now->next = new_obj;
				new_obj->next = nextToNow;

				nextToNow->previous = new_obj;
				new_obj->previous = now;
			}
			quantity++;
			now = head;
			while (now) {
				now->newNumber();
				now = now->next;
			}
			cout << "Елемент успешно добавлен";
			break;
		case '8':
			system("cls");
			now = head;
			cout << "Какой элемент удалить?(всего " << quantity << ")\n";
			cin >> numElement;
			if (numElement < 1 || numElement > quantity)
			{
				cout << "Ошибка: Вы вышли за пределы списка";
				break;
			}
			else if (numElement == 1) {
				PhoneNumber::sumAll -= head->getSumOne();
				nextToNow = head->next;
				delete head;
				head = nextToNow;
			}
			else if (numElement == quantity) {
				PhoneNumber::sumAll -= last->getSumOne();
				now = last->previous;
				delete last;
				last = now;
				last->next = 0;
			}
			else {
				for (int i = 1; i < numElement - 1; i++) {
					now = now->next;
				}
				PhoneNumber::sumAll -= nextToNow->getSumOne();
				nextToNow = now->next;
				now->next = nextToNow->next;
				delete nextToNow;
				nextToNow = now->next;
				nextToNow->previous = now;
			}
			quantity--;
			now = head;
			while (now) {
				now->newNumber();
				now = now->next;
			}
			cout << "Елемент успешно удален";
			break;
		case '9': 
			system("cls");
			cout << "Автор курсового проекта: Дворянникова Алина Александровна\nСтудентка группы ОПК - 319";
			break;
		}

		if (chsMenu != '0' && chsMenu < '10') {
			cout << "\n\nДля продолжения нажмите любую клавишу";
			_getch();
			system("cls");
		}
		
	} while (chsMenu != '0');
}