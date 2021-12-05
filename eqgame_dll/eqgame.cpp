#include <Windows.h>
#include "MQ2Main.h"
#include <stdio.h>
#include <map>
#include "dinput8.h"
#include "..\Detours\inc\detours.h"
#include "eqmac.h"
#include "eqmac_functions.h"
#include "d3d9.h"
#include "xorstr.h"
#include <tlhelp32.h>
#include <list>
#include <Psapi.h>
#include <vector>
#include <set>
#include <dinput.h>
#include <intrin.h>
#include <iphlpapi.h>
#include <IPTypes.h>
#include "spaghetti.h"

#pragma comment(lib, "Iphlpapi.lib")

extern "C" { __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" { __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; }

extern bool was_background;
extern void LoadIniSettings();
extern HMODULE heqwMod;
HANDLE myproc = 0;
bool title_set = false;
bool first_maximize = true;
bool can_fullscreen = false;

bool is_digits(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

bool ResolutionStored = false;
DWORD resx = 0;
DWORD resy = 0;
DWORD bpp = 0;
DWORD refresh = 0;
HMODULE eqmain_dll = 0;
BOOL bExeChecksumrequested = 0;
BOOL g_mouseWheelZoomIsEnabled = true;
unsigned int g_buffWindowTimersFontSize = 3;
bool has_focus = true;
WINDOWINFO stored_window_info;
WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
bool start_fullscreen = false;
bool in_full_screen = false;
bool startup = true;
POINT posPoint;
DWORD o_MouseEvents = 0x0055B3B9;
DWORD o_MouseCenter = 0x0055B722;

typedef signed int(__cdecl* ProcessGameEvents_t)();
ProcessGameEvents_t return_ProcessGameEvents;
ProcessGameEvents_t return_ProcessMouseEvent;
ProcessGameEvents_t return_SetMouseCenter;

DWORD d3ddev = 0;
DWORD eqgfxMod = 0;
BOOL bWindowedMode = true;
 
#define DLL_VERSION_NUMBER (uint64_t)140

typedef struct _detourinfo
{
	DWORD_PTR tramp;
	DWORD_PTR detour;
}detourinfo;
std::map<DWORD,_detourinfo> ourdetours;


#define FUNCTION_AT_ADDRESS(function,offset) __declspec(naked) function\
{\
	__asm{mov eax, offset};\
	__asm{jmp eax};\
}

#define EQ_FUNCTION_flush_mouse 0x0055B5B9
#ifdef EQ_FUNCTION_flush_mouse
FUNCTION_AT_ADDRESS(signed int EQ_flush_mouse(), EQ_FUNCTION_flush_mouse);
#endif

void PatchA(LPVOID address, const void *dwValue, SIZE_T dwBytes) {
	unsigned long oldProtect;
	VirtualProtect((void *)address, dwBytes, PAGE_EXECUTE_READWRITE, &oldProtect);
	FlushInstructionCache(GetCurrentProcess(), (void *)address, dwBytes);
	memcpy((void *)address, dwValue, dwBytes);
	VirtualProtect((void *)address, dwBytes, oldProtect, &oldProtect);
}

char bMySEQDetected = 3;


//Function Addr's
DWORD CXWndActivateAddr = 0x864100;
DWORD ValueSellMerchantAddr = 0x5E1690;
DWORD IsItemRentable = 0x5E0620;
DWORD IsItemDroppable = 0x5E06A0;
DWORD GetItemValue = 0x5E0800;
DWORD SetCCreateCameraAddr = 0x004950F0;
DWORD SelectCharacterAddr = 0x004F1A03;
typedef int(__fastcall *Activate_t)(CXWnd* thisptr);
typedef int(__fastcall *ValueSellMerchant_t)(DWORD* thisptr, float a2, float a3);
typedef int(__fastcall *SelectCharacter_t)(DWORD* thisptr, int a1, int a2, int a3);
typedef int(__fastcall *SetCCreateCamera_t)(DWORD thisptr);
Activate_t return_ActivateDet;
ValueSellMerchant_t return_ValueSellMerchantDet;
SetCCreateCamera_t return_SetCCreateCameraDet;
SelectCharacter_t return_SelectCharacterDet;
bool FirstSel = false;

DWORD currTime = 0;
bool SetTime = false;

std::map<std::string, LONGLONG> simpleFileList;

DWORD timeGetTimeVal = 0;

int __fastcall ValueSellMerchantHook(DWORD* thisptr, float a2, float a3)
{
	int retVal = return_ValueSellMerchantDet(thisptr, a2, a3);
	int isDroppable = ((int(__thiscall*) (LPVOID, int)) IsItemRentable) ((LPVOID)thisptr, 1);
	int isRentable = ((int(__thiscall*) (LPVOID, int)) IsItemDroppable) ((LPVOID)thisptr, 1);
	int itemValue = ((int(__thiscall*) (LPVOID, int)) GetItemValue) ((LPVOID)thisptr, 1);
	if (retVal <= 0 && isDroppable && isRentable && itemValue > 0)
		retVal = 1;
	return retVal;
}

bool IsEvil(int race, int class_, int deity)
{
	bool result = false; // eax in disasm

	if (race == 9 || race == 10 || race == 6 || race == 128)
		result = true;
	if (class_ == 11 || class_ == 5)
		result = true;
	if (deity == 1 || deity == 3 || deity == 4 || deity == 201 || deity == 203 || deity == 206)
		result = true;
	return result;
}

char __fastcall SetCCreateCameraHook(DWORD thisptr)
{
	if (pLocalPlayer && pDisplay && GetGameState() == GAMESTATE_CHARSELECT)
	{
		bool evil = IsEvil(pLocalPlayer->Data.Race, pLocalPlayer->Data.Class, pLocalPlayer->Data.Deity);

		//For "load"
		//pLocalPlayer->Data.Z = 12.75f;
		//pLocalPlayer->Data.Y = 5.0f;
		//pLocalPlayer->Data.X = -316.0f;


		pLocalPlayer->Data.Y = -76.66f;
		pLocalPlayer->Data.X = -221.45f;
		pLocalPlayer->Data.Z = -21.0f;


		//if (evil)
		//{

		//	pLocalPlayer->Data.Z = -78.0f;
		//	pLocalPlayer->Data.X = -2466.0f;
		//	pLocalPlayer->Data.Y = -9;
		//	//pLocalPlayer->Data.Z = 12.75f;
		//	//pLocalPlayer->Data.Y = 5.0f;
		//	//pLocalPlayer->Data.X = -316.0f;
		//}
		//else
		//{
		//	//pLocalPlayer->Data.X = 0.0f;
		//	//pLocalPlayer->Data.Y = 0.0f;
		//	//pLocalPlayer->Data.Z = 10.0f;
		//}
		double result = 0.0f;
	}


	return return_SetCCreateCameraDet(thisptr);;
}

int __fastcall SelectCharacterHook(DWORD* thisptr, int a2, int a3, int a4)
{
	int retVal = return_SelectCharacterDet(thisptr, a2, a3, a4);

	if (pLocalPlayer && pDisplay && GetGameState() == GAMESTATE_CHARSELECT)
	{
		//bool evil = IsEvil(pLocalPlayer->Data.Race, pLocalPlayer->Data.Class, pLocalPlayer->Data.Deity);
		//if (evil)
		//{
		//	pLocalPlayer->Data.Z = 12.75f;
		//	pLocalPlayer->Data.Y = 5.0f;
		//	pLocalPlayer->Data.X = -316.0f;
		//}
		//else
		//{
		//	pLocalPlayer->Data.X = 0.0f;
		//	pLocalPlayer->Data.Y = 0.0f;
		//	pLocalPlayer->Data.Z = 10.0f;
		//}	{
		pLocalPlayer->Data.Y = -76.66f;
		pLocalPlayer->Data.X = -221.45f;
		pLocalPlayer->Data.Z = -21.0f;

		double result = 0.0f;
		result = ((DWORD(__thiscall*) (LPVOID, int, int)) 0x0049D620) ((LPVOID)pDisplay, 12, 0); //position on ground
		result = ((DWORD(__thiscall*) (LPVOID)) 0x00496AF0) ((LPVOID)pDisplay); // update player
		((int(__thiscall*) (LPVOID)) 0x59ECF0) ((LPVOID)pLocalPlayer); // move player
	}

	return retVal;
}

int fsize(FILE *fp) {

	int sz = 0;

	if (fp)
	{
		int prev = ftell(fp);
		fseek(fp, 0L, SEEK_END);
		sz = ftell(fp);
		fseek(fp, prev, SEEK_SET); //go back to where we were
	}
	return sz;
}
// 43C187 in Titanium


std::vector<std::string> splitpath(
	const std::string& str
	, const std::set<char> delimiters)
{
	std::vector<std::string> result;

	char const* pch = str.c_str();
	char const* start = pch;
	for (; *pch; ++pch)
	{
		if (delimiters.find(*pch) != delimiters.end())
		{
			if (start != pch)
			{
				std::string str(start, pch);
				result.push_back(str);
			}
			else
			{
				result.push_back("");
			}
			start = pch + 1;
		}
	}
	result.push_back(start);

	return result;
}

typedef HANDLE(__stdcall *CreateFileA_t)(LPCSTR s3dFile, DWORD a2, DWORD a3, LPSECURITY_ATTRIBUTES a4, DWORD a5, DWORD a6, HANDLE hTemplateFile);
CreateFileA_t return_CreateFileA;
HANDLE __stdcall /*CDisplay::*/CreateFileAHook(LPCSTR s3dFile, DWORD a2, DWORD a3, LPSECURITY_ATTRIBUTES a4, DWORD a5, DWORD a6, HANDLE hTemplateFile)
{
	std::string data = s3dFile;
	std::set<char> delims{ '/' };

	std::vector<std::string> path = splitpath(data, delims);

	std::string dataFile = path.back();
	std::transform(dataFile.begin(), dataFile.end(), dataFile.begin(), ::tolower);

	if (strlen(dataFile.c_str()) > 1 && strstr(dataFile.c_str(), "s3d") != 0)
	{

		HANDLE file = return_CreateFileA(s3dFile, GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, NULL);
		if (file)
		{
			LARGE_INTEGER size;
			if (!GetFileSizeEx(file, &size))
			{
				CloseHandle(file);
				return return_CreateFileA(s3dFile, a2, a3, a4, a5, a6, hTemplateFile);
			}
			simpleFileList[dataFile] = size.QuadPart;
			CloseHandle(file);
		}
	}
	return return_CreateFileA(s3dFile, a2, a3, a4, a5, a6, hTemplateFile);
}


//4EECA0

int __fastcall CXWndActivateHook(CXWnd* thisptr)
{
	//if ((DWORD)thisptr->pvfTable == (DWORD)0x009de408) //AltAdv Again
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool, bool)) 0x00865290) (thisptr, 0, 1, 1);
	//	return 0;
	//}

	if ((DWORD*)thisptr->pvfTable == (DWORD*)0x009ECDA8) //Leadership
	{
		((int(__thiscall*) (LPVOID, bool, bool, bool)) 0x00865290) (thisptr, 0, 1, 1);
		return 0;
	}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x009EE940) //Leadership
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool, bool)) 0x00865290) (thisptr, 0, 1, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x0064E9C0) //Adventure Window Stats
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x0064E878) //Adventure Request
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x00653698) //DZ Window
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x0065BEB8) //Raid Window
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x00655B68) //Guild Management
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x00654598) // Find Location Window
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x0065DE10) // Quest Journal
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x006538F0) // DZ Switch List
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x0065f5b0) // Journal
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x0064c220) // Tribute
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	//if ((DWORD*)thisptr->pvfTable == (DWORD*)0x00656f28) // Storyline
	//{
	//	((int(__thiscall*) (LPVOID, bool, bool)) 0x005A0A80) (thisptr, 0, 1);
	//	return 0;
	//}

	return return_ActivateDet(thisptr);
}

