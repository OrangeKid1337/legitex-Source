#include <Windows.h>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <TlHelp32.h>

inline HWND hWnd;
inline UINT64 base_address;
inline std::uint32_t proc = 0;

typedef struct mem_memory
{
	void* buffer_address;
	UINT_PTR address;
	ULONGLONG size;
	ULONG pid;
	BOOLEAN write;
	BOOLEAN read;
	BOOLEAN req_base;
	BOOLEAN clearcache;
	void* output;
	const char* module_name;
	ULONG64 base_address;
}memmemory;

struct HandleDisposer
{
	using pointer = HANDLE;

	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
			CloseHandle(handle);
	}
};

using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

static std::uint32_t __fastcall get_process_id(std::string_view process_name)
{
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return NULL;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
	{
		if (process_name.compare((LPSTR)(processentry.szExeFile)) == NULL)
		{
			return processentry.th32ProcessID;
		}
	}
	return NULL;
}

template<typename ... Arg>
inline uint64_t call_hook(const Arg ... args)
{
	void* hooked_func = GetProcAddress(LoadLibrary((LPCSTR)"win32u.dll"), "NtGdiDdDDIWaitForVerticalBlankEvent2");

	auto func = static_cast<uint64_t(_stdcall*)(Arg...)>(hooked_func);

	return func(args ...);
}

static ULONG64 get_module_base_address(const char* module_name)
{
	memmemory instructions = { 0 };
	instructions.pid = proc;
	instructions.req_base = TRUE;
	instructions.read = FALSE;
	instructions.write = FALSE;
	instructions.clearcache = FALSE;
	instructions.module_name = module_name;
	call_hook(&instructions);

	ULONG64 base = NULL;
	base = instructions.base_address;
	return base;
}

static BOOLEAN __fastcall clearCache()
{
	memmemory instructions = { 0 };

	instructions.pid = proc;
	instructions.read = FALSE;
	instructions.write = FALSE;
	instructions.req_base = FALSE;
	instructions.clearcache = TRUE;
	call_hook(&instructions);

	return true;
}

template <class T>
T read(uintptr_t read_address)
{
	T response{};
	memmemory instructions;
	instructions.pid = proc;
	instructions.size = sizeof(T);
	instructions.address = read_address;
	instructions.read = TRUE;
	instructions.write = FALSE;
	instructions.req_base = FALSE;
	instructions.clearcache = FALSE;
	instructions.output = &response;
	call_hook(&instructions);

	return response;
}

template <typename Type>
Type read_chain(uint64_t address, std::vector<uint64_t> chain) {
	uint64_t current = address;
	for (int i = 0; i < chain.size() - 1; i++) {
		current = read<uint64_t>(current + chain[i]);
	}
	return read<Type>(current + chain[chain.size() - 1]);
}

static bool __fastcall WriteVirtualMemoryRaw(UINT_PTR WriteAddress, UINT_PTR SourceAddress, SIZE_T WriteSize);

template<typename S>
bool __fastcall write(UINT_PTR WriteAddress, const S& value)
{
	return WriteVirtualMemoryRaw(WriteAddress, (UINT_PTR)&value, sizeof(S));
}

bool __fastcall WriteVirtualMemoryRaw(UINT_PTR WriteAddress, UINT_PTR SourceAddress, SIZE_T WriteSize)
{
	memmemory instructions;
	instructions.address = WriteAddress;
	instructions.pid = proc;
	instructions.write = TRUE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.clearcache = FALSE;
	instructions.buffer_address = (void*)SourceAddress;
	instructions.size = WriteSize;

	call_hook(&instructions);

	return true;
}

static void __fastcall ReadString(UINT_PTR String_address, void* buffer, SIZE_T size, bool esp_driver = false)
{
	memmemory instructions;
	instructions.read = TRUE;
	instructions.write = FALSE;
	instructions.req_base = FALSE;
	instructions.clearcache = FALSE;

	instructions.pid = proc;
	instructions.size = size;
	instructions.address = String_address;
	instructions.output = buffer;

	call_hook(&instructions);
}

static std::wstring read_uni(uint64_t address) {
	wchar_t buffer[1024 * sizeof(wchar_t)];

	ReadString(address, &buffer, 1024 * sizeof(wchar_t));

	return std::wstring(buffer);
}