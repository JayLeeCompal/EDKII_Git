#include "EEPROM.h"
#define EC_DAT_METHOD_8042      0x60
#define EC_CMD_METHOD_8042      0x64
#define EEPROM_WRITE            0x4D
#define EEPROM_READ             0x4E
#define RANGE_MAX               0xFF

VOID
EFIAPI
ErrorMessage(VOID)
{
    Print(L"Parameter Error\n");
    Print(L"\nPlease Enter 3 Parameters:\n");
    Print(L"Parameter 1 : Write(-w/-W) or Read(-r/-R)\n");
    Print(L"Parameter 2 : Offset [FF:00]\n");
    Print(L"Parameter 3 : Data\n");
    
}


EFI_STATUS
EFIAPI
EC_main (

  IN UINTN Argc,
  IN CHAR16 **Argv
)
{
  INTN        i,count=0;
  CHAR16      Cmd;
  UINT8       Offset,Data=0,Value[10];
  UINT16      TimeOut=5000;
  EFI_STATUS  Status = EFI_SUCCESS;
  //if parameters too large or too small display error message
  //If overflow print error ,CHAE max value is a WORD(2 byte)
  //include NULL, (FF) value is 6 byte
  if ( Argc>4 || Argc<3 || ((StrSize(Argv[1])>6) || (StrSize(Argv[2])>6)))
    {
     ErrorMessage();
    }

  else
    {
     Cmd      = *Argv[1];
     Offset   = StrToHex8(Argv[2]);
     //Read mode
     if( Argc==3 && (!StrCmp(Argv[1], L"-r") || !StrCmp(Argv[1], L"-R")) )
      {
        Check_IBF(EC_CMD_METHOD_8042);                //wait EC read amd check IBF is empty or not
        IoWrite8(EC_CMD_METHOD_8042,EEPROM_READ);     //send command from command port

        Check_IBF(EC_CMD_METHOD_8042);                //wait EC read amd check IBF is empty or not
        IoWrite8(EC_DAT_METHOD_8042,Offset);           //send data from data port
        
      }
     //Write mode
     else if (
              Argc == 4 &&( !StrCmp(Argv[1], L"-w") || !StrCmp(Argv[1], L"-W") ) && (StrLen(Argv[3])<=2)
             )
      {
        Data     = StrToHex8(Argv[3]);
        Check_IBF(EC_CMD_METHOD_8042);                //wait EC read amd check IBF is empty or not
        IoWrite8(EC_CMD_METHOD_8042,EEPROM_WRITE);    //send command from command port

        Check_IBF(EC_CMD_METHOD_8042);                //wait EC read amd check IBF is empty or not
        IoWrite8(EC_DAT_METHOD_8042,Offset);           //send data from data port

        Check_IBF(EC_CMD_METHOD_8042);                //wait EC read amd check IBF is empty or not
        IoWrite8(EC_DAT_METHOD_8042,Data);           //send data from data port
      }
     else
      {
       ErrorMessage();
      }
     Check_OBF(EC_CMD_METHOD_8042);                //wait EC read amd check OBF is empty or not
     while(TimeOut--)
      {
       if((IoRead8(EC_CMD_METHOD_8042)&BIT0) == 1) //when OBF=1 read data from Data Port
         {
          MicroSecondDelay(3000);
          Value[count] = IoRead8(EC_DAT_METHOD_8042);//data value save to buffer
          count++;
         }
      }
     Check_OBF(EC_CMD_METHOD_8042);
     //Diaplay return data from value buffer
     for(i=0;i<count;i++)
       {
        Print(L"Data %d :(0x%x) %c\n",i+1,Value[i],Value[i]);
       }     
        Print(L"Time out\n");
        Print(L"Success\n");
        
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


