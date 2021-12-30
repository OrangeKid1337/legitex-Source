#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "common.hpp"
#include <array>

ImU32 __fastcall FtIM(float* color) {
	return ImGui::ColorConvertFloat4ToU32(ImVec4(color[0], color[1], color[2], color[3]));
}
void c_cheat::create()
{
		auto local_player = reinterpret_cast<c_baseplayer*>(init->local_player());

		if (local_player != 0 /*in server wont be 0*/)
		{
			local_player->set_spyderman(vars.spyderman);
			if (localPlayer2.getHeldItem().IsWeapon())
			{
				local_player->set_recoil(vars.no_recoil);
				local_player->set_nospread(vars.nospread);
				local_player->set_thickbullet(vars.thickbullet);
			//	local_player->set_instanteoka(vars.instanteoka);
			}
			local_player->set_flag(4, vars.admin_flags);
			local_player->set_fov(vars.fov_amount, vars.set_zoom, vars.zoombind);
			local_player->set_gravity(vars.gravity_amount);
			local_player->set_doublejump(vars.doublejump);
			local_player->set_always_shoot(vars.always_shoot);
			//local_player->set_longneck(vars.longbind);
			//local_player->set_desynconkey(vars.desync, vars.longbind);



		}
}

#pragma region Drawing Funcs
void __fastcall Text(ImVec2 pos, std::string strText, ImColor color, bool outline, ImFont* font, float fontSize)
{
	ImGuiContext& g = *GImGui;

	const char* text_end = strText.c_str() + strlen(strText.c_str());
	const char* text_display_end = ImGui::FindRenderedTextEnd(strText.c_str(), text_end);

	if (fontSize == 0.f) fontSize = g.Font->FontSize;

	if (outline) {
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos - ImVec2(1, 0), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos - ImVec2(0, 1), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos + ImVec2(1, 0), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
		ImGui::GetWindowDrawList()->AddText(font, fontSize, pos + ImVec2(0, 1), ImColor(0, 0, 0), strText.c_str(), NULL, 0.0f, NULL);
	}

	ImGui::GetWindowDrawList()->AddText(font, fontSize, pos, color, strText.c_str(), NULL, 0.0f, NULL);
}
void __fastcall DrawFilledRect(float x, float y, float w, float h, ImVec4 color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), NULL, NULL);
}
void __fastcall Line(ImVec2 pos, ImVec2 size, ImU32 color, float thickness)
{
	ImGui::GetWindowDrawList()->AddLine(pos, size, color, thickness);
}
void _fastcall DrawPlayerHealth(uint64_t player, float actualhealth)
{
	auto health = actualhealth;
	if (health > 100)
		health = 99;
	Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
	Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet, tempHead;
	if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
		float height = (tempHead.y - tempFeet.y);
		float width = height / 4.0f;

		float Entity_x = tempFeet.x + width;
		float Entity_y = tempFeet.y;
		float flBoxes = std::ceil(health / 10.f);
		float flX = Entity_x - 4; float flY = Entity_y;
		float flHeight = height / 10.f;
		float flMultiplier = 12 / 360.f; flMultiplier *= flBoxes - 1;
		ImColor ColHealth = ImColor(1, 255, 1);

		Text(ImVec2(flX, flY), "hp: " + std::to_string((int)actualhealth), ImColor(255, 255, 255, 255), true, structure.c_font_defult, 0.f);

		DrawFilledRect(flX + 1, flY, 2, flHeight * flBoxes + 3, ColHealth);
		DrawFilledRect(flX, flY, 4, height + 2, ImColor(80, 80, 80, 160));
	}
}
void _fastcall DrawPlayerWeapon(uint64_t player, std::string buffer)
{
	Vector3 Head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.23, 0));
	Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet;

	wchar_t res[256];
	std::string final = buffer;
	if (Utils::WorldToScreen(Feet, tempFeet)) {
		auto text_size = ImGui::CalcTextSize(final.c_str());
		Text(ImVec2(tempFeet.x - text_size.x / 2, (tempFeet.y + 30) - text_size.y), final, ImColor(255, 255, 255), true, structure.c_font_defult, 0.f);
	}
}
void _fastcall DrawPlayerName(uint64_t player, std::string buffer, int distance) {
	Vector3 Head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(-0.3, 0.4, 0));
	Vector3 Feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet;
	Vector2 tempHead;

	wchar_t res[256];
	std::string full_str = buffer + " - " + std::to_string(distance) + "m";
	//std::string full_str = buffer;

	if (Utils::WorldToScreen(Feet, tempFeet) && Utils::WorldToScreen(Head, tempHead)) {
		auto text_size = ImGui::CalcTextSize(full_str.c_str());
		Text(ImVec2(tempFeet.x - text_size.x / 2, tempHead.y - text_size.y), full_str, ImColor(255,255,255), true, structure.c_font_defult, 0.f);
	}
}
void __fastcall DrawCornerBox(ImVec2 pos, ImVec2 size, ImColor color)
{
	float lineW = (size.x / 5);
	float lineH = (size.y / 6);
	float lineT = 1;
	auto overlay = ImGui::GetWindowDrawList();
	{
		overlay->AddLine(ImVec2(pos.x - lineT, pos.y - lineT), ImVec2(pos.x + lineW, pos.y - lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x - lineT, pos.y - lineT), ImVec2(pos.x - lineT, pos.y + lineH), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x - lineT, pos.y + size.y - lineH), ImVec2(pos.x - lineT, pos.y + size.y + lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x - lineT, pos.y + size.y + lineT), ImVec2(pos.x + lineW, pos.y + size.y + lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x + size.x - lineW, pos.y - lineT), ImVec2(pos.x + size.x + lineT, pos.y - lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x + size.x + lineT, pos.y - lineT), ImVec2(pos.x + size.x + lineT, pos.y + lineH), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x + size.x + lineT, pos.y + size.y - lineH), ImVec2(pos.x + size.x + lineT, pos.y + size.y + lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x + size.x - lineW, pos.y + size.y + lineT), ImVec2(pos.x + size.x + lineT, pos.y + size.y + lineT), (1, 1, 1, 255), 3.f);
		overlay->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x, pos.y + lineH), color, 1.f);
		overlay->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + lineW, pos.y), color, 1.f);
		overlay->AddLine(ImVec2(pos.x + size.x - lineW, pos.y), ImVec2(pos.x + size.x, pos.y), color, 1.f);
		overlay->AddLine(ImVec2(pos.x + size.x, pos.y), ImVec2(pos.x + size.x, pos.y + lineH), color, 1.f);
		overlay->AddLine(ImVec2(pos.x, pos.y + size.y - lineH), ImVec2(pos.x, pos.y + size.y), color, 1.f);
		overlay->AddLine(ImVec2(pos.x, pos.y + size.y), ImVec2(pos.x + lineW, pos.y + size.y), color, 1.f);
		overlay->AddLine(ImVec2(pos.x + size.x - lineW, pos.y + size.y), ImVec2(pos.x + size.x, pos.y + size.y), color);
		overlay->AddLine(ImVec2(pos.x + size.x, pos.y + size.y - lineH), ImVec2(pos.x + size.x, pos.y + size.y), color, 1.f);
	}
}
void __fastcall DrawBoxx(ImVec2 pos, ImVec2 size, ImColor color)
{
	const ImRect rect_bb(pos, pos + size);

	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), FtIM(vars.esp_color), 0.0f, 15, 1);
	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min + ImVec2(1, 1), rect_bb.Max - ImVec2(1, 1), FtIM(vars.esp_color), 0.0f, 15, 1);
	ImGui::GetWindowDrawList()->AddRect(rect_bb.Min, rect_bb.Max, color, 0.0f, 15, 1);
}
void __fastcall DrawBox(uint64_t player) {

	Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
	Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet, tempHead;

	if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
		float height = (tempHead.y - tempFeet.y);
		float width = height / 4.0f;

		float Entity_x = tempFeet.x - width;
		float Entity_y = tempFeet.y;
		float Entity_w = height / 2;
		DrawCornerBox(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), FtIM(vars.corner_color));

	}
}
void  DrawSkeleton(uint64_t player) {
	float drawColor_skeleton[4] = { 1.f, 1.f, 1.f, 1.f };

	std::array<BonesList, 15> Bones = {
		r_foot, l_knee, l_hip,
		l_foot, r_knee, r_hip,
		spine1, neck, head,
		l_upperarm, l_forearm, l_hand,
		r_upperarm, r_forearm, r_hand
		
	}; std::array<Vector2, Bones.size()> BonesPos;

	for (int i = 0; i < BonesPos.size(); ++i) {
		if (!(Utils::WorldToScreen(Utils::GetBonePosition(player, Bones[i]), BonesPos.at(i)))) continue;
	}

	for (int j = 0; j < BonesPos.size(); j += 3) {
		Line({ BonesPos[j].x, BonesPos[j].y }, { BonesPos[j + 1].x, BonesPos[j + 1].y }, FtIM(vars.drawColor_skeleton), 1.0f);
		Line({ BonesPos[j + 1].x, BonesPos[j + 1].y }, { BonesPos[j + 2].x, BonesPos[j + 2].y }, FtIM(vars.drawColor_skeleton), 1.0f);
	}

	Line({ BonesPos[2].x, BonesPos[2].y }, { BonesPos[6].x, BonesPos[6].y }, FtIM(vars.drawColor_skeleton), 1.0f);
	Line({ BonesPos[5].x, BonesPos[5].y }, { BonesPos[6].x, BonesPos[6].y }, FtIM(vars.drawColor_skeleton), 1.0f);
	Line({ BonesPos[9].x, BonesPos[9].y }, { BonesPos[7].x, BonesPos[7].y }, FtIM(vars.drawColor_skeleton), 1.0f);
	Line({ BonesPos[12].x, BonesPos[12].y }, { BonesPos[7].x, BonesPos[7].y }, FtIM(vars.drawColor_skeleton), 1.0f);
}
void __fastcall DrawBox2(uint64_t player) {

	Vector3 head = (Utils::GetBonePosition(player, BonesList::head) + Vector3(0, 0.2, 0));
	Vector3 feet = (Utils::GetBonePosition(player, BonesList::l_foot) + Utils::GetBonePosition(player, BonesList::r_foot)) / 2.f;
	Vector2 tempFeet, tempHead;

	if (Utils::WorldToScreen(head, tempHead) && Utils::WorldToScreen(feet, tempFeet)) {
		float height = (tempHead.y - tempFeet.y);
		float width = height / 4.0f;

		float Entity_x = tempFeet.x - width;
		float Entity_y = tempFeet.y;
		float Entity_w = height / 2;
		DrawBoxx(ImVec2(Entity_x, Entity_y), ImVec2(Entity_w, height), ImColor(255, 255, 255, 1));

	}
}
float normalize_angle(float angle)
{
	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return angle;
}
Vector2 RotatePoint(Vector2 pointToRotate, Vector2 centerPoint, float angle, bool angleInRadians = false)
{
	float rad = (normalize_angle(angle) * static_cast<float>((M_PI / 180.0f)));
	float s = -sin(rad);
	float c = cos(rad);
	pointToRotate.x -= centerPoint.x;
	pointToRotate.y -= centerPoint.y;
	float xnew = pointToRotate.x * c - pointToRotate.y * s;
	float znew = pointToRotate.x * s + pointToRotate.y * c;
	pointToRotate.x = xnew + centerPoint.x;
	pointToRotate.y = znew + centerPoint.y;
	return pointToRotate;
}

