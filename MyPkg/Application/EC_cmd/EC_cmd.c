#include "EC_cmd.h"

#define EC_DAT_METHOD_8042                               0x60
#define EC_CMD_METHOD_8042                               0x64

#define EC_DAT_METHOD_ACPI                               0x62
#define EC_CMD_METHOD_ACPI                               0x66

VOID
EFIAPI
ErrorMessage(VOID)
{
    Print(L"Parameter Error\n");
    Print(L"\nPlease Enter 3 Parameters:\n");
    Print(L"Parameter 1 : Command Port --> 64 or 66\n");
    Print(L"Parameter 2 : Command Number\n");
    Print(L"Parameter 3 : Data\n");
}




EFI_STATUS
EFIAPI
EC_main (

  IN UINTN Argc,
  IN CHAR16 **Argv
)
{
  UINT16      TimeOut=5000;
  INTN        i,count=0;
  UINT8       CmdPort,DataPort,Cmd,Data,Value[10];
  EFI_STATUS  Status = EFI_SUCCESS;
  //if parameters too large or too small display error message
  //If overflow print error ,CHAE max value is a WORD(2 byte)
  //include NULL, (FF) value is 6 byte
  if ((Argc!=4) || ((StrSize(Argv[1])>6) || (StrSize(Argv[2])>6) || (StrSize(Argv[3])>6)))
    {
     ErrorMessage();
    }
  else
    {
     CmdPort  = StrToHex8(Argv[1]);
     Cmd      = StrToHex8(Argv[2]);
     Data     = StrToHex8(Argv[3]);
     if(CmdPort == EC_CMD_METHOD_8042)     //0x64 cmd port
       {
        DataPort = EC_DAT_METHOD_8042;     //0x60 data port
        Check_IBF(CmdPort);                //wait EC read amd check IBF is empty or not
        IoWrite8(CmdPort,Cmd);             //send command from command port

        Check_IBF(CmdPort);                //wait EC read amd check IBF is empty or not
        IoWrite8(DataPort,Data);           //send data from data port
        
        Check_OBF(CmdPort);                //wait EC read amd check OBF is empty or not
        while(TimeOut--){
          if((IoRead8(CmdPort)&BIT0) == 1) //when OBF=1 read data from Data Port
            {
             MicroSecondDelay(3000);
             Value[count] = IoRead8(DataPort);
             count++;
            }
          }
          Check_OBF(CmdPort);
          for(i=0;i<count;i++)
            {
             Print(L"Data %d :(0x%x) %c\n",i+1,Value[i],Value[i]);
            }
          
        Print(L"Time out\n");
        Print(L"Success\n");
        
       }
     else if (CmdPort == EC_CMD_METHOD_ACPI) //0x66 cmd port
       {
        DataPort = EC_DAT_METHOD_ACPI;    //0x62 data port
        Check_IBF(CmdPort);               //wait EC read amd check IBF is empty or not
        IoWrite8(CmdPort,Cmd);            //send command from Command Port

        Check_IBF(CmdPort);               //wait EC read amd check IBF is empty or not
        IoWrite8(DataPort,Data);          //send data from Data Port
 
        Check_OBF(CmdPort);                //wait EC read amd check OBF is empty or not
        while(TimeOut--){                  // Set TimeOut Mechanism
          if((IoRead8(CmdPort)&BIT0) == 1) //when OBF=1 read data from Data Port
            {
             MicroSecondDelay(3000);
             Value[count] = IoRead8(DataPort);
             count++;
            }
          }
          Check_OBF(CmdPort);
          for(i=0;i<count;i++)
            {
             Print(L"Data %d :(0x%x) %c\n",i+1,Value[i],Value[i]);
            }
          
        Print(L"Time out\n");
        Print(L"Success\n");
       }
     else
       {
        ErrorMessage();
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
      Status=EC_main( Argc, Argv);
		}
    //
    // use shell 2.0 interface
    //
    
	return Status;
}


