#pragma once
#include "User.hpp"

class Client : public User {
public:
	// Constructor function of the client.
	Client(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_, std::string password_);

	// Destructor function of the client.
	~Client();

	// Returns the current money of the client.
	std::string GetMoney();

	// Sets the current money of the client.
	void SetMoney(std::string money_);
private:
	std::string* money = new std::string;
};