#pragma endregion

std::unique_ptr<std::vector<baseEntity>> local_players = std::make_unique<std::vector<baseEntity>>();

void c_cheat::entityLoop()
{
	std::unique_ptr<std::vector<baseEntity>> entList = std::make_unique<std::vector<baseEntity>>();

	auto i = read<uintptr_t>(g_base + 0x3112AE0);
	auto want = read<uintptr_t>(i + 0xB8);
	auto ggg = read<uintptr_t>(want);
	auto to = read<uintptr_t>(ggg + 0x10);
	
	while (true)
	{
		auto die = read<uintptr_t>(to + 0x28);
		auto objList = read<uintptr_t>(die + 0x18);
		auto objListSize = read<uint32_t>(die + 0x10);
		//std::cout << "Looped\n";
		for (auto i = 0; i < objListSize; i++)
		{
			auto curObject = read<uintptr_t>(objList + (0x20 + (i * 8)));
			auto baseObject = read<uintptr_t>(curObject + 0x10);
			auto object = read<uintptr_t>(baseObject + 0x30);
			auto tag = read<WORD>(object + 0x54);

			auto ukn01 = read<uintptr_t>(baseObject + 0x28);

			auto ukn02 = read<uintptr_t>(ukn01);
			if (!ukn02)
				continue;

			if (tag == 6)
			{

				auto objectClass = read<uintptr_t>(object + 0x30);
				auto entity = read<uintptr_t>(objectClass + 0x18);
				auto transform = read<uintptr_t>(objectClass + 0x8);
				std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(entity, transform);

				if (read<bool>(BPlayer->playerModel + 0x289))
				{
					//if(localPlayer2.player = NULL)
						localPlayer2 = *BPlayer;
					continue;
				}
				entList->push_back(*BPlayer);


			}
		}
		*local_players = *entList;

		entList->clear();

		SleepEx(3000, false);
	}
}

