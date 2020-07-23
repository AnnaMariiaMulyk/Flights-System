#include "Flight.h"

void Ticket::setType(TicketType type) { this->type = type; }
void Ticket::setValue(float value) { this->value = value; }
void Ticket::setPossibleToReturn(bool possibleToReturn){ this->possibleToReturn = possibleToReturn; }
TicketType Ticket::getType(){ return type; }
float Ticket::getValue(){ return value; }
bool Ticket::getPossibleToReturn() { return possibleToReturn; }
void Ticket::Print() const
{
	cout << "\< - - - - - - - - - - - \>" << endl;
	cout << "Ticket type: " << type << endl;
	cout << "Ticket value: " << value << endl;
	cout << "Possible to return: ";
	if (possibleToReturn)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}


void ConnectionFlight::setCity(string city) { this->city = city; }
void ConnectionFlight::setTime(Date departure, Date arrive)
{
	this->departure = departure;
	this->arrive = arrive;
}
string ConnectionFlight::GetCity() const { return city; }
Date ConnectionFlight::GetDepartureTime() const { return departure; }
Date ConnectionFlight::GetArriveTime() const { return arrive; }
void ConnectionFlight::Print() const
{
	cout << "\< - - - - - - - - - - - \>" << endl;
	cout << "Connection flight city: " << city << endl;
	cout << "Connection flight departure date: ";
	departure.Print();
	cout << "Connection flight arrive time: ";
	arrive.Print();
}





string Flight::GetName() const { return name; }
string Flight::GetCompany() const { return company; }
string Flight::GetDepartureCity() const { return departureCity; }
string Flight::GetArrivalCity() const { return arrivalCity; }
Date Flight::GetDerartureDate() const { return departure; }
Date Flight::GetArriveDate() const { return arrive; }
int Flight::GetDepartureDay() const { return departure.day; }
int Flight::GetDepartureMonth() const { return departure.day; }
int Flight::GetDepartureYear() const { return departure.year; }
void Flight::SetName(string name) { this->name = name; }
void Flight::SetCompany(string company) { this->company = company; }
void Flight::SetDepartureCity(string departureCity) { this->departureCity = departureCity; }
void Flight::SetArriveCity(string arriveCity) { this->arrivalCity = arrivalCity; }
void Flight::SetDepartureTime(Date departure) { this->departure = departure; }
void Flight::SetArriveTime(Date arrive) { this->arrive = arrive; }
void Flight::AddTicket(const Ticket& ticket)
{
	tickets.push_back(ticket);
}
void Flight::AddConnectionFlight(const ConnectionFlight& connectionFlight)
{
	connectionFlights.push_back(connectionFlight);
}

bool Flight::RemoveTicket(TicketType type)
{
	for (auto i : tickets)
	{
		if (i.getType() == type)
		{
			tickets.remove(i);
			return true;
		}
	}
	return false;
}

void Flight::Print() const
{
	cout << "\< - - - - - - - - - - - \>" << endl;
	cout << "Name: " << name << endl;
	cout << "Company: " << company << endl;
	cout << "Departure city: " << departureCity << endl;
	cout << "Arrive city: " << arrivalCity << endl;
	departure.Print();
	arrive.Print();
	for (auto i : tickets)
	{
		i.Print();
	}
	for (auto i : connectionFlights)
	{
		i.Print();
	}
}


Date::Date()
{
	hours = 0;
	minutes = 0;
	day = 0;
	month = 0;
	year = 0;
}
void Date::SetYear()
{
	cout << "Enter year: ";
	cin >> temp;
	if (year < now->tm_year)
	{
		cout << "Invalid year!" << endl;
		SetYear();
	}
	else
	{
		year = temp;
		return;
	}
}
void Date::SetMonth()
{
	cout << "Enter month: ";
	cin >> temp;
	if ((year == 2020 && temp < now->tm_mon) || temp > 12)
	{
		cout << "Invalid month!" << endl;
		SetMonth();
	}
	else
	{
		month = temp;
		return;
	}
}
void Date::SetDay()
{
	cout << "Enter day: ";
	cin >> temp;
	if ((month == now->tm_mon && temp < now->tm_mday)
		|| (month == 1 && temp > 31)
		|| (month == 3 && temp > 31)
		|| (month == 5 && temp > 31)
		|| (month == 7 && temp > 31)
		|| (month == 8 && temp > 31)
		|| (month == 10 && temp > 31)
		|| (month == 12 && temp > 31)
		|| (month == 2 && year % 4 != 0 && temp > 29)
		|| (month == 2 && temp > 28)
		|| (month == 4 && temp > 30)
		|| (month == 6 && temp > 30)
		|| (month == 9 && temp > 30)
		|| (month == 11 && temp > 30)
		|| (temp < 1))
	{
		SetDay();
	}
	else
	{
		day = temp;
		return;
	}
}
bool Date::operator<(const Date& other)
{
	int date1 = (this->hours + (this->minutes / 60)
		+ (this->day * 24) + (this->month * 31 * 24)
		+ (this->year * 356 * 31 * 24));
	long date2 = (other.hours + (other.minutes / 60)
		+ (other.day * 24) + (other.month * 31 * 24)
		+ (((other.year * 356) * 31) * 24));
	return date1 < date2;
}
void Date::Print() const
{
	cout << hours << "\:" << minutes << "  " << day << "\/" << month << "\/" << year << endl;
}
