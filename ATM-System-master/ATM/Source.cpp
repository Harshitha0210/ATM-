#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>//for file input & output
#include <conio.h>// for getch()
#include <ctime>//for displaying time and date now
//#include <stdlib.h>//rand function
//#include <stdio.h>//rand function

using namespace std;

struct client
{
	int id;
	string username;
	char password[4];
	int balance;
	int index;//for search in file
};
struct employee
{
	int id;
	string username;
	char password[4];
};
//Login
bool emplogin(employee&, employee);
bool login(client&, client);
//bank functionalty
int withdrawl(client arrayoffile[], client &user);
int deposit(client arrayoffile[], client&user);
void inquiry(client&user);
int transfer(client&user, client arrayoffile[], client&user2);
bool checkuser2(client&user2, client clientfile);
int donation(client arrayoffile[], client&user);
int phone_bill(int bill, client&user, client arrayoffile[]);
int elec_bill(int bill, client&user, client arrayoffile[]);
int mob_bill(int bill, client&user, client arrayoffile[]);
void search_transactionuser(client user);
void last_transaction(client user);
//file editing
void editfile(client arrayoffile[], int linesoffile);
void outputfile(client, string, int);


void main()
{//open scope of int main

	client user, user2, arrayoffile[100], clientfile;
	employee userr, employeefile;
	fstream client_file;
	ifstream employee_file;
	fstream transaction_file;
	//to make header
	transaction_file.open("transaction.txt");
	transaction_file << "ID" << '\t' << "Username" << '\t' << "Type of operation" << '\t' << "amount" << '\t' << "   Balance" << '\t' << "Time" << '\n';
	transaction_file.close();
	SetConsoleTitle("FCIS BANKING SYSTEMS "); // set title for console
	while (true)
	{//open scope of while true
		int amount, choice;
		int linesoffile = 0;
		int bill = rand() % 30 + 785;
		{     client_file.open("client.txt");//to save data of file in array so we can edit it
		while (client_file >> clientfile.id >> clientfile.username >> clientfile.password[0] >> clientfile.password[1] >> clientfile.password[2] >> clientfile.password[3] >> clientfile.balance)
		{
			arrayoffile[linesoffile].id = clientfile.id;
			arrayoffile[linesoffile].username = clientfile.username;
			for (int i = 0; i<4; i++)
			{
				arrayoffile[linesoffile].password[i] = clientfile.password[i];
			}
			arrayoffile[linesoffile].balance = clientfile.balance;
			linesoffile++;
		}
		client_file.close();
		}
		system("color F0");
		cout << "Client (1) \n\n";
		cout << "Employee (0) \n\n";

		cin >> choice;
		switch (choice)
		{//open scope of client or employee

		case 0:
		{ //open scope of employee case

			bool emploginn = emplogin(userr, employeefile);
			if (emploginn)
			{//open scope of login employee true

				cout << "Valid\n";
				cout << "Daily Transactions [1]                 " << endl;
				cout << "Search for a specific user [2]                 " << endl;
				cin >> choice;
				switch (choice)
				{//open scope of employee functions
				case 1://Daily Transactions
				{
					transaction_file.open("transaction.txt");
					cout << transaction_file.rdbuf();//to display the file
					transaction_file.close();
					break;
				}

				case 2://Search for user
				{
					bool check_user = checkuser2(user, clientfile);
					if (check_user)
					{

						search_transactionuser(user);
					}
					else cout << "Invalid\a \n";
					break;
				}
				default: //default of employee functions
				{
					cout << "Invalid input\a\n" << endl;

					break;
				}
				}//close scope of employee functions
			}//close scope of login employee true
			else{
				cout << "Invalid username or password\a" << endl;
			}
			break;
		}//close scope of login employee true

		case 1://open scope of client case
		{
			bool checklogin = login(user, clientfile); //to input and return true or false
			if (checklogin){
				cout << "Valid\n";

				bool return_choice;
				do
				{
					return_choice = true;
					system("pause");
					system("cls");
					cout << "Please select the operation you want to do" << endl;
					cout << "Withdraw cash[1]" << endl;
					cout << "Deposit [2]" << endl;
					cout << "Balance inquiry[3]" << endl;
					cout << "other[4]" << endl;

					cin >> choice;
					switch (choice)
					{//open scope of essential banking functions
					case 1:
					{
						amount = withdrawl(arrayoffile, user);
						editfile(arrayoffile, linesoffile);
						outputfile(user, "Withdraw", amount);
						break;
					}
					case 2:
					{
						amount = deposit(arrayoffile, user);
						editfile(arrayoffile, linesoffile);
						outputfile(user, "Deposited", amount);
						break;
					}
					case 3:
					{
						inquiry(user);
						outputfile(user, "Inquiry   ", user.balance);
						break;
					}

					case 4:
					{
						system("cls");
						system("color 1A");
						cout << "Transfer Funds[5]" << endl;
						cout << "Donate[6]" << endl;
						cout << "Bill Payment[7]" << endl;
						cout << "Print the last 5 transactions[8]" << endl;
						cin >> choice;
						system("cls");
						switch (choice)
						{//open scope of other banking functions
						case 5:
						{
							bool check_other_user = checkuser2(user2, clientfile); //check for the user we transfer to
							if (check_other_user)
							{
								amount = transfer(user, arrayoffile, user2);
								editfile(arrayoffile, linesoffile);
								outputfile(user, "transfer ", amount);
							}
							else cout << "Invalid id or user name\a\n";
							break;
						}
						case 6:
						{
							amount = donation(arrayoffile, user);
							editfile(arrayoffile, linesoffile);
							outputfile(user, "donation", amount);
							break;
						}
						case 7:
						{system("color 58");
						cout << "which bill do you want to pay" << endl;
						cout << "[1]Telephone bill" << endl;
						cout << "[2]Electricty bill" << endl;
						cout << "[3]Mobilephone bill" << endl;
						cin >> choice;
						switch (choice)
						{//open scope of  bill case
						case 1:
						{

							int billl = phone_bill(bill, user, arrayoffile);
							editfile(arrayoffile, linesoffile);
							outputfile(user, "pay telephone bill", billl);
							break;
						}

						case 2:
						{
							int billl = elec_bill(bill, user, arrayoffile);
							editfile(arrayoffile, linesoffile);
							outputfile(user, "pay electricity bill", billl);
							break;
						}

						case 3:
						{
							int billl = mob_bill(bill, user, arrayoffile);
							editfile(arrayoffile, linesoffile);
							outputfile(user, "pay mobile bill", billl);

							break;
						}

						default://bill
						{
							cout << "Invalid input\n" << endl;
							return_choice = false;
							break;
						}
						}//close scope of switch bill
						break;
						}
						case 8:
						{
							last_transaction(user);
							break;
						}
						default://scope of other banking functions
						{
							cout << "Invalid input\a\n" << endl;
							return_choice = false;
							break;
						}
						}//close scope of other banking functions
						break;
					}
					default://scope of essential banking functions
					{
						cout << "Invalid input\a\n" << endl;
						return_choice = false;
						break;
					}
					}//close scope of 1,2,3,4
				} while (!return_choice);
			}//end of if client login//end of client login
			else
			{
				cout << "Invalid password or username\a\n";
			}
			break;
		}//close scope of client case
		default://other of client&employee
		{
			cout << "Wrong choice\a" << endl;
			break;
		}
		}//close scope of client or employee
		cout << "* Thank you ^-^ *\n\n";
		system("Pause");
		system("cls");
	}//close scope of while true
	system("Pause");
}//close scope of main function


