#include "Read_EDID_Str.h"
//
//Function of Vendor Abbreviation
//
CHAR16 *
ManufacturerAbbrev(UINT16 ManufactureName)
{
    static CHAR16 mcode[8];
    UINT16 VID=SwapBytes16(ManufactureName);
    
    mcode[0] = (CHAR16)((VID>>10) & 0x1F) + 'A' - 1;
    mcode[1] = (CHAR16)((VID>>5) & 0x1F) + 'A' - 1;
    mcode[2] = (CHAR16)(VID & 0x1F) + 'A' - 1;
    mcode[3] = (CHAR16)'\0';
    return mcode;
}
 
void
PrintEdidStr(EFI_EDID_DISCOVERED_PROTOCOL *Edid)
{
    VESA_BIOS_EXTENSIONS_EDID_DATA_BLOCK *EdidDataBlock = (VESA_BIOS_EXTENSIONS_EDID_DATA_BLOCK*)Edid->Edid;
    UINT8 tmp,Check_Ana_Dit;
    //
    //Display Basic Information
    //
    Print(L"\n");
    Print(L"EDID Version       : %d\n",  EdidDataBlock->EdidVersion);
    Print(L"EDID Revision      : %d\n",  EdidDataBlock->EdidRevision);
    Print(L"Vendor ID          : %s\n", ManufacturerAbbrev(EdidDataBlock->ManufactureName));
    Print(L"Product ID         : %08lx\n", EdidDataBlock->ProductCode);
    Print(L"Serial Number      : %08lx\n",  EdidDataBlock->SerialNumber);
    Print(L"Manufacture Week   : %d\n", EdidDataBlock->WeekOfManufacture);
    Print(L"Manufacture Year   : %d\n", EdidDataBlock->YearOfManufacture + 1990);
    //
    //Display Video output type 
    //
    tmp = EdidDataBlock->VideoInputDefinition;
    Print(L"Video Input        : "); 
    //Check Video Input type ,if BIT7=0 Analog BIT7=1 Digital
    Check_Ana_Dit=tmp & BIT7;
    if (Check_Ana_Dit)
      {
       Print(L"Digital\n");
       Print(L"Bit depth          : ");
       switch((tmp>>4)&0x7)
        {
          case 0:
            Print(L"undefined\n");
            break;
          case 1:
            Print(L"6 bits per color\n");
            break;
          case 2:
            Print(L"8 bits per color\n");            
            break;
          case 3:
            Print(L"10 bits per color\n");
            break;
          case 4:
            Print(L"12 bits per color\n");
            break;
          case 5:
            Print(L"14 bits per color\n");
            break;
          case 6:
            Print(L"16 bits per color\n");
            break;
          case 7:
            Print(L"reserved\n");
            break;
        }
       Print(L"Video interface    : ");
       
       //check Video Interface type bit[3:0]
       //0000 1111
       switch(tmp&0xF)
        {

          case 0:
            Print(L"undefined\n");
            break;
          case 2:
            Print(L"HDMIa\n");
            break;
          case 3:
            Print(L"HDMIb\n");
            break;
          case 4:
            Print(L"MDDI\n");
            break;
          case 5:
            Print(L"DisplayPort\n");
            break;
        }
      }
     else 
      {
      Print(L"Analog\n");
      Print(L"Syncronization     : ");
      //0001 1111
      //Check bit[4:0]
      tmp &= 0x1F;
      if (tmp & BIT4){Print(L"BlankToBackSetup ");}
      if (tmp & BIT3){Print(L"SeparateSync ");} 
      if (tmp & BIT2){Print(L"CompositeSync ");}
      if (tmp & BIT1){Print(L"SyncOnGreen ");}
      if (tmp & BIT0){Print(L"SerrationVSync ");}
      Print(L"\n");
      }
    tmp=EdidDataBlock->DisplayTransferCharacteristic;
    Print(L"Stored Value       : %d.%d Gamma\n",(tmp/100)+1,tmp%100);
    //
    // 0x18 Display Featurn support
    //
    tmp = EdidDataBlock->FeatureSupport;
    Print(L"Display Type       : ");
    if (Check_Ana_Dit) 
      {//0001 1000 >> 3   ---> 0000 0011
       //Check bit[4:3] 
       switch ((tmp>>3) & 0x11)
        {
         case 0:
          Print(L"RGB 4:4:4\n");
          break;
         case 1:
          Print(L"RGB 4:4:4 + YCrCb 4:4:4\n");
          break;
         case 2:
          Print(L"RGB 4:4:4 + YCrCb 4:2:2\n");
          break;
         default:
          Print(L"RGB 4:4:4 + YCrCb 4:4:4 + YCrCb 4:2:2\n");
          break;
        }
      }
    else
      {//0001 1000 >> 3   ---> 0000 0011
       //check bit3 & bit4
       switch ((tmp>>3) & 0x11)
        {
         case 0:
          Print(L"monochrome or grayscale\n");
          break;
         case 1:
          Print(L"RGB color\n");
          break;
         case 2:
          Print(L"non-RGB color\n");
          break;
         default:
          Print(L"undefined\n");
          break;
        }
      }
 
    Print(L"Max Horizonal Size : %ld cm\n", EdidDataBlock->MaxHorizontalImageSize);
    Print(L"Max Vertical Size  : %ld cm\n", EdidDataBlock->MaxVerticalImageSize);
    
    tmp=EdidDataBlock->EstablishedTimings[0];
    Print(L"EstablishedTimings : ");
    tmp&=0xFF;
    if (tmp & BIT0){Print(L"800 * 600 @ 60 Hz \n");}
    if (tmp & BIT1){Print(L"800 * 600 @ 56 Hz \n");}
    if (tmp & BIT2){Print(L"640 * 480 @ 75 Hz \n");}
    if (tmp & BIT3){Print(L"640 * 480 @ 72 Hz \n");}
    if (tmp & BIT4){Print(L"640 * 480 @ 67 Hz (Apple Macintosh II) \n");}
    if (tmp & BIT5){Print(L"640 * 480 @ 60 Hz (VGA) \n");}
    if (tmp & BIT6){Print(L"720 * 400 @ 88 Hz (XGA) \n");}
    if (tmp & BIT7){Print(L"720 * 400 @ 70 Hz (VGA) \n");}

    tmp=EdidDataBlock->EstablishedTimings[1];
    tmp&=0xFF;
    if (tmp & BIT0){Print(L"1280 * 1024 @ 75 Hz \n");}
    if (tmp & BIT1){Print(L"1024 * 768 @ 75 Hz \n");}
    if (tmp & BIT2){Print(L"1024 * 768 @ 70 Hz \n");}
    if (tmp & BIT3){Print(L"1024 * 768 @ 60 Hz \n");}
    if (tmp & BIT4){Print(L"1024 * 768 @ 87 Hz, interlaced (1024 * 768i) \n");}
    if (tmp & BIT5){Print(L"832 * 624 @ 75 Hz (Apple Macintosh II) \n");}
    if (tmp & BIT6){Print(L"800 * 600 @ 75 Hz \n");}
    if (tmp & BIT7){Print(L"800 * 600 @ 72 Hz \n");}

    tmp=EdidDataBlock->EstablishedTimings[2];
    tmp&=0xFF;
    (tmp & BIT7)?Print(L"1152 * 870 @ 75 Hz (Apple Macintosh II)\n"):Print(L"Other manufacturer-specific display modes\n");

    tmp=EdidDataBlock->StandardTimingIdentification[0];
    Print(L"Resolution         : %d pixels\n",(tmp+31)*8);

    tmp=EdidDataBlock->StandardTimingIdentification[1];
    Print(L"Image aspect ratio : ");
    switch((tmp>>6)&0x3)
      {
        case 0:
          Print(L"16:10\n");
          break;
        case 1:
          Print(L"4:3\n");
          break;
        case 2:
          Print(L"5:4\n");
          break;
        case 3:
          Print(L"16:9\n");
          break;
      }
    Print(L"Field Refresh Rate : %d Hz\n",(tmp&0x1F)+60);
}
EFI_STATUS
EFIAPI
Main(
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable

)
{

 
  EFI_STATUS Status = EFI_SUCCESS;
  UINT16    i ;
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
    
    for(i = 0 ; i < (EDID->SizeOfEdid) ; i++)
      {
        Print_Register_Table(i,16);
        //EDID Information Data
        Print(L"%02X ", EDID->Edid[i]);
      }
    
    PrintEdidStr(EDID);
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











































