#include "EC_cmd_62_66_RtcWake.h"
#define EC_CMD_SYSTEM_NOTIFICATION_RTC_WAKE_ENABLE       0xBD
#define EC_CMD_SYSTEM_NOTIFICATION_RTC_WAKE_DISABLE      0xBE
#define EC_CMD_SYSTEM_NOTIFICATION                       0x59
#define EC_DAT_METHOD_ACPI                               0x62
#define EC_CMD_METHOD_ACPI                               0x66

EFI_STATUS
EFIAPI
EC_main (

  IN UINTN Argc,
  IN CHAR16 **Argv
)
{
  UINTN num;
  
  //if parameters too large or too small print 
  if(Argc!=2){
    Print(L"Please one parameter:\n");
    Print(L"'0'=RTC Wake Disable,'1'=RTC Wake Enable\n");
  }
  else
    {
    num=StrDecimalToUintn(Argv[1]);
    //Wait EC read and Check IBF is empty or not
    while(Check_IBF(EC_CMD_METHOD_ACPI) != 0x0);
    //from 0x66 command port to send 0x59 command
    IoWrite8(EC_CMD_METHOD_ACPI,EC_CMD_SYSTEM_NOTIFICATION);
    //if num=0 is disable
    //   num=1 is enable
    //   num neither 1 and 0 display error message
    switch(num)
      {
        case 0:
          if(Check_IBF(EC_CMD_METHOD_ACPI) == 0x0)
            {
              IoWrite8(EC_DAT_METHOD_ACPI,EC_CMD_SYSTEM_NOTIFICATION_RTC_WAKE_DISABLE);
              Print(L"RTC_Wake Disable success\n");
            }
          break;
          
        case 1:
          if(Check_IBF(EC_CMD_METHOD_ACPI) == 0x0)
            {
              IoWrite8(EC_DAT_METHOD_ACPI,EC_CMD_SYSTEM_NOTIFICATION_RTC_WAKE_ENABLE);
              Print(L"RTC_Wake Enable success\n");
            }
          break;
          
        default:
          Print(L"Error Parameter\n");
          break;
      }
    }
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
  Print(L" ");
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
	    return EFI_UNSUPPORTED;
	  }
  else
    {
		  Argc = gEfiShellParametersProtocol->Argc; // @ Argc : Number of Parameter
			Argv = gEfiShellParametersProtocol->Argv; // @ Argv : Value of Parameter
		}
    //
    // use shell 2.0 interface
    //
    EC_main( Argc, Argv);
    //Read_MSR(0x17);
	return EFI_SUCCESS;
}


