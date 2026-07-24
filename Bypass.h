#include <jni.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <time.h>
#include <sys/time.h>
#include <unordered_map>
#include <string>
#include <thread>
#include <atomic>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <arm_neon.h>
#include "Main/KittyMemory/MemoryPatch.h"
#include "Main/KittyMemory/KittyMemory.h"
#include "Main/Logger.h"
#include "Main/oxorany.h"
#include "Main/Utils.h"
#include "Main/Macros.h"

#define targetLibName oxorany("libanogs.so")
#define _ReadStatusReg
#define ARM64_SYSREG
typedef uint64_t _QWORD;
typedef long long __int64;

#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t

// ================= GLOBAL =================
uintptr_t libanogsBase = 0;
uintptr_t libUE4Base   = 0;
uintptr_t libanogs = Tools::GetBaseAddress("libanogs.so");
DWORD libanogsAlloc = 0;
DWORD libUE4Alloc   = 0;

unsigned int libanogsSize;
unsigned int libUE4Size;
// ================= BASIC =================
#define R2F(RET, NAME, ARGS) \
typedef RET (*NAME##_t) ARGS; \
static NAME##_t o##NAME = nullptr; \
static RET h##NAME ARGS
__int64 r2fsunilyt_rs_vip(){ return 0LL; }

int64_t hook_ret_zero()
{
	return 0LL;
}
//===========================[ Get Taime ]===============================
static unsigned int rs;
__attribute__((constructor)) static void init_hook(){
    rs = (unsigned)time(NULL) ^ (unsigned)getpid();
}

__int64 __fastcall gettaimeofday_r2f(__int64 a1, __int64 a2, __int64 a3)
{
    if ((rand_r(&rs) % 100) < 5) {
        int delay_ms = 20 + (rand_r(&rs) % 11);
        usleep((useconds_t)delay_ms * 1000);
    }
    return a1;
}
extern "C" void __attribute__((constructor)) init_hook_alias(){}
//======================================================================
 __int64 __fastcall (*osub_2328F0)(__int64 a1, const char *a2, bool a3, int a4);

__int64 __fastcall hsub_2328F0(__int64 a1, const char *a2, bool a3, int a4) {
    if (a2 && strstr(a2, "XTask_builtin.zip_vm_main.img")) {
        sleep(100000);
        return 0LL;
    }

 if ( a2 && strstr(a2,"scan1") || //Crash Fix
   strstr(a2,"anti_root") || //Crash Fix
    strstr(a2,"opcode_scan") || //Crash Fix
   strstr(a2,"opcode_crash") || //Crash Fix
    strstr(a2,"various_opcode") || //Crash Fix
   strstr(a2,"zygisk_stack") || //Crash Fix
   strstr(a2, "zygisk_module") || //Crash Fix
    strstr(a2,"module_crash") //Crash Fix
 ){ 
   return 0;
 }
 return osub_2328F0(a1, a2, a3, a4);
}
//======================================================================

int64_t (__fastcall *osub_228560)(__int64 a1);
int64_t __fastcall hsub_228560(__int64 a1)
{
  if (!a1) {  return 0;  }
  *(_QWORD*)(a1 + 1120) = 0;
  *(_QWORD*)(a1 + 1064) = 0;
  return osub_228560(a1);
}

//======================================================================
int64_t (*osub_228168)(__int64 a1, unsigned __int8 *a2, unsigned int a3);
int64_t hsub_228168(__int64 a1, unsigned __int8 *a2, unsigned int a3) {

    switch (a3) {
        case 0x18:
        case 0x1a:
        case 0x1e:
        case 0x2a:
        case 0x2e:
        return oxorany(0);
      default:
        return osub_228168(a1, a2, a3);
    }
}
//===================================================================
__int64 __fastcall (*osub_37FD78)(_QWORD *a1, __int64 a2, unsigned __int64 a3, unsigned int a4);

__int64 __fastcall hsub_37FD78(_QWORD *a1, __int64 a2, unsigned __int64 a3, unsigned int a4) {
    if (osub_37FD78) {
        osub_37FD78(a1, a2, a3, a4);
    }
    return 1;
}

__int64 __fastcall (*osub_330494)(const void *a1, unsigned int a2);
__int64 __fastcall hsub_330494(const void *a1, unsigned int a2) {
    if (osub_330494) {
        osub_330494(a1, a2);
    }
    return 0;
}
__int64 __fastcall (*osub_379220)(__int64 a1, const char *a2, const char *a3);
__int64 __fastcall hsub_379220(__int64 a1, const char *a2, const char *a3) {
    return 0;
}

__int64 __fastcall (*osub_37966C)(int *a1, __int64 a2);
__int64 __fastcall hsub_37966C(int *a1, __int64 a2) {
    return 0;
}

__int64 __fastcall (*osub_37F7F4)(__int64 a1, __int64 a2);
__int64 __fastcall hsub_37F7F4(__int64 a1, __int64 a2) {
    return 0;
}
//============================================================================
__int64 __fastcall (*osub_3A564C)(__int64 a1, unsigned __int64 a2, void *a3, double a4);
__int64 __fastcall hsub_3A564C(__int64 a1, unsigned __int64 a2, void *a3, double a4)
{
    switch ((int)a2)
    {
        case 935: case 936: case 937: case 938: 
        return 0LL;
        case 860: case 861: case 862: 
        return 1LL;
        default: 
        return osub_3A564C(a1, a2, a3, a4);
    }
}

int64_t (*osub_4908A8)(__int64 a1, unsigned int *a2, __int64 *a3, __int64 a4, __int64 a5);
int64_t __fastcall hsub_4908A8(__int64 a1, unsigned int *a2, __int64 *a3, __int64 a4, __int64 a5) {
    int64_t result = osub_4908A8(a1, a2, a3, a4, a5);
    if (result == -3 || result == -4) {
        if (a5 != 0) {
            *(__int64 *)(a5 + 48) = 0; 
            *(_DWORD *)(a5 + 16) = 0;  
        }
        return 0; 
    }
    return result;
}

__int64 __fastcall (*osub_338680)(__int64 a1, __int64 a2, __int64 a3);
__int64 __fastcall hsub_338680(__int64 a1, __int64 a2, __int64 a3) {
    if (osub_338680) { osub_338680(a1, a2, a3); }
    return 0;
}
  
R2F(int64_t, anogs_4DFB40, (int32_t *a1, void *a2, uint64_t a3, size_t *a4, char a5)) 
{
    return 0LL;
}

R2F(int64_t, anogs_227050, (int64_t result)) 
{
    if (result) {
        *reinterpret_cast<uint64_t *>(result + 24) = 1;
    }
    return result;
}
//===========================================================================
void* main_r2f(void*)
{
    while (!isLibraryLoaded(oxorany("libUE4.so"))) sleep(1);
    while (!isLibraryLoaded(oxorany("libanogs.so"))) sleep(1);

//============================================================================
//PATCH_LIB("libanogs.so","0x51FB10","00 00 80 D2 C0 03 5F D6"); // CRASH GL
HOOK_LIB_NO_ORIG("libanogs.so","0x51FA80", gettaimeofday_r2f); // Crash Fix
//HOOK_LIB("libanogs.so", "0x2328F0", hsub_2328F0, osub_2328F0); // Case 16
HOOK_LIB("libanogs.so", "0x228168", hsub_228168, osub_228168); // Case 35 ✓✓
HOOK_LIB("libanogs.so", "0x228560", hsub_228560, osub_228560); // Case 37 ✓✓
PATCH_LIB("libanogs.so","0x3A8DA8","00 00 80 D2 C0 03 5F D6"); // OFFLINE
PATCH_LIB("libanogs.so","0x3E850C","00 00 80 D2 C0 03 5F D6"); // OFFLINE
HOOK_LIB("libanogs.so", "0x4908A8", hsub_4908A8, osub_4908A8); // OFFLINE Fix ✓

PATCH_LIB("libanogs.so","0x371418","0000 80 D2 C0 03 5F D6");  // 1 Day Fix ✓
HOOK_LIB("libanogs.so", "0x37FD78", hsub_37FD78, osub_37FD78); // 1 Day Fix ✓
HOOK_LIB("libanogs.so", "0x330494", hsub_330494, osub_330494); // 1 Day Fix ✓
HOOK_LIB("libanogs.so", "0x379220", hsub_379220, osub_379220); // 1 Day Fix ✓
HOOK_LIB("libanogs.so", "0x37966C", hsub_37966C, osub_37966C); // 1 Day Fix ✓
HOOK_LIB("libanogs.so", "0x37F7F4", hsub_37F7F4, osub_37F7F4); // 1 Day Fix ✓

HOOK_LIB_NO_ORIG("libanogs.so","0x49A624", r2fsunilyt_rs_vip); // 1 Day Fix ✓
HOOK_LIB_NO_ORIG("libanogs.so","0x49A628", r2fsunilyt_rs_vip); // 1 Day Fix ✓
HOOK_LIB_NO_ORIG("libanogs.so","0x4CAB6C", r2fsunilyt_rs_vip); // 1 Day Fix ✓

PATCH_LIB("libanogs.so" ,"0x39F56C", "00 00 80 D2 C0 03 5F D6"); // 1 Day Fix
PATCH_LIB("libanogs.so", "0x1FC168", "00 00 80 D2 C0 03 5F D6"); // 1 Day Fix
PATCH_LIB("libanogs.so", "0x2001FC", "00 00 80 D2 C0 03 5F D6"); // 1 Day Fix
PATCH_LIB("libanogs.so", "0x202150", "00 00 80 D2 C0 03 5F D6"); // 1 Day Fix

PATCH_LIB("libanogs.so","0x24877C", "00 00 80 D2 C0 03 5F D6"); //1 DAY
HOOK_LIB("libanogs.so","0x4DFB40",hanogs_4DFB40,oanogs_4DFB40); //1 DAY
HOOK_LIB("libanogs.so","0x227050",hanogs_227050,oanogs_227050); //1 DAY
PATCH_LIB("libanogs.so", "0x318B88","00 00 80 D2 C0 03 5F D6"); //1 Day Fix ✓

PATCH_LIB("libanogs.so","0x313810", "00 00 80 D2 C0 03 5F D6"); // OFFLINE 
HOOK_LIB("libanogs.so", "0x3A564C",  hsub_3A564C, osub_3A564C); // VTABLE CHECK

MemoryPatch::createWithHex("libanogs.so", 0x4FF684, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x4EDC50, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x4ED958, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x3DF500, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x2EF3A0, "00 00 80 D2 C0 03 5F D6").Modify();

MemoryPatch::createWithHex("libanogs.so", 0x4E6300, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x4E6E20, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x4E7790, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x4E7D68, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x4F7878, "00 00 80 D2 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so", 0x5201E0, "00 00 80 D2 C0 03 5F D6").Modify();
// ======================= Bypass END ========================================

return NULL;
}

// ================= ENTRY =================
__attribute__((constructor))
void lib_main()
{
    pthread_t ptid;
    pthread_create(&ptid, nullptr, main_r2f, nullptr);
}
