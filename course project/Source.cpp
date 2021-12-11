#include "PhoneNumber.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

int PhoneNumber::sumAll = 0, PhoneNumber::quantity = 0;

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

	int quantityMenuItem, y = 0, chsOperator;
	string userFiltr;
	ofstream fillObj;
	PhoneNumber* head = 0, * now = 0, * last = 0, * nextToNow = 0;

	do {
		cout << "Введите количество экземпляров(до 20): ";
		cin >> PhoneNumber::quantity;
		if (PhoneNumber::PhoneNumber::quantity > 20 || PhoneNumber::PhoneNumber::quantity < 1) {
			cout << "Ошибка: Вы ввели некорректное количество экземпляров\nПопробуйте снова от 1 до 20\n\n";
		}
	} while (PhoneNumber::quantity > 20 || PhoneNumber::quantity < 1);
	system("cls");

	for (int i = 0; i < PhoneNumber::quantity; i++) {
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
			<< "· Добавить экземпляр\n· Удалить экземпляр\n· Сменить оператора\n· Узнать информацию об авторе\n· Выход из программмы\n";
		quantityMenuItem = 10;
		y = selectItemCursor(quantityMenuItem);
		switch (y) {
		case 0:
			system("cls");
			now = head;
			if (PhoneNumber::quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				while (now) {
					now->print();
					now = now->next;
				}
				cout << "Сумма всех номеров: " << now->sumAll << "\n\n";
			}
			break;
		case 1:
			system("cls");
			now = last;
			if (PhoneNumber::quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				while (now) {
					now->print();
					now = now->previous;
				}
				cout << "Сумма всех номеров: " << now->sumAll << "\n\n";
			}
			break;
		case 2:
			system("cls");
			now = head;
			int numElement;
			if (PhoneNumber::quantity == 0) {
				cout << "Список пустой\n\n5";
			}
			else {
				cout << "Какой элемент вывести?(всего " << PhoneNumber::quantity << ")\n";
				cin >> numElement;
				system("cls");
				if (numElement <= PhoneNumber::quantity && numElement > 0) {
					for (int i = 1; i < numElement; i++) {
						now = now->next;
					}
					now->print();
					cout << "Сумма всех номеров: " << now->sumAll << "\n\n";
				}
				else {
					cout << "Ошибка: Такого элемента не существует\n\n";
				}
			}
			break;
		case 3: {
			system("cls");
			int num;
			string* names = new string[PhoneNumber::quantity];
			int* numbers = new int[PhoneNumber::quantity];

			if (PhoneNumber::quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				now = head;
				for (int i = 0; i < PhoneNumber::quantity; i++) {
					names[i] = now->getSurname() + " " + now->getName() + " " + now->getPatronymic();
					numbers[i] = now->getNumber();
					now = now->next;
				}

				for (int i = 0; i < PhoneNumber::quantity - 1; i++) {
					for (int j = 0; j < PhoneNumber::quantity - 1; j++)
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

				for (int i = 0; i < PhoneNumber::quantity; i++) {
					now = head;
					while (now) {
						if (now->getNumber() == numbers[i]) {
							now->print();
						}
						now = now->next;
					}
				}
				cout << "Сумма всех номеров: " << now->sumAll << "\n\n";
			}
			break;
		}
		case 4: {
			string value;
			system("cls");
			if (PhoneNumber::quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				cout << "· Имя\n· Фамилия\n· Отчество\n· Оператор\n";
				quantityMenuItem = 3;
				y = selectItemCursor(quantityMenuItem);
				system("cls");
				now = head;
				switch (y) {
				case 0:
					cout << "Введите имя: ";
					cin >> value;
					system("cls");
					while (now) {
						if (now->getName() == value) {
							now->print();
						}
						now = now->next;
					}
					break;
				case 1:
					cout << "Введите фамилию: ";
					cin >> value;
					system("cls");
					while (now) {
						if (now->getSurname() == value) {
							now->print();
						}
						now = now->next;
					}
					break;
				case 2:
					cout << "Введите отчество: ";
					cin >> value;
					system("cls");
					while (now) {
						if (now->getPatronymic() == value) {
							now->print();
						}
						now = now->next;
					}
					break;
				case 3:
					cout << "Введите оператор(Kyivstar, Vodafon, Life): ";
					cin >> value;
					system("cls");
					while (now) {
						if (now->getCellOperator() == value) {
							now->print();
						}
						now = now->next;
					}
					break;
				}
				cout << "Сумма всех номеров: " << now->sumAll << "\n\n";
			}
			break;
		}
		case 5:
			system("cls");
			if (PhoneNumber::quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				fillObj.open("objects.txt");
				now = head;
				while (now)
				{
					fillObj << now->printInFile();
					now = now->next;
				}
				fillObj << "Сумма всех номеров: " << to_string(now->sumAll);
				cout << "Елементы успешно записаны в файл\n\n";
				fillObj.close();
			}
			break;
		case 6: {
			system("cls");
			now = head;
			cout << "· Автоматическая инициализация\n· Заполнение в ручную\n";
			quantityMenuItem = 1;
			y = selectItemCursor(quantityMenuItem);
			system("cls");
			cout << "На какое место вставить элемент?(всего " << PhoneNumber::quantity << ")\n";
			cin >> numElement;
			system("cls");
			if (numElement < 1 || numElement > PhoneNumber::quantity + 1)
			{
				cout << "Ошибка: Вы вышли за пределы списка\n\n";
				break;
			}
			PhoneNumber* new_obj = new PhoneNumber();
			if (y == 1) {
				string name, surname, patronymic;
				system("cls");
				cout << "Введите фамилию: ";
				cin >> surname;
				new_obj->setSurname(surname);
				system("cls");
				cout << "Введите имя: ";
				cin >> name;
				new_obj->setName(name);
				system("cls");
				cout << "Введите отчество: ";
				cin >> patronymic;
				new_obj->setPatronymic(patronymic);

				system("cls");

				cout << "· Kyivstar\n· Vodafon\n· Life";
				quantityMenuItem = 2;
				chsOperator = selectItemCursor(quantityMenuItem);
				system("cls");
				switch (chsOperator) {
				case 0:
					new_obj->setCellOperator("Kyivstar");
					break;
				case 1:
					new_obj->setCellOperator("Vodafon");
					break;
				case 2:
					new_obj->setCellOperator("Life");
					break;
				}
				new_obj->setOperatorNumber(chsOperator);
				new_obj->createNumber();
				new_obj->setSumOneNumber();
			}
			PhoneNumber::sumAll += new_obj->getSumOne();
			if (numElement == 1) {
				if (PhoneNumber::quantity == 0) {
					head = new_obj;
					head->previous = 0;
				}
				else {
					new_obj->next = head;
					head->previous = new_obj;
					head = new_obj;
				}
			}
			else if (numElement == PhoneNumber::quantity + 1) {
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
			PhoneNumber::quantity++;
			now = head;
			while (now) {
				now->newNumber();
				now = now->next;
			}
			cout << "Елемент успешно добавлен\n\n";
			break;
		}
		case 7:
			system("cls");
			now = head;
			if (PhoneNumber::quantity == 0) {
				cout << "Список пустой\n\n";
			}
			else {
				cout << "Какой элемент удалить?(всего " << PhoneNumber::quantity << ")\n";
				cin >> numElement;
				if (numElement < 1 || numElement > PhoneNumber::quantity)
				{
					cout << "Ошибка: Вы вышли за пределы списка\n\n";
					break;
				}
				else if (numElement == 1) {
					PhoneNumber::sumAll -= head->getSumOne();
					nextToNow = head->next;
					if (PhoneNumber::quantity == 1) {
						delete head;
						head = 0;
					}
					else {
						delete head;
						head = nextToNow;
						head->previous = 0;
					}
				}
				else if (numElement == PhoneNumber::quantity) {
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
					nextToNow = now->next;
					now->next = nextToNow->next;
					PhoneNumber::sumAll -= nextToNow->getSumOne();
					delete nextToNow;
					nextToNow = now->next;
					nextToNow->previous = now;
				}
				PhoneNumber::quantity--;
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
			if (PhoneNumber::quantity == 0) {
				cout << "Список пустой\n\n";
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
				cout << "· Kyivstar\n· Vodafon\n· Life";
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
				cout << "Ваши данные успешно изменены\n\n";
				now->print();
			}
			break;
		case 9:
			system("cls");
			PhoneNumber::aboutAuthor();
			break;
		case 10:
			system("cls");
			cout << "Спасибо, что воспользовались моим приложением\n\n";
			break;
		}

		if (y < 10) {
			cout << "Для продолжения нажмите любую клавишу";
			_getch();
			system("cls");
		}
		
	} while (y != 10);
}