void __cdecl ResetMouseFlags() {
	DWORD ptr = *(DWORD *)0x00809DB4;
	if (ptr)
	{
		*(BYTE*)(ptr + 85) = 0;
		*(BYTE*)(ptr + 86) = 0;
		*(BYTE*)(ptr + 87) = 0;
		*(BYTE*)(ptr + 88) = 0;
	}

	*(DWORD*)0x00809320 = 0;
	*(DWORD*)0x0080931C = 0;
	*(DWORD*)0x00809324 = 0;
	*(DWORD*)0x00809328 = 0;
	*(DWORD*)0x0080932C = 0;
}

std::list<std::string> x86ProcessModuleList;

char bDetectedMQ2 = 0;

struct Checksum_Struct {
	uint16_t opcode;
	uint64_t checksum;
	char HDDSerial[512];
	char GPUString[256];
	char CPUBrandString[256];
	char CRC1[4];
	char CRC2[4];
	char CRC3[4];
	char CRC4[4];
	char CRC5[4];
	char DisplayW[4];
	char DisplayH[4];
};

struct SimpleChecksum_Struct {
	uint16_t opcode;
	uint64_t checksum;
	uint8_t  data[3];
};

struct ProcessListEntry_Struct {
	char zoneName[260];
};

struct MacEntry_Struct {
	uint16_t opcode;
	BYTE address[8];
};

struct ProcessList_Struct {
   uint16_t opcode;
   uint8_t count;
   ProcessListEntry_Struct process[200];
};

struct FileList_Struct {
	uint16_t opcode;
	int NumEntries;
    ProcessListEntry_Struct Keys[200];
    uint64_t Values[200];
};

enum Options {
	NothingFound = 0,
	MQ2MainDetected = 1 << 0,
	ShowEQServerDetected = 1 << 1,
	ShowEQClientDetected = 1 << 2,
	MQ2ProcessDetected = 1 << 3,
	KenetixDetected = 1 << 4,
	EQTrainerDetected = 1 << 5,
	MMOLoader = 1 << 6,
	ShowEQTitleBar = 1 << 7
};


__int64 FileSize(const char* name)
{
	struct _stat64 buf;
	if (_stat64(name, &buf) != 0)
		return -1; // error, could use errno to find out more

	return buf.st_size;
}

DETOUR_TRAMPOLINE_EMPTY(DWORD WINAPI GetModuleFileNameA_tramp(HMODULE, LPTSTR, DWORD));

DWORD WINAPI GetModuleFileNameA_detour(HMODULE hMod, LPTSTR outstring, DWORD nSize)
{
	DWORD allocsize = nSize;
	DWORD ret = GetModuleFileNameA_tramp(hMod, outstring, nSize);
	if (bExeChecksumrequested) {
		if (strstr(outstring, "eqgame.exe")) {
			bExeChecksumrequested = 0;
			PCHAR szProcessName = 0;
			szProcessName = strrchr(outstring, '\\');
			szProcessName[0] = '\0';
			sprintf_s(outstring, allocsize, "%s\\dinput8.dll", outstring);
		}
	}
	return ret;
}

