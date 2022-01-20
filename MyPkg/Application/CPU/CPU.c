#include "CPU.h"
//

//
// Display CPU_String
//
VOID
CPU_String( VOID )
{
    UINT32 Eax, Ebx, Ecx, Edx;
    CHAR8  String[13];
    
    AsmCpuid( CPUID_SIGNATURE, &Eax, &Ebx, &Ecx, &Edx );
 
 
    *(UINT32 *)(String + 0) = Ebx;
    *(UINT32 *)(String + 4) = Edx;
    *(UINT32 *)(String + 8) = Ecx;
    String[12] = 0;
 
    Print(L"    CPU String: %a\n", String);
}
//
// Display Processor Version Information
//
VOID
VersionInfo( VOID )
{
    UINT32 Eax, Ebx, Ecx, Edx;
    UINT64 Stepping,Family,Model;
    UINT64 Num_core,CPUID,Microcode_Rev;
    UINT64 TjMAX,Platform_ID,Proccessor_Flag;

    AsmCpuid(CPUID_VERSION_INFO, &Eax, &Ebx, &Ecx, &Edx);

    Stepping=BitFieldRead32(Eax,0,3);
    Model=(BitFieldRead32(Eax,16,19)<<4)+BitFieldRead32(Eax,4,7);
    Family=BitFieldRead32(Eax,20,27)+BitFieldRead32(Eax,8,11);
    Print(L"    Stepping: 0x%x\n",Stepping);
    Print(L"    Model: 0x%x\n",Model);
    Print(L"    Family: 0x%x\n",Family);
    //read EAX[31:0] to found CPUID and print
    CPUID=BitFieldRead32(Eax,0,31);   
    Print(L"    CPUID: %x\n", CPUID);
    
    //use MSR number to found Microcode Rev and print
    Microcode_Rev=AsmReadMsr64(MICROCODE_REV);
    Print(L"    Microcode Rev: %x\n", (Microcode_Rev>>48));
    
    //use MSR number to found Number of cores and print
    Num_core=AsmReadMsr64(NUM_CORE);      
    Print(L"    Number of cores: %d\n", (Num_core>>16));
    
    //use MSR number to found Processor TjMAX and print
    TjMAX=BitFieldRead64(AsmReadMsr64(TJMAX),16,23);
    Print(L"    Processor TjMAX: %d\n", TjMAX);
    
    //use MSR number to found Platform ID and print
    Platform_ID=BitFieldRead64(AsmReadMsr64(PLATFORM_ID),50,52);
    Print(L"    Platform ID: %d\n", Platform_ID);
    
    //use MSR number to found Processor Flag and print
    Proccessor_Flag=BitFieldRead64(AsmReadMsr64(PROCCESSOR_FLAG),50,52);
    Print(L"    Processor Flag: %d\n", Proccessor_Flag);
}
 

