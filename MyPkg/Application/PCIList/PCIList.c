#include "PCIList.h"


EFI_STATUS
EFIAPI
Main
(
          IN EFI_HANDLE        ImageHandle,
          IN EFI_SYSTEM_TABLE  *SystemTable
)
{
  UINT8 bus,dev,fun,offset=0x0;
  UINT16 vid,did;
  UINT32 pfa;
  Print(L"PCI List\n");
  Print(L"   PFA         Bus    Dev    Fun    VID    DID\n");
  for(bus=0x0;bus<=0xFF;bus++){               //search Bus number [23:16]
    for(dev=0x0;dev<=0x1F;dev++){             //search Device number [15:11]
      for(fun=0x0;fun<=0x7;fun++){            //search Function number [10:8]
        pfa=Get_Pci_CFG(bus,dev,fun,offset);  //Colculate PFA(PCI Fumction Address)
        IoWrite32(PCI_Index_IO_ConfigPort,pfa);                 //Write PFA in I/O port from 0xcf8
        vid=(UINT16)IoRead32(PCI_Index_IO_DataPort);                  //Read Vendor ID from 0xCFC
        did=(UINT16)(IoRead32(PCI_Index_IO_DataPort)>>16);                  //Read Device ID from 0xCFE
        //If have device print all
        if(vid!=0xffff&&vid!=0x0000){
          Print(L"%08lx       %02x     %02x     %02x     %04x   %04x\n",pfa,bus,dev,fun,vid,did);
          }
        }
      }
    if(bus==0xff)break;
    }
  return EFI_SUCCESS;   
}