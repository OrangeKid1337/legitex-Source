#pragma once
#ifndef gui_cpp
#define gui_cpp
#include "gui.hpp"
int tab = 0;
ImU32 rainbow()
{
    auto pos = ImGui::GetWindowPos();
    auto size = ImGui::GetWindowSize();
    float rainbowSpeed = 0.001;
    static float staticHue = 0;

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    staticHue -= rainbowSpeed;
    if (staticHue < -1.f) staticHue += 1.f;
    for (int i = 0; i < 3; i++)
    {
        float hue = staticHue + (1.f / (float)3) * i;
        if (hue < 0.f) hue += 1.f;
        ImColor cRainbow = ImColor::HSV(hue, 1.f, 1.f);
        draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 0), ImVec2(pos.x + 545, pos.y + 7), ImColor(0, 183, 255));
    }
    return rainbowSpeed;
}
ImColor rainbow_color()
{
    float rainbowSpeed = 0.001;
    static float staticHue = 0;
    staticHue -= rainbowSpeed;
    ImColor cRainbow;
    for (int i = 0; i < 3; i++)
    {
        float hue = staticHue + (1.f / (float)3) * i;
        if (hue < 0.f) hue += .1f;
        cRainbow = ImColor::HSV(hue, 1.f, 1.f);
        //std::cout << std::to_string(hue) + "\n";
        //if (hue < 1.f) hue += 0.0f;
    }
    return cRainbow;
}
void check()
{

    ImGui::SetCursorPos(ImVec2(13, 320));
   
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 4));
        if (ImGui::tab("aimbot", 0 == tab)) tab = 0;
        ImGui::SetCursorPos(ImVec2(100, 320));
        if (ImGui::tab("visuals", 1 == tab)) tab = 1;
        ImGui::SetCursorPos(ImVec2(180, 320));
        if (ImGui::tab("misc", 2 == tab)) tab = 2;
       
           
      
       // if (ImGui::tab("weapon", 3 == tab)) tab = 3;
        ImGui::PopStyleVar();
    
   
}

ImU32 __fastcall FtIM2(float* color) {
    return ImGui::ColorConvertFloat4ToU32(ImVec4(color[0], color[1], color[2], color[3]));
}

void c_gui::draw()
{
    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF,
        0x0400, 0x044F,
        0,
    };
    ImFontConfig font_config;
    font_config.OversampleH = 1;
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;
    ImFont* icon = nullptr;
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = ImGui::GetStyle().Colors;
    icon = io.Fonts->AddFontFromMemoryTTF((void*)icon, sizeof(icon), 25, &font_config, ranges);

    if (vars.fov == true)
    {
        ImGui::Begin("##CIRCLE", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
        auto draw = ImGui::GetBackgroundDrawList();
        draw->AddCircle(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2), vars.fovamount, FtIM2(vars.fovcolor), 100, 1.0f);
        ImGui::End();
    }
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    POINT mPos;
    GetCursorPos(&mPos);
    ImVec2 window_size = ImVec2(280, 380);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowPos(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2 - window_size.x / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - window_size.y / 2), ImGuiCond_Once);
    
        
    if (vars.g_open)
    {


        ImGui::Begin("##MENU", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar );
        {
            ImGui::PushFont(icon);
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            auto pos = ImGui::GetWindowPos();
            auto size = ImGui::GetWindowSize();
            bool isHovering = mPos.x >= pos.x && mPos.y >= pos.y && mPos.x <= (pos.x + size.x) && mPos.y <= (pos.y + size.y);

            if (isHovering)
                GAPI::EnableInput();
            else if (!isHovering)
                GAPI::DisableInput();
           
            ImGui::SetNextWindowBgAlpha(1.f);
            //draw_list->AddRectFilled(pos, ImVec2(pos.x + 545, pos.y + 355), ImColor(38, 38, 42), 9);
           // draw_list->AddRectFilled(pos, ImVec2(pos.x + 545, pos.y + 355), ImGui::GetColorU32(ImGuiCol_WindowBg), 9);
           // draw_list->AddRectFilled(ImVec2(pos.x, pos.y + 30), ImVec2(pos.x + 130, pos.y + 355), ImGui::GetColorU32(ImGuiCol_TabBar), 9, 4);
            //draw_list->AddLine(ImVec2(pos.x, pos.y + 8), ImVec2(pos.x + 545, pos.y + 8), ImColor(38, 38, 42));

           

            switch (tab)
            {
                break;
            case 0: //aimbot

                ImGui::SetCursorPos(ImVec2(5, 7));
                ImGui::BeginChild("", ImVec2(270, 365));
                {
                    ImGui::SetCursorPos(ImVec2(5, 10));
                    ImGui::Text("legitex");
                    draw_list->AddRectFilled(ImVec2(0, 12), ImVec2(pos.x, pos.y - 5), rainbow());
                    check();
                   // ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(13 / 255.f, 13 / 255.f, 13 / 255.f));
                    ImGui::SetCursorPos(ImVec2(5, 10));
                    ImGui::BeginChild("", ImVec2(260, 305));
                    {


                    }
                    ImGui::EndChild();
                }
                ImGui::EndChild();
                break;
            case 1:

                ImGui::SetCursorPos(ImVec2(5, 7));
                ImGui::BeginChild("", ImVec2(270, 365));
                {
                    draw_list->AddRectFilled(ImVec2(0, 12), ImVec2(pos.x, pos.y - 5), rainbow());

                    check();
                    ImGui::SetCursorPos(ImVec2(5, 10));
                    ImGui::BeginChild("", ImVec2(260, 305));
                    {


                    }
                    ImGui::EndChild();
                }
                ImGui::EndChild();
                break;
            case 2:
                ImGui::SetCursorPos(ImVec2(5, 7));
                ImGui::BeginChild("", ImVec2(270, 365));
                {
                    draw_list->AddRectFilled(ImVec2(0, 12), ImVec2(pos.x, pos.y - 5), rainbow());

                    check();
                    ImGui::SetCursorPos(ImVec2(5, 10));
                    ImGui::BeginChild("", ImVec2(260, 305));
                    {
                        ImGui::Checkbox


                    }
                    ImGui::EndChild();
                }
                ImGui::EndChild();
            }
        }
    }
    ImGui::PopFont();
	ImGui::End();
}

void c_gui::drawESPOverlay()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    POINT mPos;
    GetCursorPos(&mPos);
    ImVec2 window_size = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowPos(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2 - window_size.x / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - window_size.y / 2), ImGuiCond_Once);
    if (ImGui::Begin("##ESP", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove))
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        cheat->ESP();

    ImGui::End();
}

#endif // !gui_cpp