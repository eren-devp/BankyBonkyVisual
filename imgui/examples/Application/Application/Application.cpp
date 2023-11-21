#include "Application.h"


Application::Application()
{
    Client* me = new Client("talha", "genc", 20, "12704324542", "vip", "asdf");
    Client* testClient = new Client("2", "2", 20, "12705324542", "vip", "a");
    Client* testClient2 = new Client("3", "3", 20, "12704324942", "vip", "a");
    Client* testClient3 = new Client("4", "4", 20, "12305324542", "vip", "a");
    Client* testClient4 = new Client("5", "5", 20, "12706324542", "vip", "a");
    Client* testClient5 = new Client("6", "6", 20, "12705124542", "vip", "a");
    manager->AddClient(me);
    manager->AddClient(testClient);
    manager->AddClient(testClient2);
    manager->AddClient(testClient3);
    manager->AddClient(testClient4);
    manager->AddClient(testClient5);

    Employee* testEmployee = new Employee("burak", "ergul", 21, "12121212121", "manager", 30000,"aa");
    manager->AddEmployee(testEmployee);
}

template<size_t N> void ResetCharArray(char(&arr)[N]) { memset(&arr, 0, sizeof(arr)); }

void Application::Login()
{
    static char username[12] = "";
    static char password[6] = "";

    ImGui::InputTextWithHint("username", "enter the username", username, IM_ARRAYSIZE(username), ImGuiInputTextFlags_Password);
    ImGui::InputTextWithHint("password", "enter the password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

    ImGui::Text(username);
    ImGui::Text(password);

    ImGui::Spacing(); ImGui::SameLine();

    if (ImGui::Button("login", ImVec2(100, 50)))
    {
        for (auto person : manager->GetLoginTuples())
        {
            if (std::get<0>(person) == std::string(username) && std::get<1>(person) == std::string(password))
            {
                if (std::get<2>(person) == Helper::PersonType::t_Client)
                {
                    SetSelectedFunction(&Application::ClientScreen);
                    firstName = std::get<3>(person);

                    ResetCharArray(username);
                    ResetCharArray(password);
                }
                else
                {
                    SetSelectedFunction(&Application::ManageClients);

                    ResetCharArray(username);
                    ResetCharArray(password);
                }
            }
            else if (std::string(adminLoginUsername) == std::string(username) && (std::string(adminLoginPassword) == std::string(password)))
            {
                SetSelectedFunction(&Application::ManageEveryone);

                ResetCharArray(username);
                ResetCharArray(password);
            }
        }
    }
}

void Application::GetNewUserInformations(Helper::PersonType t_type)
{
    static char firstName[16];
    static char lastName[16];
    static char status[16];
    static char idNumber[12];
    static char password[16];
    static int age = 18;
    static int salary;

    ImGui::BeginTable("Input-Table", 3);

    ImGui::TableNextColumn();

    ImGui::TextColored(INPUT_COLOR, "First name:");
    ImGui::TableNextColumn();
    ImGui::InputText("firstname", firstName, IM_ARRAYSIZE(firstName), false);

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGui::TextColored(INPUT_COLOR, "Last name:");
    ImGui::TableNextColumn();
    ImGui::InputText("lastname", lastName, IM_ARRAYSIZE(lastName), false);

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGui::TextColored(INPUT_COLOR, "ID Number: ");
    ImGui::TableNextColumn();
    ImGui::InputText("idNumber", idNumber, IM_ARRAYSIZE(idNumber), false);

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGui::TextColored(INPUT_COLOR, "Status:");
    ImGui::TableNextColumn();
    ImGui::InputText("status", status, IM_ARRAYSIZE(status), false);

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGui::TextColored(INPUT_COLOR, "Password:");
    ImGui::TableNextColumn();
    ImGui::InputText("password", password, IM_ARRAYSIZE(password), false);

    ImGui::TableNextRow();
    ImGui::TableNextColumn();

    ImGui::TextColored(INPUT_COLOR, "Age: ");
    ImGui::TableNextColumn();
    ImGui::DragInt("age", &age, 1, 18, 120);

    if (t_type == Helper::PersonType::t_Employee)
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::TextColored(INPUT_COLOR, "Salary: ");
        ImGui::TableNextColumn();
        ImGui::InputInt("salary", &salary);
    }

    if (ImGui::Button("Reset"))
    {
        ResetCharArray(firstName);
        ResetCharArray(lastName);
        ResetCharArray(status);
        ResetCharArray(idNumber);
        ResetCharArray(password);
        age = 18;
        salary = 0;
    }
    ImGui::SameLine();

    if (ImGui::Button("Add"))
    {
        if (t_type == Helper::PersonType::t_Client)
            manager->AddClient(new Client(firstName, lastName, age, idNumber, status, password));

        else if (t_type == Helper::PersonType::t_Employee)
            manager->AddEmployee(new Employee(firstName, lastName, age, idNumber, status, salary, password));

        ResetCharArray(firstName);
        ResetCharArray(lastName);
        ResetCharArray(status);
        ResetCharArray(idNumber);
        ResetCharArray(password);
        age = 18;
        salary = 0;
    }
    
    ImGui::EndTable();
}

void Application::AddClient() { GetNewUserInformations(Helper::PersonType::t_Client); }

void Application::AddEmployee() { GetNewUserInformations(Helper::PersonType::t_Employee); }

