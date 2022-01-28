#include "SMBIOS.h"
VOID
EFIAPI
Usage( void )
{
    Print(L"        Parameter Error\n");
    Print(L"        Parameter 1 : -t | Type   \n");
    Print(L"                      -s | Smbios Entry   \n\n");                              
    Print(L"        Parameter 2 : Type Number \n");
    Print(L"          Type Number = 0  | BIOS Information\n");
    Print(L"          Type Number = 1  | Sysyem Information\n");
    Print(L"          Type Number = 2  | Base Board Information\n");
    Print(L"          Type Number = 3  | System Enclosure or Chassis\n");
    Print(L"          Type Number = 17 | Memory Device\n");
    Print(L"          Type Number = 22 | Protable Battery\n");
}

EFI_STATUS
EFIAPI
Smbios_main (

  IN UINTN Argc,
  IN CHAR16 **Argv
)
{
  

  EFI_STATUS  Status = EFI_SUCCESS;
  EFI_GUID  SMBIOSTableGuid = SMBIOS_TABLE_GUID;
 
  EFI_SMBIOS_PROTOCOL           *Smbios;
  EFI_SMBIOS_HANDLE             SmbiosHandle;
  EFI_SMBIOS_TABLE_HEADER       *Header;

  SMBIOS_TABLE_TYPE0            *Type0;
  SMBIOS_TABLE_TYPE1            *Type1;
  SMBIOS_TABLE_TYPE2            *Type2;
  SMBIOS_TABLE_TYPE3            *Type3;
  SMBIOS_TABLE_TYPE17           *Type17;
  SMBIOS_TABLE_TYPE22           *Type22;
  UINTN                          Type;

  UINT16  	 Handle;
 	UINTN   	 Index;
 	UINT16  	 Length;
 	UINT8   	 *Buffer;
  
  
  //
  //Find SMBIOS Entry
  //
  Status = EfiGetSystemConfigurationTable(&SMBIOSTableGuid, (VOID**)&mSmbiosTable);
  (CompareMem (mSmbiosTable->AnchorString, "_SM_", 4) || Status)? Print(L"Can't find Smbios Table\n"):Print(L"Entry Status : %d\n",Status);
  //
  //Initialization  Struct
  //
  mSmbiosStruct.Raw  = (UINT8 *) (UINTN) (mSmbiosTable->TableAddress);
  
 
  if ( Argc < 2 || Argc > 3 )
    {
     Usage();
    }
  else
    {
     if ( !StrCmp(Argv[1], L"-s") && Argc == 2)
      {
       
       PrintSmbiosEntryInfo(mSmbiosTable);
       
      }
     else if ( !StrCmp(Argv[1], L"-t") && Argc==3 )
      {
       Status = gBS->LocateProtocol (
                  &gEfiSmbiosProtocolGuid,
                  NULL,
                  (VOID**)&Smbios
                  );
       (Status)? Print(L"Can't find Smbios Table\n"):Print(L"Type Status : %d\n",Status);

       SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
       Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Header, NULL);
       
       Type = StrDecimalToUintn(Argv[2]);
     
       switch(Type)
         {
          case 0:
            while (!EFI_ERROR(Status)) 
              {
                if(Header->Type == 0)
                  {
                    Type0 = (SMBIOS_TABLE_TYPE0*)Header;
                    Handle  = INVALID_HANDLE;
                    LibGetSmbiosStructure (&Handle, NULL, NULL);
                    for (Index = 0; Index < mSmbiosTable->NumberOfSmbiosStructures; Index++)
        	            {
          	           if ( (Handle == INVALID_HANDLE) ||\
                            (LibGetSmbiosStructure (&Handle, &Buffer, &Length) != DMI_SUCCESS)
                          ) {break;}
                       mSmbiosStruct.Raw = Buffer;
                       if (mSmbiosStruct.Hdr->Type == 0) 
                          {
                           Type0 = (SMBIOS_TABLE_TYPE0*)Header;
                           PrintSmbiosType0(Type0,mSmbiosStruct);
                          }
                       }
                  }
                Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Header, NULL);
              }
             break;

          case 1:
            while (!EFI_ERROR(Status)) 
              {
                if(Header->Type == 1)
                  {
                    Type1 = (SMBIOS_TABLE_TYPE1*)Header;
                    Handle  = INVALID_HANDLE;
                    LibGetSmbiosStructure (&Handle, NULL, NULL);
                    for (Index = 0; Index < mSmbiosTable->NumberOfSmbiosStructures; Index++)
        	            {
          	           if ( (Handle == INVALID_HANDLE) ||\
                            (LibGetSmbiosStructure (&Handle, &Buffer, &Length) != DMI_SUCCESS)
                          ) {break;}
                       mSmbiosStruct.Raw = Buffer;
                       if (mSmbiosStruct.Hdr->Type == 1) 
                          {
                           Type1 = (SMBIOS_TABLE_TYPE1*)Header;
                           PrintSmbiosType1(Type1,mSmbiosStruct);
                          }
                       }
                  }
                Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Header, NULL);
              }
             break;
          case 2:
            while (!EFI_ERROR(Status)) 
              {
                if(Header->Type == 2)
                  {
                    Type2 = (SMBIOS_TABLE_TYPE2*)Header;
                    Handle  = INVALID_HANDLE;
                    LibGetSmbiosStructure (&Handle, NULL, NULL);
                    for (Index = 0; Index < mSmbiosTable->NumberOfSmbiosStructures; Index++)
        	            {
          	           if ( (Handle == INVALID_HANDLE) ||\
                            (LibGetSmbiosStructure (&Handle, &Buffer, &Length) != DMI_SUCCESS)
                          ) {break;}
                       mSmbiosStruct.Raw = Buffer;
                       if (mSmbiosStruct.Hdr->Type == 2) 
                          {
                           Type2 = (SMBIOS_TABLE_TYPE2*)Header;
                           PrintSmbiosType2(Type2,mSmbiosStruct);
                          }
                       }
                  }
                Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Header, NULL);
              }
             break;

          case 3:
            while (!EFI_ERROR(Status)) 
              {
                if(Header->Type == 3)
                  {
                    Type3 = (SMBIOS_TABLE_TYPE3*)Header;
                    Handle  = INVALID_HANDLE;
                    LibGetSmbiosStructure (&Handle, NULL, NULL);
                    for (Index = 0; Index < mSmbiosTable->NumberOfSmbiosStructures; Index++)
        	            {
          	           if ( (Handle == INVALID_HANDLE) ||\
                            (LibGetSmbiosStructure (&Handle, &Buffer, &Length) != DMI_SUCCESS)
                          ) {break;}
                       mSmbiosStruct.Raw = Buffer;
                       if (mSmbiosStruct.Hdr->Type == 3) 
                          {
                           Type3 = (SMBIOS_TABLE_TYPE3*)Header;
                           PrintSmbiosType3(Type3,mSmbiosStruct);
                          }
                       }
                  }
                Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Header, NULL);
              }
             break;
          
          case 17:
            while (!EFI_ERROR(Status)) 
              {
                if(Header->Type == 17)
                  {
                    Type17 = (SMBIOS_TABLE_TYPE17*)Header;
                    Handle  = INVALID_HANDLE;
                    LibGetSmbiosStructure (&Handle, NULL, NULL);
                    for (Index = 0; Index < mSmbiosTable->NumberOfSmbiosStructures; Index++)
        	            {
          	           if ( (Handle == INVALID_HANDLE) ||\
                            (LibGetSmbiosStructure (&Handle, &Buffer, &Length) != DMI_SUCCESS)
                          ) {break;}
                       mSmbiosStruct.Raw = Buffer;
                       if (mSmbiosStruct.Hdr->Type == 17) 
                          {
                           Type17 = (SMBIOS_TABLE_TYPE17*)Header;
                           PrintSmbiosType17(Type17,mSmbiosStruct);
                          }
                       }
                  }
                Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Header, NULL);
              }
             break;

          case 22:
            while (!EFI_ERROR(Status)) 
              {
                if(Header->Type == 22)
                  {
                    Type22 = (SMBIOS_TABLE_TYPE22*)Header;
                    Handle  = INVALID_HANDLE;
                    LibGetSmbiosStructure (&Handle, NULL, NULL);
                    for (Index = 0; Index < mSmbiosTable->NumberOfSmbiosStructures; Index++)
        	            {
          	           if ( (Handle == INVALID_HANDLE) ||\
                            (LibGetSmbiosStructure (&Handle, &Buffer, &Length) != DMI_SUCCESS)
                          ) {break;}
                       mSmbiosStruct.Raw = Buffer;
                       if (mSmbiosStruct.Hdr->Type == 22) 
                          {
                           Type22 = (SMBIOS_TABLE_TYPE22*)Header;
                           PrintSmbiosType22(Type22,mSmbiosStruct);
                          }
                       }
                  }
                Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Header, NULL);
              }
             break;
         
          default:
            Usage();
            break;
        }
     }
     else
      {
       Usage();
      }
   }
  return Status; 
}


EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_SHELL_PARAMETERS_PROTOCOL *gEfiShellParametersProtocol;
	
  UINTN			    Argc;
	CHAR16			**Argv;
  EFI_STATUS  Status;
  EFI_GUID  mEfiShellParametersProtocolGuid = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;

	gEfiShellParametersProtocol = NULL;
  // check out input parameters from command line using UEFI Shell 2.0
  //Open Protocol about EfiShellParametersProtocol
	Status = gBS->OpenProtocol(ImageHandle,
                             &mEfiShellParametersProtocolGuid,
                             (VOID **)&gEfiShellParametersProtocol,
                             ImageHandle,
                             NULL,
                             EFI_OPEN_PROTOCOL_GET_PROTOCOL
                            ); 
	if (EFI_ERROR(Status))
    {
	    Print(L"\n Fail to Open Protocol\n");
	  }
  else
    {
		  Argc = gEfiShellParametersProtocol->Argc; // @ Argc : Number of Parameter
			Argv = gEfiShellParametersProtocol->Argv; // @ Argv : Value of Parameter
      Status=Smbios_main( Argc, Argv);
		}
    //
    // use shell 2.0 interface
    //
    
	return Status;
}