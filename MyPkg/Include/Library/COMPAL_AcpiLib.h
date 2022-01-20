#ifndef __JAY_AcpiLIB__
#define __JAY_AcpiLIB__
#include <Base.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>

//
//Display Table
//
VOID
EFIAPI
Print_Register_Table(IN UINT16 range,
                     IN UINT8 LineBreak);
//
//ASCII to size of Byte then pass to buffer
//
VOID
EFIAPI
AsciiToUnicodeSize(IN CHAR8 *String,
                   IN UINT8 length,
                   IN CHAR16 *UniString,
                   IN BOOLEAN Quote );
//
//Display Standard Header
//
VOID
EFIAPI
PrintFadtHeader( IN EFI_ACPI_5_0_FIXED_ACPI_DESCRIPTION_TABLE *Ptr );

//
//Display ACPI Table
//
VOID
EFIAPI
PrintAcpiTable( IN UINT8 *ptr,
                IN UINT16 Length );


#endif