void Application::SetSelectedFunction(void(__thiscall Application::*newFunc)())
{
    history.push_back(newFunc);
    selectedFunction = newFunc;
}

// TODO
void Application::ClientScreen()
{
    ImGui::BeginTable("client-screen", 3);
    ImGui::TableNextColumn();
    // 1, 1

    ImGui::TableNextColumn();
    // 1, 2

    ImGui::TableNextColumn();
    // 1, 3

    ImGui::TextColored(NIGHT_BLUE, ("Welcome back " + firstName).c_str());

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    // 2, 1

    ImGui::EndTable();
}

void Application::ManageClients()
{
    ImGui::Spacing();
    ImGui::Spacing(); ImGui::SameLine(); ImGui::Spacing(); ImGui::SameLine();
    if (manager->GetClients().size() == 0)
        ImGui::TextColored(RED, "No Employee!");
    else
    {
        int i = 0;
        ImGui::BeginTable("Client-Table", 5);

        for (Client* client : manager->GetClients())
        {
            if (i % 5 == 0)
                ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::BeginChildFrame(std::strtoll(client->GetIDNumber().c_str(), NULL, 11), FRAME_SIZE);
            ImGui::TextColored(INFORMATION_COLOR, "First Name: ");
            ImGui::SameLine(); ImGui::Text(client->GetFirstName().c_str());

            ImGui::TextColored(INFORMATION_COLOR, "Last Name: ");
            ImGui::SameLine(); ImGui::Text(client->GetLastName().c_str());

            ImGui::TextColored(INFORMATION_COLOR, "Age: ");
            ImGui::SameLine(); ImGui::Text(std::to_string(client->GetAge()).c_str());
            
            ImGui::TextColored(INFORMATION_COLOR, "ID Number: ");
            ImGui::SameLine(); ImGui::Text(client->GetIDNumber().c_str());

            ImGui::TextColored(INFORMATION_COLOR, "Money on Account: ");
            ImGui::SameLine(); ImGui::Text(client->GetMoney().c_str());

            ImGui::TextColored(INFORMATION_COLOR, "Status: ");
            ImGui::SameLine(); ImGui::Text(client->GetStatus().c_str());

            ImGui::EndChildFrame();

            i++;
        }
        ImGui::EndTable();
    }
}

void Application::ManageEmployees()
{
    ImGui::Spacing();
    ImGui::Spacing(); ImGui::SameLine(); ImGui::Spacing(); ImGui::SameLine();

    if (manager->GetEmployees().size() == 0)
        ImGui::TextColored(RED, "No Employee!");
    else
    {
        int i = 0;
        ImGui::BeginTable("Employee-Table", 5);
        for (Employee* employee : manager->GetEmployees())
        {
            if (i % 5 == 0)
                ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::BeginChildFrame(std::strtoll(employee->GetIDNumber().c_str(), NULL, 11), FRAME_SIZE);
            ImGui::TextColored(INFORMATION_COLOR, "First Name: ");
            ImGui::SameLine(); ImGui::Text(employee->GetFirstName().c_str());

            ImGui::TextColored(INFORMATION_COLOR, "Last Name: ");
            ImGui::SameLine(); ImGui::Text(employee->GetLastName().c_str());

            ImGui::TextColored(INFORMATION_COLOR, "Age: ");
            ImGui::SameLine(); ImGui::Text(std::to_string(employee->GetAge()).c_str());

            ImGui::TextColored(INFORMATION_COLOR, "ID Number: ");
            ImGui::SameLine(); ImGui::Text(employee->GetIDNumber().c_str());

            ImGui::TextColored(INFORMATION_COLOR, "Salary: ");
            ImGui::SameLine(); ImGui::Text(std::to_string(employee->GetSalary()).c_str());

            ImGui::TextColored(INFORMATION_COLOR, "Status: ");
            ImGui::SameLine(); ImGui::Text(employee->GetStatus().c_str());

            ImGui::EndChildFrame();

            i++;
        }
        ImGui::EndTable();
    }
}

void Application::ManageEveryone()
{
    if (ImGui::CollapsingHeader("Clients", ImGuiTreeNodeFlags_None))
    {
        ImGui::Spacing(); ImGui::SameLine();
        if(ImGui::CollapsingHeader("Show Clients"))
            this->ManageClients();

        ImGui::Spacing(); ImGui::SameLine();
        if (ImGui::Button("Add New Client"))
        {
            SetSelectedFunction(&Application::AddClient);
        }
    }
    ImGui::Separator();
    if (ImGui::CollapsingHeader("Employees", ImGuiTreeNodeFlags_None))
    {
        ImGui::Spacing(); ImGui::SameLine();
        if(ImGui::CollapsingHeader("Show Employees"))
            this->ManageEmployees();

        ImGui::Spacing(); ImGui::SameLine();
        if (ImGui::Button("Add Employee"))
        {
            SetSelectedFunction(&Application::AddEmployee);
        }
    }
}

void Application::Render()
{
#pragma region DockSpace
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
            if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
            if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
            if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();
#pragma endregion
    
#pragma region Viewport
    ImGui::Begin("Viewport");
    
    if (history.size() >= 2)
    {
        if (ImGui::ArrowButton("Back", 0))
        {
            history.pop_back();
            SetSelectedFunction(history.back());
            history.pop_back();
        }
    }

    (this->*selectedFunction)();

    ImGui::End();
#pragma endregion

    ImGui::ShowDemoWindow();
}
