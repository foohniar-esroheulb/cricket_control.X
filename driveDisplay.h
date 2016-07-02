#ifndef disp_thingy
#define disp_thingy

union unionNumberBits{
    char Byte;
    struct
{
    unsigned segA        :1;                                                    // bit zero
    unsigned segB        :1;
    unsigned segC        :1;
    unsigned segD        :1;
    unsigned segE        :1;
    unsigned segF        :1;
    unsigned segG        :1;                                                    // bit 6 (not quite msb)
};
};

extern union unionNumberBits numberBits;

#endif
