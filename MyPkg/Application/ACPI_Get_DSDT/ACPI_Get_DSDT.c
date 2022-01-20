#include "ACPI_Get_DSDT.h"

VOID
EFIAPI
Usage( void )
{
    Print(L"       ShowFACP  -v | --verbose\n");
    Print(L"       ShowFACP  -d | --dump\n");
    Print(L"       ShowXSDT  -x | --xsdt\n");
}

EFI_STATUS
EFIAPI
Acpi_main (

  IN UINTN Argc,
  IN CHAR16 **Argv
)
{
  EFI_STATUS Status=EFI_SUCCESS;
  EFI_GUID  ACPITableGuid = EFI_ACPI_TABLE_GUID;
  EFI_ACPI_5_0_ROOT_SYSTEM_DESCRIPTION_POINTER *Rsdp;
  EFI_ACPI_DESCRIPTION_HEADER                  *Xsdt;
  EFI_ACPI_5_0_FIXED_ACPI_DESCRIPTION_TABLE    *Fadt;
  CHAR16          Buffer[50];
  UINT8           *Ptr;
  UINTN           Index,count;
  UINT64          *Entry;
  //
  //1. Find RSDP
  //
  Status = EfiGetSystemConfigurationTable(&ACPITableGuid, (VOID**)&Rsdp);
  EFI_ERROR(Status)? Print(L"Can't find Acpi Table\n"):Print(L"Status : %d\n",Status);
  

  //
  //2. Find XSDT
  //
  Xsdt = (EFI_ACPI_DESCRIPTION_HEADER*)Rsdp->XsdtAddress;
  Ptr = (UINT8*)Xsdt;

  //
  //3.Find FACP Entry
  //
  Entry = (UINT64*) & Xsdt[1];
  Ptr=(UINT8*)(*Entry);
  Fadt=(EFI_ACPI_5_0_FIXED_ACPI_DESCRIPTION_TABLE*)Ptr;



  if (Argc!=2)
   {
     Usage();
   }
  else
   { 
     //
     //Show some FACP information 
     //
     if ( !StrCmp(Argv[1], L"--verbose") || !StrCmp(Argv[1], L"-v") ) 
       {
        Print(L"RSDP address :0x%X\n", Rsdp);
        Print(L"XSDT address :0x%X\n", Rsdp->XsdtAddress);
        if (SIGNATURE_32('F', 'A', 'C', 'P'))
         {
          Print(L"\nACPI Standard Header\n");
          Print(L"FACP Address    : 0x%08x\n",*Entry);
          PrintFadtHeader(Fadt);
          Print(L"Firmware Control: 0x%X - FACS\n",Fadt->FirmwareCtrl);
          Print(L"Dsdt Address    : 0x%X - DSDT\n",Fadt->Dsdt); 
         }
       }
     
     //
     //Dump FADT Table
     //
     else if ( !StrCmp(Argv[1], L"--dump") || !StrCmp(Argv[1], L"-d") ) 
       {
        Print(L"RSDP address :0x%X\n", Rsdp); 
        Print(L"XSDT address :0x%X\n", Rsdp->XsdtAddress);
        
        Print(L"   ");
        PrintAcpiTable((UINT8*)Fadt,(UINT16)Fadt->Header.Length);
       }
     
     //
     //Dump XSDT all Entry Point
     //
     else if ( !StrCmp(Argv[1], L"--xsdt") || !StrCmp(Argv[1], L"-x") )
       {
         count=((Xsdt->Length) - sizeof(EFI_ACPI_DESCRIPTION_HEADER))/8;
         Print(L"Entry    Signature       Address\n");
         for(Index = 0; Index < count; Entry++,Index++)
           {
            Ptr=(UINT8*)(*Entry);       
            Fadt=(EFI_ACPI_5_0_FIXED_ACPI_DESCRIPTION_TABLE*)Ptr;
            //display Entry number   Signature   Address
            AsciiToUnicodeSize((CHAR8 *)&(Fadt->Header.Signature), 4, Buffer, TRUE);
            Print(L" %02d        %s      0x%X\n",Index,Buffer,*Entry);
           }
       }
     //
     //User Information
     //
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
      Status=Acpi_main( Argc, Argv);
		}
    //
    // use shell 2.0 interface
    //
    
	return Status;
}