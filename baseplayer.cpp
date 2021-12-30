#pragma once
#include "baseplayer.hpp"
#include "common.hpp"

void c_baseplayer::set_spyderman(bool toggle) {
	if (toggle)
	{
		uintptr_t movement = read<uintptr_t>((uintptr_t)this + 0x4E8);
		write<float>(movement + 0xC8, 0.f);
	}
}

DWORD64 GetHeldItem(UINT64 LocalPlayer)
{
	int active_weapon_id = read<int>(LocalPlayer + 0x5D0); //private uint clActiveItem;
	uint64_t items = read_chain<uint64_t>(LocalPlayer, { (uint64_t)0x690, (uint64_t)0x28, (uint64_t)0x38, 0x10 }); //public PlayerInventory inventory;
	//std::cout << "Held weapon: found :" <<  items << std::endl;

	for (int items_on_belt = 0; items_on_belt <= 6; items_on_belt++)
	{
		uint64_t item = read<uint64_t>(items + 0x20 + (items_on_belt * 0x8));
		int active_weapon = read<uint32_t>(item + 0x28);
		if (active_weapon_id == active_weapon)
		{
			HeldItem item_obj = HeldItem(item);

			return item_obj.ent;
		}
	}
	return 0;
}

void c_baseplayer::set_recoil(bool toggle) {
	//uintptr_t player_input = read<uintptr_t>((uintptr_t)this + 0x4E0);
	uintptr_t held = GetHeldItem((uintptr_t)this);
	uintptr_t base_projectile = read<uintptr_t>(held + 0x98);
	uintptr_t recoil = read<uintptr_t>(base_projectile + 0x2D8); // public RecoilProperties recoil;
	if (toggle)
	{
		write<float>(recoil + 0x18, 0.f);
		write<float>(recoil + 0x1C, 0.f);
		write<float>(recoil + 0x20, 0.f);
		write<float>(recoil + 0x24, 0.f);

	}

}
void c_baseplayer::set_nospread(bool toggle) {
	//uintptr_t player_input = read<uintptr_t>((uintptr_t)this + 0x4E0);
	uintptr_t held = GetHeldItem((uintptr_t)this);
	uintptr_t base_projectile = read<uintptr_t>(held + 0x98);


	if (toggle)
	{
		write<float>(base_projectile + 0x31C, 0.f);
		write<float>(base_projectile + 0x320, 0.f);
		write<float>(base_projectile + 0x2EC, 0.f);
		write<float>(base_projectile + 0x2E8, 0.f);
		write<float>(base_projectile + 0x2F0, 0.f);
	}
}
void c_baseplayer::set_flag(int flag, bool toggle) {
	if (toggle)
	{
		auto player_flags = read<uintptr_t>(localPlayer2.player + 0x680);
		player_flags |= flag;
		write<uintptr_t>(localPlayer2.player + 0x680, player_flags);
	}
}
void c_baseplayer::set_fov(float value, bool zoom, int key) {
	if (GetAsyncKeyState(key) && zoom)
	{
		uintptr_t graphics_convar = read<uintptr_t>(g_base + 0x3110720 /* maybe incorrect "*/);
		uintptr_t graphics_current = read<uintptr_t>(graphics_convar + 0xB8);
		write<float>(graphics_current + 0x18, 25.f);
	}
	else
	{
		uintptr_t graphics_convar = read<uintptr_t>(g_base + 0x3110720 /* maybe incorrect "*/);
		uintptr_t graphics_current = read<uintptr_t>(graphics_convar + 0xB8);
		write<float>(graphics_current + 0x18, value);
	}
}
void c_baseplayer::set_gravity(float value) {
	uintptr_t movement = read<uintptr_t>((uintptr_t)this + 0x4E8);
	write<float>(movement + 0x84, value);
}
void c_baseplayer::set_doublejump(bool toggle) /*admin flags*/
{
	if (toggle)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			uintptr_t movement = read<uintptr_t>((uintptr_t)this + 0x4E8);
			write<Vector3>(movement + 0xc8, Vector3(0, 10000000, 0));
			write<Vector3>(movement + 0xc4, Vector3(99999999, 99999999, 99999999));
		}
	}
}
void c_baseplayer::set_longneck(int key) {

	if (key)
	{
		uintptr_t eyes = read<DWORD64>((uintptr_t)this + 0x1672);
		write<Vector3>(eyes + 0x38, Vector3(0, vars.neckamount, 0));
	}
}
void c_baseplayer::set_always_shoot(bool toggle) {
	uintptr_t movement = read<uintptr_t>((uintptr_t)this + 0x4E8);
	uintptr_t modelstate = read<uintptr_t>((uintptr_t)this + 0x5f8);
	if (toggle)
	{
		write<int>(modelstate + 0x24, 4);
		write<float>(movement + 0x4C, 1.f);
	}
}

void c_baseplayer::set_thickbullet(bool toggle) {

	if (toggle)
	{
			uintptr_t List = read<DWORD64>(localPlayer2.getHeldItem().bp + 0x358); //private List<Projectile> createdProjectiles;
			List = read<DWORD64>(List + 0x10);
			for (int i = 0; i < 8; ++i)
			{
				UINT64 Item = read<UINT64>(List + 0x20 + (i * 0x8));
				write<float>(Item + 0x2C, 0.8f);
			}
	
	}
}

void c_baseplayer::set_instanteoka(bool toggle) {
	if (localPlayer2.getHeldItem().name.find("eoka") != std::string::npos)
	{
		uintptr_t held = GetHeldItem((uintptr_t)this);
		uintptr_t base_projectile = read<uintptr_t>(held + 0x98);
		write<bool>(base_projectile + 0x370, true);
		write<float>(base_projectile + 0x360, 100.f);
	}
}

void c_baseplayer::SetVA(const Vector2& VA)
{
	UINT64 Input = read<UINT64>((uintptr_t)this + 0x4E0);
	write<Vector2>(Input + 0x44, VA);
}

void c_baseplayer::set_desynconkey(bool toggle, int key)
{
	if (toggle && key)
	{
		uintptr_t client_tick = read<float>((uintptr_t)this + 0x650);
		write<float>((uintptr_t)this + 0x650, 0.99f);
	}
	else {
		write<float>((uintptr_t)this + 0x650, 0.0f);

	}
}
