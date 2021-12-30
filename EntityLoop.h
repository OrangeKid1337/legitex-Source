#pragma once
#include "common.hpp"

void EntityLoop()
{
	auto baseNetwork = 0x3112AE0;
	std::cout << "started";
	while (true)
	{
		//std::unique_ptr<std::vector<baseEntity>> entList = std::make_unique<std::vector<baseEntity>>();

		auto i = read<uintptr_t>(g_base + baseNetwork);
		auto want = read<uintptr_t>(i + 0xB8);
		auto ggg = read<uintptr_t>(want);
		auto to = read<uintptr_t>(ggg + 0x10);
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
				//std::unique_ptr<baseEntity> BPlayer = std::make_unique<baseEntity>(entity, transform, object);

				//if (read<bool>(BPlayer->playerModel + 0x289))
				//	continue;

				//if (!BPlayer->health <= 0) entList->push_back(*BPlayer); 
				//continue;

			}
		}
		//*totalEntityList = *entList;
		SleepEx(1, false);
	}
}