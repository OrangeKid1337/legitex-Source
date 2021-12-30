#pragma once
#ifndef u_vars_hpp
#define u_vars_hpp

class c_vars
{
public:
	// menu
	bool g_open = true;
	int g_menu_key = VK_INSERT;
	int walkbind = 0;
	int longbind = 0;
	int speedbind = 0;
	int mountbind = 0;
	int zoombind = 0;
	int desyncbind = 0;
	int flyhackbind = 0;

	int rWidth;
	int rHeight;
	float health_color[4] = { 1.f, 1.f, 1.f, 1.f };
	float esp_color[4] = { 1.f, 1.f, 1.f, 1.f };
	float corner_color[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_skeleton[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_crosshair[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_name[4] = { 1.f, 1.f, 1.f, 1.f };
	float drawColor_weapon[4] = { 1.f, 1.f, 1.f, 1.f };
	bool bone_esp = false;
	float draw_coolcolor[4] = { 1.f, 1.f, 1.f, 0.15f };
	// cheat
	bool no_recoil = false;
	bool admin_flags = false;
	bool doublejump = false;
	bool walkonwater = false;
	bool spyderman = false;
	bool always_shoot = false;
	bool flyhack = false;
	bool longeject = false;
	bool thickbullet = false;
	bool instacompound = false;
	bool speedhack = false;
	bool nospread = false;
	bool mountfire = false;
	bool omnisprint = false;
	bool set_zoom = false;
	bool instanteoka = false;
	bool desync = false;

	bool aimbot = false;
	bool silentaim = false;
	bool prediction = true;
	bool chams = false;
	int aimbotkey = 0;
	float aimbotDist = 150.f;
	bool fov = false;
	float fovamount = 30.0f;

	bool esp = false;
	bool corner = false;
	bool boxesp = false;
	bool healthesp = false;
	bool nameesp = false;
	bool weaponesp = false;
	bool head = false;
	bool chest = false;
	bool pelvis = false;

	const char* bone[4] = {
		"Head",
		"Chest",
		"Arms",
		"Legs",
	};

	float fovcolor[4] = { 1.f, 1.f, 1.f, 1.f };
	int dist;
	int max_distance = 150;
	float neckamount = 0.0f;
	float fov_amount = 120.0f;
	float gravity_amount = 2.5f;
	float fatbulletamount = 1.f;
};
inline c_vars vars; 

#endif // !u_vars_hpp
