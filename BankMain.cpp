/*	Author: Naveed Sheikh
	File Name: BankMain.cpp
	Revision History: 
	12/27/2020 - Initial Commit
	12/28/2020 - Added function declarations and definitions
	12/29/2020 - saveData() function completed
---------------------------------------------------------- - */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Account.h"

/***********************************
 All accounts stored in this STL container
 ***********************************/
vector<Account> accounts;

/***********************************
 function declarations
 ***********************************/
void header();
int mainMenu();
void loadData(const char* filename);
int accountType();
int checkPIN(int PIN);
void viewAccount(int index);
void saveData(const char* file);

/***********************************
 Main function
 ***********************************/
int main(int argc, char** argv) {
	//This try catch block tries to load data from file into the STL container and throws an error if it fails
	try {
		loadData(argv[1]);
	}
	catch (const std::string& msg) {
		cout << msg << std::endl;
	}

	int choice = -1;
	while (choice != 0) {
		header();
		int PIN;
		cout << "Enter your PIN number: ";
		cin >> PIN;
		if (checkPIN(PIN) == 0) {
			//Print error if PIN number does not match an existing PIN
			cout << "Incorrect PIN." << endl;
		}
		else {
			//get index of current account in accounts STL container
			int index = 0;
			double amount = 0.0;
			for (int i = 0; i < accounts.size(); i++) {
				if (accounts[i].getPIN() == PIN) {
					index = i;
				}
			}
			choice = mainMenu();
			switch (choice) {
			//Exit
			case 0:
				break;
			//Deposit
			case 1:
				//Checking
				if (accountType() == 1) {
					cout << "Account Balance: $" << accounts[index].getChecking() << endl;
					cout << "Select Amount: $";
					cin >> amount;
					accounts[index].updateChecking(amount, "a");
					cout << "New Balance: $" << accounts[index].getChecking() << endl << endl;
				}
				//Savings
				else {
					cout << "Account Balance: $" << accounts[index].getSavings() << endl;
					cout << "Select Amount: $";
					cin >> amount;
					accounts[index].updateSavings(amount, "a");
					cout << "New Balance: $" << accounts[index].getSavings() << endl << endl;
				}
				break;
			// Withdraw
			case 2:
				//Checking
				if (accountType() == 1) {
					cout << "Account Balance: $" << accounts[index].getChecking() << endl;
					cout << "Select Amount: $";
					cin >> amount;
					//Validation to make sure user can only withdraw an amount that already exists in the account
					while (amount <= 0 || amount > accounts[index].getChecking()) {
						cout << "Invalid amount, please enter an amount between $1 and $" << accounts[index].getChecking() << ": ";
						cin >> amount;
					}
					accounts[index].updateChecking(amount, "s");
					cout << "New Balance: $" << accounts[index].getChecking() << endl << endl;
				}
				//Savings
				else {
					cout << "Account Balance: $" << accounts[index].getSavings() << endl;
					cout << "Select Amount: $";
					cin >> amount;
					//Validation to make sure user can only withdraw an amount that already exists in the account
					while (amount <= 0 || amount > accounts[index].getSavings()) {
						cout << "Invalid amount, please enter an amount between $1 and $" << accounts[index].getSavings() << ": ";
						cin >> amount;
					}
					accounts[index].updateSavings(amount, "s");
					cout << "New Balance: $" << accounts[index].getSavings() << endl << endl;
				}
				break;
			//View Statement
			case 3:
				viewAccount(index);
				break;
			}
		}
	}
	saveData(argv[1]);
	cout << "Signing out!..." << endl;
}

/***********************************
 Print Header
 ***********************************/
void header() {
	cout << "==============================" << endl;
	cout << "|          ATM BANK          |" << endl;
	cout << "|    Author: Naveed Sheikh   |" << endl;
	cout << "==============================" << endl;
	
}

/***********************************
 Main menu function
 ***********************************/
int mainMenu() {
	int option;
	cout << "=================================" << endl;
	cout << "1) Deposit" << endl;
	cout << "2) Withdraw" << endl;
	cout << "3) View Account Statement" << endl;
	cout << "0) Exit" << endl;
	cout << "=================================" << endl;
	cout << "Enter an option (0-3): ";
	cin >> option;
	while (option != 0 && option != 1 && option != 2 && option != 3) {
		cout << "=================================" << endl;
		cout << "1) Deposit" << endl;
		cout << "2) Withdraw" << endl;
		cout << "3) View Account Statement" << endl;
		cout << "0) Exit" << endl;
		cout << "=================================" << endl;
		cout << "You entered a wrong value. Enter an option (0-1): ";
		cin >> option;
	}
	return option;
}

/***********************************
Loading data from file into accounts vector
 ***********************************/
void loadData(const char* filename) {
	//Counting number of lines in the file
	int number_of_lines = 0;
	std::string line;
	std::ifstream myfile(filename);

	while (std::getline(myfile, line))
		++number_of_lines;
	myfile.close();

	std::ifstream file(filename);
	if (!file) {
		//Throw an error if file can't open
		throw string("\n***Failed to open file ") + string(filename) + string(" ***\n");
	}
	std::string strAccount;
	for (auto i = 0u; i < number_of_lines; ++i) {
		std::getline(file, strAccount);
		// if the previous operation failed, the "file" object is
		//   in error mode
		if (file) {
			// Check if this is a commented line.
			//   In the input file, commented lines start with '#'
			if (strAccount[0] != '#')
				accounts.push_back(Account(strAccount));
			else
				--i;
		}
	}
	//Creating an Account object using one argument constructor for each account in the text file and adding it to the accounts container
	for (auto i = 0u; i < number_of_lines; i++) {
		std::getline(file, strAccount);
		if (file) {
			if (strAccount[0] != '#')
				accounts.push_back(Account(strAccount));
		}
	}
	file.close();
}

/***********************************
 Menu for selecting account type
 ***********************************/
int accountType() {
	int option;
	cout << endl << "====================" << endl;
	cout << "1) Checking" << endl;
	cout << "2) Savings" << endl;
	cout << "Enter an option (1-2): ";
	cin >> option;
	while (option != 1 && option != 2) {
		cout << endl << "====================" << endl;
		cout << "1) Checking" << endl;
		cout << "2) Savings" << endl;
		cout << "You entered a wrong value. Enter an option (1-2): ";
		cin >> option;
	}
	return option;
}

/***********************************
 Checks entered PIN number with stored PIN numbers in accounts
 ***********************************/
int checkPIN(int PIN) {
	int found = 0;
	for (int i = 0; i < accounts.size(); i++)
		if (accounts[i].getPIN() == PIN)
			found = 1;
	return found;
}

/***********************************
 View account balance and information
 ***********************************/
void viewAccount(int index) {
	cout << endl << "===============================" << endl;
	cout << "Account holder: " << accounts[index].getName() << endl;
	cout << "Checking account balance: " << accounts[index].getChecking() << endl;
	cout << "Savings account balance: " << accounts[index].getSavings() << endl;
	cout << "===============================" << endl << endl;
}

/***********************************
 Saves updated data to file
 ***********************************/
void saveData(const char* file) {
	string text;
	for (int i = 0; i < accounts.size(); i++) {
		text += accounts[i].getName();
		text += ", ";
		text += to_string(accounts[i].getPIN());
		text += ", ";
		text += to_string(accounts[i].getChecking());
		text += ", ";
		text += to_string(accounts[i].getSavings());
		text += "\n";
	}
	std::ofstream ofs(file, std::ofstream::trunc);
	ofs << text;
}