DETOUR_TRAMPOLINE_EMPTY(unsigned char __cdecl SendExe_Tramp(DWORD));

unsigned char __cdecl SendExe_Tramp(DWORD);
unsigned char __cdecl SendExe_Detour(DWORD con)
{
	return SendExe_Tramp(con);
}

typedef struct BankRequest_Struct
{
	uint8_t requestType;
	uint32_t entityid;
	float rate;
};

PLUGIN_API BOOL OnRecvInitBankerPacket(DWORD Type, PVOID Packet, DWORD Size)
{
	if ((Size < 5) || !Packet)
	{
		return true;
	}

	BankRequest_Struct* bnkRequest = (BankRequest_Struct*)Packet;


	auto bankerNPC = bnkRequest->entityid > 0 ? (PSPAWNINFO)GetSpawnByID(bnkRequest->entityid) : nullptr;

	if (bankerNPC)
	{
		if (bankerNPC->pSpawn)
		{
			EQPlayer* bankerPlayer = (EQPlayer*)bankerNPC->pSpawn;
			if (bankerPlayer)
			{
				switch (bnkRequest->requestType)
				{
					case 0:
					{
						pCurrentlyInteracting++;
						pMerchantWnd->Activate(bankerPlayer, bnkRequest->rate, 3, 2592000);
						break;
					}
					case 1:
					{
						pBankWnd->Activate(bankerPlayer);
						break;
					}
					default:
					{
						break;
					}
				}
			}
		}
	}

	return true;
}

unsigned char __fastcall HandleWorldMessage_Trampoline(DWORD *con, DWORD edx, unsigned __int32 unk, unsigned __int16 opcode, char* buf, size_t size);
unsigned char __fastcall HandleWorldMessage_Detour(DWORD *con, DWORD edx, unsigned __int32 unk, unsigned __int16 opcode, char* buf, size_t size)
{
	switch(opcode)
	{
#ifdef DPSPLUGIN
		case 0x1337:
			OnRecvEdgeDPSPacket(opcode, buf, size);
			break;
#endif
		case 0x1338:
			OnRecvEdgeStatLabelPacket(opcode, buf, size);
			break;
		case 0x1339:
			OnRecvInitBankerPacket(opcode, buf, size);
			break;
		default:
			break;
	}
	return HandleWorldMessage_Trampoline(con, edx, unk, opcode, buf, size);
}

DETOUR_TRAMPOLINE_EMPTY(unsigned char __fastcall HandleWorldMessage_Trampoline(DWORD *con, DWORD edx, unsigned __int32 unk, unsigned __int16 opcode, char* buf, size_t size));

//unsigned char __fastcall SendMessage_Trampoline(DWORD *, unsigned __int32, unsigned __int32, char* buf, size_t, DWORD, DWORD);
//unsigned char __fastcall SendMessage_Detour(DWORD *con, unsigned __int32 unk, unsigned __int32 channel, char* buf, size_t size, DWORD a6, DWORD a7)
//{
//	DWORD retval = 0;
//	bExeChecksumrequested = 1;
//	int16_t opcode = 0;
//	memcpy(&opcode, buf, 2);
//
//	if (opcode == 0xf13 || opcode == 0x578f)
//	{
//		//if (opcode == 0xf13) //only need to do this once
//		//{
//		//	g_HWID.Grab();
//		//}
//
//		//IP_ADAPTER_INFO AdapterInfo[16];
//		//BYTE macAddress[8];
//		//memset(macAddress, 0, sizeof(macAddress));
//		//DWORD dwBufLen = sizeof(AdapterInfo);
//		//DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
//		//if (dwStatus == ERROR_SUCCESS)
//		//{
//
//		//	IP_ADAPTER_INFO AdapterInfo[16];
//		//	DWORD dwBufLen = sizeof(AdapterInfo);
//		//	DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
//
//		//	MacEntry_Struct* me = new MacEntry_Struct;
//		//	memset(me, 0, sizeof(MacEntry_Struct));
//		//	me->opcode = 0xf13;
//		//	memcpy(&me->address, AdapterInfo[0].Address, 8);
//
//		//	SendMessage_Trampoline(con, unk, channel, (char*)me,
//		//		sizeof(MacEntry_Struct), a6, a7);
//
//		//	delete me;
//
//		//}
//
//		//DWORD var = 0;
//		//auto charToBreak = rand();
//		//var = (((DWORD)0x009DD250 - 0x400000) + baseAddress);
//		//PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);
//
//		//charToBreak = rand();
//		//var = (((DWORD)0x009DD254 - 0x400000) + baseAddress);
//		//PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);
//
//		//charToBreak = rand();
//		//var = (((DWORD)0x009DD258 - 0x400000) + baseAddress);
//		//PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);
//
//		//charToBreak = rand();
//		//var = (((DWORD)0x009DD25C - 0x400000) + baseAddress);
//		//PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);
//
//		//charToBreak = rand();
//		//var = (((DWORD)0x009DD260 - 0x400000) + baseAddress);
//		//PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);
//
//		char bOldUIEnabled = 0;
//
//		HMODULE hMods[1024];
//		DWORD cbNeeded;
//		unsigned int i;
//
//		if (opcode == 0xf13)
//		{
//			Checksum_Struct* scs = new Checksum_Struct;
//			memset(scs, 0, sizeof(Checksum_Struct));
//			scs->opcode = 0xf13;
//			Checksum_Struct* cs = (Checksum_Struct*)buf;
//			scs->checksum = cs->checksum;
//
//			retval = SendMessage_Trampoline(con, unk, channel, (char*)scs,
//				sizeof(Checksum_Struct), a6, a7);
//
//			delete scs;
//
//			//memset(cs->GPUString, 0, 256);
//			//memset(cs->CPUBrandString, 0, 256);
//			//memset(cs->HDDSerial, 0, 512);
//			//strncpy(cs->CPUBrandString, g_HWID.CPUBrandString, 64);
//			//strncpy(cs->GPUString, g_HWID.gfxDescription, 256);
//			//strncpy(cs->HDDSerial, std::string(g_HWID.HDDSerial.begin(), g_HWID.HDDSerial.end()).c_str(), 512);
//			//memcpy(cs->CRC1, &g_HWID.CPUBrandCRC, 4);
//			//memcpy(cs->CRC2, &g_HWID.CPUFeaturesCRC, 4);
//			//memcpy(cs->CRC3, &g_HWID.CPUFreqCRC, 4);
//			//memcpy(cs->CRC4, &g_HWID.CPUStringCRC, 4);
//			//memcpy(cs->CRC5, &g_HWID.MacCRC, 4);
//			//memcpy(cs->DisplayW, &g_HWID.DisplayW, 4);
//			//memcpy(cs->DisplayH, &g_HWID.DisplayH, 4);
//			return retval;
//		}
//	}
//
//	else if (opcode == 0x298d)
//	{
//		Checksum_Struct* cs = (Checksum_Struct*)buf;
//		Checksum_Struct* scs = new Checksum_Struct;
//		memset(scs, 0, sizeof(Checksum_Struct));
//		scs->opcode = 0x298d;
//		scs->checksum = cs->checksum;
//
//		retval = SendMessage_Trampoline(con, unk, channel, (char*)scs,
//			sizeof(Checksum_Struct), a6, a7);
//
//		delete scs;
//		return retval;
//	}
//
//	retval = SendMessage_Trampoline(con, unk, channel, buf,
//		size, a6, a7);
//
//	return retval;
//}
//
//DETOUR_TRAMPOLINE_EMPTY(unsigned char __fastcall SendMessage_Trampoline(DWORD *, unsigned __int32, unsigned __int32, char* buf, size_t, DWORD, DWORD));
DETOUR_TRAMPOLINE_EMPTY(unsigned char __fastcall SetDeviceGammaRamp_Trampoline(HDC hdc, LPVOID lpRamp));

