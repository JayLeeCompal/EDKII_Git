#include "MSR.h"

EFI_STATUS
EFIAPI
MSR_main (

  IN UINTN Argc,
  IN CHAR16 **Argv
)
{ 
  UINT16 addr;
  //If Parameters too few or too more print string
  if(Argc!=2){
    Print(L"Parameters too few or too more\n");
  }
  
  else{
    addr=(UINT16)StrHexToUintn(Argv[1]); //String transform to hex  
    Read_MSR(addr);//wrtie value to ECX,read data in EAX[31:0] or EDX[63:32]
    Print(L"\n");  
    }
         
         
  
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
Main (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_SHELL_PARAMETERS_PROTOCOL *gEfiShellParametersProtocol;

	
    UINTN			Argc;
	CHAR16			**Argv;
    EFI_STATUS      Status;
    EFI_GUID  mEfiShellParametersProtocolGuid = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;

	gEfiShellParametersProtocol = NULL;

	if (gEfiShellParametersProtocol != NULL){
		Print (L"gEfiShellParametersProtocol is initialized\n");
        Argc = gEfiShellParametersProtocol->Argc;
        Argv = gEfiShellParametersProtocol->Argv;

	}else {
        // check out input parameters from command line using UEFI Shell 2.0
        Print(L"       Read_MSR_EAX_&_EDX       \n");
        Print(L"____________________________________\n");
		Status = gBS->OpenProtocol(ImageHandle,
                             &mEfiShellParametersProtocolGuid,
                             (VOID **)&gEfiShellParametersProtocol,
                             ImageHandle,
                             NULL,
                             EFI_OPEN_PROTOCOL_GET_PROTOCOL
                            ); 
		if (EFI_ERROR(Status)) {
		      Print(L"\nSorry, Getting Shell params did NOT work or in the EFI Shell 1.0: \n");
			  return EFI_UNSUPPORTED;
		}else{
		    Argc = gEfiShellParametersProtocol->Argc;
			Argv = gEfiShellParametersProtocol->Argv;
		}
	
	}
    //
    // use shell 2.0 interface
    //
    MSR_main( Argc, Argv);
   
	return EFI_SUCCESS;
}



