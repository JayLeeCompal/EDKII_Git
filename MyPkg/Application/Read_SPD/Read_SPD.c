#include "Read_SPD.h"

EFI_STATUS
EFIAPI
Main (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINT8 SlaveAddr,Temp[256];
  UINT16 Index;
  UINT32 SmBusIoPort;
  SmBusIoPort=Get_SMBus_IoPort();
  for(SlaveAddr=0xA0;SlaveAddr<0xAE;SlaveAddr+=2)
    {
     Read_SPD_Byte(SmBusIoPort,SlaveAddr+1,0);
     if(IoRead8(SmBusIoPort)&0x04){continue;}//detect error bit
     Print(L"\n");
     Print(L"    ");

     for(Index=0;Index<=0xFF;Index++)
       {
        Print_Register_Table(Index,16);
        Read_SPD_Byte(SmBusIoPort,SlaveAddr+1,(UINT8)Index);
        
        Temp[Index]=IoRead8(SmBusIoPort+0x05);
        Print(L"%02x ",Temp[Index]);
       }      
    }
  Print(L"\n");
	return EFI_SUCCESS;
}