signed int ProcessGameEvents_Hook()
{
   DWORD oldTimeGetTimeVal = 0;
   return return_ProcessGameEvents();
}

void SkipLicense()
{
	//char str[255];
	//DWORD ff;
	//sprintf(str, "%d",*(DWORD*)(0x807DFC));
	//MessageBox(NULL, str, NULL, MB_OK);
	//DWORD offset = (DWORD)eqmain_dll + 0x255D2;
	//const char test1[] = { 0xEB }; // , 0x90, 0x90, 0x90, 0x90, 0x90};
	//PatchA((DWORD*)offset, &test1, sizeof(test1));

}

void SkipSplash()
{
	// Set timer for intro splash screens to 0

	////gypsies
	//const char test1[] = { 0x90, 0x90, 0x90 };
	//PatchA((DWORD*)0x004798ED, &test1, sizeof(test1));

	////skeletons
	//const char test2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	//PatchA((DWORD*)0x0048276F, &test2, sizeof(test2));

	////PVP Attack 
	//const char test3[] = { 0xEB, 0x39, 0x90, 0x90, 0x90, 0x90 };
	//PatchA((DWORD*)0x0047EC22, &test3, sizeof(test3));

	//const char test4[] = { 0xEB, 0x09, 0x90, 0x90, 0x90, 0x90 };
	//PatchA((DWORD*)0x0047EC78, &test4, sizeof(test4));

	//const char test5[] = { 0xEB, 0xD8, 0x90, 0x90, 0x90, 0x90 };
	//PatchA((DWORD*)0x000047EC83, &test5, sizeof(test5)); // 0047EC83 | EB D8                    | jmp eqgame.47EC5D                       |
	//item bonuses
	/*const char test3[] = { 0x2a, 0x06 };
	PatchA((DWORD*)0x0051E323, &test3, sizeof(test3));
	PatchA((DWORD*)0x0051E521, &test3, sizeof(test3));
	PatchA((DWORD*)0x0051E5FB, &test3, sizeof(test3));*/
	/*const char test1[] = { 0x00, 0x00 }


	//gypsies

	DWORD offset = (DWORD)eqmain_dll + 0x21998;
	PatchA((DWORD*)offset, &test1, sizeof(test1));

	const char test2[] = { 0x01 }; // , 0x90, 0x90, 0x90, 0x90, 0x90};

	const char test3[] = { 0x90, 0x90, 0x90, 0xEB, 0x36 }; // , 0x90, 0x90, 0x90, 0x90, 0x90};

	const char test4[] = { 0x57 }; // , 0x90, 0x90, 0x90, 0x90, 0x90};

	const char test5[] = { 0x90, 0x90, 0x90, 0x90 }; // , 0x90, 0x90, 0x90, 0x90,


	const char test6[] = { 0xE9, 0xB6, 0x02, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }; // , 0x90, 0x90, 0x90, 0x90,

	const char test7[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	const char test8[] = { 0x3B, 0xC1, 0x81, 0xC7, 0xE8, 0x03, 0x00, 0x00 };

	//Dual Wield for rangers
	PatchA((DWORD*)0x004D2800, &test2, sizeof(test2));
	PatchA((DWORD*)0x004D280C, &test2, sizeof(test2));
	PatchA((DWORD*)0x004D2828, &test2, sizeof(test2));
	//Meditate
	PatchA((DWORD*)0x004D304C, &test2, sizeof(test2));
	//Double Attack
	PatchA((DWORD*)0x004D25FD, &test2, sizeof(test2));

	//Mana at any level on rangers fix
	PatchA((DWORD*)0x004B949C, &test3, sizeof(test3));

	//Target label shows name
	PatchA((DWORD*)0x0043622A, &test4, sizeof(test4));

	//Instantly scribe spells
	PatchA((DWORD*)0x00043514F, &test5, sizeof(test5));

	//No local coord evac on zoning fail
	//PatchA((DWORD*)0x0005461F4, &test6, sizeof(test6));

	//Bard songs have modifier when calculating the value sent by the server, even if you're not a bard. Use 1.0 multiplier for non-bard spells on the server.
	PatchA((DWORD*)0x004CA16A, &test7, sizeof(test7));

	//Increase stat cap increase granted by AAs to be 1000 instead of 25 max.
	PatchA((DWORD*)0x004B7D45, &test8, sizeof(test8));
	*/

	//PatchA((void*)0x0050C06E, "\x00", 1); //Group pet health removal
	//PatchA((void*)0x00545001, "\xEB", 1); //Self pet health removal
	//PatchA((void*)0x005540D1, "\xEB", 1); //Skills (open/inspect) removal
	//PatchA((void*)0x0046356A, "\xE9\xD6\x0D\x00\x00\x90\x90\x90\x90", 9); //Find Window removal (Button exists, but does nothing.)
	//PatchA((void*)0x00464141, "\xE9\xFF\x01\x00\x00\x90\x90\x90\x90", 9); //DZ Window (All forms of hotkey disabled.)
	//PatchA((void*)0x004642F2, "\xEB\x51\x90", 3); //Task Selection Window disabled.
	//PatchA((void*)0x004A71D6, "\xE9\x2D\x01\x00", 4); //Left Click Shows Target Help Disabled and cannot be re-enabled.
	//return_ActivateDet = (Activate_t)DetourFunction((PBYTE)CXWndActivateAddr, (PBYTE)CXWndActivateHook); // Almost all non-classic windows have been disabled.
	//return_ValueSellMerchantDet = (ValueSellMerchant_t)DetourFunction((PBYTE)ValueSellMerchantAddr, (PBYTE)ValueSellMerchantHook); // Items sold to greedy merchants that are sold at 0cp are now sold at 1cp
	//return_SetCCreateCameraDet = (SetCCreateCamera_t)DetourFunction((PBYTE)0x507b30, (PBYTE)SetCCreateCameraHook); // Character Creation screen hook for position based on class/race/deity.
	//return_SelectCharacterDet = (SelectCharacter_t)DetourFunction((PBYTE)SelectCharacterAddr, (PBYTE)SelectCharacterHook); // Character Selection screen hook for position based on class/race/deity.
	//PatchA((void*)0x004AAA15, "\xB8", 1); //For Character Selection. Tells client to load "load.s3d" instead of "clz.eqg".
	//PatchA((void*)0x0063EF73, "pickchar.xmi", 12); //Writes "pickchar.xmi" to unused memory in eqgame.exe
	//PatchA((void*)0x009C8C2C, "load\x00", 5); // Use load instead of "CLZ" 
	//PatchA((void*)0x0044B7D8, "\x68\x73\xEF\x63", 4); //Makes a PUSH load the above into memory instead of "eqtheme.mp3" for future use.
	//PatchA((void*)0x0044B83D, "\xEB", 1); //Force-loads "opener4.xmi" when opening the character selection screen into theme position 1.
	//PatchA((void*)0x0044B895, "\x14", 1); //Instead of assigning "opener4.xmi" to both positions which Titanium does by default, we overwrite position 4 (char select) with the pickchar.xmi asset

}


