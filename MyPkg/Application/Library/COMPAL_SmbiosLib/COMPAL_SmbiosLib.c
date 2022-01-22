#include <COMPAL_SmbiosLib.h>
CHAR8*
LibGetSmbiosString
( 
	SMBIOS_STRUCTURE_POINTER *Smbios,
  UINT16 StringNumber
)
{
	UINT16  Index;
	CHAR8   *String;
  String = (CHAR8 *) (Smbios->Raw + Smbios->Hdr->Length);
	for (Index = 1; Index <= StringNumber; Index++) {
		if (StringNumber == Index) {
      return String;
    }
    for (; *String != 0; String++);
    String++;
    if (*String == 0) {
     	Smbios->Raw = (UINT8 *)++String;
     	return NULL;
    }
  }
	return NULL;
}


EFI_STATUS
LibGetSmbiosStructure
(
	UINT16 *Handle,
  UINT8  **Buffer,
  UINT16 *Length
)
{
	SMBIOS_STRUCTURE_POINTER  Smbios;
 	SMBIOS_STRUCTURE_POINTER  SmbiosEnd;
 	UINT8 *Raw;

 	if (*Handle == INVALID_HANDLE)
	{
  	*Handle =  mSmbiosStruct.Hdr->Handle;
    return DMI_INVALID_HANDLE;
	}

	if ((Buffer == NULL) || (Length == NULL))
	{
  	Print(L"Invalid handle\n");
    return DMI_INVALID_HANDLE;
	}

 *Length = 0;
 Smbios.Hdr = mSmbiosStruct.Hdr;
 SmbiosEnd.Raw = Smbios.Raw + mSmbiosTable->TableLength;
	while (Smbios.Raw < SmbiosEnd.Raw) {
  	if (Smbios.Hdr->Handle == *Handle) {
     	Raw = Smbios.Raw;
    	 LibGetSmbiosString (&Smbios, INVALID_HANDLE);
   	  *Length = (UINT16) (Smbios.Raw - Raw);
   	  *Buffer = Raw;
   	  if (Smbios.Raw < SmbiosEnd.Raw) {
      	 *Handle = Smbios.Hdr->Handle;
     	} else {
      	*Handle = INVALID_HANDLE;
     	}
    return DMI_SUCCESS;
	}
 	LibGetSmbiosString (&Smbios, INVALID_HANDLE);
}

	*Handle = INVALID_HANDLE;
 
	return DMI_INVALID_HANDLE;
}


CHAR16 *
ASCII_to_UCS2(const char *s, UINTN len)
{
    CHAR16 *ret = NULL;
    UINTN i;
 
    ret = AllocateZeroPool(len*2 + 2);
    if (!ret)
        return NULL;
 
    for (i = 0; i < len; i++)
        ret[i] = s[i];
 
    return ret;
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
     Print(L"Formatted Area          : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
                                      Ptr->FormattedArea[0],
                                      Ptr->FormattedArea[1],
                                      Ptr->FormattedArea[2],
                                      Ptr->FormattedArea[3],
                                      Ptr->FormattedArea[4]);
     AsciiToUnicodeSize((CHAR8 *)&(Ptr->IntermediateAnchorString), 5, Buffer, TRUE);
     Print(L"Intermediate Anchor     : %s\n",Buffer);
     Print(L"Intermediate CheckSum   : 0x%x\n",Ptr->IntermediateChecksum);
     Print(L"Structure Table Length  : 0x%x\n",Ptr->TableLength);
     Print(L"Structure Table Address : 0x%x\n",Ptr->TableAddress);
     Print(L"Number of Structures    : %d\n",Ptr->NumberOfSmbiosStructures);
     
  }


VOID
EFIAPI
PrintSmbiosType0(
  IN SMBIOS_TABLE_TYPE0 *Type0,
  IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct
             )
  {
    
    Print(L"Type                                 : %02d\n",Type0->Hdr.Type);
    Print(L"Length                               : 0x%x\n",Type0->Hdr.Length);
    //String 1 BIOS Vendor
    str = LibGetSmbiosString(&mSmbiosStruct,1);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"BIOS Vendor                          : %s\n",ptr);
    FreePool(ptr);
    //String 2 Bios Version
    str = LibGetSmbiosString(&mSmbiosStruct,2);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"BIOS Vision                          : %s\n",ptr);
    FreePool(ptr);
    
    Print(L"Start Addr BIOS Segment              : %x\n",Type0->BiosSegment);

    //String 3 BIOS Release Date
    str = LibGetSmbiosString(&mSmbiosStruct,3);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"BIOS Release Date                    : %s\n",ptr);
    FreePool(ptr);
    
    Print(L"BIOS Size                            : %x\n",Type0->BiosSize);
    Print(L"BIOS Characteristics                 : %x\n",Type0->BiosCharacteristics);
    Print(L"BIOS Characteristics Extension Bytes : %02x %02x\n",
           Type0->BIOSCharacteristicsExtensionBytes[0],
           Type0->BIOSCharacteristicsExtensionBytes[1]);
    Print(L"System Bios Major Release            : %x\n",Type0->SystemBiosMajorRelease);
    Print(L"System Bios Minor Release            : %x\n",Type0->SystemBiosMinorRelease);
    Print(L"EC Firmware Major Release            : %x\n",Type0->EmbeddedControllerFirmwareMajorRelease);
    Print(L"EC Firmware Minor Release            : %x\n",Type0->EmbeddedControllerFirmwareMinorRelease);
  }



