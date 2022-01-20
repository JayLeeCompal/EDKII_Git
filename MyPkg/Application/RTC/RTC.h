#include <Uefi.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/IoLib.h>
#include <COMPAL_IOLib.h>
//RTC data defination
#define SECONDS       0x0
#define SECONDS_ALARM 0x1
#define MINUTES       0x2
#define MINUTES_ALARM 0x3
#define HOURS         0x4
#define HOURS_ALARM   0x5
#define DAY_OF_WEEK   0x6
#define DAY_OF_MONTH  0x7
#define MONTH         0x8
#define YEAR          0x9