void __fastcall DrawRadar()
{

	float x = GetSystemMetrics(SM_CXSCREEN) - 175, y = 200;

	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2{ x - 150, y - 150 }, ImVec2{ x + 150, y + 150 }, ImColor(18, 18, 18, 120));

	ImGui::GetWindowDrawList()->AddLine(ImVec2{ x, y - 150 }, ImVec2{ x, y + 150 }, ImColor{ 0.f, 0.f, 0.f, 1.f });
	ImGui::GetWindowDrawList()->AddLine(ImVec2{ x - 150, y }, ImVec2{ x + 150, y }, ImColor{ 0.f, 0.f, 0.f, 1.f });
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2{ x - 1, y - 1 }, ImVec2{ x + 2, y + 2 }, ImColor(18,18,18,255));
	
	Vector2 m_vecLocal = localPlayer2.getPosition2D();
	Vector2 m_angLocal = localPlayer2.getBodyAngles();
	for (auto i = 0; i < local_players->size(); i++)
	{
		std::unique_ptr<baseEntity> nn = std::make_unique<baseEntity>(local_players->at(i));
		const Vector3 position = nn->getPosition();

		if (nn->isSleeping())
			continue;

		Vector2 m_vecEnemy{ position.x, position.z };
		m_vecEnemy = m_vecLocal - m_vecEnemy;

		float m_flDistance = m_vecEnemy.length();
		m_vecEnemy = m_vecEnemy.normalized();
		m_flDistance = min(150.f, m_flDistance);
		m_vecEnemy *= m_flDistance;
		m_vecEnemy = RotatePoint(m_vecEnemy, { 0.f, 0.f }, 360.f - m_angLocal.y, false);
		{
			ImColor color = ImColor{ 1.f, 0.f, 0.f, 1.f };
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2{ x - m_vecEnemy.x - 2, y + m_vecEnemy.y - 2 }, ImVec2{ x - m_vecEnemy.x + 2, y + m_vecEnemy.y + 2 }, color, 0.5f);
		}
	}
}

