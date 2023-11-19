#include "Client.hpp"

Client::Client(std::string firstName_, std::string lastName_, int age_, std::string idNumber_, std::string status_) : User(firstName_, lastName_, age_, idNumber_, status_)
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