//
// Display Processor Brand String
//
VOID
BrandString( VOID )
{
    UINT32 Eax, Ebx, Ecx, Edx;
    UINT32 BrandString[13];
 
    AsmCpuid(CPUID_BRAND_STRING1, &Eax, &Ebx, &Ecx, &Edx);

    *(UINT32 *)(BrandString + 0) = Eax;
    *(UINT32 *)(BrandString + 1) = Ebx;
    *(UINT32 *)(BrandString + 2) = Ecx;
    *(UINT32 *)(BrandString + 3) = Edx;
 
    AsmCpuid(CPUID_BRAND_STRING2, &Eax, &Ebx, &Ecx, &Edx);

    *(UINT32 *)(BrandString + 4) = Eax;
    *(UINT32 *)(BrandString + 5) = Ebx;
    *(UINT32 *)(BrandString + 6) = Ecx;
    *(UINT32 *)(BrandString + 7) = Edx;
 
    AsmCpuid(CPUID_BRAND_STRING3, &Eax, &Ebx, &Ecx, &Edx);

    *(UINT32 *)(BrandString + 8) = Eax;
    *(UINT32 *)(BrandString + 9) = Ebx;
    *(UINT32 *)(BrandString + 10) = Ecx;
    *(UINT32 *)(BrandString + 11) = Edx;
 
    BrandString[12] = 0;
 
    Print (L"    CPU Information\n    %a\n",(CHAR8 *)BrandString);
    Print (L"-------------------------------------------------\n");
}
//
// Display Available Processor Features
//
VOID
Features_check( VOID )
{   
    UINT32                     Eax,Ebx,Ecx,Edx;
    CHAR16                     Buf[80],Features[1000];
    BOOLEAN                    FirstRow = TRUE;
    UINT32                     Col = 0;
    UINT8                      Width = WIDTH;
    CHAR16                     *f = Features;

    ZeroMem( Features, 1000 );
 
    AsmCpuid(CPUID_VERSION_INFO, &Eax, &Ebx, &Ecx, &Edx);

    

 
    // Presorted list. No sorting routine!
    if (Edx & BIT22) StrCat(Features, L" ACPI");                 // ACPI via MSR Support
    if (Ecx & BIT25) StrCat(Features, L" AESNT");
    if (Edx & BIT9) StrCat(Features, L" APIC");
    if (Ecx & BIT28) StrCat(Features, L" AVX");                  // Advanced Vector Extensions
    if (Edx & BIT19) StrCat(Features, L" CLFSH");                // CLFLUSH (Cache Line Flush) Instruction Support
    if (Edx & BIT15) StrCat(Features, L" CMOV");                 // CMOV Instructions Extension
    if (Ecx & BIT13) StrCat(Features, L" CMPXCHG16B");           // CMPXCHG16B Instruction Support
    if (Ecx & BIT10) StrCat(Features, L" CNXT_ID");              // L1 Cache Adaptive Or Shared Mode Support
    if (Edx & BIT8) StrCat(Features, L" CX8");                    // CMPXCHG8 Instruction Support
    if (Ecx & BIT18) StrCat(Features, L" DCA");                  // Direct Cache Access
    if (Edx & BIT2) StrCat(Features, L" DE");                     // Debugging Extensions
    if (Edx & BIT21) StrCat(Features, L" DS");                   // Dubug Store Support
    if (Ecx & BIT4) StrCat(Features, L" DS_CPL");                 // CPL Qual. Debug Store Support
    if (Ecx & BIT2) StrCat(Features, L" DTES64");                 // 64-bit Debug Store Support
    if (Ecx & BIT29) StrCat(Features, L" F16C");                 // 16-bit FP Conversion Instructions Support
    if (Ecx & BIT12) StrCat(Features, L" FMA");                  // Fused Multiply-Add
    if (Edx & BIT0) StrCat(Features, L" FPU");                    // Floating Point Unit
    if (Edx & BIT24) StrCat(Features, L" FXSR");                 // FXSAVE/FXRSTOR Support
    if (Edx & BIT28) StrCat(Features, L" HTT");                  // Max APIC IDs reserved field is Valid
    if (Edx & BIT14) StrCat(Features, L" MCA");                  // Machine Check Architecture
    if (Edx & BIT17) StrCat(Features, L" MCE");                  // Machine Check Exception
    if (Ecx & BIT3) StrCat(Features, L" MONITOR");                          // Monitor/Mwait Support (SSE3 supplements)
    if (Edx & BIT23) StrCat(Features, L" MMX");                  // Multimedia Extensions
    if (Ecx & BIT22) StrCat(Features, L" MOVBE");                              // Move Data After Swapping Bytes Instruction Support
    if (Edx & BIT5)StrCat(Features, L" MSR");                     // Model Specific Registers
    if (Edx & BIT12) StrCat(Features, L" MTRR");                 // Memory Type Range Registers
    if (Ecx & BIT27) StrCat(Features, L" OSXSAVE");                          // OS has set bit to support CPU extended state management using XSAVE/XRSTOR
    if (Edx & BIT6) StrCat(Features, L" PAE");                    // Physical Address Extensions
    if (Edx & BIT16) StrCat(Features, L" PAT");                  // Page Attribute Table
    if (Edx & BIT31) StrCat(Features, L" PBE");                  // Pending Break Enable
    if (Ecx & BIT17) StrCat(Features, L" PCID");                 // Process Context Identifiers
    if (Ecx & BIT1) StrCat(Features, L" PCLMULQDQ");              // Support Carry-Less Multiplication of Quadword instruction
    if (Ecx & BIT15) StrCat(Features, L" PDCM");                 // Performance Capabilities
    if (Edx & BIT13) StrCat(Features, L" PGE");                  // Page Global Enable
    if (Ecx & BIT23) StrCat(Features, L" POPCNT");               // Return the Count of Number of Bits Set to 1 instruction
    if (Edx & BIT3) StrCat(Features, L" PSE");                    // Page Size Extensions (4MB memory pages)
    if (Edx & BIT17) StrCat(Features, L" PSE_36");               // 36-Bit (> 4MB) Page Size Extension
    if (Edx & BIT18) StrCat(Features, L" PSN");                  // Processor Serial Number Support
    if (Ecx & BIT30) StrCat(Features, L" RDRAND");               // Read Random Number from hardware random number generator instruction Support
    if (Ecx & BIT11) StrCat(Features, L" SDBG");                 // Silicon Debug Support
    if (Edx & BIT11) StrCat(Features, L" SEP");                  // SYSENTER/SYSEXIT Support
    if (Ecx & BIT6) StrCat(Features, L" SMX");
    if (Edx & BIT27) StrCat(Features, L" SS");
    if (Edx & BIT25) StrCat(Features, L" SSE");
    if (Edx & BIT26) StrCat(Features, L" SSE2");
    if (Ecx & BIT0) StrCat(Features, L" SSE3");
    if (Ecx & BIT19) StrCat(Features, L" SSE4_1");
    if (Ecx & BIT20) StrCat(Features, L" SSE4_2");
    if (Ecx & BIT9) StrCat(Features, L" SSSE3");                  // Supplemental SSE-3
    if (Edx & BIT4) StrCat(Features, L" TSC");                    // Time Stamp Counter
    if (Ecx & BIT24) StrCat(Features, L" TSC_DEADLINE");         // TSC Deadline Timer
    if (Edx & BIT29) StrCat(Features, L" TM");                   // Automatic Clock Control (Thermal Monitor)
    if (Ecx & BIT8) StrCat(Features, L" TM2");                    // Thermal Monitor 2
    if (Edx & BIT1) StrCat(Features, L" VME");                    // Virtual 8086 Mode Enhancements
    if (Ecx & BIT5) StrCat(Features, L" VMX");                    // Hardware Virtualization Support
    if (Ecx & BIT21) StrCat(Features, L" X2APIC");               // x2APIC Support
    if (Ecx & BIT26) StrCat(Features, L" XSAVE");                // Save Processor Extended States
    if (Ecx & BIT14) StrCat(Features, L" XTPR_UPDATE_CONTROL");


    AsmCpuid(CPUID_EXTENDED_CPU_SIG, &Eax, NULL, &Ecx, &Edx);
    if (Ecx & BIT0) StrCat(Features, L" LAHF_SAHF");
    if (Ecx & BIT5) StrCat(Features, L" LZCNT");
    if (Ecx & BIT8) StrCat(Features, L" PREFETCHW");
                
    
    if (Edx & BIT11) StrCat(Features, L" SYSCALL_SYSRET");
    if (Edx & BIT20)StrCat(Features, L" XD Bit");               //Excute Disable Bit avaliable
    if (Edx & BIT26) StrCat(Features, L" PAGE1GB");
    if (Edx & BIT27) StrCat(Features, L" RDTSCP");
    if (Edx & BIT29) StrCat(Features, L" Intel");               //Intel(R)64 Architecture available


    // Change IA32_MISC_ENABLE Support
    Print(L"    Features:");
     
        // Not the most elegant output folding code but it works!
        ZeroMem( Buf, 80 );
        while (*f) {
             Buf[Col++] = *f++;
             if (Col > Width) {
                 while (Col >= 0 && Buf[Col] != L' ') {
                     Buf[Col] = CHAR_NULL; 
                     f--; Col--;
                 }
                 if (FirstRow) {
                     Print(L"%s\n", Buf);
                     FirstRow = FALSE;
                 } else {
                     Print(L"              %s\n", Buf);
                 }
                 ZeroMem(Buf,80);
                 Col = 0;
             }
        }
        if (Col) {
            if (FirstRow) {
                Print(L"%s\n", Buf);
            } else {
                Print(L"              %s\n", Buf);
            }
    }

}


 

EFI_STATUS
EFIAPI
Main
(         IN EFI_HANDLE        ImageHandle,
          IN EFI_SYSTEM_TABLE  *SystemTable
)
{
   EFI_STATUS Status = EFI_SUCCESS;
 
    
    Print(L"\n");
    BrandString();
    CPU_String();
    VersionInfo();
    Features_check();
    Print(L"\n");

    
    return Status;
}
































