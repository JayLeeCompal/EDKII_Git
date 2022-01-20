#ifndef __JAY_SmbiosLIB__
#define __JAY_SmbiosLIB__
#include <Base.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <COMPAL_StringLib.h>
#include <IndustryStandard/SmBios.h>
CHAR16*
ASCII_to_UCS2(const char *s, int len);

CHAR8*
LibGetSmbiosString (
  IN  SMBIOS_STRUCTURE_POINTER    *Smbios,
  IN  UINT16                      StringNumber
  );


VOID
EFIAPI
PrintSmbiosEntryInfo(IN SMBIOS_TABLE_ENTRY_POINT  *Ptr);

VOID
EFIAPI
PrintSmbiosType0(IN SMBIOS_TABLE_TYPE0 *Type0);

VOID
EFIAPI
PrintSmbiosType1(IN SMBIOS_TABLE_TYPE1 *Type1);

VOID
EFIAPI
PrintSmbiosType2(IN SMBIOS_TABLE_TYPE2 *Type2);

VOID
EFIAPI
PrintSmbiosType3(IN SMBIOS_TABLE_TYPE3 *Type3);

VOID
EFIAPI
PrintSmbiosType17(IN SMBIOS_TABLE_TYPE17 *Type17);

VOID
EFIAPI
PrintSmbiosType22(IN SMBIOS_TABLE_TYPE22 *Type22);

#endif


