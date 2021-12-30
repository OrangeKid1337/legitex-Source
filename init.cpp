#pragma once
#include "common.hpp"

auto c_init::cheat() -> bool
{
	clearCache();
	proc = get_process_id("RustClient.exe");
	base_address = get_module_base_address("RustClient.exe");
	u_base = get_module_base_address("UnityPlayer.dll");
	g_base = get_module_base_address("GameAssembly.dll");
	

	return true;
}

auto c_init::local_player() ->uintptr_t
{
	uintptr_t local_player_pointer_1 = read<uintptr_t>(g_base + 0x3112AE0); //gom
	uintptr_t local_player_pointer_2 = read<uintptr_t>(local_player_pointer_1 + 0xB8);
	uintptr_t local_player_pointer_3 = read<uintptr_t>(local_player_pointer_2 + 0x0);
	uintptr_t local_player_pointer_4 = read<uintptr_t>(local_player_pointer_3 + 0x10);
	uintptr_t local_player_pointer_5 = read<uintptr_t>(local_player_pointer_4 + 0x28);
	uintptr_t local_player_pointer_6 = read<uintptr_t>(local_player_pointer_5 + 0x18);
	return read<uintptr_t>(local_player_pointer_6 + 0x20);
}



