/*	Author: Naveed Sheikh
	Revision Date: 12/28/2020
	File Name: Account.cpp
---------------------------------------------------------- - */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip> 
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include "Account.h"
using namespace std;

Account::Account() {
	m_name = "";
	m_PIN = 0000;
	m_checkingAmount = 0.0;
	m_savingsAmount = 0.0;
}

Account::Account(const std::string& strAccount) {
	string temp = strAccount;

	size_t position = temp.find(",");
	m_name = temp.substr(0, position);
	temp.erase(0, position + 1);

	position = temp.find(",");
	m_PIN = stoi(temp.substr(0, position));
	temp.erase(0, position + 1);

	position = temp.find(",");
	m_checkingAmount = stod(temp.substr(0, position));
	temp.erase(0, position + 1);

	m_savingsAmount = stod(temp);
}

void Account::setName(string name) {
	m_name = name;
}

void Account::setPIN(int PIN) {
	m_PIN = PIN;
}

void Account::updateChecking(double amount, const char* action) {
	if (action == "a")
		m_checkingAmount += amount;
	else if (action == "s")
		m_checkingAmount -= amount;
}

void Account::updateSavings(double amount, const char* action) {
	if (action == "a")
		m_savingsAmount += amount;
	else if (action == "s")
		m_savingsAmount -= amount;
}

string Account::getName() const {
	return m_name;
}

int Account::getPIN() const {
	return m_PIN;
}

double Account::getChecking() const {
	return m_checkingAmount;
}

double Account::getSavings() const {
	return m_savingsAmount;
}

ostream& operator<<(ostream& os, const Account& account) {
	os << setw(20) << right << account.getName() << " | ";
	os << setw(5) << right << account.getChecking() << " | ";
	os << account.getSavings() << endl;
	return os;
}