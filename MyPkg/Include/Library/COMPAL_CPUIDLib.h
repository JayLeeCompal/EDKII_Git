#ifndef __JAY_CPUIDLIB__
#define __JAY_CPUIDLIB__


#include <Base.h>
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>

#define MICROCODE_REV             0x17
#define NUM_CORE                  0x35
#define TJMAX                     0x1A2
#define PLATFORM_ID               0x17
#define PROCCESSOR_FLAG           0x17

#define CPUID_SIGNATURE           0x0
#define CPUID_VERSION_INFO        0x1
#define CPUID_EXTENDED_CPU_SIG    0x80000001
#define CPUID_BRAND_STRING1       0x80000002
#define CPUID_BRAND_STRING2       0x80000003
#define CPUID_BRAND_STRING3       0x80000004



#endif


