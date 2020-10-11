#include <xc.h>

#define GetSystemClock()        ( 200000000UL )
#define GetPeripheralClock()    ( 40000000UL )

#define RED_LED         _LATH_LATH0_MASK
#define YELLOW_LED      _LATH_LATH1_MASK
#define GREEN_LED       _LATH_LATH2_MASK

// To use:
// * srec_cat stub.hex -intel u-boot.srec -offset -0x80000000 -o u-boot-skde.hex -intel
// * Use PKOB to flash PIC32

#define USER_APP_RESET_ADDRESS      (__KSEG0_PROGRAM_MEM_BASE)

#define PREFETCH_INSTRUCTIONS       1
#define PREFETCH_ANY_ADDRESS        3

#define SYSKEY_UNLOCK_SEQ0  0xAA996655UL
#define SYSKEY_UNLOCK_SEQ1  0x556699AAUL

#define SYSKEY_UNLOCK() \
    SYSKEY = 0; \
    SYSKEY = SYSKEY_UNLOCK_SEQ0; \
    SYSKEY = SYSKEY_UNLOCK_SEQ1; \

#define SYSKEY_LOCK() \
    SYSKEY = 0; \

static void HardwareConfigurePerformance(void);

int main(int argc __attribute((unused)), char *argv[] __attribute__((unused)))
{
    HardwareConfigurePerformance();

    LATHSET = RED_LED;

    uintptr_t *pAppPtr = (uintptr_t *) USER_APP_RESET_ADDRESS;

    if(*pAppPtr != 0xFFFFFFFFUL)
    {
        typedef void (*pfn)(void);
        (*(pfn) pAppPtr)();

        LATHSET = RED_LED | YELLOW_LED | GREEN_LED;
    }

    for( ; ; )
    {
        _wait();
    }

    return 0;
}

static uint8_t PIC32CalcFlashWaitStates(void)
{
    static const uint32_t nFLASH_LIMITS[] = {74000000UL, 140000000UL, 200000000UL, 252000000UL, 0};
    static const uint8_t nWAIT_STATES[] = {0, 1, 2, 4};

    uint8_t indx = 0;

    while( GetSystemClock() > nFLASH_LIMITS[indx] )
    {
        if( !nFLASH_LIMITS[indx] )
        {
            return 0;
        }

        indx++;
    }

    return nWAIT_STATES[indx];
}

static void PIC32MZConfigureWaitStates(void)
{
    uint8_t waitStates = PIC32CalcFlashWaitStates();

    uint32_t precon = PRECON;

    precon &= ~(_PRECON_PFMWS_MASK | _PRECON_PREFEN_MASK);

    if(waitStates > 0)
    {
        precon |= (PREFETCH_INSTRUCTIONS << _PRECON_PREFEN_POSITION)
                   | (waitStates << _PRECON_PFMWS_POSITION);
    }

    PRECON = precon;
}

void HardwareConfigurePerformance(void)
{
    SYSKEY_UNLOCK();

    // I/O configuration for UART2 [pins B0, G9] and I2C3 [pins F2, F8]
    ANSELBCLR = _ANSELB_ANSB0_MASK;
    ANSELGCLR = _ANSELG_ANSG9_MASK;

    TRISBSET = _TRISB_TRISB0_MASK;
    U2RXRbits.U2RXR = 0b0101;   // RPB0
    RPG9Rbits.RPG9R = 0b0010;   // U2TX

    // I/O configuration for LEDs/switches
    ANSELBCLR = _ANSELB_ANSB12_MASK | _ANSELB_ANSB13_MASK | _ANSELB_ANSB14_MASK;
    LATHCLR = RED_LED | YELLOW_LED | GREEN_LED;
    TRISHCLR = _TRISH_TRISH0_MASK | _TRISH_TRISH1_MASK | _TRISH_TRISH2_MASK;

    // Configure peripheral busses

    // Set PBCLK2 to deliver 40Mhz clock for PMP/I2C/UART/SPI
    // 200MHz / 5 = 40MHz
    PB2DIVbits.PBDIV = 0b0000100;

    // Ports use PBCLK4, max allowed frequency is 100MHz
    PB4DIVbits.PBDIV = 0b0000001;

    // Enable prefetch module
    PIC32MZConfigureWaitStates();

    SYSKEY_LOCK();
}

void _bootstrap_exception_handler(void)
{
    LATHSET = RED_LED | YELLOW_LED | GREEN_LED;

    for( ; ; )
    {
        _wait();
    }
}

void _general_exception_context(void)
{
    LATHSET = RED_LED | YELLOW_LED | GREEN_LED;

    for( ; ; )
    {
        _wait();
    }
}

void _nmi_handler(void)
{
    LATHSET = RED_LED | YELLOW_LED | GREEN_LED;

    for( ; ; )
    {
        _wait();
    }
}
