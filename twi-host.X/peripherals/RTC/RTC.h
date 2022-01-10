#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    //Start the RTC
    void RTC_init(void);
    
    //Set the function called by the PIT Interrupt
    void PIT_setISR(void (*func)(void));
    
#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