void PatchSaveBypass()
{
}
DWORD wpsaddress = 0;
DWORD swAddress = 0;
DWORD cwAddress = 0;
DWORD swlAddress = 0;
DWORD uwAddress = 0;

PVOID pHandler;
bool bInitalized=false;


// DirectXSetupGetVersion
int __stdcall DirectXSetupGetVersion(DWORD *lpdwVersion, DWORD *lpdwMinorVersion)
{
	return 1;
}

BOOL __stdcall SetDeviceGammaRamp_Hook(HDC hdc, LPVOID lpRamp)
{
	return 1;
}

extern CRITICAL_SECTION gDetourCS;
void InitHooks()
{
   rename("arena.eqg", "arena.eqg.bak");
   rename("highpasshold.eqg", "highpasshold.eqg.bak");
   rename("nektulos.eqg", "nektulos.eqg.bak");
   rename("lavastorm.eqg", "lavastorm.eqg.bak");

   InitOffsets();
   GetEQPath(gszEQPath);
   InitializeCriticalSection(&gDetourCS);
   InitializeMQ2Detours();
   InitializeDisplayHook();
   InitializeChatHook();
   InitializeMQ2Commands();
   InitializeMQ2Windows();
   InitializeMQ2Pulse();
   InitializeMQ2Spawns();
   InitializeMapPlugin();
   InitializeMQ2ItemDisplay();
   InitializeMQ2Labels();
#ifdef DPSPLUGIN
   InitializeEdgeDPSPlugin();
   InitializeDPSPlugin();
#endif

	//heqwMod
	//wpsaddress = (DWORD)GetProcAddress(hkernel32Mod, "WritePrivateProfileStringA");
	//HMODULE huser32Mod = GetModuleHandleA("user32.dll");
	//
	//swAddress = (DWORD)GetProcAddress(huser32Mod, "ShowWindow");
	//cwAddress = (DWORD)GetProcAddress(huser32Mod, "CreateWindowExA");
	//swlAddress = (DWORD)GetProcAddress(huser32Mod, "SetWindowLong");
	//EzDetour(0x004F2ED0, SendExeChecksum_Detour, SendExeChecksum_Trampoline);
	//EzDetour(0x004AA8BC, &Eqmachooks::CDisplay__Render_World_Detour, &Eqmachooks::CDisplay__Render_World_Trampoline);
	//EzDetour(cwAddress, CreateWindowExA_Detour, CreateWindowExA_Trampoline);
	//here to fix the no items on corpse bug - eqmule
	//wpsaddress = (DWORD)GetProcAddress(hkernel32Mod, "WritePrivateProfileStringA");
	//HMODULE huser32Mod = GetModuleHandleA("user32.dll");
	//
	//swAddress = (DWORD)GetProcAddress(huser32Mod, "ShowWindow");
	//cwAddress = (DWORD)GetProcAddress(huser32Mod, "CreateWindowExA");
	//swlAddress = (DWORD)GetProcAddress(huser32Mod, "SetWindowLong");
	//EzDetour(0x004F2ED0, SendExeChecksum_Detour, SendExeChecksum_Trampoline);
	//EzDetour(0x004AA8BC, &Eqmachooks::CDisplay__Render_World_Detour, &Eqmachooks::CDisplay__Render_World_Trampoline);
	//EzDetour(cwAddress, CreateWindowExA_Detour, CreateWindowExA_Trampoline);
	//here to fix the no items on corpse bug - eqmule
	//EzDetour(0x00537E4B, &Eqmachooks::CEverQuest__StripName_Detour, &Eqmachooks::CEverQuest__StripName_Trampoline);
	//EzDetour(0x00537D39, &Eqmachooks::CEverQuest__TrimName_Detour, &Eqmachooks::CEverQuest__TrimName_Trampoline);

   if (baseAddress) {

	   DWORD var = (((DWORD)0x008C4CE0 - 0x400000) + baseAddress);

	   //EzDetour((DWORD)var, SendMessage_Detour, SendMessage_Trampoline);


	   var = (((DWORD)0x004C3250 - 0x400000) + baseAddress);

	   EzDetour((DWORD)var, HandleWorldMessage_Detour, HandleWorldMessage_Trampoline);

	   // DWORD var = (((DWORD)CXWndActivateAddr - 0x400000) + baseAddress);

	   // return_ActivateDet = (Activate_t)DetourFunction((PBYTE)var, (PBYTE)CXWndActivateHook); // Almost all non-classic windows have been disabled.

	   var = ((0x00507b30 - 0x400000) + baseAddress);
	   return_SetCCreateCameraDet =
		   (SetCCreateCamera_t)DetourFunction((PBYTE)var, (PBYTE)SetCCreateCameraHook);
	   var = (((DWORD)0x009C8C2C - 0x400000) + baseAddress);
	   PatchA((DWORD*)var, "freeporttheater\x00", 16); // Use load instead of "CLZ"


	   //basedata as spell CRC begin
	   var = (((DWORD)0x00AA6980 - 0x400000) + baseAddress);
	   PatchA((DWORD*)var, "spells_us.txt", 13);

	   DWORD varToPatch = (((DWORD)0x00AA6980 - 0x400000) + baseAddress);
	   var = (((DWORD)0x004EEAAB - 0x400000) + baseAddress);
	   PatchA((DWORD*)var, (void*)&varToPatch, 4);
	   //basedata as spell CRC end
	   var = (((DWORD)0x007E22CE - 0x400000) + baseAddress); // push "Theater", 0x64 preceeds these bytes, 0xCE is start of dword ptr
	   DWORD byteAddrForPush = (((DWORD)0x015D95C4 - 0x400000) + baseAddress);
	   const char* bytearray = (const char*)byteAddrForPush;
	   char c[4];
	   memcpy(&c, &byteAddrForPush, 4);
	   PatchA((DWORD*)byteAddrForPush, "New Freeport\x00", 13);
	   PatchA((DWORD*)var, (char*)&c[0], 1);
	   PatchA((DWORD*)(var + 1), (char*)&c[1], 1);
	   PatchA((DWORD*)(var + 2), (char*)&c[2], 1);
	   PatchA((DWORD*)(var + 3), (char*)&c[3], 1);

	   //var = (((DWORD)0x0044410C - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\xEB", 3); // Remove heroic Stamina

	   //var = (((DWORD)0x00442B36 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\xEB", 3); // Remove heroic int
	   //var = (((DWORD)0x00442BB6 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\xEB", 3); // Remove heroic wis

	   ////#pragma comment(lib, "Iphlpapi.lib")

	   //var = (((DWORD)0x004538AE - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\xEB",
		  // 3); // Fix Max HP setting
	   ////0065CC71
	   //var = (((DWORD)0x0065CC09 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\x90\x90",
		  // 4); // Fix tradeskill containers

	   DWORD varArray = (((DWORD)0x009BFF6D - 0x400000) + baseAddress);

	   //var = (((DWORD)0x004ED03B - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x4C", 1); // Link stuff
	   //var = (((DWORD)0x004ED051 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&varArray, 4); // Link stuff
	   //var = (((DWORD)0x004ED072 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&varArray, 4); // Link stuff
	   //var = (((DWORD)0x007BBC9A - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&varArray, 4); // Link stuff
	   //var = (((DWORD)0x007BBD77 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&varArray, 4); // Link stuff

	   //var = (((DWORD)0x009BFF6D - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x25\x30\x38\x58", 4); // Link stuff

	   //var = (((DWORD)0x00A1ACE0 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x4F", 1); // Link stuff

	   //var = (((DWORD)0x004ED062 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x08", 1); // Fix current HP cap

	   //var = (((DWORD)0x004ED083 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x08", 1); // Fix current HP cap

	   //var = (((DWORD)0x0063C36F - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\x90\x90", 4); // Bazaar trader anywhere

	   //var = (((DWORD)0x0063978E - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\xEB", 3); // Bazaar trader anywhere

	   //var = (((DWORD)0x006AB6AF - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\xE9\xA5\x00", 5); // nop / jmp dmg bonus

	   //var = (((DWORD)0x006AB6B6 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90", 1); // nop / jmp dmg bonus

	   //var = (((DWORD)0x00632DE6 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90", 2); // nop trader check

	   //var = (((DWORD)0x00632DDF - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90", 2); // nop trader check

	   //var = (((DWORD)0x00632DF6 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90", 2); // nop trader check

	   //var = (((DWORD)0x00632E08 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90", 2); // nop trader check

	   var = (((DWORD)0x005FE751 - 0x400000) + baseAddress);
	   PatchA((DWORD*)var, "\xEB\x1C\x90\x90\x90", 5); // patchme req bypass

	   //var = (((DWORD)0x006A3FB0 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\xEB", 3); // nop / jmp dmg bonus #2

	   //var = (((DWORD)0x0057F2C7 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\xBF\xFF\xFF\xFF\x0F\x90\x90\x90\xE9\xF4\x01\x00\x00\x90", 14); //patch stat cap to be 0x0FFFFFFF

	   //var = (((DWORD)0x0069A3D1 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\xB8\x60\xEA\x00\x00\x90", 6); //reuse time hack, up to 1 minute


	   // Spells BEGIN
	   //   var = (((DWORD)0x00433c24 - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\xB0\x01", 2);

	   // var = (((DWORD)0x00647562 - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x006475F7 - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x00647853 - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x00648051 - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x006484A2 - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x00648DBC - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x00648F02 - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x00648F4E - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x00649149 - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	   // var = (((DWORD)0x0064920D - 0x400000) + baseAddress);
	   //      PatchA((DWORD*)var, "\x10", 1);

	  // var = (((DWORD)0x00444158 - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
		 //  12); // Fix max HP cap

	  // var = (((DWORD)0x0045F26E - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\xE9\xB3\x01\x00\x00\x90",
		 //  11); // Disable regen ticks // maybe hp

	  //var = (((DWORD)0x0045E376 - 0x400000) + baseAddress);
	  //PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\x90\x90\x90", 8); // No unconscious pls

	  // var = (((DWORD)0x0045E381 - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\x90\x90\x90", 8); // No unconscious pls

	  // var = (((DWORD)0x00449E3B - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\x90\x90\xE9\x1B\x01\x00\x00\x90", 13); // HP fix - the real deal

	  // var = (((DWORD)0x00449F62 - 0x400000) + baseAddress); // HP fix - the real deal
	  // PatchA((DWORD*)var, "\x90\x90", 2);
	  // var = (((DWORD)0x00449F64 - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
		 //  13); // Fix current HP cap

	  // var = (((DWORD)0x00444308 - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\xEB\x64",
		 //  4); // Fix current mana amounts

	  // var = (((DWORD)0x00444198 - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\xEB\x64",
		 //  4); // Fix current endur

	  // var = (((DWORD)0x0045AE9F - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\xE9\x76\x03\x00\x00\x90",
		 //  8); // Fix food/drink spam

	  // var = (((DWORD)0x0045385D - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 30); //hp damage in combat abilities fix

	   //var = (((DWORD)0x00409776 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x05", 1); // Monk armor fix

	   //var = (((DWORD)0x00409793 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x05", 1); // Monk armor fix

	   //var = (((DWORD)0x004097DC - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x05", 1); // Monk armor fix

	   //var = (((DWORD)0x00409882 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\xFB", 1); // Monk armor fix

	   //var = (((DWORD)0x004098AD - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x05", 1); // Monk armor fix

	   //var = (((DWORD)0x00409953 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\xFB", 1); // Monk armor fix

	   //var = (((DWORD)0x00409968 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x05", 1); // Monk armor fix

	  // var = (((DWORD)0x00443631 - 0x400000) + baseAddress);
	  // PatchA((DWORD*)var, "\xB0\x01\x5E\xC2\x04\x00\x90", 7); // Group marker in a party of 2

	   //var = (((DWORD)0x004972AC - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90",
		  //35); // Nop the gamma slider

	   //var = (((DWORD)0x00709AC1 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, "\x90\x90\x90\x90\x90\x90\xE9\xD0\x00\x90",
		  // 10); // Nop the gamma slider

	   //auto charToBreak = rand();

	   //var = (((DWORD)0x009DD250 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);

	   //charToBreak = rand();
	   //var = (((DWORD)0x009DD254 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);

	   //charToBreak = rand();
	   //var = (((DWORD)0x009DD258 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);

	   //charToBreak = rand();
	   //var = (((DWORD)0x009DD25C - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);

	   //charToBreak = rand();
	   //var = (((DWORD)0x009DD260 - 0x400000) + baseAddress);
	   //PatchA((DWORD*)var, (DWORD*)&charToBreak, 4);
	   HMODULE hkernel32Mod = GetModuleHandle("kernel32.dll");
	   DWORD gmfadress = (DWORD)GetProcAddress(hkernel32Mod, "GetModuleFileNameA");
	   EzDetour(gmfadress, GetModuleFileNameA_detour, GetModuleFileNameA_tramp);
	   HMODULE gdi32mod = GetModuleHandle("gdi32.dll");
	   DWORD jmpToDeviceGamma = (DWORD)GetProcAddress(gdi32mod, "SetDeviceGammaRamp");
	   EzDetour(jmpToDeviceGamma, SetDeviceGammaRamp_Hook, SetDeviceGammaRamp_Trampoline);



   }
	//EzDetour(0x00537E4B, &Eqmachooks::CEverQuest__StripName_Detour, &Eqmachooks::CEverQuest__StripName_Trampoline);
	//EzDetour(0x00537D39, &Eqmachooks::CEverQuest__TrimName_Detour, &Eqmachooks::CEverQuest__TrimName_Trampoline);

	//return_CreateFileA = (CreateFileA_t)DetourFunction((PBYTE)GetProcAddress(hkernel32Mod, "CreateFileA"),(PBYTE)CreateFileAHook);
	//EzDetour(wpsaddress, WritePrivateProfileStringA_detour, WritePrivateProfileStringA_tramp);
	//EQMACMQ_REAL_CBuffWindow__RefreshBuffDisplay = (EQ_FUNCTION_TYPE_CBuffWindow__RefreshBuffDisplay)DetourFunction((PBYTE)EQ_FUNCTION_CBuffWindow__RefreshBuffDisplay, (PBYTE)EQMACMQ_DETOUR_CBuffWindow__RefreshBuffDisplay);
	//heqwMod = GetModuleHandle("eqw.dll");

	//return_ProcessGameEvents = (ProcessGameEvents_t)DetourFunction((PBYTE)__ProcessGameEvents, (PBYTE)return_ProcessGameEvents);
	//return_SetMouseCenter = (ProcessGameEvents_t)DetourFunction((PBYTE)o_MouseCenter, (PBYTE)SetMouseCenter_Hook);

	//eqgfxMod = *(DWORD*)(0x007F9C50);
	//d3ddev = (DWORD)(eqgfxMod + 0x00A4F92C);
	//	
	//EzDetour(0x0055A4F4, WndProc_Detour, WndProc_Trampoline);
	//// This detours key press down handler, so we can capture alt-enter to switch video modes
	//EzDetour(0x00525B04, ProcessKeyDown_Detour, ProcessKeyDown_Trampoline);
	//	
	//EzDetour(0x00538CE6, CEverQuest__DisplayScreen_Detour, CEverQuest__DisplayScreen_Trampoline);

	//// Add MGB for Beastlords
	//EzDetour(0x004B8231, sub_4B8231_Detour, sub_4B8231_Trampoline);

	////this one is here for eqplaynice - eqmule

	//EzDetour(0x0055AFE2, &Eqmachooks::CDisplay__Process_Events_Detour, &Eqmachooks::CDisplay__Process_Events_Trampoline);

	//EzDetour(EQ_FUNCTION_HandleMouseWheel, HandleMouseWheel_Detour, HandleMouseWheel_Trampoline);

	//EQMACMQ_REAL_CCharacterSelectWnd__Quit = (EQ_FUNCTION_TYPE_CCharacterSelectWnd__Quit)DetourFunction((PBYTE)EQ_FUNCTION_CCharacterSelectWnd__Quit, (PBYTE)EQMACMQ_DETOUR_CCharacterSelectWnd__Quit);



	//char szResult[255];
	//char szDefault[255];
	//sprintf(szDefault, "%s", "TRUE");
	//DWORD error = GetPrivateProfileStringA("Options", "WindowedMode", szDefault, szResult, 255, "./eqclient.ini");
	//if (GetLastError())
	//{
	//	WritePrivateProfileStringA("Options", "WindowedMode", szDefault, "./eqclient.ini");
	//}
	//if (!strcmp(szResult, "FALSE")) {
	//	bWindowedMode = false;
	//	start_fullscreen = true;
	//}
	//
	//sprintf(szDefault, "%d", 32);
	//error = GetPrivateProfileStringA("VideoMode", "BitsPerPixel", szDefault, szResult, 255, "./eqclient.ini");
	//if (!GetLastError())
	//{
	//	// if set to 16 bit, change to 32
	//	if (!strcmp(szResult, "16"))
	//		WritePrivateProfileStringA_tramp("VideoMode", "BitsPerPixel", szDefault, "./eqclient.ini");
	//}
	//else {
	//	// we do not have one set
	//	DEVMODE dm;
	//	// initialize the DEVMODE structure
	//	ZeroMemory(&dm, sizeof(dm));
	//	dm.dmSize = sizeof(dm);
	//	DWORD bits = 32;
	//	DWORD freq = 40;
	//	if (0 != EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
	//	{
	//		// get default display settings
	//		bits = dm.dmBitsPerPel;
	//		freq = dm.dmDisplayFrequency;
	//	}
	//	sprintf(szDefault, "%d", freq);
	//	WritePrivateProfileStringA_tramp("VideoMode", "RefreshRate", szDefault, "./eqclient.ini");
	//	sprintf(szDefault, "%d", bits);
	//	WritePrivateProfileStringA_tramp("VideoMode", "BitsPerPixel", szDefault, "./eqclient.ini");
	//}
	//bInitalized=true;
}

