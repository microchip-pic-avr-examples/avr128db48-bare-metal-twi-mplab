#include "IO.h"

#include <xc.h>

//Configures Device I/O
void IO_init(void)
{
    //TWI 
    {
        //PA2/PA3
        
        //Output I/O
        PORTA.DIRSET = PIN2_bm | PIN3_bm;

        //Enable Pull-Ups
        PORTA.PINCONFIG = PORT_PULLUPEN_bm;

        //Select RA2/RA3
        PORTA.PINCTRLUPD = PIN2_bm | PIN3_bm;
    }
}