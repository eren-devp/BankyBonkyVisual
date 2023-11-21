#include "Client.hpp"

Client::Client(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_, std::string password_) : User(firstName_, lastName_, age_, idNumber_, status_, Helper::PersonType::t_Client, password_)
{
	
}

Client::~Client()
{
	
}

std::string Client::GetMoney()
{
	return *money;
}

void Client::SetMoney(std::string money_)
{
	*money = money_;
}