void ExitHooks()
{
	if(!bInitalized)
	{
		return;
	}

	//RemoveDetour(0x4E829F); // HandleWorldMessage
}
BOOL ParseINIFile(PCHAR lpINIPath)
{
   CHAR Filename[MAX_STRING] = {0};
   CHAR MQChatSettings[MAX_STRING] = {0};
   CHAR CustomSettings[MAX_STRING] = {0};
   CHAR ClientINI[MAX_STRING] = {0};
   CHAR szBuffer[MAX_STRING] = {0};
   CHAR ClientName[MAX_STRING] = {0};
   CHAR FilterList[MAX_STRING * 10] = {0};
   GetEQPath(gszEQPath);

   sprintf(Filename, "%s\\Edge.ini", lpINIPath);
   sprintf(ClientINI, "%s\\eqgame.ini", lpINIPath);
   strcpy(gszINIFilename, Filename);

   DebugSpew("Expected Client version: %s %s", __ExpectedVersionDate,
             __ExpectedVersionTime);
   DebugSpew("    Real Client version: %s %s", __ActualVersionDate, __ActualVersionTime);

   // note: __ClientOverride is always #defined as 1 or 0
#if (!__ClientOverride)
   if (strncmp(__ExpectedVersionDate, (const char*)__ActualVersionDate,
               strlen(__ExpectedVersionDate)) ||
       strncmp(__ExpectedVersionTime, (const char*)__ActualVersionTime,
               strlen(__ExpectedVersionTime))) {
      MessageBox(NULL, "Incorrect client version", "Edge", MB_OK);
      return FALSE;
   }
#endif

      gbAlwaysDrawMQHUD = false;
   gbHUDUnderUI = false;

   DefaultFilters();

   return TRUE;
}


