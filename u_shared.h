#pragma once
#include <cstdint>
constexpr auto packet_magic = 0x7F000001;
constexpr auto server_ip = 0x7F000001; // 127.0.0.1
constexpr auto server_port = 25922;
//25921
enum class PacketType
{
	packet_copy_memory,
	packet_get_base_address,
	packet_get_dll_address,
	packet_clean_piddbcachetable,
	packet_clean_mmunloadeddrivers,
	packet_spoof_drives,
	packet_completed
};

struct PacketCopyMemory
{
	uint32_t dest_process_id;
	uint64_t dest_address;

	uint32_t src_process_id;
	uint64_t src_address;

	uint32_t size;
};

struct PacketGetBaseAddress
{
	uint32_t process_id;
	uint32_t exe_id;
	int name;
};

struct PacketGetProcessId
{
	char* process_name;
};

struct PacketCleanPiDDBCacheTable {
};

struct PacketCleanMMUnloadedDrivers {
};

struct PacketSpoofDrives {
};

struct PackedCompleted
{
	uint64_t result;
};

struct PacketHeader
{
	uint32_t   magic;
	PacketType type;
};

struct Packet
{
	PacketHeader header;
	union
	{
		PacketCopyMemory	 copy_memory;
		PacketGetBaseAddress get_base_address;
		PacketGetBaseAddress get_dll_address;
		PacketCleanPiDDBCacheTable clean_piddbcachetable;
		PacketCleanMMUnloadedDrivers clean_mmunloadeddrivers;
		PacketSpoofDrives	 spoof_drives;
		PackedCompleted		 completed;
	} data;
};