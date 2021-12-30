#pragma once
#include "common.hpp"



// functions

class c_baseplayer {
public:
	void set_spyderman(bool toggle);
	void set_recoil(bool toggle);
	void set_nospread(bool toggle);
	void set_flag(int flag, bool toggle);
	void set_fov(float value, bool zoom, int key);
	void set_gravity(float value);
	void set_doublejump(bool toggle);
	void set_longneck(int key);
	void set_always_shoot(bool toggle);
	void flyhack(bool toggle, int key);
	void set_thickbullet(bool toggle);
	void set_instanteoka(bool toggle);
	void set_desynconkey(bool toggle, int key);
//	void aimbot(bool toggle, int key);
	void SetVA(const Vector2& VA);
	//void AimbotTarget(std::unique_ptr<baseEntity>& BPlayer, BonesList Bone);

};

class HeldItem {
public:

	HeldItem() {}

	HeldItem(uint64_t _ent) {
		this->ent = _ent;

		this->name = GetItemName();

		this->bp = read<uintptr_t>(this->ent + 0x98); // private EntityRef heldEntity;

		this->recoil_properties = read<uintptr_t>(this->bp + 0x2D8); // public RecoilProperties recoil;

		this->primary_mag = read<uint64_t>(this->bp + 0x2B8); //public BaseProjectile.Magazine primaryMagazine;
	}

public:
	std::string GetItemName()
	{
		uint64_t info = read<uint64_t>(this->ent + 0x20);

		uint64_t display_name = read<uint64_t>(info + 0x20);

		std::wstring wide_name = read_uni(display_name + 0x14);

		if (!wide_name.empty())
			return std::string(wide_name.begin(), wide_name.end()).c_str();

		return "nothing";
	}

	std::string GetAmmoType()
	{
		uint64_t item_def = read<uint64_t>(this->primary_mag + 0x20);
		uint64_t short_name = read<uint64_t>(item_def + 0x20);

		std::wstring wide_name = read_uni(short_name + 0x14);

		if (!wide_name.empty())
			return std::string(wide_name.begin(), wide_name.end()).c_str();

		return "No Ammo";
	}

	int GetAmmoTypeID()
	{
		uint64_t item_def = read<uint64_t>(this->primary_mag + 0x20);
		if (item_def <= 0 || item_def == 0x3F000000)
		{
			return 0;
		}
		const int ammo = read<int>(item_def + 0x18);
		return ammo;
	}

	bool IsWeapon()
	{
		if (this->name.find("rifle") != std::string::npos)
		{
			return true;
		}
		if (this->name.find("pistol") != std::string::npos)
		{
			return true;
		}
		if (this->name.find("bow") != std::string::npos)
		{
			return true;
		}
		if (this->name.find("lmg") != std::string::npos)
		{
			return true;
		}
		if (this->name.find("shotgun") != std::string::npos)
		{
			return true;
		}
		if (this->name.find("smg") != std::string::npos)
		{
			return true;
		}
		else
			return false;
	}

public:
	uint64_t ent;
	uintptr_t bp;
	uintptr_t recoil_properties;
	uint64_t primary_mag;
	std::string name;
};

class baseEntity
{

public:
	baseEntity() { }

	baseEntity(uintptr_t ent, uintptr_t trans)
	{
		this->player = read<uintptr_t>(ent + 0x28); //Entity
		this->visualState = read<uintptr_t>(trans + 0x38);

		this->playerFlags = read<int32_t>(ent + 0x680); //public BasePlayer.PlayerFlags playerFlags;
		//wchar_t buffer[1024 * sizeof(wchar_t)];
		//ReadString(read<uint64_t>(this->player + 0x6E0) + 0x14, buffer, 1024 * sizeof(wchar_t));
		//this->name = buffer;
		this->entityFlags = read<int32_t>(ent + 0x130);

		this->playerModel = read<uintptr_t>(this->player + 0x4C0); //BasePlayer -> public PlayerModel playerModel;
		this->modelState = read<uintptr_t>(this->player + 0x5F8); //0x588 // public ModelState modelState;
		this->playerMovement = read<uintptr_t>(this->player + 0x4E8); // public BaseMovement movement;

		this->position = read<Vector3>(this->visualState + 0x90); //internal Vector3 position;
		this->health = read<float>(this->player + 0x224);//private float _health;
	}
	

public:
	
