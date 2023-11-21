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

std::deque<std::tuple<std::string, std::string, Helper::PersonType, std::string>> Manager::GetLoginTuples()
{
    std::deque<std::tuple<std::string, std::string, Helper::PersonType, std::string>> loginTuples;
   
    for (auto person : GetEmployees())
    {
        loginTuples.push_back(std::make_tuple(person->GetIDNumber(), person->GetPassword(), Helper::PersonType::t_Employee, person->GetFirstName()));
    }
    for (auto person : GetClients())
    {
        loginTuples.push_back(std::make_tuple(person->GetIDNumber(), person->GetPassword(), Helper::PersonType::t_Client, person->GetFirstName()));
    }

    return loginTuples;
}
#pragma endregion
