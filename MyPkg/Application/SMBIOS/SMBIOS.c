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
  if ( Argc < 2 || Argc > 3 )
    {
     Usage();
    }
  else
    {
     if ( !StrCmp(Argv[1], L"-s") && Argc == 2)
      {
       PrintSmbiosEntryInfo(SmbiosTable);
       
      }

     else if ( !StrCmp(Argv[1], L"-t") && Argc==3 )
      {
       Type = StrDecimalToUintn(Argv[2]);
     
       switch(Type)
         {
          case 0:
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