void  c_cheat::ESP()
{
	uintptr_t gom = read<uintptr_t>(u_base + 0x17C1F18);
	uintptr_t tagOjbs = read<uintptr_t>(gom + 0x8);
	uintptr_t ojbs = read<uintptr_t>(tagOjbs + 0x10);
	uintptr_t objClass = read<uintptr_t>(ojbs + 0x30);
	uintptr_t ent = read<uintptr_t>(objClass + 0x18);

	Utils::pViewMatrix = read<Matrix4x4>(ent + 0x2E4);

	//DrawRadar();

	for (auto i = 0; i < local_players->size(); i++)
	{
			std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(local_players->at(i));

			if (read<bool>(BPlayer->playerModel + 0x289))
			{
				continue;
			}
			
			if (!BPlayer->IsInView()) continue;

			if (BPlayer->isSleeping()) continue;

			//if (BPlayer->health <= 0.00f);
			//	continue;

			//Vector2 pos;
			//auto position = read<Vector3>(BPlayer->visualState + 0x90);

			//auto localPosition = read<Vector3>((uintptr_t)local_player_visual + 0x90);

			auto dist = (int)Math::Distance(&localPlayer2.position, &BPlayer->position);

			if (dist > vars.max_distance) continue;

			if (dist > vars.max_distance) continue;
			if (vars.esp == true && vars.boxesp)
			{
				DrawBox2(BPlayer->player);
			}
			if (vars.esp == true && vars.corner)
			{
				DrawBox(BPlayer->player);
			}
			if (vars.esp == true && vars.healthesp)
			{
				DrawPlayerHealth(BPlayer->player, BPlayer->health);
			}
			if (vars.esp == true && vars.nameesp)
			{
				DrawPlayerName(BPlayer->player, BPlayer->getName(), dist);
			}
			if (vars.esp == true && vars.weaponesp)
			{
				DrawPlayerWeapon(BPlayer->player, BPlayer->getHeldItem().GetItemName());
			}
			if (vars.esp == true && vars.bone_esp)
			{
				DrawSkeleton(BPlayer->player);
			}

		}
	
}


