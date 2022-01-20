#include <COMPAL_MSRLib.h>


VOID
EFIAPI
Read_MSR
(
  IN UINT16 Addr//@Addr Address of Read data from EAX or EDX
)
{
  UINT32 EAX,EDX;
  EAX=(UINT32)AsmReadMsr64(Addr); // Read MSR address return 64bit= EAX[31:0]+EDX[63:32] 
  EDX=(UINT32)(AsmReadMsr64(Addr)>>32);
  Print(L"       EAX:%08lx\n",EAX);
  Print(L"       EDX:%08lx\n",EDX);


}



