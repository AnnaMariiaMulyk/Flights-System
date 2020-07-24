#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <ctime>
using namespace std;
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define CLEAR system("CLS");
#define PAUSE system("pause");

struct Date
{
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	int hours;
	int minutes;
	int day;
	int month;
	int year;
	int temp = 0;
	Date();
	void SetYear();
	void SetMonth();
	void SetDay();
	bool operator<(const Date& other);
	bool operator==(const Date& other);
	void Print()const;
	friend ofstream& operator<<(ofstream& ofs, const Date& date);
	friend ifstream& operator>>(ifstream& ifs, Date& date);
};
enum TicketType
{
	UNKNOWN,
	ECONOM,
	BUSINESS,
	FIRST
};
//ofstream& operator<<(ofstream& ofs, const TicketType& type);
ifstream& operator>>(ifstream& ifs, TicketType& type);
class Ticket
{
private:
	TicketType type;
	float value;
	bool possibleToReturn;
public:
	Ticket() :type(UNKNOWN), value(0), possibleToReturn(false) {}
	Ticket(TicketType type, float value, bool possibleToReturn)
		:type(type), value(value), possibleToReturn(possibleToReturn) {}
	bool IsValid(float value);
	void setType(TicketType type);
	void setValue(float value);
	void setPossibleToReturn(bool possibleToReturn);
	TicketType getType();
	float getValue();
	bool getPossibleToReturn();
	bool operator==(const Ticket& other);
	void Print()const;
	friend ofstream& operator<<(ofstream& ofs, const Ticket& ticket);
	friend ifstream& operator>>(ifstream& ifs, Ticket& ticket);
};
class ConnectionFlight
{
private:
	string city;
	Date departure;
	Date arrive;
public:
	ConnectionFlight() :city(""), departure(), arrive() {}
	ConnectionFlight(string city, Date departure, Date arrive)
		:city(city), departure(departure), arrive(arrive)  {}
	void setCity(string city);
	void setTime(Date departure, Date arrive);
	string GetCity()const;
	Date GetDepartureTime()const;
	Date GetArriveTime()const;
	bool operator==(const ConnectionFlight& other);
	void Print()const;
	friend ofstream& operator<<(ofstream& ofs, const ConnectionFlight& connectionFlight);
	friend ifstream& operator>>(ifstream& ifs, ConnectionFlight& connectionFlight);
};
class Flight
{
private:
	string name;
	string company;
	string departureCity;
	string arrivalCity;
	Date departure;
	Date arrive;
	list<Ticket> tickets;
	list<ConnectionFlight> connectionFlights;
public:
	Flight() :name("no name"), company("unknown"), departureCity("unknown"), arrivalCity("unknown")
	{
		departure.day = 0;
		departure.hours = 0;
		departure.minutes = 0;
		departure.month = 0;
		departure.year = 0;
		arrive.day = 0;
		arrive.hours = 0;
		arrive.minutes = 0;
		arrive.month = 0;
		arrive.year = 0;
		
	}
	Flight(string name, string company, string departureCity, string arrivalCity, Date departure, Date arrive, int countTickets, Ticket* tickets, int countConectionFlights, ConnectionFlight* connectionFlights)
		:name(name), company(company), departureCity(departureCity), arrivalCity(arrivalCity), departure(departure), arrive(arrive)
	{
		for (int i = 0; i < countTickets; i++)
		{
			this->tickets.push_back(tickets[i]);
		}
		for (int i = 0; i < countConectionFlights; i++)
		{
			this->connectionFlights.push_back(connectionFlights[i]);
		}
	}
	string GetName()const;
	string GetCompany()const;
	string GetDepartureCity()const;
	string GetArrivalCity()const;
	Date GetDerartureDate()const;
	Date GetArriveDate()const;
	int GetDepartureDay()const;
	int GetDepartureMonth()const;
	int GetDepartureYear()const;
	void SetName(string name);
	void SetCompany(string company);
	void SetDepartureCity(string departureCity);
	void SetArriveCity(string arriveCity);
	void SetDepartureTime(Date departure);
	void SetArriveTime(Date arrive);
	void AddTicket(const Ticket& ticket);
	void AddConnectionFlight(const ConnectionFlight& connectionFlight);
	bool RemoveTicket(TicketType type);
	bool IsAvailable(TicketType type)const;
	bool operator==(const Flight& other);
	bool operator()(const Flight& other);
	list<Ticket> GetTickets()/*const*/;
	list<ConnectionFlight> GetConnectionFlights()const;
	void Print()const;
	friend ofstream& operator<<(ofstream& ofs, const Flight& flight);
	friend ifstream& operator>>(ifstream& ifs, Flight& flight);

};

