#pragma once
#include "User.hpp"
#include <string>

class Client : public User {
public:
	// Constructor function of the client.
	Client(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_, std::string password_);

	// Destructor function of the client.
	~Client();

	// Returns the current money of the client.
    long long int GetMoney();

    std::string GetMoneyS();

	// Sets the current money of the client.
	void SetMoney(unsigned long long int money_);

    // Withdraws money from the client.
    void WithdrawMoney(unsigned long long int amount);

    void DepositMoney(unsigned long long int amount);
private:
	unsigned long long int* money = new unsigned long long int;
};
