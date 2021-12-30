#pragma once
#include "scene.hpp"
void styles()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	{

		colors[ImGuiCol_TabLine1] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(.02f , .02f, .02f, 0.50f);
		colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.0f, 1.00f);

		colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.10f, 0.10f, 0.10f, 0.54f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 0.54f);

		colors[ImGuiCol_TitleBg] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(10 / 255.f, 10 / 255.f, 10 / 255, 255 / 255.f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.41f, 0.41f, 1.00f);

		colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.41f, 0.41f, 1.00f);

		colors[ImGuiCol_Header] = ImVec4(1.00f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.41f, 0.41f, 1.00f);

		colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.41f, 0.41f, 1.00f);

		colors[ImGuiCol_Button] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	}

	ImGuiStyle* style = &ImGui::GetStyle();
	{
		style->WindowBorderSize = 1.0f;
		style->ChildBorderSize = 1.0f;

		style->FramePadding = ImVec2(4, 0);

		style->WindowTitleAlign = ImVec2(.5, .5);
	}
}
auto wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> bool
{
	return true;
}
auto init_ui() -> void  
{

	//ImGui::StyleColorsDark();
	styles();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImFontConfig font_config;
	font_config.OversampleH = 1; //or 2 is the same
	font_config.OversampleV = 1;
	font_config.PixelSnapH = 1;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x044F, // Cyrillic
		0,
	};
	structure.c_font_defult = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 15.f);
	structure.c_font_icon = io.Fonts->AddFontFromMemoryTTF((void*)iconfont, sizeof(iconfont), 30, &font_config, ranges);
}
auto create_scene() -> void 
{
	// create cheat 
	cheat->create();
	//cheat->entityLoop();
	
	// draw gui 
	gui->draw();	
}

void espThread()
{
	//if (vars.esp)
	gui->drawESPOverlay();
		
}

void c_scene::create()
{
	Sleep(1000);
	GAPI::MakeWindow("hook_with_imgui", "c_hook_with_imgui", wnd_proc, init_ui, create_scene, espThread, &vars.g_open, &vars.g_menu_key);
}

