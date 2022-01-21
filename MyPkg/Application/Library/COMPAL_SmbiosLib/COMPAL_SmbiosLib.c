#include <COMPAL_SmbiosLib.h>
CHAR16 *
ASCII_to_UCS2(const char *s, int len)
{
    CHAR16 *ret = NULL;
    int i;
 
    ret = AllocatePool(len*2 + 2);
    if (!ret)
        return NULL;
 
    for (i = 0; i < len; i++)
        ret[i] = s[i];
 
    return ret;
}

CHAR8*
LibGetSmbiosString (
  IN  SMBIOS_STRUCTURE_POINTER    *Smbios,
  IN  UINT16                      StringNumber
  )
{
  UINT16  Index;
  CHAR8   *String;

  //
  // Skip over formatted section
  //
  String = (CHAR8 *) (Smbios->Raw + Smbios->Hdr->Length);

  //
  // Look through unformated section
  //
  for (Index = 1; Index <= StringNumber; Index++) {
    if (StringNumber == Index) {
      return String;
    }
    //
    // Skip string
    //
    for (; *String != 0; String++);
    String++;

    if (*String == 0) {
      //
      // If double NULL then we are done.
      //  Return pointer to next structure in Smbios.
      //  if you pass in a -1 you will always get here
      //
      Smbios->Raw = (UINT8 *)++String;
      return NULL;
    }
  }

  return NULL;
}



VOID
EFIAPI
PrintSmbiosEntryInfo(IN SMBIOS_TABLE_ENTRY_POINT  *Ptr)
  {
     CHAR16                    Buffer[50];
     AsciiToUnicodeSize((CHAR8 *)&(Ptr->AnchorString), 4, Buffer, TRUE);
     Print(L"Anchor String           : %s\n",Buffer);
     Print(L"CheckSum                : 0x%x\n",Ptr->EntryPointStructureChecksum);
     Print(L"Length                  : 0x%x\n",Ptr->EntryPointLength);
     Print(L"Version                 : %x.%x\n",Ptr->MajorVersion,Ptr->MinorVersion);
     Print(L"Maximum Structure Size  : 0x%x\n",Ptr->MaxStructureSize);
     Print(L"Entry Point Revision    : 0x%x\n",Ptr->EntryPointRevision);
     Print(L"Formatted Area          : 0x%x\n",Ptr->FormattedArea);
     AsciiToUnicodeSize((CHAR8 *)&(Ptr->IntermediateAnchorString), 5, Buffer, TRUE);
     Print(L"Intermediate Anchor     : %s\n",Buffer);
     Print(L"Intermediate CheckSum   : 0x%x\n",Ptr->IntermediateChecksum);
     Print(L"Structure Table Length  : 0x%x\n",Ptr->TableLength);
     Print(L"Structure Table Address : 0x%x\n",Ptr->TableAddress);
     Print(L"Number of Structures    : %d\n",Ptr->NumberOfSmbiosStructures);
  }


VOID
EFIAPI
PrintSmbiosType0(IN SMBIOS_TABLE_TYPE0 *Type0)
  {
    CHAR16                    Buffer[50];
    //Print(L"Type                                 : %02x\n",Type0->Hdr.Type);
    //Print(L"Length                               : 0x%x\n",Type0->Hdr.Length);
    //Print(L"Handle                               : 0x%02x\n",Type0->Hdr.Handle);
    AsciiToUnicodeSize((CHAR8 *)&(Type0->Vendor), 12, Buffer, TRUE);
    Print(L"BIOS Vendor                          : %s\n",Buffer);
    Print(L"BIOS Vision                          : %d\n",Type0->BiosVersion);
    //Print(L"Start Addr BIOS Segment              : %x\n",Type0->BiosSegment);
    Print(L"BIOS Release Date                    : %s\n",Type0->BiosReleaseDate);
    //Print(L"BIOS Size                            : %x\n",Type0->BiosSize);
    //Print(L"BIOS Characteristics                 : %x\n",Type0->BiosCharacteristics);
    AsciiToUnicodeSize((CHAR8 *)&(Type0->BIOSCharacteristicsExtensionBytes), 2, Buffer, TRUE);
    Print(L"BIOS Characteristics Extension Bytes : %s\n",Buffer);
    //Print(L"System Bios Major Release            : %x\n",Type0->SystemBiosMajorRelease);
    //Print(L"System Bios Minor Release            : %x\n",Type0->SystemBiosMinorRelease);
    //Print(L"EC Firmware Major Release            : %x\n",Type0->EmbeddedControllerFirmwareMajorRelease);
    //Print(L"EC Firmware Minor Release            : %x\n",Type0->EmbeddedControllerFirmwareMinorRelease);
  }



VOID
EFIAPI
PrintSmbiosType1(IN SMBIOS_TABLE_TYPE1 *Type1)
  {
    Print(L"Type          : %02x\n",Type1->Hdr.Type);
    Print(L"Length        : 0x%x\n",Type1->Hdr.Length);
    Print(L"Handle        : 0x%02x\n",Type1->Hdr.Handle);
    /*Print(L"Manufacturer  : \n"Type1->Manufacturer);
    Print(L"Product Name  : \n"Type1->ProductName);
    Print(L"Version       : \n"Type1->Version);
    Print(L"Serial Number : \n"Type1->SerialNumber);
    Print(L"UUID          : \n"Type1->Uuid);
    Print(L"Wakeup Type   : \n"Type1->WakeUpType);
    Print(L"SKU Number    : \n"Type1->SKUNumber);
    Print(L"Family        : \n"Type1->Family);*/
  }
VOID
EFIAPI
PrintSmbiosType2(IN SMBIOS_TABLE_TYPE2 *Type2)
  {
    Print(L"Type          : %02x\n",Type2->Hdr.Type);
    Print(L"Length        : 0x%x\n",Type2->Hdr.Length);
    Print(L"Handle        : 0x%02x\n",Type2->Hdr.Handle);
    //Print(L"Manufacturer  : \n"Type2->Manufacturer);
    //Print(L"Product Name  : \n"Type2->ProductName)
    //Print(L"Version       : \n"Type2->Version);
    //Print(L"Serial Number : \n"Type2->SerialNumber);

  }
VOID
EFIAPI
PrintSmbiosType3(IN SMBIOS_TABLE_TYPE3 *Type3)
  {
    Print(L"Type          : %02x\n",Type3->Hdr.Type);
    Print(L"Length        : 0x%x\n",Type3->Hdr.Length);
    Print(L"Handle        : 0x%02x\n",Type3->Hdr.Handle);
    //Print(L"Manufacturer  : \n"Type3->Manufacturer);
    //Print(L"Product Name  : \n"Type3->ProductName)
    //Print(L"Version       : \n"Type3->Version);
    //Print(L"Serial Number : \n"Type3->SerialNumber);

  }
VOID
EFIAPI
PrintSmbiosType17(IN SMBIOS_TABLE_TYPE17 *Type17)
  {

  }
VOID
EFIAPI
PrintSmbiosType22(IN SMBIOS_TABLE_TYPE22 *Type22)
  {  

  }
