#include "PhoneNumber.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

void main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));

	int quantity = 0, chsFiltr;
	char chsMenu;
	string userFiltr;
	ofstream fillObj;
	COORD coordinate;
	PhoneNumber* head = 0, * now = 0, * last = 0, * nextToNow = 0;

	do {
		cout << "������� ���������� �����������: ";
		cin >> quantity;
	} while (quantity > 20 || quantity < 0);
	string* arrSurname = new string[quantity];
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
	}

	do {
		cout << "1 - ����� ���� ����������� �� �������\n2 - ����� ���� ����������� � �������� �������\n3 - ����� ������ ���������� �� ������\n"
			<< "4 - ����� ���� ����������� �� ��������\n5 - ����� ���������� �� �������\n6 - ������ ���������� ��� ���� ����������� � ����\n"
			<< "7 - �������� ���������\n8 - ������� ���������\n9 - ������ ���������� �� ������\n0 - ����� �� ����������\n";
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
			cout << "����� ������� �������?(����� " << quantity << ")\n";
			cin >> numElement;
			system("cls");
			if (numElement <= quantity && numElement > 0) {
				for (int i = 1; i < numElement; i++) {
					now = now->next;
				}
				now->print();
			}
			else {
				cout << "������: ������ �������� �� ����������\n\n";
			}
			break;
		case '4': {
			system("cls");
			now = head;
			PhoneNumber* headCopy = 0, * nowCopy = now;

			for (int i = 0; i < quantity; i++) {
				for (int j = 0; j < quantity - 1; j++) {
					if (now->getSurname() < nowCopy->getSurname()) {
						nowCopy = now;
					}
					else if (now->getSurname() == nowCopy->getSurname()) {
						if (now->getName() < nowCopy->getName()) {
							nowCopy = now;
						}
						else if (now->getName() == nowCopy->getName()) {
							if (now->getPatronymic() < nowCopy->getPatronymic()) {
								nowCopy = now;
							}
							else if (now->getPatronymic() == nowCopy->getPatronymic()) {
								nowCopy = now;
							}
						}
					}
					now = now->next;
				}
				if (headCopy == 0) {
					headCopy = nowCopy;
				}
				nowCopy = nowCopy->next;
			}

			nowCopy = headCopy;
			while (nowCopy) {
				nowCopy->print();
				nowCopy = nowCopy->next;
			}
			break;
		}
		case '5':
			system("cls");
			cout << "1 - ���\n2 - �������\n3 - ��������\n4 - ��������\n";
			cin >> chsFiltr;
			//system("cls");
			switch (chsFiltr) {
			case 1:
				cout << "������� ���: ";
				cin >> userFiltr;
				cout << userFiltr << endl;
				now = head;
				while (now)
				{
					if (now->getName() == userFiltr)
					{
						now->print();
					}
					now = now->next;
				}
				break;
			case 2:
				cout << "������� �������: ";
				cin >> userFiltr;
				now = head;
				while (now)
				{
					if (now->getSurname() == userFiltr)
					{
						now->print();
					}
					now = now->next;
				}
				break;
			case 3:
				cout << "������� ��������: ";
				cin >> userFiltr;
				now = head;
				while (now)
				{
					if (now->getPatronymic() == userFiltr)
					{
						now->print();
					}
					now = now->next;
				}
				break;
			case 4:
				cout << "������� ��������: ";
				cin >> userFiltr;
				now = head;
				while (now)
				{
					if (now->getCellOperator() == userFiltr)
					{
						now->print();
					}
					now = now->next;
				}
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
			cout << "�������� ������� �������� � ����\n\n";

			fillObj.close();
			break;
		case '7': 
			system("cls");
			now = head;
			do {
				cout << "�� ����� ����� �������� �������?(����� " << quantity << ")\n";
				cin >> numElement;
				if (numElement < 1 || numElement > quantity + 1)
				{
					cout << "������: �� ����� �� ������� ������\n��� ���������� ����� ������� enter";
					_getch();
					system("cls");
				}
			} while (numElement < 1 || numElement > quantity + 1);
			if (numElement == 1) {
				PhoneNumber* new_obj = new PhoneNumber();
				new_obj->next = head;
				head->previous = new_obj;
				head = new_obj;
			}
			else if (numElement == quantity + 1) {
				PhoneNumber* new_obj = new PhoneNumber();
				last->next = new_obj;
				new_obj->previous = last;
				last = new_obj;
			}
			else {
				PhoneNumber* new_obj = new PhoneNumber();
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
			cout << "������� ������� ��������\n";
			break;
		case '8':
			system("cls");
			now = head;
			do {
				cout << "����� ������� �������?(����� " << quantity << ")\n";
				cin >> numElement;
				if (numElement < 1 || numElement > quantity)
				{
					cout << "������: �� ����� �� ������� ������\n��� ���������� ����� ������� enter";
					_getch();
					system("cls");
				}
			} while (numElement < 1 || numElement > quantity);
			if (numElement == 1) {
				nextToNow = head->next;
				delete head;
				head = nextToNow;
			}
			else if (numElement == quantity) {
				now = last->previous;
				delete last;
				last = now;
				last->next = 0;
			}
			else {
				for (int i = 1; i < numElement - 1; i++) {
					now = now->next;
				}
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
			cout << "������� ������� ������\n";
			break;
		case '9': 
			system("cls");
			cout << "����� ��������� �������: ������������ ����� �������������\n��������� ������ ��� - 319\n";
			break;
		}


		if (chsMenu != '0' && chsMenu < '10') {
			cout << "��� ����������� ������� ����� �������";
			_getch();
			system("cls");
		}
		else if (chsMenu < '0' || chsMenu > '9') {
			cout << "������: ������ ������������ ����� ����\n��� ����������� ������� ����� �������";
			_getch();
			system("cls");
		}
		
	} while (chsMenu != '0');
}