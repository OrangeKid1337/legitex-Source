#pragma once
#include "common.hpp"
class c_cheat
{
public:
	void create();
	void entityLoop();
	void ESP();
	void Aimbot();
};
inline c_cheat* cheat;
enum BonesList : int
{
	r_foot = 3,
	l_knee = 2,
	l_hip = 1,
	pelvis = 6,
	l_foot = 15,
	r_knee = 14,
	r_hip = 13,
	spine1 = 18,
	neck = 46,
	head = 47,
	l_upperarm = 24,
	l_forearm = 25,
	l_hand = 26,
	r_upperarm = 55,
	r_forearm = 56,
	r_hand = 57
};
