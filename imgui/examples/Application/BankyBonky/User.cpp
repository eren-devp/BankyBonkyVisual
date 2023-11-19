#include "User.hpp"

User::User(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_)
{
	SetFirstName(firstName_);
	SetLastName(lastName_);
	SetAge(age_);
	SetIDNumber(idNumber_);
	SetStatus(status_);
}

std::string User::GetFirstName()
{
	return *firstName;
}

std::string User::GetLastName()
{
	return *lastName;
}

std::string User::GetStatus()
{
	return *status;
}

int User::GetAge()
{
	return *age;
}

std::string User::GetIDNumber()
{
	return *idNumber;
}

void User::SetFirstName(std::string firstName_)
{
	if (firstName_.empty()) {
		throw std::exception("First name can not be empty.");
	}
	else {
		*firstName = firstName_;
	}
}

void User::SetLastName(std::string lastName_)
{
	if (lastName_.empty()) {
		throw std::exception("Last name can not be empty.");
	}
	else {
		*lastName = lastName_;
	}
}

void User::SetAge(int age_)
{
	if (age_ < 18) {
		throw std::exception("Person must be older than 18!");
	}
	else {
		*age = age_;
	}
}

void User::SetIDNumber(std::string idNumber_)
{
	if (idNumber_.empty()) {
		throw std::exception("Not valid ID number.");
	}
	else {
		*idNumber = idNumber_;
	}
}

void User::SetStatus(std::string status_)
{
	*status = status_;
}
