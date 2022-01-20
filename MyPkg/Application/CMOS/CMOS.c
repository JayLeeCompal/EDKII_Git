#include "CMOS.h"

VOID
EFIAPI
Usage(void)
{
    Print(L"Please Enter two parameter:\n");
    Print(L"1. Read / Write : -r|-R / -w|-W \n");
    Print(L"2. Bank         : 0 / 1\n");
    Print(L"3. Offset       : 0x00~0xFF\n");
    Print(L"4. Value        : 0x00~0xFF\n");
    Print(L"123\n");

}





EFI_STATUS
EFIAPI
cmos_main (

  IN UINTN Argc,
  IN CHAR16 **Argv
)
{
  UINTN Bank;
  UINT8 Index,Value=0x0,Offset=0x0;
 
  
  //if parameters too large or too small print 
  if ( (Argc>5) || (Argc<3) || (Offset>0xFF) || (Value>0xFF) )
    {
     Usage();
    }
  else
   {
     Bank = StrDecimalToUintn(Argv[2]);
     Print(L"CMOS configration space\n");
     if ( 
         ( !StrCmp(Argv[1], L"-r") || !StrCmp(Argv[1], L"-R") ) &&\
         (Argc==3) \
        )
        {
         switch (Bank)
           {
            case 0:
              Print(L"Bank 0\n");
              Print(L"    ");
              for (Index=0;Index<=0xff;Index++)
                {
                 Print_Register_Table(Index,16);//Print table of 256bits
                 Read_CMOS_IO(Index);
                 if (Index==0xff) break;
                }
              Print(L"\n");
              break;

            case 1:
              Print(L"Bank 1\n");
              Print(L"    ");
              for (Index=0;Index<=0xff;Index++)
                {
                 Print_Register_Table(Index,16);//Print table of 256bits
                 Read_Extern_CMOS_IO(Index);
                 if (Index==0xff)break;
                }
              Print(L"\n");
              break;

             default:
               Usage();
               break;
             }
         } 
     	else if(Argc==5 && (!StrCmp(Argv[1],L"-w") || !StrCmp(Argv[1],L"-W")) && (StrLen(Argv[3])<=2 && StrLen(Argv[4])<=2))
        {
          Offset = (UINT8)StrHexToUintn(Argv[3]);
          Value  = (UINT8)StrHexToUintn(Argv[4]);
          switch (Bank)
            {
             case 0:
               Write_CMOS_IO(Offset,Value);
               Print(L"Bank 0\n");
               Print(L"    ");
               for(Index=0;Index<=0xff;Index++)
                 {
                  Print_Register_Table(Index,16);//Print table of 256bits
                  Read_CMOS_IO(Index);
                if(Index==0xff)break;
                 }
               Print(L"\n");
               break;

             case 1:            
               Write_Extern_CMOS_IO(Offset,Value);
               Print(L"Bank 1\n");
               Print(L"    ");
               for(Index=0;Index<=0xff;Index++)
                 {
                  Print_Register_Table(Index,16);//Print table of 256bits
                  Read_Extern_CMOS_IO(Index);
                  if(Index==0xff)break;
                   }
               Print(L"\n");
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
      Status=cmos_main( Argc, Argv);
		}
    //
    // use shell 2.0 interface
    //
    
	return Status;
}


