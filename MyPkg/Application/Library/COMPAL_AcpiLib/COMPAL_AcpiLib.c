#include <COMPAL_AcpiLib.h>

//@range      Number of data
//@LineBreak  Line of table

VOID
EFIAPI
Print_Register_Table(IN UINT16 range,IN UINT8 LineBreak)
{
  UINTN i;
  if(range==0)
    {
    for(i=0;i<LineBreak;i++)   //print row of table
      {
       Print(L"0%x ",i);
      }
    
    Print(L"\n");              //print col of table
    }
 if(range%LineBreak==0)
   {
    Print(L"\n%03x  ",range);
   }
}

//
//@*String        ASCII of value in Table
//@length         Character length
//@*UniString     Buffer
//@Quote          Bolean value   TRUE or FALSE
//
VOID
EFIAPI
AsciiToUnicodeSize( CHAR8 *String,
                    UINT8 length,
                    CHAR16 *UniString,
                    BOOLEAN Quote )
{
    int len = length;
 
    if (Quote)
        *(UniString++) = L'"';
    while (*String != '\0' && len > 0) {
        *(UniString++) = (CHAR16) *(String++);
        len--;
    }
    if (Quote)
        *(UniString++) = L'"';
    *UniString = '\0';
}


//
// @*Ptr Pointer to table address
//

VOID
EFIAPI
PrintFadtHeader( 
  IN EFI_ACPI_5_0_FIXED_ACPI_DESCRIPTION_TABLE *Ptr)
{
    CHAR16 Buffer[50];
    AsciiToUnicodeSize((CHAR8 *)&(Ptr->Header.Signature), 4, Buffer, TRUE);
    Print(L"Signature       : %s \n",Buffer);
    Print(L"Length          : 0x%X (%d)\n",Ptr->Header.Length,Ptr->Header.Length);
    Print(L"Revision        : 0x%X (%d)\n",Ptr->Header.Revision,Ptr->Header.Revision);
    Print(L"CheckSum        : 0x%X (%d)\n",Ptr->Header.Checksum,Ptr->Header.Checksum);

    AsciiToUnicodeSize((CHAR8 *)&(Ptr->Header.OemId), 6, Buffer, TRUE);
    Print(L"OEM ID          : %s (0x%X)\n",Buffer,Ptr->Header.OemId);

    AsciiToUnicodeSize((CHAR8 *)&(Ptr->Header.OemTableId), 8, Buffer, TRUE);
    Print(L"OEM Table ID    : %s (0x%X)\n",Buffer,Ptr->Header.OemTableId);
    
    Print(L"OEM Revision    : 0x%X (%d)\n",Ptr->Header.OemRevision,Ptr->Header.OemRevision);

    AsciiToUnicodeSize((CHAR8 *)&(Ptr->Header.CreatorId), 4, Buffer, TRUE);
    Print(L"Creator ID      : %s (0x%X)\n",Buffer,Ptr->Header.CreatorId);

    Print(L"Creator Revision: 0x%X\n",Ptr->Header.CreatorRevision,Ptr->Header.CreatorRevision);
     
}


//
// @*Ptr   Pointer to Table adress
// @Length Table length
//
VOID
EFIAPI
PrintAcpiTable( 
  IN         UINT8 *ptr,
  IN         UINT16 Length )
{
    UINT16 i = 0;
 
    Print(L"  ");
    for (i = 0; i < Length; i++ ) 
      {
        Print_Register_Table(i,16);
        Print(L"%02x ", 0xff & *ptr++);
      }
    Print(L"\n");
}
 