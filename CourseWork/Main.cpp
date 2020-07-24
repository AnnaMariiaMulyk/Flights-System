#include <iostream>
#include <string>
#include <fstream>
#include<conio.h>
#include "Users.h"
using namespace std;


int main()
{
	int choise;
	string login;
	string password;
	UsersAdmins userAdmin;
	Guest guest;
	userAdmin.Init();
	do
	{
		CLEAR;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "\t\t\t\MENU" << endl;
		cout << "\t\t1. Sign in" << endl;
		cout << "\t\t2. Sign up" << endl;
		cout << "\t\t3. Continue as guest" << endl;
		cout << "\t\t4. Exit" << endl;
		cout << endl;
		cout << "\t\tEnter choise: ";
		cin >> choise;
		switch (choise)
		{
		case 1:
		{
			CLEAR;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\tSIGN IN" << endl;
			cout << "\t\tEnter login: ";
			cin >> login;
			cout << "\t\tPassword: ";
			char ch;
			ch = _getch();
			while (ch != 13) {

				password.push_back(ch);
				cout << '*';
				ch = _getch();
			}
			userAdmin.SignIn(login, password);
			break;
		}
		case 2:
		{
			int choiseCase2;
			CLEAR;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\tSIGN UP" << endl;
			do
			{
				cout << "\t\tSign up as" << endl;
				cout << "\t\t\t1. User" << endl;
				cout << "\t\t\t2. Admin" << endl;
				cout << "\t\t3. Exit" << endl;
				cout << endl;
				cout << "\t\tEnter choise: ";
				cin >> choiseCase2;
				switch (choiseCase2)
				{
				case 1:
				{
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tSIGN UP AS USER" << endl;
					string tempL;
					string tempP;
					float tempM;
					cout << "\t\tEnter login: ";
					cin >> tempL;
					cout << "Enter password: ";
					cin >> tempP;
					do
					{
						cout << "Enter money: ";
						cin >> tempM;
					} while (tempM < 0);
					if (userAdmin.SignUpUser(tempL, tempP, tempM))
						cout << "\t\tAccount succesfuly created!" << endl;
					else
						cout << "\t\tAccount with this login already exist" << endl;
					break;
				}
				case 2:
				{
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tSIGN UP AS ADMIN" << endl;
					string tempL;
					string tempP;
					cout << "\t\tEnter login: ";
					cin >> tempL;
					cout << "Enter password: ";
					cin >> tempP;
					if (userAdmin.SignUpAdmin(tempL, tempP))
						cout << "\t\tAccount succesfuly created!" << endl;
					else
						cout << "\t\tAccount with this login already exist" << endl;
					break;
				}
				default:
					break;
				}
			} while (choiseCase2 != 3);
			
			
			break;
		}
		case 3:
		{
			int choiseCase3;
			CLEAR;
			cout << endl;
			cout << endl;
			cout << endl;
			do
			{
				cout << "\t\t\tCONTINUE AS GUEST" << endl;
				cout << "\t\t1. Search flight" << endl;
				cout << "\t\t2. Exit" << endl;
				cout << endl;
				cout << "\t\tEnter choise: ";
				cin >> choiseCase3;
				switch (choiseCase3)
				{
				case 1:
				{
					Date date;
					string departureCity;
					string arriveCity;
					date.SetYear();
					date.SetMonth();
					date.SetDay();
					cout << "\t\tEnter departure city: ";
					cin >> departureCity;
					cout << "\t\tEnter arrival city: ";
					cin >> arriveCity;
					guest.SearchFlight(userAdmin.GetFlights(), date.day, date.month, date.year, departureCity, arriveCity);
					break;
				}
				case 2:
				{
					cout << "\t\tGoobye!" << endl;
					PAUSE;
					break;
				}
				default:
					break;
				}
			} while (choiseCase3 != 2);
			break;
		}
		case 4:
		{
			userAdmin.RewriteUsersFile();
			userAdmin.RewriteAdminsFile();
			userAdmin.RewriteFlightsFile();
			CLEAR;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "\t\t\tGoodbye!" << endl;
			break;
		}
		default:
			break;
		}

	} while (choise != 4);

	PAUSE;
	return 0;
}