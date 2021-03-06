#include <Windows.h>
#pragma once 

#define X86_NOP 0x90 
#define X86_RETN 0xC3 
#define X86_CALL 0xE8 
#define X86_JMP 0xE9 

struct ProtectionInfo 
{ 
    DWORD dwAddress; 
    DWORD dwOldProtection; 
    int   iSize; 
}; 

class CPatcher 
{ 
public: 
    static ProtectionInfo Unprotect(DWORD dwAddress, int iSize); 
    static void           Reprotect(ProtectionInfo protectionInfo);
    static void           InstallNopPatch(DWORD dwAddress, int iSize = 5); 
    static void         * InstallDetourPatchInternal(DWORD dwAddress, DWORD dwDetourAddress, BYTE byteType, int iSize = 5); 
    static void           UninstallDetourPatchInternal(DWORD dwAddress, void * pTrampoline, int iSize = 5); 
    static void           InstallPatchType(DWORD dwAddress, DWORD dwTypeAddress, BYTE byteType, int iSize = 5);
    static void           InstallRetnPatch(DWORD dwAddress); 
    static void           InstallStringPatch(DWORD dwAddress, char * szString, int iSize); 
    static void           InstallMethodPatch(DWORD dwHookAddress, DWORD dwFunctionAddress); 
    static DWORD          GetFunctionAddress(char * szLibrary, char * szFunction); 
    static DWORD          GetFunctionAddress(char * szLibrary, unsigned int uOrdinal); 
    static void         * InstallDetourPatch(char * szLibrary, char * szFunction, DWORD dwFunctionAddress); 
    static void         * InstallDetourPatch(char * szLibrary, unsigned int uOrdinal, DWORD dwFunctionAddress); 
    static BYTE           InstallDetourPatchWithData(char * szLibrary, unsigned int uOrdinal, DWORD dwFunctionAddress); 
    static void           UninstallDetourPatch(void * pTrampoline, DWORD dwFunctionAddress); 
    static void           InstallPushPatch(DWORD dwAddress, DWORD dwFunc); 
};  