bool emplogin(employee&userr, employee employeefile)
{
	fstream employee_file;
	system("color 85");
	cout << "Please enter id : ";
	cin >> userr.id;
	cout << "Please enter username : ";
	cin >> userr.username;
	cout << "Please enter password : ";
	for (int i = 0; i<4; i++)
	{
		userr.password[i] = getch();
		cout << '*';
	}
	cout << endl;
	for (int i = 0; i<userr.username.length(); i++)  //to handel mistakes of entering upper or lower case letters
	{
		if (userr.username[i] >= 'A' && userr.username[i] <= 'Z')
		{
			userr.username[i] += 32;
		}
	}
	employee_file.open("employee.txt");
	while (employee_file >> employeefile.id >> employeefile.username >> employeefile.password[0] >> employeefile.password[1] >> employeefile.password[2] >> employeefile.password[3])
	{
		bool check_password = true;
		for (int i = 0; i<4; i++)
		{
			if (userr.password[i] != employeefile.password[i])
				check_password = false;
		}

		if (userr.id == employeefile.id && userr.username == employeefile.username && check_password)
			return true;
	}
	employee_file.close();
	return false;
}

bool login(client& user, client clientfile)
{
	int indexoffile = 0;
	fstream client_file;
	system("color 1A");
	cout << "Please enter id : ";
	cin >> user.id;
	cout << "Please enter username : ";
	cin >> user.username;
	cout << "Please enter password : ";
	for (int i = 0; i<4; i++)
	{
		user.password[i] = getch();
		cout << '*';
	}
	cout << endl;
	for (int i = 0; i<user.username.length(); i++)  //to handel mistakes of entering upper or lower case letters
	{
		if (user.username[i] >= 'A' && user.username[i] <= 'Z') { user.username[i] += 32; }
	}

	client_file.open("client.txt");
	while (client_file >> clientfile.id >> clientfile.username >> clientfile.password[0] >> clientfile.password[1] >> clientfile.password[2] >> clientfile.password[3] >> clientfile.balance)
	{
		bool check_password = true;
		for (int i = 0; i<4; i++)
		{
			if (user.password[i] != clientfile.password[i])check_password = false;
		}

		if (user.id == clientfile.id && user.username == clientfile.username && check_password)
		{
			user.balance = clientfile.balance;
			user.index = indexoffile;
			return true;
		}

		indexoffile++;
	}
	client_file.close();
	return false;
}