VOID
EFIAPI
PrintSmbiosType1(IN SMBIOS_TABLE_TYPE1 *Type1,IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct)
  {
    Print(L"Type          : %02d\n",Type1->Hdr.Type);
    Print(L"Length        : 0x%x\n",Type1->Hdr.Length);
    Print(L"Handle        : 0x%02x\n",Type1->Hdr.Handle);

    str = LibGetSmbiosString(&mSmbiosStruct,1);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Manufacturer  : %s\n",ptr);//String 1
    FreePool(ptr);
    
    str = LibGetSmbiosString(&mSmbiosStruct,2);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Product Name  : %s\n",ptr);//String 2
    FreePool(ptr);
    
    str = LibGetSmbiosString(&mSmbiosStruct,3);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Version       : %s\n",ptr);//String 3
    FreePool(ptr);
    
    str = LibGetSmbiosString(&mSmbiosStruct,4);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Serial Number : %s\n",ptr);//String 4
    FreePool(ptr);

    Print(L"UUID          : %X-%X-%X-%x%x%x%x-%x%x%x%x\n",
                            Type1->Uuid.Data1,
                            Type1->Uuid.Data2,
                            Type1->Uuid.Data3,
                            Type1->Uuid.Data4[0],
                            Type1->Uuid.Data4[1],
                            Type1->Uuid.Data4[2],
                            Type1->Uuid.Data4[3],
                            Type1->Uuid.Data4[4],
                            Type1->Uuid.Data4[5],
                            Type1->Uuid.Data4[6],
                            Type1->Uuid.Data4[7],
                            Type1->Uuid.Data4[8]
                            );
    Print(L"Wakeup Type   : 0x%x\n",Type1->WakeUpType);

    str = LibGetSmbiosString(&mSmbiosStruct,5);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"SKU Number    : %s\n",ptr);//String 5
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,6);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Family        : %s\n",ptr);//String 6
    FreePool(ptr);
  }
VOID
EFIAPI
PrintSmbiosType2(IN SMBIOS_TABLE_TYPE2 *Type2,IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct)
  {
    Print(L"Type                : %02d\n",Type2->Hdr.Type);
    Print(L"Length              : 0x%x\n",Type2->Hdr.Length);
    Print(L"Handle              : 0x%02x\n",Type2->Hdr.Handle);

    str = LibGetSmbiosString(&mSmbiosStruct,1);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Manufacturer        : %s\n",ptr);//String 1
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,2);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Product Name        : %s\n",ptr);//String 2
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,3);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Version             : %s\n",ptr);//String 3
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,4);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Serial Number       : %s\n",ptr);//String 4
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,5);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"BIOS Asset Tag      : %s\n",ptr);//String 5
    FreePool(ptr);
    
    Print(L"Feature Flag        : %d\n",Type2->FeatureFlag);
    //Print(L"Bit0                : \n",Type2->LocationInChassis);
    //Print(L"Bit1                : \n",Type2->LocationInChassis);
    //Print(L"Bit2                : \n",Type2->LocationInChassis);
    //Print(L"Bit3                : \n",Type2->LocationInChassis);
    //Print(L"Bit4                : \n",Type2->LocationInChassis);
    //Print(L"BIOS Family         : \n",Type2->LocationInChassis);
    Print(L"Chassis Handle      : 0x%X\n",Type2->ChassisHandle);
    Print(L"Board Type          : 0x%X\n",Type2->BoardType);
    Print(L"Number of Contained : 0x%X\n",Type2->NumberOfContainedObjectHandles);    

  }
