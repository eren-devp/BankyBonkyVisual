#include "Client.hpp"

Client::Client(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_, std::string password_) : User(firstName_, lastName_, age_, idNumber_, status_, Helper::PersonType::t_Client, password_)
{
	
}

Client::~Client()
{
	
}

long long int Client::GetMoney()
{
	return *money;
}

std::string Client::GetMoneyS()
{
    return std::to_string(GetMoney());
}

void Client::SetMoney(unsigned long long int money_)
{
	*money = money_;
}

void Client::WithdrawMoney(unsigned long long int amount)
{
    if (*money >= amount)
    {
        *money -= amount;
    }
}

void Client::DepositMoney(unsigned long long int amount)
{
    *money += amount;
}
