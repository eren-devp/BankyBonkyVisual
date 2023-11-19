#include "Application.h"

Application::Application()
{
    Client* cl = new Client("1", "1", 20, "12704324542", "vip");
    Client* cdl = new Client("2", "2", 20, "12705324542", "vip");
    Client* asd = new Client("3", "3", 20, "12704324942", "vip");
    Client* as = new Client("4", "4", 20, "12305324542", "vip");
    Client* ff = new Client("5", "5", 20, "12706324542", "vip");
    Client* fff = new Client("6", "6", 20, "12705124542", "vip");
    manager->AddClient(cl);
    manager->AddClient(cdl);
    manager->AddClient(asd);
    manager->AddClient(as);
    manager->AddClient(ff);
    manager->AddClient(fff);
}

void Application::Login()
{
    ImGui::InputTextWithHint("username", "enter the username", username, IM_ARRAYSIZE(username), ImGuiInputTextFlags_Password);

    ImGui::InputTextWithHint("password", "enter the password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

    ImGui::Text(username);
    ImGui::Text(password);
    ImGui::Text(loginUsername);
    ImGui::Text(loginPassword);

    if (std::string(loginUsername) == std::string(username) && (std::string(loginPassword) == std::string(password)))
    {
        SetSelectedFunction(&Application::ManageEveryone);

        memset(username, 0, sizeof username);
        memset(password, 0, sizeof password);
    }
}

void Application::GetNewUserInformations(PersonType t_type)
{
    static char firstName[16];
    static char lastName[16];
    static char status[16];
    static int age = 18;
    static char idNumber[12];
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

    ImGui::TextColored(INPUT_COLOR, "Age: ");
    ImGui::TableNextColumn();
    ImGui::DragInt("age", &age, 1, 18, 120);

    if (t_type == PersonType::t_Employee)
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::TextColored(INPUT_COLOR, "Salary: ");
        ImGui::TableNextColumn();
        ImGui::InputInt("salary", &salary);
    }

    if (ImGui::Button("Reset"))
    {
        memset(firstName, 0, sizeof firstName);
        memset(lastName, 0, sizeof lastName);
        memset(status, 0, sizeof status);
        memset(idNumber, 0, sizeof idNumber);
        age = 18;
        salary = 0;
    }
    ImGui::SameLine();
    if (ImGui::Button("Add"))
    {
        if (t_type == PersonType::t_Client)
            manager->AddClient(new Client(firstName, lastName, age, idNumber, status));

        else if (t_type == PersonType::t_Employee)
            manager->AddEmployee(new Employee(firstName, lastName, age, idNumber, status, salary));

        memset(firstName, 0, sizeof firstName);
        memset(lastName, 0, sizeof lastName);
        memset(status, 0, sizeof status);
        memset(idNumber, 0, sizeof idNumber);
        age = 18;
        salary = 0;
    }
    
    ImGui::EndTable();
}

void Application::AddClient()
{
    GetNewUserInformations(PersonType::t_Client);
}

void Application::AddEmployee()
{
    GetNewUserInformations(PersonType::t_Employee);
}

void Application::SetSelectedFunction(void(__thiscall Application::*newFunc)())
{
    history.push_back(newFunc);
    selectedFunction = newFunc;
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