#pragma region Aimbot

std::map<std::string, float> BulletSpeeds = {
		{ std::string("ammo.rifle"), 1.0f },
		{ std::string("ammo.rifle.hv"), 1.2f },
		{ std::string("ammo.rifle.explosive"), 0.6f },
		{ std::string("ammo.rifle.incendiary"), 0.6f },

		{ std::string("ammo.pistol"), 1.0f },
		{ std::string("ammo.pistol.hv"), 1.33333f },
		{ std::string("ammo.pistol.incendiary"), 0.75f },

		{ std::string("arrow.wooden"), 1.0f },
		{ std::string("arrow.hv"), 1.6f },
		{ std::string("arrow.fire"), 0.8f },
		{ std::string("arrow.bone"), 0.9f },

		{ std::string("ammo.handmade.shell"), 1.0f },
		{ std::string("ammo.shotgun.slug"), 2.25f },
		{ std::string("ammo.shotgun.fire"), 1.0f },
		{ std::string("ammo.shotgun"), 2.25f },

		{ std::string("ammo.nailgun.nails"), 1.0f }
};
float ProjectileSpeed_Normal() {
	std::string held_item = localPlayer2.getHeldItem().GetItemName();
	float Ammunition_Multiplier = BulletSpeeds[localPlayer2.getHeldItem().GetAmmoType()];

	if (held_item == "No Item")										return 300.0f;

	if (held_item == "rifle.ak")									return 375.0f * Ammunition_Multiplier;
	if (held_item == "rifle.lr300")									return 376.0f * Ammunition_Multiplier;
	if (held_item == "rifle.bolt")									return 656.f * Ammunition_Multiplier;
	if (held_item == "rifle.l96")									return 1125.0f * Ammunition_Multiplier;
	if (held_item == "rifle.m39")									return 469.0f * Ammunition_Multiplier;
	if (held_item == "rifle.semiauto")								return 375.0f * Ammunition_Multiplier;

	if (held_item == "lmg.m249")									return 488.0f * Ammunition_Multiplier;

	if (held_item == "smg.thompson")								return 300.0f * Ammunition_Multiplier;
	if (held_item == "smg.custom")									return 300.0f * Ammunition_Multiplier;
	if (held_item == "smg.mp5")										return 240.0f * Ammunition_Multiplier;

	if (held_item == "pistol.python")								return 300.0f * Ammunition_Multiplier;
	if (held_item == "pistol.semi")									return 300.0f * Ammunition_Multiplier;
	if (held_item == "pistol.revolver")								return 300.0f * Ammunition_Multiplier;
	if (held_item == "pistol.m92")									return 300.0f * Ammunition_Multiplier;
	if (held_item == "pistol.eoka")									return 225.0f * Ammunition_Multiplier;
	if (held_item == "pistol.nailgun")								return 50.0f;

	if (held_item == "crossbow")									return 75.0f * Ammunition_Multiplier;
	if (held_item == "bow.compound")								return 50.f * Ammunition_Multiplier;
	if (held_item == "bow.hunting")									return 50.0f * Ammunition_Multiplier;

	if (held_item == "shotgun.pump")								return 225.0f * Ammunition_Multiplier;
	if (held_item == "shotgun.spas12")								return 225.0f * Ammunition_Multiplier;
	if (held_item == "shotgun.waterpipe")							return 225.0f * Ammunition_Multiplier;
	if (held_item == "shotgun.doublebarrel")						return 225.0f * Ammunition_Multiplier;

	return 200.0f;
}

