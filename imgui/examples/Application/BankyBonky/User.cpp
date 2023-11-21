#include "User.hpp"

User::User(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_, Helper::PersonType personType_, std::string password_)
{
	SetFirstName(firstName_);
	SetLastName(lastName_);
	SetAge(age_);
	SetIDNumber(idNumber_);
	SetStatus(status_);
    SetPersonType(personType_);
    SetPassword(password_);
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

std::string User::GetPassword()
{
    return *password;
}

Helper::PersonType User::GetPersonType()
{
    return personType;
}

void User::SetFirstName(const std::string firstName_)
{
	if (firstName_.empty()) {
		throw std::exception("First name can not be empty.");
	}
	else {
		*firstName = firstName_;
	}
}

void User::SetLastName(const std::string lastName_)
{
	if (lastName_.empty()) {
		throw std::exception("Last name can not be empty.");
	}
	else {
		*lastName = lastName_;
	}
}

void User::SetAge(const int age_)
{
	if (age_ < 18) {
		throw std::exception("Person must be older than 18!");
	}
	else {
		*age = age_;
	}
}

void User::SetIDNumber(const std::string idNumber_)
{
	if (idNumber_.empty()) {
		throw std::exception("Not valid ID number.");
	}
	else {
		*idNumber = idNumber_;
	}
}

void User::SetStatus(const std::string status_)
{
	*status = status_;
}

void User::SetPassword(const std::string password_)
{
    *password = password_;
}

void User::SetPersonType(const Helper::PersonType type_)
{
    personType = type_;
}
