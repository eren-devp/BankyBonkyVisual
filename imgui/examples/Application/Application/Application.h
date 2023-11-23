#pragma once
#include <string>
#include <vector>
#include <Bits.h>

#include "imgui.h"
#include "Helper.h"
#include "Manager.hpp"

#define RED ImVec4(1, 0, 0, 1)
#define GREEN ImVec4(0, 1, 0, 1)
#define NIGHT_BLUE ImVec4(0, 0.35f, 1, 1)

class Application
{
public:
    Application();
    void Render();

private:
    void Login();
    void ManageClients();
    void ManageEmployees();
    void ManageEveryone();

    void ClientScreen();

    void GetNewUserInformations(Helper::PersonType t_type);
    void AddClient();
    void AddEmployee();
    void SetSelectedFunction(void(__thiscall Application::* newFunc)() );

    void(Application::* selectedFunction)() = &Application::Login;
    std::vector<void(Application::*)()> history = std::vector<void(Application::*)()>();

    ImVec4 INFORMATION_COLOR = GREEN;
    ImVec4 INPUT_COLOR = NIGHT_BLUE;


    ImVec2 FRAME_SIZE = ImVec2(200, 108);


    Manager* manager = new Manager();

    const char adminLoginUsername[12] = "admin";
    const char adminLoginPassword[6] = "admin";

    Client* client;
};
