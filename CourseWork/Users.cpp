#include "Users.h"

void User::AddMoney(float money)
{
	this->money += money;
}

void User::SetPassword(string password)
{
	this->password = password;
}
void User::SetLogin(string login)
{
	this->login = login;
}
string User::GetPassword() const { return password; }
string User::GetLogin() const { return login; }
bool User::IsCorrectPassword(string password)
{
	return this->password == password;
}
void User::SearchFlight(list<Flight>& list, int day, int month, int year, string departureCity, string arrivalCity)
{
	string choise;
	for (auto i : list)
	{
		if (i.GetArrivalCity() == arrivalCity
			&& i.GetDepartureCity() == departureCity
			&& i.GetDepartureDay() == day
			&& i.GetDepartureMonth() == month
			&& i.GetDepartureYear() == year)
		{
			i.Print();
			cout << "Do you want to buy the ticket?" << endl;
			do
			{
				cout << "Enter yes/YES/y/Y or no/NO/n/N: ";
				cin >> choise;
			} while (choise != "yes" && choise != "YES" && choise != "y" && choise != "Y" && choise != "no" && choise != "NO" && choise != "N" && choise != "n");
			if (choise == "yes" || choise == "YES" || choise == "y" || choise == "Y")
			{
				system("CLS");
				string typeT;
				do
				{
					cout << "Enter ticket type to buy(econom - e, business - b, first - f): ";
					cin >> typeT;
				} while (typeT != "e" && typeT != "e" && typeT != "f");
				if (BuyTicket(i, typeT) == true)
				{
					list.remove(i);
				}
			}
		}
	}
}
bool User::BuyTicket(Flight flight, string typeT)
{
	
	TicketType type;
	
	if (typeT == "e")
	{
		type = ECONOM;
	}
	else if (typeT == "b")
	{
		type = BUSINESS;
	}
	else if (typeT == "f")
	{
		type = FIRST;
	}
	if (flight.IsAvailable(type) == true)
	{
		for (auto i : flight.GetTickets())
		{
			if (i.getType() == type)
			{
				cout << "Value of ticket is " << i.getType() << " \$" << endl;
				if (this->money >= i.getValue())
				{
					string temp;
					cout << "Enter your password to continue: ";
					cin >> temp;
					
					if (IsCorrectPassword(temp))
					{
						this->money -= i.getValue();
						return true;
					}
					else
					{
						cout << "Password is incorrect, please try again: "; 
						cin >> temp;
						if (!IsCorrectPassword(temp))
						{
							cout << "Password is incorrect, please try again later";
							return false;
						}
					}
				}
				else
				{
					string choise;
					cout << "You don`t have enought money to buy this ticket" << endl;
					cout << "Do you want to add money?" << endl;
					do
					{
						cout << "Enter yes/YES/y/Y or no/NO/n/N: ";
						cin >> choise;
					} while (choise != "yes" && choise != "YES" && choise != "y" && choise != "Y" && choise != "no" && choise != "NO" && choise != "N" && choise != "n");
					if (choise == "yes" || choise == "YES" || choise == "y" || choise == "Y")
					{
						do
						{
							float moneyAdd;
							cout << "Enter money: ";
							cin >> moneyAdd;
							AddMoney(moneyAdd);
						} while (this->money < i.getValue());
						this->money -= i.getValue(); 
						string temp;
						cout << "Enter your password to continue: ";
						cin >> temp;

						if (IsCorrectPassword(temp))
						{
							this->money -= i.getValue();
							return true;
						}
						else
						{
							cout << "Password is incorrect, please try again: ";
							cin >> temp;
							if (!IsCorrectPassword(temp))
							{
								cout << "Password is incorrect, please try again later";
								return false;
							}
						}
					}
					else
						return false;
				}
			}
		}
	}
	else
	{
		cout << "There is no available ticket with this type" << endl;
		return false;
	}
}

bool UsersAdmins::IsAlreadyExist(string login)
{
	for (auto i : users)
	{
		if (i.GetLogin() == login)
			return true;
	}
	return false;
}