int withdrawl(client arrayoffile[], client &user)
{
	int amount;
	system("color 5A");
	cout << "Enter amount to be withdrawn :" << endl;
	cin >> amount;

	if (amount <= user.balance)
	{
		user.balance -= amount;
		cout << "Successfully\n";
	}
	else{
		cout << "Insufficient funds\a\n";
	}
	cout << "YOUR BALANCE ->" << user.balance << endl;
	arrayoffile[user.index].balance = user.balance;
	return amount;
}

int deposit(client arrayoffile[], client&user)
{
	int amount;
	system("color FD");
	cout << "Enter amount to be deposited" << endl;
	cin >> amount;
	cout << "PLease insert the money\n ";
	user.balance += amount;
	cout << amount << " is Successfully added to your account\n";
	cout << "YOUR BALANCE ->" << user.balance << endl;
	arrayoffile[user.index].balance = user.balance;
	return amount;
}

void inquiry(client&user)
{
	cout << "In your balance: ";
	cout << user.balance << endl;
}

bool checkuser2(client&user2, client clientfile)
{
	int index2offile = 0;
	fstream client_file;
	cout << "Enter id of account you want  \n";
	cin >> user2.id;
	cout << "Enter username of account you \n";
	cin >> user2.username;
	for (int i = 0; i<user2.username.length(); i++)  //to handel mistakes of entering upper or lower case letters
	{
		if (user2.username[i] >= 'A' && user2.username[i] <= 'Z') { user2.username[i] += 32; }
	}

	client_file.open("client.txt");
	while (client_file >> clientfile.id >> clientfile.username >> clientfile.password >> clientfile.balance)
	{
		if (user2.id == clientfile.id && user2.username == clientfile.username)
		{
			user2.balance = clientfile.balance;
			user2.index = index2offile;
			return true;
		}
		index2offile++;
	}
	client_file.close();
	return false;
}

int transfer(client&user, client arrayoffile[], client&user2)
{
	int amount;
	system("color 15");
	cout << "Enter amount to transfer" << endl;
	cin >> amount;
	if (amount <= user.balance)
	{
		user.balance -= amount;
		user2.balance += amount;
		cout << "Successfully transfered\n";
	}
	else{ cout << "Insufficient funds\n"; }

	cout << "YOUR BALANCE ->" << user.balance << endl;
	arrayoffile[user.index].balance = user.balance;
	arrayoffile[user2.index].balance = user2.balance;
	return amount;
}