bool __cdecl MQ2Initialize()
{
   if (!InitOffsets()) {
      DebugSpewAlways("InitOffsets returned false - thread aborted.");
      g_Loaded = FALSE;
      return false;
   }

   if (!ParseINIFile("eqclient.ini")) {
      DebugSpewAlways("ParseINIFile returned false - thread aborted.");
      g_Loaded = FALSE;
      return false;
   }
   srand((unsigned int)time(0));
   ZeroMemory(gDiKeyName, sizeof(gDiKeyName));
   unsigned long i;
   for (i = 0; gDiKeyID[i].Id; i++) {
      gDiKeyName[gDiKeyID[i].Id] = gDiKeyID[i].szName;
   }

   ZeroMemory(szEQMappableCommands, sizeof(szEQMappableCommands));
   for (i = 0; i < nEQMappableCommands; i++) {
      if ((DWORD)EQMappableCommandList[i] == 0 ||
          (DWORD)EQMappableCommandList[i] > (DWORD)__AC1_Data)
         continue;
      szEQMappableCommands[i] = EQMappableCommandList[i];
   }
   gnNormalEQMappableCommands = i;

   // as long nEQMappableCommands is right and these remain at the end, these
   // should never need updating who uses the unknowns anyway? - ieatacid
   szEQMappableCommands[nEQMappableCommands - 23] = "UNKNOWN0x10d";
   szEQMappableCommands[nEQMappableCommands - 22] = "UNKNOWN0x10e";
   szEQMappableCommands[nEQMappableCommands - 21] = "UNKNOWN0x10f";
   szEQMappableCommands[nEQMappableCommands - 20] = "UNKNOWN0x110";
   szEQMappableCommands[nEQMappableCommands - 19] = "CHAT_SEMICOLON";
   szEQMappableCommands[nEQMappableCommands - 18] = "CHAT_SLASH";
   szEQMappableCommands[nEQMappableCommands - 17] = "UNKNOWN0x113";
   szEQMappableCommands[nEQMappableCommands - 16] = "UNKNOWN0x114";
   szEQMappableCommands[nEQMappableCommands - 15] = "INSTANT_CAMP";
   szEQMappableCommands[nEQMappableCommands - 14] = "UNKNOWN0x116";
   szEQMappableCommands[nEQMappableCommands - 13] = "UNKNOWN0x117";
   szEQMappableCommands[nEQMappableCommands - 12] = "CHAT_EMPTY";
   szEQMappableCommands[nEQMappableCommands - 11] = "TOGGLE_WINDOWMODE";
   szEQMappableCommands[nEQMappableCommands - 10] = "UNKNOWN0x11a";
   szEQMappableCommands[nEQMappableCommands - 9] = "UNKNOWN0x11b";
   szEQMappableCommands[nEQMappableCommands - 8] =
      "CHANGEFACE"; // maybe? something that requires models.
   szEQMappableCommands[nEQMappableCommands - 7] = "UNKNOWN0x11d";
   szEQMappableCommands[nEQMappableCommands - 6] = "UNKNOWN0x11e";
   szEQMappableCommands[nEQMappableCommands - 5] = "UNKNOWN0x11f";
   szEQMappableCommands[nEQMappableCommands - 4] = "UNKNOWN0x120";
   szEQMappableCommands[nEQMappableCommands - 3] = "UNKNOWN0x121";
   szEQMappableCommands[nEQMappableCommands - 2] = "UNKNOWN0x122";
   szEQMappableCommands[nEQMappableCommands - 1] = "UNKNOWN0x123";

   for (nColorAdjective = 0; szColorAdjective[nColorAdjective]; nColorAdjective++) {
   }
   for (nColorAdjectiveYou = 0; szColorAdjectiveYou[nColorAdjectiveYou];
        nColorAdjectiveYou++) {
   }
   for (nColorExpletive = 0; szColorExpletive[nColorExpletive]; nColorExpletive++) {
   }
   for (nColorSyntaxError = 0; szColorSyntaxError[nColorSyntaxError];
        nColorSyntaxError++) {
   }
   for (nColorMacroError = 0; szColorMacroError[nColorMacroError]; nColorMacroError++) {
   }
   for (nColorMQ2DataError = 0; szColorMQ2DataError[nColorMQ2DataError];
        nColorMQ2DataError++) {
   }
   for (nColorFatalError = 0; szColorFatalError[nColorFatalError]; nColorFatalError++) {
   }
#ifndef ISXEQ
   InitializeParser();
#endif
   InitializeMQ2Detours();
   InitializeDisplayHook();
   InitializeChatHook();
   InitializeMQ2Spawns();
   InitializeMQ2Pulse();
   InitializeMQ2Commands();
   InitializeMQ2Windows();
   InitializeMapPlugin();
  // InitializeMQ2KeyBinds();
   return true;
}


