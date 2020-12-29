/*	Author: Naveed Sheikh
	File Name: Account.h
	Revision History:
	12/27/2020 - Initial Commit
---------------------------------------------------------- - */
#ifndef SDDS_ACCOUNT_H__
#define SDDS_ACCOUNT_H__
#include <iostream>
using namespace std;
class Account{
	std::string m_name;
	int m_PIN;
	double m_checkingAmount;
	double m_savingsAmount;
public:
	Account();
	Account(const std::string& strAccount);
	void setName(string name);
	void setPIN(int PIN);
	void updateChecking(double amount, const char* action);
	void updateSavings(double amount, const char* action);
	std::string getName() const;
	int getPIN() const;
	double getChecking() const;
	double getSavings() const;
	friend ostream& operator<<(ostream& os, const Account& account);
};
#endif

