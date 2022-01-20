#include "PCIdump.h"

VOID
EFIAPI
Usage(void)
{
 Print(L"Please Enter Parameters\n\n");
 Print(L"1. Read/Write : -r|-R / -w|-W\n");
 Print(L"2. Bus        : 0x00 ~ 0xFF\n");
 Print(L"3. Device     : 0x00 ~ 0x1F\n");
 Print(L"4. Function   : 0x00 ~ 0x07\n");
 Print(L"5. Offset     : 0x00 ~ 0xFF\n");
 Print(L"6. Data       : 0x00 ~ 0xFF\n");

}


EFI_STATUS
EFIAPI
PCIdump (

    IN UINTN Argc,
    IN CHAR16 **Argv

    )
{

  UINT8 bus=0x0,dev=0x0,fun=0x0,offset=0x0;
  UINT32 check,data,Index;
  //Transform Argv into UINT16 of Hex and Assign a value to variable
  if ( (Argc>7) || (Argc<5) || (bus>0xff) || (dev>0x1f) || (fun>0x7) )
    {
     Usage();
    }

  else
    {
     bus    = (UINT8)StrHexToUintn(Argv[2]); 
     dev    = (UINT8)StrHexToUintn(Argv[3]);
     fun    = (UINT8)StrHexToUintn(Argv[4]);

     //
     //PCI read
     //
     if ( ( !StrCmp(Argv[1], L"-r") || !StrCmp(Argv[1], L"-R") ) && Argc==5)
       {
        //if parameter too large ,then print
        IoWrite32(PCI_Index_IO_ConfigPort,Get_Pci_CFG(bus,dev,fun,offset));
        check=IoRead32(PCI_Index_IO_DataPort);
        if (check!=0xfffffff&&check!=0x0)
         {
          Print(L"Bus[%02x],Dev[%02x],Fun[%02x]\nPFA=%08lx\n",bus,dev,fun,Get_Pci_CFG(bus,dev,fun,offset));
          Get_Pci_Register(bus,dev,fun,offset);
         }
       }
     
     //
     //PCI Write
     //
     else if 
       ( 
         ( Argc == 7 && (!StrCmp(Argv[1], L"-w") || !StrCmp(Argv[1], L"-W")) && ( StrLen(Argv[5])<=2 && StrLen(Argv[6])<=2) )
       )
       {
        Index  = (UINT32)StrHexToUintn(Argv[5]);
        data   = (UINT32)StrHexToUintn(Argv[6]);
        IoWrite32(PCI_Index_IO_ConfigPort,Get_Pci_CFG(bus,dev,fun,Index));
        IoWrite32(PCI_Index_IO_DataPort,data);
        //PciWrite32(Get_Pci_CFG(bus,dev,fun,Index),data);

        check=IoRead32(PCI_Index_IO_DataPort);
        if ( check != 0xfffffff && check != 0x0 )
         { 
          Print(L"Bus[%02x],Dev[%02x],Fun[%02x]\nPFA=%08lx\n",bus,dev,fun,Get_Pci_CFG(bus,dev,fun,offset));
          Get_Pci_Register(bus,dev,fun,offset);
         }
       }
     else
       {
         Usage();
       }
    }
 Print(L"\n");
 return EFI_SUCCESS;
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
      Status=PCIdump( Argc, Argv);
		}
    //
    // use shell 2.0 interface
    //
    
	return Status;
}

