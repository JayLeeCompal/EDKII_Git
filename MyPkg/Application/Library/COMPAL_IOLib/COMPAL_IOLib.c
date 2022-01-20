#include <COMPAL_IOLib.h>

//@range      Number of data
//@LineBreak  Line of table

VOID
EFIAPI
Print_Register_Table(IN UINT16 range,IN UINT8 LineBreak)
{
  UINTN i;
  if ( range == 0 )
    {
    for ( i=0 ; i<LineBreak ; i++ )   //print row of table
      {
       Print(L"0%x ",i);
      }
    
    Print(L"\n");              //print col of table
    }
 if ( range % LineBreak == 0 )
   {
    Print(L"\n%02x  ",range);
   }
}


//Get_Pci_Register
//Use function of Get_Pci_CFG to search PFA
//and then use offset read register of 256 bytes              

//-------------------------------------------------------------------------------------------//

VOID
EFIAPI
Get_Pci_Register
(
     IN   UINT16  bus,
     IN   UINT16  dev,
     IN   UINT16  fun,
     IN   UINT16  offset
)
{
     UINT16 count=0x0;
     UINT32 value,pfa;
     Print(L"    ");
     for ( count = 0x0 ; count <= 0xff ; count += 0x4 )
      {
       Print_Register_Table(count,16); //Print table of 256bits
       
       pfa = Get_Pci_CFG(bus,dev,fun,offset);//Get PFA
       IoWrite32(PCI_Index_IO_ConfigPort,pfa);//Write data in 0xCFC
       value = IoRead32(PCI_Index_IO_DataPort);//read data from 0xCFC
       Print(L"%02x ",(UINT8)value);
       Print(L"%02x ",(UINT8)(value>>8));      
       Print(L"%02x ",(UINT8)(value>>16));      
       Print(L"%02x ",(UINT8)(value>>24));
       offset+=0x4;
      }
}
//-------------------------------------------------------------------------------------------//
//
//RTC tools
//
UINT8
EFIAPI
Get_Time
(
  IN UINT8 DataAddress
)
{
  UINT8 Time;
  IoWrite8(CMOS_IndexPort,DataAddress); 
  Time = IoRead8(CMOS_IndexDataPort);
  return Time;

}

//-------------------------------------------------------------------------------------------//
//Read_CMOS_IO
//                    
//@bank 0 Input from 0x70  Output from 0x71
//@bank 1 Input from 0x71  Output from 0x72    
//If parameters are not 1 and 0  print error
//Use Indec IO to Access the Data in regester

VOID
EFIAPI
Read_CMOS_IO
(
  IN  UINT8  Index
)
{
  UINT8  Value;
  IoWrite8(CMOS_IndexPort,Index);//Write data in index Io port 0x70
  Value = IoRead8(CMOS_IndexDataPort);//Read data from index Io port 0x71
  Print(L"%02x ",Value);
  
}
VOID
EFIAPI
Write_CMOS_IO
(
  IN  UINT8  Index,
  IN  UINT8  Data
)
{
  IoWrite8(CMOS_IndexPort,Index);//Write data in index Io port 0x70
  IoWrite8(CMOS_IndexDataPort,Data);

  Print(L"Success\n");
  
}

VOID
EFIAPI
Read_Extern_CMOS_IO
(
  IN  UINT8  Index
)
{
  UINT8  Value;
  IoWrite8(CMOS_Extern_IndexPort,Index);//Write data in Index Io port 0x72
  Value = IoRead8(CMOS_Extern_IndexDataPort);//Read data from Index Io port 0x73
  Print(L"%02x ",Value);
}

VOID
EFIAPI
Write_Extern_CMOS_IO
(
  IN  UINT8  Index,
  IN  UINT8  Data
)
{
  IoWrite8(CMOS_Extern_IndexPort,Index);//Write data in Index Io port 0x72
  IoWrite8(CMOS_Extern_IndexDataPort,Data);
  Print(L"Success\n");
}

//-------------------------------------------------------------------------------------------//

UINT32
EFIAPI
Get_SMBus_Base(VOID)
{
  UINT8  dev,fun;
  UINT32 addr;
  addr = 0x80000000;
  for ( dev = 0x0 ; dev <= 0x1F ; dev++ )
    {
    for ( fun = 0x0 ; fun <= 0x07 ; fun++ )
      {
      addr = Get_Pci_CFG(0,dev,fun,0);//set the pci device ,Host Bus always 0
      IoWrite32(PCI_Index_IO_ConfigPort,addr);
      if ( (IoRead32(PCI_Index_IO_DataPort) != 0xffffffff) && (IoRead32(PCI_Index_IO_DataPort) !=0 ) )
        {
        addr += 0x8;//read class code
        IoWrite32(PCI_Index_IO_ConfigPort,addr);
        if ( (IoRead32(PCI_Index_IO_DataPort)>>16) == 0xc05 )
          {//it's smbus class code
          return addr - 0x8;
          } 
        }
      }
    }
  return addr;
}

UINT32
EFIAPI
Get_SMBus_IoPort(VOID)
{
  UINT32 PciConfigAddr;
  PciConfigAddr = Get_SMBus_Base();
  IoWrite32(PCI_Index_IO_ConfigPort,PciConfigAddr+0x20);//Pci bar5 is Io Base Address
  return IoRead32(PCI_Index_IO_DataPort)&0xFFFE;
}

VOID
EFIAPI
Read_SPD_Byte(
  IN  UINT32 IoPort,
  IN  UINT8  addr,
  IN  UINT8  Index
)
{
    IoWrite8(IoPort,0x1E);
    IoWrite8(IoPort+0x04,addr);
    IoWrite8(IoPort+0x03,Index);//read first byte
    IoWrite8(IoPort+0x02,0x48);//read a byte
    while(IoRead8(IoPort)&0x01);//wating for smbus
}


//-------------------------------------------------------------------------------------------//

UINT8
EFIAPI
Check_IBF(IN UINT8 address)
{
  INTN count = 0;
  while ( (IoRead8(address)& BIT1) != 0 )//check input buffer is empty and wait
    {
     if ( count<0x5000 ){count++;}

     else {break;}
     
    }
  return EFI_SUCCESS;
}

UINT8
EFIAPI
Check_OBF(IN UINT8 address)
{
  INTN count=0;
  while ( (IoRead8(address)& BIT0) == 0 )//check output buffer is empty and wait
    {
     if ( count < 0x5000 ){count++;}

     else {break;}
     
    }
  
  return EFI_SUCCESS;
}
//-------------------------------------------------------------------------------------------//



