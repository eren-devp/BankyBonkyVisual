#include "Manager.hpp"

#pragma region Client
void Manager::AddClient(Client* client_)
{
	clients.push_back(client_);
}

void Manager::RemoveClient(Client* client_)
{
	clients.remove(client_);
}

std::list<Client*> Manager::GetClients()
{
    return clients;
}
#pragma endregion

#pragma region Employee
void Manager::AddEmployee(Employee* employee_)
{
	employees.push_back(employee_);
}

void Manager::RemoveEmployee(Employee* employee_)
{
	employees.remove(employee_);
}

std::list<Employee*> Manager::GetEmployees()
{
    return employees;
}
#pragma endregion
