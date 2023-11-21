#pragma once
#include <iostream>
#include <Helper.h>

// User class is the superclass of the other sub-classes. It contains common veriables and functions.
class User {
public:
	// Base constructor function of the person. 
	User(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_, Helper::PersonType personType_, std::string password_);

	// Returns the first name of the person.
    std::string GetFirstName();

	// Returns the last name of the person.
    std::string GetLastName();

	// Returns the status of the person.
    std::string GetStatus();

	// Returns age of the person.
	int GetAge();

	// Returns ID number of the person.
    std::string GetIDNumber();

    // Returns the password of the person.
    std::string GetPassword();

    // Returns the type of the person.
    Helper::PersonType GetPersonType();


	// Sets the first name of the person.
	void SetFirstName(const std::string firstName_);

	// Sets the last name of the person.
	void SetLastName(const std::string lastName_);

	// Sets the age of the person.
	void SetAge(const int age_);

	// Sets the ID number of the person.
	void SetIDNumber(const std::string idNumber_);

	// Sets the status of the person.
	void SetStatus(const std::string status_);

    // Sets the password of the person.
    void SetPassword(const std::string password_);

    // Sets the person type of the person.
    void SetPersonType(const Helper::PersonType type_);

	bool operator == (const User& user) const {
        return user.idNumber == this->idNumber;
	}

private:
    std::string* firstName = new std::string;
    std::string* lastName = new std::string;
    std::string* status = new std::string;
	int* age = new int;
    std::string* idNumber = new std::string;
    std::string* password = new std::string;

    Helper::PersonType personType;
};
