#include "RTC.h"
EFI_STATUS
EFIAPI
Main
(
          IN EFI_HANDLE        ImageHandle,
          IN EFI_SYSTEM_TABLE  *SystemTable

)
{
  UINT8 hr,min,sec;
  hr=Get_Time(HOURS);    //hour
  min=Get_Time(MINUTES); //minutes
  sec=Get_Time(SECONDS); //second
  

  Print(L" %02d:%02d:%02d \n",hr,min,sec);
  return EFI_SUCCESS;
}
