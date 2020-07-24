#pragma once
#include "Users.h"
#include <conio.h>

class Menu
{
private:
	UsersAdmins userAdmin;
public:
	Menu() :userAdmin() {}
	void Clear()const
	{
		CLEAR;
		cout << endl;
		cout << endl;
		cout << endl;
	}
	void SignInMenu();
	void SignUpMenu();
	void GuestMenu();
	void ExitMenu();
	void Main();

};
