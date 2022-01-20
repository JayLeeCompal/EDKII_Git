#include "Read_EDID.h"

EFI_STATUS
EFIAPI
Main(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable

)
{

 
  EFI_STATUS Status = EFI_SUCCESS;
  UINT16      i;
  UINTN       Index,EDIDHandleCount;
  EFI_HANDLE *EDIDHandleBuffer;
  EFI_EDID_DISCOVERED_PROTOCOL * EDID;

  //LocateHandleBuffer for find special protocol via guid
  Status=gBS->LocateHandleBuffer(
                        ByProtocol,
                        &gEfiEdidDiscoveredProtocolGuid,
                        NULL,
                        &EDIDHandleCount,
                        &EDIDHandleBuffer
    );
  //Comfirm Protocol Success 
  //If get success print error message
  Print(L"Status: %d\n",Status);  
  if(EFI_ERROR(Status)){ Print(L"Fail to LocateHandleBuffer\n");return Status;}
  
  Print(L"HandleCount: %d\n",EDIDHandleCount);
  //Check EDIDHandleCount
  for(Index = 0 ; Index < EDIDHandleCount ; Index++){
    //Comfirm Open Protocol Success 
    //If get success print error message
    Status=gBS->OpenProtocol(
                EDIDHandleBuffer[Index],//Handle Buffer
                &gEfiEdidDiscoveredProtocolGuid,//Protocol Guid
                (VOID**)&EDID,//EDID potiner to protocol data
                ImageHandle,
                NULL,
                EFI_OPEN_PROTOCOL_GET_PROTOCOL //get data by 0x2
              );
    if(EFI_ERROR(Status)){Print(L"Fail to OpenProtocol\n");return Status;}

    
    //EDID Information Size
    Print(L"Edid_Size: %d\n",EDID->SizeOfEdid);
    //Print register table of EDID information from 0x0~0x7F
    Print(L"    ");
    for(i = 0 ; i <= 0xFF ; i++)
      {
        Print_Register_Table(i,16);
        //EDID Information Data
        Print(L"%02X ", EDID->Edid[i]);
      }
    //Comfirm Close Protocol Success 
    //If get success print error message
    Status = gBS->CloseProtocol(
                EDIDHandleBuffer[Index],//Handle Buffer
  			        &gEfiEdidDiscoveredProtocolGuid,//Protocol Guid
  			        gImageHandle,
  			        NULL
  			     ); 
        
    if(EFI_ERROR (Status)){Print(L"Fail to CloseProtocol\n");return Status;}  
  }
  Print(L"\n");
  return EFI_SUCCESS; 
}

























