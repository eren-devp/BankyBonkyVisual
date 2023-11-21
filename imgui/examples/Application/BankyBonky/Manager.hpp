#pragma once
#include <list>
#include <iterator>
#include <deque>
#include <tuple>
#include <Helper.h>

#include "Client.hpp"
#include "Employee.hpp"

// Management system of the saved people on bank system.
class Manager {
public:
    Manager()
    {
        
    }

#pragma region Client
	// Add client to client list.
	void AddClient(Client* client_);

	// Remove client from the client list.
	void RemoveClient(Client* client_);

    std::list<Client*> GetClients();
#pragma endregion

#pragma region Employee
	// Add employee to employee list.
	void AddEmployee(Employee* employee_);

	// Remove employee from the employee list.
	void RemoveEmployee(Employee* employee_);

    std::list<Employee*> GetEmployees();
#pragma endregion

    // Returns the saved Employee or Clients.
    std::deque<std::tuple<std::string, std::string, Helper::PersonType, std::string>> GetLoginTuples();

private:
	std::list<Client*> clients;
	std::list<Employee*> employees;
};
