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
		cout << "Ошибка: Такого элемента не существует\n\n";
	}
}

void setCursor(int y) {
	COORD c = { 0, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int quantity = 0, availabilityValue = 0, y = 0;
	char chsMenu, chsFiltr;
	string userFiltr;
	ofstream fillObj;
	PhoneNumber* head = 0, * now = 0, * last = 0, * nextToNow = 0;

	do {
		cout << "Введите количество экземпляров(до 20): ";
		cin >> quantity;
		if (quantity > 20 || quantity < 0) {
			cout << "Ошибка: Вы ввели слишком много экземпляров\nПопробуйте снова до 20\n\n";
		}
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
		system("cls");
		cout << "· Вывод всех экземпляров по порядку\n· Вывод всех экземпляров в обратном порядке\n· Вывод одного экземпляра по номеру\n"
			<< "· Вывод всех экземпляров по алфавиту\n· Вывод экземпляра по фильтру\n· Запись информации обо всех экземпляров в файл\n"
			<< "· Добавить экземпляр\n· Удалить экземпляр\n· Узнать информацию об авторе\n· Выход из программмы\n";
		y = 0;
		setCursor(y);
		do {
			chsMenu = _getch();
			if (chsMenu == 72) {
				if (y > 0) {
					y--;
				}
			}
			else if (chsMenu == 80) {
				if (y < 9) {
					y++;
				}
			}
			setCursor(y);
		} while (chsMenu != 13);
		
		switch (y) {
		case 0:
			system("cls");
			now = head;
			if (quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				while (now) {
					now->print();
					now = now->next;
				}
			}
			break;
		case 1:
			system("cls");
			now = last;
			if (quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				while (now) {
					now->print();
					now = now->previous;
				}
			}
			break;
		case 2:
			system("cls");
			now = head;
			int numElement;
			if (quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
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
					cout << "Ошибка: Такого элемента не существует\n\n";
				}
			}
			break;
		case 3: {
			system("cls");
			int num;
			string* names = new string[quantity];
			int* numbers = new int[quantity];

			if (quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
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
			}
			break;
		}
		case 4:
			system("cls");
			if (quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
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
			}
			break;
		case 5:
			system("cls");
			if (quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				fillObj.open("objects.txt");
				now = head;
				while (now)
				{
					fillObj << now->printInFile();
					fillObj << "\n";
					now = now->next;
				}
				cout << "Елементы успешно записаны в файл\n\n";
				fillObj.close();
			}
			break;
		case 6: 
			system("cls");
			now = head;
			cout << "На какое место вставить элемент?(всего " << quantity << ")\n";
			cin >> numElement;
			if (numElement < 1 || numElement > quantity + 1)
			{
				cout << "Ошибка: Вы вышли за пределы списка\n\n";
				break;
			}
			if (numElement == 1) {
				if (quantity == 0) {
					PhoneNumber* new_obj = new PhoneNumber();
					PhoneNumber::sumAll += new_obj->getSumOne();
					head = new_obj;
					head->previous = 0;
				}
				else {
					PhoneNumber* new_obj = new PhoneNumber();
					PhoneNumber::sumAll += new_obj->getSumOne();
					new_obj->next = head;
					head->previous = new_obj;
					head = new_obj;
				}
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
			cout << "Елемент успешно добавлен\n\n";
			break;
		case 7:
			system("cls");
			now = head;
			if (quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				cout << "Какой элемент удалить?(всего " << quantity << ")\n";
				cin >> numElement;
				if (numElement < 1 || numElement > quantity)
				{
					cout << "Ошибка: Вы вышли за пределы списка\n\n";
					break;
				}
				else if (numElement == 1) {
					PhoneNumber::sumAll -= head->getSumOne();
					nextToNow = head->next;
					if (quantity == 1) {
						delete head;
						head = 0;
					}
					else {
						delete head;
						head = nextToNow;
						head->previous = 0;
					}
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
				cout << "Елемент успешно удален\n\n";
			}
			break;
		case 8: 
			system("cls");
			cout << "Автор курсового проекта: Дворянникова Алина Александровна\nСтудентка группы ОПК - 319\n\n";
			break;
		case 9:
			system("cls");
			cout << "Спасибо, что воспользовались моим приложением\n\n";
			break;
		}

		if (y < 9) {
			cout << "Для продолжения нажмите любую клавишу";
			_getch();
			system("cls");
		}
		
	} while (y != 9);
}