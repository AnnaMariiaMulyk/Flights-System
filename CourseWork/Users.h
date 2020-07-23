#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Flight.h"
using namespace std;

class Guest
{
public:
	virtual void SearchFlight(list<Flight> &list, int day, int month, int year, string departureCity, string arrivalCity)
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
class User :public Guest
{
protected:
	string login;
	string password;
	float money;
	list<Flight>flights;
public:
	User() :login(""), password(""), money(0) {}
	User(string login, string password) :login(login), password(password), money(0) {}
	User(string login, string password, float money) :login(login), password(password), money(money) {}
	void AddMoney(float money);
	void SetPassword(string password);
	void SetLogin(string login);
	string GetPassword()const;
	string GetLogin()const;
	bool IsCorrectPassword(string password);
	void SearchFlight(list<Flight>& list, int day, int month, int year, string departureCity, string arrivalCity)override;
	bool BuyTicket(Flight flight, string typeT);
};

class UsersAdmins
{
private:
	list<User> users;

public:
	UsersAdmins() :users() {}
	bool IsAlreadyExist(string login);
	bool AddUser(User user);
	void RewriteUsersFile()
	{
		 
	}
};
