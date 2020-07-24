#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <Windows.h>
#include "Flight.h"
using namespace std;
#define CLEAR system("CLS");
#define PAUSE system("pause");
#define SLEEP Sleep(2000);
class Guest
{
public:
	void SearchFlight(list<Flight>& mylList, int day, int month, int year, string departureCity, string arrivalCity);
};
class UsersAdmins;
class User 
{
protected:
	string login;
	string password;
	float money;
	list<Flight> myFlights;

public:
	User() :login(""), password(""), money(0) {}
	User(string login, string password) :login(login), password(password), money(0) {}
	User(string login, string password, float money) :login(login), password(password), money(money) {}
	bool IsValidMoney(float money)const;
	bool IsEmpty()const;
	void AddMoney(float money);
	void SetPassword(string password);
	bool SetLogin(string login, UsersAdmins& usersAdmins);
	string GetPassword()const;
	string GetLogin()const;
	float GetMoney()const;
	bool IsCorrectPassword(string password);
	void SearchFlight(list<Flight>& myList, int day, int month, int year, string departureCity, string arrivalCity);
	bool BuyTicket(Flight flight, string typeT);
	bool DeleteTicket();
	void Print()const;
	void PrintFlights()const;
	friend ofstream& operator<<(ofstream& ofs, const User& user);
	friend ifstream& operator>>(ifstream& ifs, User& user);

};
class Admin
{
private:
	string login;
	string password;
public:
	Admin() :login(""), password("") {}
	Admin(string login, string password) :login(login), password(password) {}
	bool SetLogin(string login, UsersAdmins&usersAdmins);
	void SetPassword(string password);
	string GetLogin()const;
	string GetPassword()const;
	bool IsCorrectPassword(string password)const;
	void Print()const;
	friend ofstream& operator<<(ofstream& ofs, const Admin& admin);
	friend ifstream& operator>>(ifstream& ifs, Admin& admin);
};
class UsersAdmins
{
private:
	list<User> users;
	list<Admin>admins;
	list<Flight>flights;
	void Clear()const
	{
		CLEAR;
		cout << endl;
		cout << endl;
		cout << endl;
	}
public:
	UsersAdmins() :users(), admins(), flights() {}
	bool IsAlreadyExist(string login);
	bool IsAlreadyExistFlight(string name);
	bool AddUser(User user);
	bool AddAdmin(Admin admin);
	void SignIn(string login, string password);
	bool SignUpAdmin(string login, string password);
	bool SignUpUser(string login, string password, float money);
	list<User>&GetUsers();
	list<Admin>&GetAdmins();
	list<Flight>&GetFlights();
	void RewriteUsersFile(); //const list<User>& users
	void RewriteAdminsFile();
	void RewriteFlightsFile();
	void Init();
	//friend ofstream& operator<<(ofstream& ofs, const UsersAdmins& usersAdmins);
	//friend ifstream& operator>>(ifstream& ifs, UsersAdmins& usersAdmins);
};

