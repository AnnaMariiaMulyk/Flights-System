#include "Flight.h"

bool Ticket::IsValid(float value)
{
	return value > 0;
}

void Ticket::setType(TicketType type) {
	this->type = type;
}
void Ticket::setValue(float value) { 
	if (IsValid(value))
	{
		this->value = value; 
	}
}
void Ticket::setPossibleToReturn(bool possibleToReturn){ this->possibleToReturn = possibleToReturn; }
TicketType Ticket::getType(){ return type; }
float Ticket::getValue(){ return value; }
bool Ticket::getPossibleToReturn() { return possibleToReturn; }
bool Ticket::operator==(const Ticket& other)
{
	return (this->type == other.type
		&& this->value == other.value
		&& this->possibleToReturn == other.possibleToReturn);
}
void Ticket::Print() const
{
	cout << "\t\< - - - - - - - - - - - \>" << endl;
	cout << "\t\tTicket type: " << type << endl;
	cout << "\t\tTicket value: " << value << endl;
	cout << "\t\tPossible to return: ";
	if (possibleToReturn)
		cout << "\t\tyes" << endl;
	else
		cout << "\t\tno" << endl;
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
bool ConnectionFlight::operator==(const ConnectionFlight& other)
{
	return (this->city == other.city
		&& this->departure == other.departure
		&& this->arrive == other.arrive);
}
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
//**********************
bool Flight::RemoveTicket(TicketType type)
{
	int count = 0;
	for (auto i : tickets)
	{
		count++;
		if (i.getType() == type)
		{
			list<Ticket>::iterator it;
			advance(it, count);
			tickets.erase(it);
			return true;
		}
	}
	return false;
}
bool Flight::IsAvailable(TicketType type) const
{
	for (auto i : tickets)
	{
		if (i.getType() == type)
		{
			return true;
		}
	}
	return false;
}
bool Flight::operator==(const Flight& other)
{
	return (this->name.compare(other.name) == 0
		&& this->company.compare(other.company) == 0
		&& this->departureCity.compare(other.departureCity) == 0
		&& this->arrivalCity.compare(other.arrivalCity) == 0
		&& this->departure == other.departure
		&& this->arrive == other.arrive
		&& this->tickets.begin() == other.tickets.begin()
		&& this->connectionFlights.begin() == other.connectionFlights.begin());
}
bool Flight::operator()(const Flight& other)
{
	return (*this == other);
}
list<Ticket> Flight::GetTickets() /*const*/
{
	return tickets;
}
list<ConnectionFlight> Flight::GetConnectionFlights() const
{
	return connectionFlights;
}
void Flight::Print() const
{
	cout << "\t\< - - - - - - - - - - - \>" << endl;
	cout << "\t\tName: " << name << endl;
	cout << "\t\tCompany: " << company << endl;
	cout << "\t\tDeparture city: " << departureCity << endl;
	cout << "\t\tArrive city: " << arrivalCity << endl;
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
	cout << "\t\tEnter year: ";
	cin >> temp;
	if (year < (now->tm_year+1900))
	{
		cout << "\t\tInvalid year!" << endl;
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
	cout << "\t\tEnter month: ";
	cin >> temp;
	if ((year == 2020 && temp < (now->tm_mon+1)) || temp > 12)
	{
		cout << "\t\tInvalid month!" << endl;
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
	cout << "\t\tEnter day: ";
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
	cout <<"\t\t" << hours << "\:" << minutes << "  " << day << "\/" << month << "\/" << year << endl;
}

bool Date::operator==(const Date& other)
{
	return (this->hours == other.hours
		&& this->minutes == other.minutes
		&& this->day == other.day
		&& this->month == other.minutes
		&& this->year == other.year);
}

ofstream& operator<<(ofstream& ofs, const Date& date)
{
	ofs << date.hours << endl;
	ofs << date.minutes << endl;
	ofs << date.day << endl;
	ofs << date.month << endl;
	ofs << date.year << endl;
	return ofs;
}

ifstream& operator>>(ifstream& ifs, Date& date)
{
	ifs >> date.hours;
	ifs >> date.minutes;
	ifs >> date.day;
	ifs >> date.month;
	ifs >> date.year;
	return ifs;
}

//ofstream& operator<<(ofstream& ofs, const TicketType& type)
//{
//	ofs << type << endl;
//	return ofs;
//	// TODO: insert return statement here
//}

ifstream& operator>>(ifstream& ifs, TicketType& type)
{
	ifs >> type;
	return ifs;
}
ofstream& operator<<(ofstream& ofs, const Ticket&ticket)
{
	ofs << ticket.type << endl;
	ofs << ticket.value << endl;
	ofs << ticket.possibleToReturn << endl;
	return ofs;
}
ifstream& operator>>(ifstream& ifs, Ticket& ticket)
{
	ifs >> ticket.type;
	ifs >> ticket.value;
	ifs >> ticket.possibleToReturn;
	return ifs;
	// TODO: insert return statement here
}
ofstream& operator<<(ofstream& ofs, const ConnectionFlight& connectionFlight)
{
	ofs << connectionFlight.city << endl;
	ofs << connectionFlight.departure << endl;
	ofs << connectionFlight.arrive << endl;
	return ofs;
}
ifstream& operator>>(ifstream& ifs, ConnectionFlight& connectionFlight)
{
	ifs >> connectionFlight.city;
	ifs >> connectionFlight.departure;
	ifs >> connectionFlight.arrive;
	return ifs;
}
ofstream& operator<<(ofstream& ofs, const Flight& flight)
{
	ofs << flight.name << endl;
	ofs << flight.company << endl;
	ofs << flight.departureCity << endl;
	ofs << flight.arrivalCity << endl;
	ofs << flight.departure << endl;
	ofs << flight.arrive << endl;
	ofs << flight.tickets.size() << endl;
	for (auto i : flight.tickets)
	{
		ofs << i << endl;
	}
	ofs << flight.connectionFlights.size() << endl;
	for (auto i : flight.connectionFlights)
	{
		ofs << i << endl;
	}
	return ofs;
}
ifstream& operator>>(ifstream& ifs, Flight& flight)
{
	int a = 0;
	int b = 0;
	ifs >> flight.name;
	ifs >> flight.company;
	ifs >> flight.departureCity;
	ifs >> flight.arrivalCity;
	ifs >> flight.departure;
	ifs >> flight.arrive;
	ifs >> a;
	Ticket ticket;
	for (int i = 0; i < a; i++)
	{
		ifs >> ticket;
		flight.tickets.push_back(ticket);
	}
	ifs >> b;
	ConnectionFlight connectionFligth;
	for (int i = 0; i < b; i++)
	{
		ifs >> connectionFligth;
		flight.connectionFlights.push_back(connectionFligth);
	}
	return ifs;
}


