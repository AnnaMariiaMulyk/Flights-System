#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Flight.h"
using namespace std;

class Guest
{
public:
	void SearchFlight(list<Flight> &list, int day, int month, int year, string departureCity, string arrivalCity)
	{
		for (auto i : list)
		{
			if (i.GetArrivalCity() == arrivalCity 
				&& i.GetDepartureCity() == departureCity 
				&& i.GetDepartureDay() == day 
				&& i.GetDepartureMonth() == month 
				&& i.GetDepartureYear() == year)
			{
				i.Print();
			}
		}
	}
};
class User:public Guest
{
protected:
	string login;
	string password;
	float money;
public:
	User() :login(""), password(""), money(0) {}
	User(string login, string password) :login(login), password(password), money(0) {}
	User(string login, string password, float money) :login(login), password(password), money(money) {}
	void BuyTicket()
};

class UsersAdmins
{
private:
	list<User> users;
public:
	UsersAdmins() :users() {}
};
