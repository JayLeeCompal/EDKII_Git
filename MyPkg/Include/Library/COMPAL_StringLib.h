#ifndef __JAY_StringLIB__
#define __JAY_StringLIB__
#include <Base.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>

// char to hex of byte
CHAR16
EFIAPI
CharToUpper (IN  CHAR16     Char);
//
//Char of Decimal 0 - 9
//
BOOLEAN
EFIAPI
DecimalDigitCharacter (IN  CHAR16  Char);
//
//Check all of hex's character
//
BOOLEAN
EFIAPI
HexaDecimalDigitCharacter (IN CHAR16  Char);


UINT8
EFIAPI
StrToHex8(IN CONST CHAR16 * String);


#endif


