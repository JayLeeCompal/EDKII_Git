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
#include <Library/ShellCEntryLib.h>

#define INVALID_HANDLE  (UINT16) (-1)
#define DMI_INVALID_HANDLE  0x83
#define DMI_SUCCESS 0x00

SMBIOS_TABLE_ENTRY_POINT *mSmbiosTable;
SMBIOS_STRUCTURE_POINTER mSmbiosStruct;
CHAR16 *ptr;
CHAR8  *str;

CHAR8*
LibGetSmbiosString
( 
	SMBIOS_STRUCTURE_POINTER *Smbios,
  UINT16 StringNumber
);

EFI_STATUS
LibGetSmbiosStructure
(
	UINT16 *Handle,
  UINT8  **Buffer,
  UINT16 *Length
);

CHAR16 *
ASCII_to_UCS2(const char *s, UINTN len);


VOID
EFIAPI
PrintSmbiosEntryInfo(IN SMBIOS_TABLE_ENTRY_POINT  *Ptr);

VOID
EFIAPI
PrintSmbiosType0(
  IN SMBIOS_TABLE_TYPE0 *Type0,
  IN SMBIOS_STRUCTURE_POINTER SmbiosStruct
             );

VOID
EFIAPI
PrintSmbiosType1(
  IN SMBIOS_TABLE_TYPE1 *Type1,
  IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct);

VOID
EFIAPI
PrintSmbiosType2(
  IN SMBIOS_TABLE_TYPE2 *Type2,
  IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct);

VOID
EFIAPI
PrintSmbiosType3(
  IN SMBIOS_TABLE_TYPE3 *Type3,
  IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct);

VOID
EFIAPI
PrintSmbiosType17(
  IN SMBIOS_TABLE_TYPE17 *Type17,
  IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct);

VOID
EFIAPI
PrintSmbiosType22(
  IN SMBIOS_TABLE_TYPE22 *Type22,
  IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct);

#endif


