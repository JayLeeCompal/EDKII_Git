#include <COMPAL_StringLib.h>

//
//Let character upper
//
CHAR16
EFIAPI
CharToUpper (
  IN      CHAR16                    Char
  )
{
  if (Char >= L'a' && Char <= L'z') {          //
    return (CHAR16) (Char - (L'a' - L'A'));    //a-z to A-Z
  }                                            //

  return Char;
}

//
//Char of Decimal 0 - 9
//
BOOLEAN
EFIAPI
DecimalDigitCharacter (
  IN      CHAR16                    Char
  )
{
  return (BOOLEAN) (Char >= L'0' && Char <= L'9');
}

//
//Check all of hex's character
//
BOOLEAN
EFIAPI
HexaDecimalDigitCharacter (
  IN      CHAR16                    Char
  )
{
                                                    //hex
  return (BOOLEAN) (DecimalDigitCharacter (Char) || // 0 - 9
    (Char >= L'A' && Char <= L'F') ||               // A - F 
    (Char >= L'a' && Char <= L'f'));                // a - f
}

UINTN
EFIAPI
HexCharToUintn (
  IN      CHAR16                    Char
  )
{
  if (DecimalDigitCharacter (Char)) {               // 0 - 9
    return (Char - L'0');
  }

  return (UINTN) (10 + CharToUpper (Char) - L'A'); // A - F
}




UINT8
EFIAPI
StrToHex8(
  IN CONST CHAR16 * String
)
{
  
  UINTN     Result=0;
  //
  //Check have string or not
  //
  if(StrSize (String) != 0)
    {
  
    //
    // Ignore the pad spaces (space or tab) 
    //
    while ((*String == L' ') || (*String == L'\t')) 
      {
      String++;
      }

    //
    // Ignore leading Zeros after the spaces
    //
    while (*String == L'0') 
      {
      String++;
      }

    if (CharToUpper (*String) == L'X') // Skip the 'X'
      {
      if (*(String - 1) != L'0') 
        {
        return 0;
        }
      
      String++;
      }
    while (HexaDecimalDigitCharacter (*String)) 
      {
      //Transfer next character
      Result = (Result << 4) + HexCharToUintn (*String);
      String++;
      }
    }

  return (UINT8)Result; // byte 0x0~0xFF
}


