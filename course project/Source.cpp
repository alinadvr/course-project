#include "PhoneNumber.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

int PhoneNumber::sumAll = 0;

void setCursor(int y) {
	COORD c = { 0, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int selectItemCursor(int quantityMenuItem) {
	int y = 0;
	char chsValue;
	setCursor(y);
	do {
		chsValue = _getch();
		if (chsValue == 72) {
			if (y > 0) {
				y--;
			}
		}
		else if (chsValue == 80) {
			if (y < quantityMenuItem) {
				y++;
			}
		}
		setCursor(y);
	} while (chsValue != 13);
	return y;
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	int quantity = 0, quantityMenuItem, y = 0;
	string userFiltr;
	ofstream fillObj;
	PhoneNumber* head = 0, * now = 0, * last = 0, * nextToNow = 0;

	do {
		cout << "������� ���������� �����������(�� 20): ";
		cin >> quantity;
		if (quantity > 20 || quantity < 1) {
			cout << "������: �� ����� ������������ ���������� �����������\n���������� ����� �� 1 �� 20\n\n";
		}
	} while (quantity > 20 || quantity < 1);
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
		cout << "� ����� ���� ����������� �� �������\n� ����� ���� ����������� � �������� �������\n� ����� ������ ���������� �� ������\n"
			<< "� ����� ���� ����������� �� ��������\n� ����� ���������� �� �������\n� ������ ���������� ��� ���� ����������� � ����\n"
			<< "� �������� ���������\n� ������� ���������\n� ������� ���������\n� ������ ���������� �� ������\n� ����� �� ����������\n";
		quantityMenuItem = 10;
		y = selectItemCursor(quantityMenuItem);
		switch (y) {
		case 0:
			system("cls");
			now = head;
			if (quantity == 0) {
				cout << "������ ������\n\n";
			}
			else {
				while (now) {
					now->print();
					now = now->next;
				}
				cout << "����� ���� �������: " << now->sumAll << "\n\n";
			}
			break;
		case 1:
			system("cls");
			now = last;
			if (quantity == 0) {
				cout << "������ ������\n\n";
			}
			else {
				while (now) {
					now->print();
					now = now->previous;
				}
				cout << "����� ���� �������: " << now->sumAll << "\n\n";
			}
			break;
		case 2:
			system("cls");
			now = head;
			int numElement;
			if (quantity == 0) {
				cout << "������ ������\n\n5";
			}
			else {
				cout << "����� ������� �������?(����� " << quantity << ")\n";
				cin >> numElement;
				system("cls");
				if (numElement <= quantity && numElement > 0) {
					for (int i = 1; i < numElement; i++) {
						now = now->next;
					}
					now->print();
					cout << "����� ���� �������: " << now->sumAll << "\n\n";
				}
				else {
					cout << "������: ������ �������� �� ����������\n\n";
				}
			}
			break;
		case 3: {
			system("cls");
			int num;
			string* names = new string[quantity];
			int* numbers = new int[quantity];

			if (quantity == 0) {
				cout << "������ ������\n\n";
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
				cout << "����� ���� �������: " << now->sumAll << "\n\n";
			}
			break;
		}
		case 4:
			system("cls");
			if (quantity == 0) {
				cout << "������ ������\n\n";
			}
			else {
				cout << "� ���\n� �������\n� ��������\n� ��������\n";
				quantityMenuItem = 3;
				y = selectItemCursor(quantityMenuItem);
				now = head;
				system("cls");
				quantityMenuItem = -1;
				while (now)
				{
					switch (y) {
					case 0:
						cout << "� " << now->getName() << endl;
						break;
					case 1:
						cout << "� " << now->getSurname() << endl;
						break;
					case 2:
						cout << "� " << now->getPatronymic() << endl;
						break;
					case 3:
						cout << "� " << now->getCellOperator() << endl;
						break;
					}
					now = now->next;
					quantityMenuItem++;
				}
				y = selectItemCursor(quantityMenuItem);
				now = head;
				system("cls");
				for (int i = 0; i != y; i++)
				{
					now = now->next;
				}
				now->print();
				cout << "����� ���� �������: " << now->sumAll << "\n\n";
			}
			break;
		case 5:
			system("cls");
			if (quantity == 0) {
				cout << "������ ������\n\n";
			}
			else {
				fillObj.open("objects.txt");
				now = head;
				while (now)
				{
					fillObj << now->printInFile();
					now = now->next;
				}
				fillObj << "����� ���� �������: " << to_string(now->sumAll);
				cout << "�������� ������� �������� � ����\n\n";
				fillObj.close();
			}
			break;
		case 6: {
			system("cls");
			now = head;
			cout << "�� ����� ����� �������� �������?(����� " << quantity << ")\n";
			cin >> numElement;
			if (numElement < 1 || numElement > quantity + 1)
			{
				cout << "������: �� ����� �� ������� ������\n\n";
				break;
			}
			PhoneNumber* new_obj = new PhoneNumber();
			PhoneNumber::sumAll += new_obj->getSumOne();
			if (numElement == 1) {
				if (quantity == 0) {
					head = new_obj;
					head->previous = 0;
				}
				else {
					new_obj->next = head;
					head->previous = new_obj;
					head = new_obj;
				}
			}
			else if (numElement == quantity + 1) {
				last->next = new_obj;
				new_obj->previous = last;
				last = new_obj;
			}
			else {
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
			cout << "������� ������� ��������\n\n";
			break;
		}
		case 7:
			system("cls");
			now = head;
			if (quantity == 0) {
				cout << "������ ������\n\n";
			}
			else {
				cout << "����� ������� �������?(����� " << quantity << ")\n";
				cin >> numElement;
				if (numElement < 1 || numElement > quantity)
				{
					cout << "������: �� ����� �� ������� ������\n\n";
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
				cout << "������� ������� ������\n\n";
			}
			break;
		case 8: {
			int chsOperator;
			system("cls");
			if (quantity == 0) {
				cout << "������ ������\n\n";
			}
			else {
				now = head;
				while (now) {
					cout << now->getNumber() << ". " << now->getSurname() << " " << now->getName() << " - " << now->getCellOperator() << endl;
					now = now->next;
				}
				now = head;
				quantityMenuItem = 0;
				while (now) {
					quantityMenuItem++;
					now = now->next;
				}
				y = selectItemCursor(quantityMenuItem);
				system("cls");
				cout << "� Kyivstar\n� Vodafon\n� Life";
				quantityMenuItem = 2;
				chsOperator = selectItemCursor(quantityMenuItem);
				now = head;
				for (int i = 0; i != y; i++) {
					now = now->next;
				}
				PhoneNumber::sumAll -= now->getSumOne();
				switch (chsOperator) {
				case 0:
					now->setCellOperator("Kyivstar");
					break;
				case 1:
					now->setCellOperator("Vodafon");
					break;
				case 2:
					now->setCellOperator("Life");
					break;
				}
				now->setOperatorNumber(chsOperator);
				now->setSumOneNumber();
				PhoneNumber::sumAll += now->getSumOne();
				system("cls");
				cout << "���� ������ ������� ��������\n\n";
				now->print();
			}
			break;
		}
		case 9:
			system("cls");
			PhoneNumber::aboutAuthor();
			break;
		case 10:
			system("cls");
			cout << "�������, ��� ��������������� ���� �����������\n\n";
			break;
		}

		if (y < 10) {
			cout << "��� ����������� ������� ����� �������";
			_getch();
			system("cls");
		}
		
	} while (y != 10);
}