int donation(client arrayoffile[], client&user)
{
	int amount;
	cout << "Enter amount to donate with" << endl;
	cin >> amount;

	if (amount <= user.balance)
	{
		user.balance -= amount;
		cout << "Successfully donated\n";
		cout << "YOUR BALANCE ->" << user.balance << endl;
		arrayoffile[user.index].balance = user.balance;
	}
	else
	{
		cout << "Insufficient funds\a\n";
	}
	return amount;
}

int phone_bill(int bill, client&user, client arrayoffile[])
{
	int phnum;
	cout << "Enter Telephone number" << endl;
	cin >> phnum;
	cout << "Your bill is " << bill << " $" << endl;
	if (bill <= user.balance)
	{
		user.balance -= bill;
		cout << "Successfully payed\n";
		arrayoffile[user.index].balance = user.balance;
	}
	else
	{
		cout << "Insufficient funds\a\n";
	}

	cout << "YOUR BALANCE ->" << user.balance << endl;
	return bill;
}

int elec_bill(int bill, client&user, client arrayoffile[])
{
	string add;
	int appnum;
	cout << "Enter your address and apartment number" << endl;
	cout << "Address <(without spaces)> :";
	cin >> add;
	cout << "Apartment number : ";
	cin >> appnum;
	cout << "Your bill is " << bill << " $" << endl;
	if (bill <= user.balance)
	{
		user.balance -= bill;
		cout << "Successfully payed\n";
	}
	else{ cout << "Insufficient funds\a\n"; }
	cout << "YOUR BALANCE ->" << user.balance << endl;
	arrayoffile[user.index].balance = user.balance;
	return bill;
}

int mob_bill(int bill, client&user, client arrayoffile[])
{
	int mobnum;
	cout << "Enter mobile number" << endl;
	cin >> mobnum;
	cout << "Your bill is " << bill << " $" << endl;
	if (bill <= user.balance)
	{
		user.balance -= bill;
		cout << "Successfully payed\n";
	}
	else
	{
		cout << "Insufficient funds\a\n";
	}

	cout << "YOUR BALANCE ->" << user.balance << endl;
	arrayoffile[user.index].balance = user.balance;
	return bill;
}

void editfile(client arrayoffile[], int linesoffile)
{
	fstream client_file("client.txt");
	client_file.open("client.txt", ios::trunc); //to delete the content of the file
	client_file.close();
	client_file.open("client.txt");
	for (int i = 0; i<linesoffile; i++)
	{
		client_file << arrayoffile[i].id << '\t' << arrayoffile[i].username << '\t' << arrayoffile[i].password[0] << arrayoffile[i].password[1] << arrayoffile[i].password[2] << arrayoffile[i].password[3] << '\t' << arrayoffile[i].balance << '\n';
	}
}

void outputfile(client user, string operation, int amount)
{
	time_t now = time(0);	// convert now to string form
	char* dt = ctime(&now);

	fstream transaction_file;
	transaction_file.open("transaction.txt", ios::app); // app to be in a newline
	transaction_file << user.id << '\t' << user.username << "\t\t" << operation << "\t\t" << amount << '\t' << "   " << user.balance << '\t' << '\t' << dt << '\n';				transaction_file.close();
}

void search_transactionuser(client user)
{
	fstream transaction_file;
	string line[100];//to read lines of file
	transaction_file.open("transaction.txt");
	int i = 0;
	while (getline(transaction_file, line[i])) // put lines of transactionfile in array to search on it
	{
		i++;
	}
	cout << line[0] << endl;//Titles of columns
	for (int j = 0; j <= i; j++)//loop for find username and cout this line
	{
		if (line[j].find(user.username) != string::npos)
		{
			cout << line[j] << endl;
		}
	}

}

void last_transaction(client user)
{
	fstream transaction_file;
	int count = 0;
	string line[100];
	transaction_file.open("transaction.txt", ios::in | ios::out);
	int i = 0;
	while (getline(transaction_file, line[i]))
	{
		i++;
	}
	cout << line[0] << endl;
	for (int j = i; j>0; j--) //to display from the bottom of the file
	{
		if (line[j].find(user.username) != string::npos)//search for any line that include the username
		{
			cout << line[j] << endl; count++;
		}
		if (count == 5)
			break;
	}

}