VOID
EFIAPI
PrintSmbiosType3(IN SMBIOS_TABLE_TYPE3 *Type3,IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct)
  {
    Print(L"Type                    : %02d\n",Type3->Hdr.Type);
    Print(L"Length                  : 0x%X\n",Type3->Hdr.Length);
    Print(L"Handle                  : 0x%02x\n",Type3->Hdr.Handle);

    str = LibGetSmbiosString(&mSmbiosStruct,1);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"BIOS Manufacturer       : %s\n",ptr);//String 1
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,2);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"BIOS Version            : %s\n",ptr);//String 2
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,3);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"BIOS Serial Number      : %s\n",ptr);//String 3
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,4);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"BIOS Asset Tag          : %s\n",ptr);//String 4
    FreePool(ptr);
    
    Print(L"Bootup State Flags      : 0x%X -safe\n",Type3->BootupState);
    Print(L"Power Supply State      : 0x%X -safe\n",Type3->PowerSupplyState);
    Print(L"Thermal State           : 0x%X -safe\n",Type3->ThermalState);
    Print(L"Security Status         : 0x%X -safe\n",Type3->SecurityStatus);
    Print(L"Oem Defined             : 0x%X\n",Type3->OemDefined);
    Print(L"Hight                   : 0x%X\n",Type3->Height);
    Print(L"Number of Power Cords   : 0x%X\n",Type3->NumberofPowerCords);
    Print(L"Contained Element Count : 0x%X\n",Type3->ContainedElementCount);
  }
VOID
EFIAPI
PrintSmbiosType17(IN SMBIOS_TABLE_TYPE17 *Type17,IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct)
  {
    Print(L"Type                     : %02d\n",Type17->Hdr.Type);
    Print(L"Length                   : 0x%x\n",Type17->Hdr.Length);
    Print(L"Handle                   : 0x%02x\n",Type17->Hdr.Handle);
    Print(L"Memmory Array Handle     : 0x%x\n",Type17->MemoryArrayHandle);
    Print(L"Error Information Handle : 0x%x\n",Type17->MemoryErrorInformationHandle);
    Print(L"Total Width              : %d (bits)\n",Type17->TotalWidth);
    Print(L"Data Width               : %d (bits)\n",Type17->DataWidth);
    Print(L"Size                     : %d (MB)\n",Type17->Size);
    Print(L"FormFactor               : 0x%x\n",Type17->FormFactor);
    Print(L"Memory Type              : 0x%x\n",Type17->MemoryType);
    Print(L"Speed                    : %x\n",Type17->Speed);

    str = LibGetSmbiosString(&mSmbiosStruct,1);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Device Locator           : %s\n",ptr);   //String 1
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,2);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Bank Locator             : %s\n",ptr);     //String 2
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,3);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Manufacturer             : %s\n",ptr);    //String 3
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,4);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Serial Number            : %s\n",ptr);    //String 4
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,5);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Asset Tag                : %s\n",ptr);        //String 5
    FreePool(ptr);
    
    Print(L"Maximum Voltage          : %x\n",Type17->MaximumVoltage);
    Print(L"Minimum Voltage          : %x\n",Type17->MinimumVoltage);
    Print(L"Configured Voltage       : %d (mV)\n",Type17->ConfiguredVoltage);

    str = LibGetSmbiosString(&mSmbiosStruct,6);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Part Number              : %x\n\n",ptr);
    FreePool(ptr);
  }
VOID
EFIAPI
PrintSmbiosType22(IN SMBIOS_TABLE_TYPE22 *Type22,IN SMBIOS_STRUCTURE_POINTER mSmbiosStruct)
  {  
  
    Print(L"Type                       : %02d\n",Type22->Hdr.Type);
    Print(L"Length                     : 0x%X\n",Type22->Hdr.Length);
    Print(L"Handle                     : 0x%02x\n",Type22->Hdr.Handle);

    str = LibGetSmbiosString(&mSmbiosStruct,1);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Location                   : %s\n",ptr);     //String 1
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,2);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Manufacturer               : %s\n",ptr);//String 2
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,3);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"ManufactureDate            : %s\n",ptr);//String 3
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,4);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Serial Number              : %s\n",ptr);//String 4
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,5);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"Device Name                : %s\n",ptr);//String 5
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,6);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"SBDS Version Number        : %s\n",ptr);//String 6
    FreePool(ptr);

    str = LibGetSmbiosString(&mSmbiosStruct,7);
    ptr = ASCII_to_UCS2(str, StrLen((UINT16*)str));
    Print(L"SBDS Device Chemistry      : %s\n",ptr);//String 7
    FreePool(ptr);
    
    Print(L"Device Chemistry           : %d (Undefined)\n",Type22->DeviceChemistry);
    Print(L"Device Capacity            : %X\n",Type22->DeviceCapacity);
    Print(L"Design Voltage             : %X (mV)\n",Type22->DesignVoltage);
    Print(L"Maximum Err Battery Data   : %X\n",Type22->MaximumErrorInBatteryData);
    Print(L"SBDS Serial Number         : %X\n",Type22->SBDSSerialNumber);
    Print(L"SBDS ManufactureData       : %X\n",Type22->SBDSManufactureDate);
    Print(L"Design Capacity Multiplier : %X\n",Type22->DesignCapacityMultiplier);
    Print(L"OEM Specific               : %x\n",Type22->OEMSpecific);
    
  }
