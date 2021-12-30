#pragma once
#include "common.hpp"
// get base addy and local player
inline uintptr_t g_base;
inline uintptr_t u_base;
class c_init
{
public:
	auto cheat() ->bool;
	auto local_player() ->uintptr_t;

	auto local_player_visState()->uintptr_t;

};
inline c_init* init;