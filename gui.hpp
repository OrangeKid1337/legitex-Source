#pragma once
#include "common.hpp"
class c_gui
{
public:
	auto draw() -> void;
	auto drawESPOverlay() -> void;
    auto create_tab(const char* label, const char* icon, bool selected) -> bool
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;
        ImGuiContext& g = *GImGui;
      
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        const ImVec2 icon_size = ImGui::CalcTextSize(icon, NULL, true);
        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImGui::CalcItemSize(ImVec2(200, 60), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
        const ImRect bb(ImVec2(pos), ImVec2(pos.x + 200, pos.y + 60));
        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;
        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);
        if (hovered || held)
            ImGui::SetMouseCursor(7);


        if (selected)
        {
            window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(30, 30, 30));
            window->DrawList->AddRectFilled(bb.Min, ImVec2(bb.Min.x + 3, bb.Max.y), ImColor(255, 122, 255));
        }
        ImGui::PushFont(structure.c_font_icon);
        ImGui::RenderText(ImVec2(bb.Min.x + 25 - icon_size.x / 2, bb.Min.y + (size.y / 2) - (icon_size.y / 2) - 5), icon);
        ImGui::PopFont();
        ImGui::RenderText(ImVec2(bb.Min.x + 80, bb.Min.y + (size.y / 2) - (label_size.y / 2)), label);
        return pressed;
    }
};
inline c_gui* gui;