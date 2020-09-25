#if defined(__32MZ2064DAB288__)

// DEVCFG4
#pragma config SWDTPS = SPS1048576      // Sleep Mode Watchdog Timer Postscaler (1:1048576)

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config EXTDDRSIZE = DDR_SIZE_128MB// External DDR2 SDRAM Memory Size (External DDR2 Size is 128 MB)
#pragma config FMIIEN = OFF             // Ethernet RMII/MII Enable (RMII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = OFF            // Permission Group Lock One Way Configuration (Allow multiple reconfigurations)
#pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration (Allow multiple reconfigurations)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow multiple reconfigurations)

// DEVCFG2
#pragma config FPLLIDIV = DIV_3         // System PLL Input Divider (3x Divider)
#pragma config FPLLRNG = RANGE_21_42_MHZ// System PLL Input Range (21-42 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_50        // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (2x Divider)
#pragma config VBATBOREN = OFF          // VBAT BOR Enable (Disable ZPBOR during VBAT Mode)
#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable (Disable ZPBOR during Deep Sleep Mode)
#pragma config DSWDTPS = DSPS32         // Deep Sleep Watchdog Timer Postscaler (1:2^36)
#pragma config DSWDTOSC = LPRC          // Deep Sleep WDT Reference Clock Selection (Select LPRC as DSWDT Reference clock)
#pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer Enable (Disable DSWDT during Deep Sleep Mode)
#pragma config FDSEN = OFF              // Deep Sleep Enable (Disable DSEN bit in DSCON)
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (System PLL)
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable Secondary Oscillator)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = EC             // Primary Oscillator Configuration (External clock mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disabled, FSCM Disabled)
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32768)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
#pragma config DMTCNT = DMT31           // Deadman Timer Count Selection (2^31 (2147483648))
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config TRCEN = OFF              // Trace Enable (Trace features in the CPU are disabled)
#pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_LOCKED     // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are locked))
#pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = PG_ALL          // Debug Mode CPU Access Permission (Allow CPU access to all permission regions)
#pragma config SMCLR = MCLR_NORM        // Soft Master Clear Enable (MCLR pin generates a normal system Reset)
#pragma config SOSCGAIN = GAIN_2X       // Secondary Oscillator Gain Control bits (2x gain setting)
#pragma config SOSCBOOST = OFF          // Secondary Oscillator Boost Kick Start Enable bit (Normal start of the oscillator)
#pragma config POSCGAIN = GAIN_2X       // Primary Oscillator Gain Control bits (2x gain setting)
#pragma config POSCBOOST = OFF          // Primary Oscillator Boost Kick Start Enable bit (Normal start of the oscillator)
#pragma config POSCFGAIN = GAIN_G3      // Primary Crystal Oscillator Final Gain Control (Gain is G3)
#pragma config POSCTYPE = CRYSTAL_24MHZ // Primary Oscillator Type bits (24 MHz Crystal used as Primary Oscillator)
#pragma config POSCAGCRNG = RANGE_1X    // Primary Crystal Oscillator AGC Lock Range bit (Range 1x)
#pragma config POSCAGC = ON             // Primary Oscillator Auto Gain Control bit (POSC Auto Gain Control Enabled)
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot Enable (Normal EJTAG functionality)

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// SEQ3
#pragma config TSEQ = 0xFFFF            // Boot Flash True Sequence Number (Enter Hexadecimal value)
#pragma config CSEQ = 0xFFFF            // Boot Flash Complement Sequence Number (Enter Hexadecimal value)

#else

#error Unsupported processor!

#endif