// ***************************************************************************
// Function:    MQ2Start
// Description: Where we start execution during the insertion
// ***************************************************************************
DWORD WINAPI MQ2Start()
{
   PCHAR lpINIPath = "";
   strcpy(gszINIPath, lpINIPath);
   CHAR szBuffer[MAX_STRING] = {0};

   if (!MQ2Initialize()) return 1;
   return 0;
}

// dinput8.cpp : Defines the exported functions for the DLL application.
//

#include "IDirectInput8Hook.h"
AddressLookupTable<void> ProxyAddressLookupTable = AddressLookupTable<void>();

DirectInput8CreateProc m_pDirectInput8Create;
DllCanUnloadNowProc m_pDllCanUnloadNow;
DllGetClassObjectProc m_pDllGetClassObject;
DllRegisterServerProc m_pDllRegisterServer;
DllUnregisterServerProc m_pDllUnregisterServer;
GetdfDIJoystickProc m_pGetdfDIJoystick;
bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
   static HMODULE dinput8dll = nullptr;
   CHAR szFilename[MAX_STRING] = {0};

   switch (dwReason) {
   case DLL_PROCESS_ATTACH:
	   // Load dll
	   char path[MAX_PATH];
	   GetSystemDirectoryA(path, MAX_PATH);
	   strcat_s(path, "\\dinput8.dll");
	   dinput8dll = LoadLibraryA(path);

	   PCHAR szProcessName;
	   ghModule = (HMODULE)hModule;
	   ghInstance = (HINSTANCE)hModule;

	   GetModuleFileName(ghModule, szFilename, MAX_STRING);
	   szProcessName = strrchr(szFilename, '\\');
	   szProcessName[0] = '\0';
	   strcat(szFilename, "\\eqgame.ini");

	   GetModuleFileName(NULL, szFilename, MAX_STRING);

	   szProcessName = strrchr(szFilename, '.');
	   szProcessName[0] = '\0';
	   szProcessName = strrchr(szFilename, '\\') + 1;
	  InitHooks();
	   // remove full information about my command line
	 // memset(&pbi.PebBaseAddress->ProcessParameters->ImagePathName.Buffer, 0, pbi.PebBaseAddress->ProcessParameters->ImagePathName.Length);


	   // Get function addresses
	   m_pDirectInput8Create =
		   (DirectInput8CreateProc)GetProcAddress(dinput8dll,
			   "DirectInput8Create");
	   m_pDllCanUnloadNow =
		   (DllCanUnloadNowProc)GetProcAddress(dinput8dll, "DllCanUnloadNow");
	   m_pDllGetClassObject =
		   (DllGetClassObjectProc)GetProcAddress(dinput8dll, "DllGetClassObject");
	   m_pDllRegisterServer =
		   (DllRegisterServerProc)GetProcAddress(dinput8dll, "DllRegisterServer");
	   m_pDllUnregisterServer =
		   (DllUnregisterServerProc)GetProcAddress(dinput8dll,
			   "DllUnregisterServer");
	   m_pGetdfDIJoystick =
		   (GetdfDIJoystickProc)GetProcAddress(dinput8dll, "GetdfDIJoystick");
	   break;

   case DLL_PROCESS_DETACH:
	   CoUninitialize();
	   FreeLibrary(dinput8dll);
	   break;
   }

   return true;
}

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf,
                                  LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
   if (!m_pDirectInput8Create) {
      return E_FAIL;
   }

   HRESULT hr = m_pDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);

   if (SUCCEEDED(hr)) {
      genericQueryInterface(riidltf, ppvOut);
   }

   return hr;
}

HRESULT WINAPI DllCanUnloadNow()
{
   if (!m_pDllCanUnloadNow) {
      return E_FAIL;
   }

   return m_pDllCanUnloadNow();
}

HRESULT WINAPI DllGetClassObject(IN REFCLSID rclsid, IN REFIID riid, OUT LPVOID FAR* ppv)
{
   if (!m_pDllGetClassObject) {
      return E_FAIL;
   }

   HRESULT hr = m_pDllGetClassObject(rclsid, riid, ppv);

   if (SUCCEEDED(hr)) {
      genericQueryInterface(riid, ppv);
   }

   return hr;
}

HRESULT WINAPI DllRegisterServer()
{
   if (!m_pDllRegisterServer) {
      return E_FAIL;
   }

   return m_pDllRegisterServer();
}

HRESULT WINAPI DllUnregisterServer()
{
   if (!m_pDllUnregisterServer) {
      return E_FAIL;
   }

   return m_pDllUnregisterServer();
}

LPCDIDATAFORMAT WINAPI GetdfDIJoystick()
{
   if (!m_pGetdfDIJoystick) {
      return nullptr;
   }

   return m_pGetdfDIJoystick();
}
