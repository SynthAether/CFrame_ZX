//
//      ZX Spectrum Next z88dk simple example
//

// Nightly Builds
// http://nightly.z88dk.org/

#pragma output REGISTER_SP = 0xbfff

#include <arch/zxn.h>           // ZX Spectrum Next architecture specfic functions
#include <stdint.h>             // standard names for ints with no ambiguity 
#include <z80.h>
#include <im2.h>
#include <intrinsic.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <input.h>
#include <errno.h>

#include "FrameWork.h"
#include "Kernel.h"
#include "data.h"


// ************************************************************************************************************************
//  Main Loop
// ************************************************************************************************************************
void MainLoop(void)
{
    while(1)
    {
        WaitVBlank();
        ReadKeyboard();
        FrameCounter++;

        if( Keys[VK_SPACE])
        {
            Print(80,184,"Space Pressed");
        }
        else{
            Print(80,184,"----- -------");
        }

        PrintHex((FrameCounter>>8)&0xff,0x5000);
        PrintHex(FrameCounter&0xff,0x5002);
    }    
}


// ************************************************************************************************************************
//  Main program start
// ************************************************************************************************************************
int  main(void)
{
    BREAK;                          // Stop the debugger at the start
    intrinsic_label(Main_Label);


    NextReg(0x7,3);                 // 28Mhz
    NextReg(0x8,0x4A);              // Disable RAM contention, enable DAC and turbosound
    NextReg(0x5,0x04);              // 60Hz mode
    NextReg(0x15,0x03);             // layer order - and sprites on
    NextReg(0x4b,0xe3);             // sprite transparency


    NextReg(0x57,2);                // page in kernal - $E000->$FFFF
    InitKernel();
    SetUpIRQs();


    Layer2Enable(false);
    ClsATTR(56);                    // white paper, black ink
    ClsULA();


    PrintHex(0x12,0x4000);
    Print(16,32,"Hello World");
    DMACopy(0x4000,0x4800,0x800);   // copy the top of the screen to half way down (shows HEX message)

    MainLoop();

    while(1){}                      // never exit
}


