#pragma once
#include <iostream>
#include <string>
#include <list>
#include <ctime>
using namespace std;
struct Date
{
	int hours;
	int minutes;
	int day;
	int month;
	int year;
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);
	int temp = 0;
	Date();
	void SetYear();
	void SetMonth();
	void SetDay();
	bool operator<(const Date& other);
	void Print()const;
};
enum TicketType
{
	UNKNOWN,
	ECONOM,
	BUSINESS,
	FIRST
};
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
	void setType(TicketType type);
	void setValue(float value);
	void setPossibleToReturn(bool possibleToReturn);
	TicketType getType();
	float getValue();
	bool getPossibleToReturn();
	void Print()const;
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
	void Print()const;
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
	void Print()const;
};