	Vector3 getPosition() {
		return read<Vector3>(this->visualState + 0x90);//0x90
	}

	Vector2 getPosition2D() {
		Vector3 temp = read<Vector3>(this->visualState + 0x90);

		return Vector2(temp.x, temp.z);
	}

	std::string getASCIIName(std::wstring name) {
		return std::string(name.begin(), name.end());
	}

	std::wstring getPlayerName() {
		wchar_t buffer[1024 * sizeof(wchar_t)];
		ReadString(read<uint64_t>(this->player + 0x6E0) + 0x14, &buffer, 1024 * sizeof(wchar_t)); //BasePlayer -> protected string _displayName
		std::wstring name = std::wstring(buffer);

		return name;
	}

	std::string getName() {
		return this->getASCIIName(this->getPlayerName());
	}

	Vector3 getNewVelocity() {
		return read<Vector3>(this->playerModel + 0x22C); //private Vector3 newVelocity;
	}

	HeldItem getHeldItem()
	{
		int active_weapon_id = read<int>(this->player + 0x5D0); //private uint clActiveItem;
		uint64_t items = read_chain<uint64_t>(this->player, { (uint64_t)0x690, (uint64_t)0x28, (uint64_t)0x38, 0x10 }); //public PlayerInventory inventory;
		//std::cout << "Held weapon: found :" <<  items << std::endl;

		for (int items_on_belt = 0; items_on_belt <= 6; items_on_belt++)
		{
			uint64_t item = read<uint64_t>(items + 0x20 + (items_on_belt * 0x8));
			int active_weapon = read<uint32_t>(item + 0x28);
			if (active_weapon_id == active_weapon)
			{
				HeldItem item_obj = HeldItem(item);

				return item_obj;
			}
		}
		return 0;
	}

	void setViewAngles(Vector2 angles) {
		write<Vector2>(read<uint64_t>(this->player + 0x4E0) + 0x3C, angles); //public PlayerInput input; | private Vector3 bodyAngles;
	}

	void setEyeAngles(Vector4 quat) {
		write<Vector4>(read<uint64_t>(this->player + 0x688) + 0x44, quat); //public PlayerInput input; | private Vector3 bodyAngles;
	}

	Vector2 getBodyAngles()
	{
		uintptr_t player_input = read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x4E0);
		return read<Vector2>(player_input + 0x3C);
	}
	
	
	bool IsInView() {
		Vector2 screen_pos;
		if (!Utils::WorldToScreen(this->getPosition(), screen_pos))
			return false;

		return true;
	}

	bool isSameTeam(uintptr_t localPlayer) {
		auto localTeam = read<uint32_t>(localPlayer + 0x598);
		auto playerTeam = read<uint32_t>(this->player + 0x598);

		if (localTeam == 0 || playerTeam == 0)
			return false;

		return (localTeam == playerTeam);
	}

	bool isSleeping() {
		auto pFlags = read<uint64_t>(this->player + 0x680);
		if (pFlags & 0x16) //sleeping flag
			return true;
		else
			return false;
		//return this->getPlayerFlag(BPlayerFlags::Sleeping);
	}

public:

	uintptr_t player{};
	uintptr_t visualState{};
	std::wstring name{};
	bool isCalled{};
	std::wstring nameW{};
	Vector3 position{};
	int32_t playerFlags{};
	int entityFlags{};
	uint64_t playerModel{};
	uint64_t modelState{};
	uint64_t playerMovement{};
	float health{};


};

inline baseEntity localPlayer2;

//auto local_player = reinterpret_cast<c_baseplayer*>(init->local_player());


