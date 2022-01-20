#ifndef __COMPAL_IOLIB__
#define __COMPAL_IOLIB__
#include <Base.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>
#include <Library/IoLib.h>
#include <Library/SmbusLib.h>

//Get PCI Function Address
#define Get_Pci_CFG(BUS,DEV,FUN,OFF) 0x80000000|(BUS<<16)|(DEV<<11)|(FUN<<8)|(OFF&0xFC)

//PCI index defination
#define PCI_Index_IO_ConfigPort                          0xCF8
#define PCI_Index_IO_DataPort                            0xCFC

//CMOS index defination 
#define CMOS_IndexPort                                   0x70
#define CMOS_IndexDataPort                               0x71
#define CMOS_Extern_IndexPort                            0x72
#define CMOS_Extern_IndexDataPort                        0x73

//SPD index defination
#define SLAVE_ADDR                                       0xA8
#define SMBus_Io_Port                                    0x5040



//@range      Number of data
//@LineBreak  Line of table
VOID
EFIAPI
Print_Register_Table
(
  IN UINT16 range,
  IN UINT8 LineBreak
  );


//Get_Pci_Register
//Use function of Get_Pci_CFG to search PFA
//and then use offset read register of 256 bytes              
VOID
EFIAPI
Get_Pci_Register
(
     IN   UINT16  bus,
     IN   UINT16  dev,
     IN   UINT16  fun,
     IN   UINT16  offset
);


//Get time
//
//@IndexPort write data to 0x70
//
UINT8
EFIAPI
Get_Time
(
  IN UINT8 IndexPort
);


//Read_CMOS_IO
//CMOS IoPort input 0x70 , output 0x71
//
VOID
EFIAPI
Read_CMOS_IO
(
  IN  UINT8  offset
);

//Write_CMOS_IO
//CMOS IoPort input 0x70 , output 0x71
//
VOID
EFIAPI
Write_CMOS_IO
(
  IN  UINT8  Index,
  IN  UINT8  Data
);

//Read_Extern_CMOS_IO
//CMOS IoPort input 0x72 , output 0x73
//
VOID
EFIAPI
Read_Extern_CMOS_IO
(
  IN  UINT8  offset
);
//Write_Extern_CMOS_IO
//CMOS IoPort input 0x72 , output 0x73
//
VOID
EFIAPI
Write_Extern_CMOS_IO
(
  IN  UINT8  Index,
  IN  UINT8  Data
);


//read SMbus Base Address via PCI dump
UINT32
EFIAPI
Get_SMBus_Base(VOID);

//read SMbus IoPort via SMBus Base Address
UINT32
EFIAPI
Get_SMBus_IoPort(VOID);
//read SPD of Byte via slave address
VOID
EFIAPI
Read_SPD_Byte(
  IN  UINT32 IoPort,
  IN  UINT8  SlaveAddr,
  IN  UINT8  Index
);
//Check IBF/OBF  Full or Empty and wait

UINT8
EFIAPI
Check_IBF(IN UINT8 address);

UINT8
EFIAPI
Check_OBF(IN UINT8 address);



#endif
