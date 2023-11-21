#pragma once
#include "User.hpp"

class Employee : public User {
public:
	// Constructor function of the employee.
	Employee(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_, int salary_, std::string password_);

	// Returns the salary of the employee.
	int GetSalary();

	// Sets the salary of the employee.
	void SetSalary(int salary_);

private:
	int* salary = new int(0);
};
