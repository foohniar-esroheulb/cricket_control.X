#ifndef main_fiddle
#define main_fiddle

// function prototypes are:
void high_int (void);
void low_int (void);
void timer0isr (void);
void driveDisp (void);
char bcdTo7seg(char value);



union unionSchedFlags{
    char Byte;
    struct
{
    unsigned             :1;                                                    // bit zero
    unsigned readButton  :1;                                                    // bit one
    unsigned driveDisp   :1;                                                    // bit two
    unsigned             :1;                                                    // bits three, four and five
    unsigned             :3;                                                    // bit six
    unsigned comms       :1;                                                    // bit seven
};
};

extern union unionSchedFlags schedFlags;

// cathode combinations -- derived looking at vero board, not circuit diagram

#define selectWkts      0x10
#define selectOverU     0x20
#define selectOverT     0x80
#define selectScoreThs  0x08
#define selectScoreHun  0x04
#define selectScoreTen  0x02
#define selectScoreUni  0x40
#define blankCath       0x01

#endif