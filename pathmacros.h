#ifndef __PATHMACROS_H__
#define __PATHMACROS_H__
 
// LED via SODIMM pin 55 (Linux GPIO 14)
#ifdef __ARM_EABI__    // path when executing on ARM target
    #define PATH_LED_VALUE        "/sys/class/gpio/gpio14/value"
    #define PATH_LED_DIRECTION    "/sys/class/gpio/gpio14/direction"
#else                  // path when executing on x86 host
    #define PATH_LED_VALUE        "/tmp/gpio14/value"
    #define PATH_LED_DIRECTION    "/tmp/gpio14/direction"
#endif
#endif