float GetGravityPS(int ammoid) {
	switch (ammoid) {
	case 14241751:
		return 1.f;
	case -1234735557:
		return 0.75f;
	case 215754713:
		return 0.75f;
	case -1023065463:
		return 0.5f;
	case -2097376851:
		return 0.75f;
	case -1321651331:
		return 1.25f;
	default:
		return 1.f;
	}
}

float AimFov(std::unique_ptr<baseEntity>& BPlayer, BonesList bone)
{
	Vector2 ScreenPos;
	if (!Utils::WorldToScreen(Utils::GetBonePosition(BPlayer->player, bone), ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2), ScreenPos);
}

void Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}

Vector3 Prediction(const Vector3& LP_Pos, std::unique_ptr<baseEntity>& Player, BonesList Bone) {
	Vector3 BonePos = Utils::GetBonePosition(Player->player, Bone);
	float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);

	if (Dist > 0.001f) {
		float BulletTime = Dist / ProjectileSpeed_Normal();
		Vector3 vel = Player->getNewVelocity();
		Vector3 PredictVel = vel * BulletTime * 0.75f;
		BonePos += PredictVel;
		float gravity = GetGravityPS(localPlayer2.getHeldItem().GetAmmoTypeID());
		BonePos.y += (4.905f * BulletTime * BulletTime) * gravity;
	} return BonePos;
}

void SilentAimbotTarget(std::unique_ptr<baseEntity>& BPlayer, BonesList Bone) {
	Vector3 Local = Utils::GetBonePosition(localPlayer2.player, BonesList::neck);
	Vector3 PlayerPos = Prediction(Local, BPlayer, Bone);

	Vector2 AngleToAim = Math::CalcAngle(Local, PlayerPos);
	Normalize(AngleToAim.y, AngleToAim.x);
	if (isnan(AngleToAim.x) || isnan(AngleToAim.y))
		return;
	Vector4 toQuat = Math::QuaternionLookRotation((PlayerPos - Local).normalized(), Vector3(0,1,0));
	localPlayer2.setEyeAngles(toQuat);

}

void AimbotTarget(std::unique_ptr<baseEntity>& BPlayer, BonesList Bone) {
	Vector3 Local = Utils::GetBonePosition(localPlayer2.player, BonesList::head);
	Vector3 PlayerPos = Prediction(Local, BPlayer, Bone);

	Vector2 AngleToAim = Math::CalcAngle(Local, PlayerPos);
	Normalize(AngleToAim.y, AngleToAim.x);
	if (isnan(AngleToAim.x) || isnan(AngleToAim.y))
		return;

	localPlayer2.setViewAngles(AngleToAim);
}

uintptr_t getTarget()
{
	float lastFOV = FLT_MAX;

	uintptr_t target;

	for (auto i = 0; i < local_players->size(); i++)
	{

		std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(local_players->at(i));

		if (read<bool>(BPlayer->playerModel + 0x289))
		{
			continue;
		}

		if (!BPlayer->IsInView()) continue;

		if (BPlayer->isSleeping()) continue;

		//if (BPlayer->health > 0.0f) continue;

		auto CrosshairDistanceToPlayer = AimFov(BPlayer, BonesList::head);
		if (CrosshairDistanceToPlayer < lastFOV && CrosshairDistanceToPlayer > 0.0f && CrosshairDistanceToPlayer <= vars.fovamount)
		{
			lastFOV = CrosshairDistanceToPlayer;
			target = BPlayer->player;
		}
	}
	return target;
}

void c_cheat::Aimbot()
{
	while (true)
	{
		if (vars.aimbot)
		{
			uintptr_t target = getTarget();


			for (auto i = 0; i < local_players->size(); i++)
			{
				std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(local_players->at(i));

				if (BPlayer->player != target)
					continue;

				if (target != NULL)
					//std::cout << "jit found";

				if (GetAsyncKeyState(vars.aimbotkey) && target)
				{
					auto dist = (int)Math::Distance(&localPlayer2.position, &BPlayer->position);

					//if (BPlayer->isSameTeam(localPlayer2.player)) continue;

					if (BPlayer->player && dist <= vars.aimbotDist && !vars.silentaim)
						AimbotTarget(BPlayer, BonesList::head);
					else if(BPlayer->player && dist <= vars.aimbotDist && vars.silentaim)
						SilentAimbotTarget(BPlayer, BonesList::neck);
				}
			}
		}
		SleepEx(5, false);
	}
}


#pragma endregion
