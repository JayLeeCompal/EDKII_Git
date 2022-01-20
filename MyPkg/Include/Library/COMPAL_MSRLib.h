#ifndef __JAY_MSRLIB__
#define __JAY_MSRLIB__
#include <Base.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>


VOID
EFIAPI
Read_MSR(IN UINT16 Addr);

#endif


