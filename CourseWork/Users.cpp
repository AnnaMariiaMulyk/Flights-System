#include "Users.h"

bool User::IsValidMoney(float money) const
{
	return money > 1;
}

bool User::IsEmpty() const
{
	return myFlights.size() < 0;
}

void User::AddMoney(float money)
{
	if (IsValidMoney(money) == true)
		this->money += money;
}
void User::SetPassword(string password)
{
	this->password = password;
}
bool User::SetLogin(string login, UsersAdmins& usersAdmins)
{
	if (usersAdmins.IsAlreadyExist(login) == false)
	{
		this->login = login;
		return true;
	}
	return false;
}
string User::GetPassword() const { return password; }
string User::GetLogin() const { return login; }
float User::GetMoney() const { return money; }
bool User::IsCorrectPassword(string password)
{
	return this->password == password;
}
//************************************
void User::SearchFlight(list<Flight>& myList, int day, int month, int year, string departureCity, string arrivalCity)
{
	string choise;
	int count = 0;
	for (auto i : myList)
	{
		count++;
		if (i.GetArrivalCity() == arrivalCity
			&& i.GetDepartureCity() == departureCity
			&& i.GetDepartureDay() == day
			&& i.GetDepartureMonth() == month
			&& i.GetDepartureYear() == year)
		{
			i.Print();
			cout << "\t\tDo you want to buy the ticket?" << endl;
			do
			{
				cout << "\t\tEnter yes/YES/y/Y or no/NO/n/N: ";
				cin >> choise;
			} while (choise != "yes" && choise != "YES" && choise != "y" && choise != "Y" && choise != "no" && choise != "NO" && choise != "N" && choise != "n");
			if (choise == "yes" || choise == "YES" || choise == "y" || choise == "Y")
			{
				system("CLS");
				string typeT;
				do
				{
					cout << "\t\tEnter ticket type to buy(econom - e, business - b, first - f): ";
					cin >> typeT;
				} while (typeT != "e" && typeT != "e" && typeT != "f");
				if (BuyTicket(i, typeT) == true)
				{
					int count1 = 0;
					if (i.GetTickets().size() < 0)
					{
						list<Flight>::iterator i;
						advance(i, count);
						myList.erase(i);
					}
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
		int count = 0;
		for (auto i : flight.GetTickets())
		{
			count++;
			if (i.getType() == type)
			{
				cout << "\t\tValue of ticket is " << i.getType() << " \$" << endl;
				if (this->money >= i.getValue())
				{
					string temp;
					cout << "\t\tEnter your password to continue: ";
					cin >> temp;
					
					if (IsCorrectPassword(temp))
					{
						this->money -= i.getValue();
						Flight temp(flight);
						temp.GetTickets().clear();
						temp.GetTickets().push_back(i);
						myFlights.push_back(temp);
						flight.RemoveTicket(type); 
						list<Ticket>::iterator it;
						advance(it, count);
						flight.GetTickets().erase(it);
						return true;
					}
					else
					{
						cout << "\t\tPassword is incorrect, please try again: "; 
						cin >> temp;
						if (!IsCorrectPassword(temp))
						{
							cout << "\t\tPassword is incorrect, please try again later";
							return false;
						}
					}
				}
				else
				{
					string choise;
					cout << "\t\tYou don`t have enought money to buy this ticket" << endl;
					cout << "\t\tDo you want to add money?" << endl;
					do
					{
						cout << "\t\tEnter yes/YES/y/Y or no/NO/n/N: ";
						cin >> choise;
					} while (choise != "yes" && choise != "YES" && choise != "y" && choise != "Y" && choise != "no" && choise != "NO" && choise != "N" && choise != "n");
					if (choise == "yes" || choise == "YES" || choise == "y" || choise == "Y")
					{
						do
						{
							float moneyAdd;
							cout << "\t\tEnter money: ";
							cin >> moneyAdd;
							AddMoney(moneyAdd);
						} while (this->money < i.getValue());
						this->money -= i.getValue(); 
						string temp;
						cout << "\t\tEnter your password to continue: ";
						cin >> temp;

						if (IsCorrectPassword(temp))
						{
							this->money -= i.getValue();
							return true;
						}
						else
						{
							cout << "\t\tPassword is incorrect, please try again: ";
							cin >> temp;
							if (!IsCorrectPassword(temp))
							{
								cout << "\t\tPassword is incorrect, please try again later";
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
		cout << "\t\tThere is no available ticket with this type" << endl;
		return false;
	}
}
//****************** problem solved!!!!!!!!!
bool User::DeleteTicket()
{
	string name;
	string typeT;
	TicketType type;
	int count = 0;
	for (auto i : myFlights)
	{
		i.Print();
	}
	cout << "\t\tEnter flight number to return: ";
	cin >> name;
	for (auto i : myFlights)
	{
		if (i.GetName() == name)
		{
			count++;
			do
			{
				cout << "\t\tEnter ticket type: ";
				cin >> typeT;
			} while (typeT != "business", typeT != "first", typeT != "econom");
			if (typeT == "first") { type = FIRST; }
			else if (typeT == "econom") { type = ECONOM; }
			else if (typeT == "business") { type = BUSINESS; }
			for (auto j : i.GetTickets())
			{
				if (j.getPossibleToReturn() == true && j.getType() == type)
				{
					this->money += j.getValue();
					list<Flight>::iterator it;
					advance(it, count);
					myFlights.erase(it);
					return true; 
				}
			}
		}
	}
	return false;
}
void User::Print() const
{
	cout << "\t\tLogin: " << login << endl;
	cout << "\t\tPassword: " << endl;
	cout << "\t\tMoney: " << money << endl;
}
void User::PrintFlights() const
{
	for (auto i : myFlights)
	{
		i.Print();
	}
}
bool UsersAdmins::IsAlreadyExist(string login)
{
	for (auto i : users)
	{
		if (i.GetLogin() == login)
			return true;
	}
	for (auto i : admins)
	{
		if (i.GetLogin() == login)
			return true;
	}
	return false;
}
bool UsersAdmins::IsAlreadyExistFlight(string name)
{
	for (auto i : flights)
	{
		if (i.GetName() == name)
			return true;
	}
	return false;
}
bool UsersAdmins::AddUser(User user)
{
	if (IsAlreadyExist(user.GetLogin()) == false)
	{
		users.push_back(user);
		//rewriteUsersFile();
		return true;
	}
	return false;
}
bool UsersAdmins::AddAdmin(Admin admin)
{
	if (IsAlreadyExist(admin.GetLogin()) == false)
	{
		admins.push_back(admin);
		//rewriteUsersFile();
		return true;
	}
	return false;
}

void UsersAdmins::SignIn(string login, string password)
{
	int choise = 0;
	for (auto i : users)
	{
		if (i.GetLogin() == login && i.GetPassword() == password)
		{
			int userChoise;
			do
			{
				CLEAR;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << "\t\t\tUSER MENU" << endl;
				cout << "\t\t1. My profile" << endl;
				cout << "\t\t2. My flights" << endl;
				cout << "\t\t3. My money balance" << endl;
				cout << "\t\t4. Search flight" << endl;
				cout << "\t\t5. Delete account" << endl;
				cout << "\t\t6. Sign out" << endl;
				cout << endl;
				cout << "\t\tEnter choise: ";
				cin >> userChoise;
				switch (userChoise)
				{
				case 1:
				{
					int choiseCase1;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tMY PROFILE" << endl;
					i.Print();
					do
					{
						cout << "\t\t1. Change login" << endl;
						cout << "\t\t2. Change password" << endl;
						cout << "\t\t3. Go back" << endl;
						cout << endl;
						cout << "\t\tEnter action: ";
						cin >> choiseCase1;
						switch (choiseCase1)
						{
						case 1:
						{
							string temp;
							CLEAR;
							cout << endl;
							cout << endl;
							cout << endl;
							cout << "\t\t\tCHANGE LOGIN" << endl;
							cout << "\t\tEnter password to continue: ";
							cin >> temp;
							if (i.IsCorrectPassword(temp))
							{
								cout << "\t\tEnter new login: ";
								cin >> temp;
								if (i.SetLogin(temp, *this) == true)
								{
									cout << "\t\tLogin succesfuly changed" << endl;
									PAUSE;
									CLEAR;
								}
								else
									cout << "\t\tUser with this login is aleady exists" << endl;
							}
							else
							{
								cout << "\t\tIncorect password" << endl;
							}
							break;
						}
						case 2:
						{
							string temp1;
							string temp2;
							CLEAR;
							cout << endl;
							cout << endl;
							cout << endl;
							cout << "\t\t\tCHANGE PASSWORD" << endl;
							cout << "\t\tEnter password to continue: ";
							cin >> temp1;
							if (i.IsCorrectPassword(temp1))
							{
								cout << "\t\tEnter new password: ";;
								cin >> temp1;
								cout << "\t\tConfirm new password: ";
								cin >> temp2;
								if (temp1 == temp2)
								{
									i.SetPassword(temp1);
								}
								else
									cout << "\t\tPasswords do not match" << endl;
							}
							break;
						}
						
						case 3:
						{
							PAUSE;
							break;
						}
						default:
							break;
						}
					} while (choise != 3);
					break;
				}
				case 2:
				{
					string choiseCase2;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tMY FLIGHTS" << endl;
					i.PrintFlights();
					do
					{
						cout << "\t\tDo you want to return any flight?" << endl;
						cout << "\t\tEnter action(yes / YES / Y / y or no / NO / N / n): ";
						cin >> choiseCase2;
					} while (choiseCase2 != "yes" 
						&& choiseCase2 != "YES" 
						&& choiseCase2 != "y" 
						&& choiseCase2 != "Y"
						&& choiseCase2 != "no" 
						&& choiseCase2 != "NO" 
						&& choiseCase2 != "N"
						&& choiseCase2 != "n");
					if (choiseCase2 == "yes" || choiseCase2 == "YES" || choiseCase2 == "y" || choiseCase2 == "Y")
					{
						if (i.DeleteTicket() == true)
						{
							cout << "\t\tTicket succesfuly returned!" << endl;
						}
						else
							cout << "Can not return ticket" << endl;
					}

					break;
				}
				case 3:
				{
					string choiseCase3;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tMONEY BALANCE" << endl;
					cout << "\t\tMoney: " << i.GetMoney() << endl;
					do
					{
						cout << "\t\tDo you want to add money?" << endl;
						cout << "\t\tEnter action(yes / YES / Y / y or no / NO / N / n): ";
						cin >> choiseCase3;
					} while (choiseCase3 != "yes"
						&& choiseCase3 != "YES"
						&& choiseCase3 != "y"
						&& choiseCase3 != "Y"
						&& choiseCase3 != "no"
						&& choiseCase3 != "NO"
						&& choiseCase3 != "N"
						&& choiseCase3 != "n");
					if (choiseCase3 == "yes" || choiseCase3 == "YES" || choiseCase3 == "y" || choiseCase3 == "Y")
					{
						float add;
						cout << "\t\tEnter money: ";
						cin >> add;
						i.AddMoney(add);
					}
					break;
				}
				case 4:
				{
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tSEARCH FLIGHTS" << endl;
					Date date;
					string departureCity;
					string arriveCity;
					cout << "\t\t\tSEARCH FLIGHT" << endl;
					cout << "\t\tEnter departure city: ";
					cin >> departureCity;
					cout << "Enter arrive city: ";
					cin >> arriveCity;
					date.SetYear();
					date.SetMonth();
					date.SetDay();
					i.SearchFlight(flights, date.day, date.month, date.year, departureCity, arriveCity);
					break;
				}
				case 5:
				{
					string temp;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tDELETE ACCOUNT" << endl;
					cout << "\t\tEnter password to delete account: ";
					cin >> temp;
					if (i.IsCorrectPassword(temp))
					{
						list<User>::iterator it;
						int count = 0;
						for (auto i : users)
						{
							count++;
							if (i.GetLogin() == login)
							{
								advance(it, count);
								users.erase(it);
								cout << "Account succesfuly deleted" << endl;
								SLEEP;
								return;
							}
						}
					}
					else
						cout << "\t\tIncorrect password" << endl;
				}
				case 6:
				{
					cout << "\t\tGoodbye!" << endl;
					PAUSE;;
					break;
				}
				default:
					break;
				}
			} while (choise != 6);
		}
	}
	for (auto i : admins)
	{
		if (i.GetLogin() == login && i.GetPassword() == password)
		{
			int adminChoise;
			do
			{
				CLEAR;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << "\t\t\tADMIN MENU" << endl;
				cout << "\t\t1. My profile" << endl;
				cout << "\t\t2. Add flight" << endl;
				cout << "\t\t3. Edit flight" << endl;
				cout << "\t\t4. Delete flight" << endl;
				cout << "\t\t5. Delete account" << endl;
				cout << "\t\t6. Log out" << endl;
				cout << endl;
				cout << "\t\tEnter action: ";
				cin >> adminChoise;
				switch (adminChoise)
				{
				case 1:
				{
					int choiseCase1;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tMY PROFILE" << endl;
					i.Print();
					do
					{
						cout << "\t\t1. Change login" << endl;
						cout << "\t\t2. Change password" << endl;
						cout << "\t\t3. Go back" << endl;
						cout << endl;
						cout << "\t\tEnter action: ";
						cin >> choiseCase1;
						switch (choiseCase1)
						{
						case 1:
						{
							string temp;
							CLEAR;
							cout << endl;
							cout << endl;
							cout << endl;
							cout << "\t\t\tCHANGE LOGIN" << endl;
							cout << "\t\tEnter password to continue: ";
							cin >> temp;
							if (i.IsCorrectPassword(temp))
							{
								cout << "\t\tEnter new login: ";
								cin >> temp;
								if (i.SetLogin(temp, *this) == true)
									cout << "\t\tLogin succesfuly changed" << endl;
								else
									cout << "\t\tUser with this login is aleady exists" << endl;
							}
							else
							{
								cout << "\t\tIncorect password" << endl;
							}
							break;
						}
						case 2:
						{
							string temp1;
							string temp2;
							CLEAR;
							cout << endl;
							cout << endl;
							cout << endl;
							cout << "\t\t\tCHANGE PASSWORD" << endl;
							cout << "\t\tEnter password to continue: ";
							cin >> temp1;
							if (i.IsCorrectPassword(temp1))
							{
								cout << "\t\tEnter new password: ";;
								cin >> temp1;
								cout << "\t\tConfirm new password: ";
								cin >> temp2;
								if (temp1 == temp2)
									i.SetPassword(temp1);
								else
									cout << "\t\tPasswords do not match" << endl;
							}
							break;
						}
						
						default:
							break;
						}
					} while (choise != 3);
					break;
				}
				case 2:
				{
					Flight temp;
					string info;
					Date time;
					int countTickets;
					int countCF;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tADD FLIGHT" << endl;
					cout << "\t\tEnter flight name: ";
					cin >> info;
					if (IsAlreadyExistFlight(info) == true)
					{
						cout << "\t\tFlight with this name is already exist!" << endl;
						break;
					}
					temp.SetName(info);
					cout << "\t\tEnter flight company: ";
					cin >> info;
					temp.SetCompany(info);
					cout << "\t\tEnter departure city: ";
					cin >> info;
					temp.SetDepartureCity(info);
					cout << "\t\tEnter arrival city: ";
					cin >> info;
					temp.SetArriveCity(info);
					cout << "\t\tDeparture time: " << endl;
					time.SetYear();
					time.SetMonth();
					time.SetDay();
					temp.SetDepartureTime(time);
					do
					{
						cout << "\t\tArrival time:" << endl;
						time.SetYear();
						time.SetMonth();
						time.SetDay();
					} while (time < temp.GetDerartureDate());
					temp.SetArriveTime(time);
					cout << "\t\tEnter count of tickets: ";
					cin >> countTickets;
					Ticket ticket;
					for (int i = 0; i < countTickets; i++)
					{
						do
						{
							cout << "\t\tEnter ticket type to buy(econom - e, business - b, first - f): ";
							cin >> info;
						} while (info != "e" && info != "e" && info != "f");
						TicketType type;
						float value;

						if (info == "e")
						{
							type = ECONOM;
						}
						else if (info == "b")
						{
							type = BUSINESS;
						}
						else if (info == "f")
						{
							type = FIRST;
						}
						ticket.setType(type);
						do
						{
							cout << "\t\tEnter ticket value: ";
							cin >> value;
						} while (!ticket.IsValid(value));
						ticket.setValue(value);
						do
						{
							cout << "\t\tEnter if possible to return ticket(yes/YES/Y/y or no/NO/N/n: ";
							cin >> info;
						} while (info != "yes" && info != "YES" && info != "Y" && info != "y" && info != "NO" && info != "N" && info != "no" && info != "n");
						if (info == "yes" || info == "YES" || info == "Y" || info == "y")
							ticket.setPossibleToReturn(true);
						else
							ticket.setPossibleToReturn(false);
						temp.AddTicket(ticket);
					}
					cout << "\t\tEnter count of connection flights: ";
					cin >> countCF;
					ConnectionFlight CF;
					Date time1;
					for (int i = 0; i < countCF; i++)
					{
						cout << "\t\tEnter connection flight city: ";
						cin >> info;
						CF.setCity(info);
						time.SetYear();
						time.SetMonth();
						time.SetDay();
						do
						{
							time1.SetYear();
							time1.SetMonth();
							time1.SetDay();
							
						}while(time1 < time);
						CF.setTime(time, time1);
						temp.AddConnectionFlight(CF);
					}
					flights.push_back(temp);
					//rewriteFlightsFile();
					break;
				}
				case 3:
				{
					string name;
					int choiseCase3;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\tEDIT FLIGHT" << endl;
					for (auto j : flights)
					{
						j.Print();
					}
					cout << "\t\tEnter name of flight to edit: ";
					cin >> name;
					for (auto j : flights)
					{
						if (j.GetName() == name)
						{
							string toChange;
							CLEAR;
							cout << endl;
							cout << endl;
							cout << endl;
							j.Print();
							cout << endl;
							do
							{
								cout << "\t\tEnter what do you want to change(name/company/departure/ arrive): ";
								cin >> toChange;
							} while (toChange != "name" && toChange != "company" && toChange != "departure" && toChange != "arrive");
							if (toChange == "name")
							{
								CLEAR;
								cout << endl;
								cout << endl;
								cout << endl;
								string newName;
								cout << "\t\tEnter new name: ";
								cin >> newName;
								if (IsAlreadyExistFlight(name) == false)
								{
									j.SetName(newName);
								}
								else
									cout << "\t\tFlight with this name is already exist" << endl;
							}
						}
					}
					break;
				}
				case 4:
				{
					string name;
					int count = 0;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tDELETE FLIGHT" << endl;
					for (auto i : flights)
					{
						i.Print();
					}
					cout << "\t\tEnter flight name to delete: ";
					cin >> name;
					for (auto i : flights)
					{
						count++; 
						if (i.GetName() == name)
						{
							list<Flight>::iterator it;
							advance(it, count);
							flights.erase(it);
							cout << "\t\tFlight succesfuly deleted" << endl;
							PAUSE;
							break;
						}
					}
					cout << "\t\tCan not find flight with this name" << endl;
					PAUSE;
					break;
				}
				case 5:
				{
					string temp;
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\t\tDELETE ACCOUNT" << endl;
					cout << "\t\tEnter password to delete account: ";
					cin >> temp;
					if (i.IsCorrectPassword(temp))
					{
						list<Admin>::iterator it;
						int count = 0;
						for (auto i : admins)
						{
							count++;
							if (i.GetLogin() == login)
							{
								advance(it, count);
								admins.erase(it);
								cout << "Account succesfuly deleted" << endl;
								PAUSE;
								return;
							}
						}
					}
					else
						cout << "\t\tIncorrect password" << endl;
				}
				case 6:
				{
					CLEAR;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "\t\tGoodbye" << endl;
					PAUSE;
					break;
				}
				default:
					break;
				}
			} while (adminChoise != 6);
		}
	}
	
}
bool UsersAdmins::SignUpUser(string login, string password, float money)
{
	if (IsAlreadyExist(login) == false)
	{
		User user(login, password, money);
		users.push_back(user);
		return true;
	}
	return false;
}
list<User> &UsersAdmins::GetUsers()
{
	return users;
}
list<Admin>& UsersAdmins::GetAdmins()
{
	return admins;
}
list<Flight>& UsersAdmins::GetFlights()
{
	return flights;
}
void UsersAdmins::RewriteUsersFile()
{
	ofstream ofs;
	ofs.open("users.txt");
	bool IsOpen = ofs.is_open();
	if (IsOpen == true)
	{
		for (auto i : users)
		{
			ofs << i;
		}
	}
	else
		cout << "Error in file system!" << endl;
	ofs.close();
}
void UsersAdmins::RewriteAdminsFile()
{
	ofstream ofs;
	ofs.open("admins.txt");
	bool IsOpen = ofs.is_open();
	if (IsOpen == true)
	{
		for (auto i : admins)
		{
			ofs << i;
		}
	}
	else
		cout << "Error in file system!" << endl;
	ofs.close();
}
void UsersAdmins::RewriteFlightsFile()
{
	ofstream ofs;
	ofs.open("flights.txt");
	bool IsOpen = ofs.is_open();
	if (IsOpen == true)
	{
		for (auto i : flights)
		{
			ofs << i;
		}
	}
	else
		cout << "Error in file system!" << endl;
	ofs.close();
}
void UsersAdmins::Init()
{
	User temp;
	Admin temp1;
	Flight temp2;
	ifstream ifs;
	ifs.open("users.txt");
	bool IsOpen = ifs.is_open();
	if (IsOpen == true)
	{
		while (!ifs.eof())
		{
			ifs >> temp;
			users.push_back(temp);
		}
	}
	else
		cout << "Error in file system!" << endl;
	ifs.close();


	ifs.open("admins.txt");
	IsOpen = ifs.is_open();
	if (IsOpen == true)
	{
		while (!ifs.eof())
		{
			ifs >> temp1;
			if (!ifs.eof())
				admins.push_back(temp1);
		}
	}
	else
		cout << "Error in file system!" << endl;
	ifs.close();


	ifs.open("flights.txt");
	IsOpen = ifs.is_open();
	if (IsOpen == true)
	{
		while (!ifs.eof())
		{
			ifs >> temp2;
			if (!ifs.eof())
				flights.push_back(temp2);
		}
	}
	else
		cout << "Error in file system!" << endl;
	ifs.close();
}
bool UsersAdmins::SignUpAdmin(string login, string password)
{
	if (IsAlreadyExist(login) == false)
	{
		Admin admin(login, password);
		admins.push_back(admin);
		return true;
	}
	return false;
}
ofstream& operator<<(ofstream& ofs, const User& user)
{
	ofs << user.login << endl;
	ofs << user.password << endl;
	ofs << user.money << endl;
	ofs << user.myFlights.size();
	for (auto i : user.myFlights)
	{
		ofs << i;
	}
	return ofs;
}
ifstream& operator>>(ifstream& ifs, User& user)
{
	int a;
	Flight temp;
	ifs >> user.login;
	ifs >> user.password;
	ifs >> user.money;
	ifs >> a;
	for (int i = 0; i < a; i++)
	{
		ifs >> temp;
		user.myFlights.push_back(temp);
	}
	return ifs;
}
ofstream& operator<<(ofstream& ofs, const Admin& admin)
{
	ofs <<admin. login << endl;
	ofs << admin.password << endl;
	return ofs;
}
ifstream& operator>>(ifstream& ifs, Admin& admin)
{
	ifs >> admin.login;
	ifs >> admin.password;
	return ifs;
}




//ofstream& operator<<(ofstream& ofs, const UsersAdmins& usersAdmins)
//{
//	for (auto i : usersAdmins.users)
//	{
//		ofs << i;
//	}
//	for (auto i : usersAdmins.admins)
//	{
//		ofs << i;
//	}
//	return ofs;
//}
//
//ifstream& operator>>(ifstream& ifs, UsersAdmins& usersAdmins)
//{
//	for(auto i:usersAdmins.users)
//}

bool Admin::SetLogin(string login, UsersAdmins&usersAdmins)
{
	if (usersAdmins.IsAlreadyExist(login) == false)
	{
		this->login = login;
		return true;
	}
	return false;
}
void Admin::SetPassword(string password)
{
	this->password = password;
}
string Admin::GetLogin() const
{
	return login;
}
string Admin::GetPassword() const
{
	return password;
}
bool Admin::IsCorrectPassword(string password) const
{
	return this->password == password;
}
void Admin::Print() const
{
	cout << "\t\tLogin: " << login << endl;
	cout << "\t\tPassword: " << endl;
}

void Guest::SearchFlight(list<Flight>& mylList, int day, int month, int year, string departureCity, string arrivalCity)
{
	for (auto i : mylList)
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
