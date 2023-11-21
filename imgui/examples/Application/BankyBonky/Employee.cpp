#include "Employee.hpp"

Employee::Employee(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_, int salary_, std::string password_) : User(firstName_, lastName_, age_, idNumber_, status_, Helper::PersonType::t_Employee, password_)
{
	SetSalary(salary_);
}

int Employee::GetSalary()
{
	return *salary;
}

void Employee::SetSalary(int salary_)
{
	if (salary_ < 0) {
		throw std::exception("Salary must be more than 0.");
	}
	else {
		*salary = salary_;
	}
}
