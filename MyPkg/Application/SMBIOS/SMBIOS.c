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
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 99a4263664a676da44b0baab49bc40b83ac8f715
  

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
  
 
<<<<<<< HEAD
=======
=======
  EFI_STATUS Status=EFI_SUCCESS;
  EFI_GUID  SMBIOSTableGuid = SMBIOS_TABLE_GUID;
  SMBIOS_TABLE_ENTRY_POINT  *SmbiosTable=NULL;
  SMBIOS_STRUCTURE_POINTER  *SmbiosStruct=NULL;
  UINTN                      Type;
  CHAR8                     *str;
  CHAR16                    *ptr;
  
  
  //
  //1. Find SMBIOS Entry
  //
  Status = EfiGetSystemConfigurationTable(&SMBIOSTableGuid, (VOID**)&SmbiosTable);
  (CompareMem (SmbiosTable->AnchorString, "_SM_", 4) || Status)? Print(L"Can't find Smbios Table\n"):Print(L"Status : %d\n",Status);

  SmbiosStruct->Raw = (UINT8*)(UINTN)SmbiosTable->TableAddress;
  //
  // Display Smbios Entry Ponint Information
  //
>>>>>>> f11388ec90c614a77d9a70a1a35b77ba73734886
>>>>>>> 99a4263664a676da44b0baab49bc40b83ac8f715
  if ( Argc < 2 || Argc > 3 )
    {
     Usage();
    }
  else
    {
     if ( !StrCmp(Argv[1], L"-s") && Argc == 2)
      {
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 99a4263664a676da44b0baab49bc40b83ac8f715
       
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
       
<<<<<<< HEAD
=======
=======
       PrintSmbiosEntryInfo(SmbiosTable);
       
      }

     else if ( !StrCmp(Argv[1], L"-t") && Argc==3 )
      {
>>>>>>> f11388ec90c614a77d9a70a1a35b77ba73734886
>>>>>>> 99a4263664a676da44b0baab49bc40b83ac8f715
       Type = StrDecimalToUintn(Argv[2]);
     
       switch(Type)
         {
          case 0:
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 99a4263664a676da44b0baab49bc40b83ac8f715
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
<<<<<<< HEAD
=======
=======
            //PrintSmbiosType0(SmbiosStruct->Type0);
            str=LibGetSmbiosString(&SmbiosStruct,1);
            ptr=ASCII_to_UCS2(str,StrLen(str));
            Print(L"%s",ptr);
            FreePool(ptr);
            break;

          case 1:
            PrintSmbiosType1(SmbiosStruct->Type1);
            break;

          case 2:
            PrintSmbiosType2(SmbiosStruct->Type2);
            break;

          case 3:
            PrintSmbiosType3(SmbiosStruct->Type3);
            break;

          case 17:
            PrintSmbiosType17(SmbiosStruct->Type17);
            break;

          case 22:
            PrintSmbiosType22(SmbiosStruct->Type22);
            break;
>>>>>>> f11388ec90c614a77d9a70a1a35b77ba73734886
>>>>>>> 99a4263664a676da44b0baab49bc40b83ac8f715
         
          default:
            Usage();
            break;
<<<<<<< HEAD
        }
     }
=======
<<<<<<< HEAD
        }
     }
=======
         }    
       }
>>>>>>> f11388ec90c614a77d9a70a1a35b77ba73734886
>>>>>>> 99a4263664a676da44b0baab49bc40b83ac8f715
     else
      {
       Usage();
      }
<<<<<<< HEAD
   }
=======
<<<<<<< HEAD
   }
=======
    } 
>>>>>>> f11388ec90c614a77d9a70a1a35b77ba73734886
>>>>>>> 99a4263664a676da44b0baab49bc40b83ac8f715
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