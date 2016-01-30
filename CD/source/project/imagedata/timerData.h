/**********************************************\
*       timer.h                                   *
*          by dovotos pcx->gba program         *
**********************************************/
#define  timer_WIDTH   32
#define  timer_HEIGHT  32


const u16 timerCirc[] = {
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x8317, 0x1717, 0xB817,
                    0x1852, 0xF6CB, 0x1717, 0x7617, 0xCB28, 0xA7F6, 0x1717, 0x1817, 0xDCCB, 0x17A1,
                    0x1717, 0xCC17, 0x7DF6, 0x1717, 0x1717, 0xF683, 0x1783, 0xF617, 0x1817, 0xA7F6,
                    0x1717, 0xF617, 0xA718, 0xF6F6, 0xF6F6, 0xE3F6, 0xF6F6, 0xA7D2, 0x5983, 0xB858,
                    0x83D2, 0x1758, 0x1717, 0x5217, 0x1758, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0xF6F6, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x17F6, 0x1717, 0x1717, 0xF6EF, 0xF6F6, 0xF6F6, 0x58A7, 0x5852, 0x8359,
                    0xD2A7, 0xF6F6, 0x1717, 0x1717, 0x5817, 0xD283, 0x1717, 0x1717, 0x1717, 0x5817,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0xF617, 0x1717, 0x1717, 0x1717, 0x17F6, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x18A7, 0x1717, 0x1717, 0x1717, 0xD2F6, 0x1758, 0x1752, 0x1717, 0xF6A7, 0x7CF6,
                    0x5228, 0x1717, 0x8317, 0xDCEF, 0x1776, 0x1717, 0x1717, 0xEFA1, 0x18D2, 0x1717,
                    0xF6F6, 0x83F6, 0xA7F6, 0x1717, 0x1717, 0x1717, 0xF6A7, 0x1758, 0xA717, 0x58D2,
                    0x1717, 0xF617, 0xF618, 0x1783, 0x1717, 0xF617, 0xD27D, 0x1758, 0x1717, 0xF617,
                    0xA7A7, 0x1717, 0x1717, 0xF617, 0x83D2, 0x1717, 0x1717, 0xF617, 0x59F6, 0x1717,
                    0x1717, 0xF617, 0x52F0, 0x1717, 0x1717, 0xF617, 0x9AE2, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x17F6, 0x1717, 0x1717, 0x1717, 0x17F6, 0x1717, 0x1717, 0x1717, 0x17F6,
                    0x1717, 0x1717, 0xF6F6, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0xF617, 0x1717, 0x1717, 0x1717, 0xF617, 0x1717,
                    0x1717, 0x1717, 0x1717, 0xF6F6, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x17F6, 0x1717, 0x1717, 0x1717, 0xF617, 0xF6F6,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0xD258, 0x17D2, 0x1717, 0x1717,
                    0x8317, 0x59F6, 0xF6F6, 0x1717, 0x5817, 0xA7D2, 0x1717, 0x17F6, 0x1717, 0xD2A7,
                    0x1717, 0x17F6, 0x1717, 0xF683, 0xF617, 0x1717, 0x1717, 0xF659, 0x17F6, 0x1717,
                    0x1717, 0xEF76, 0x1717, 0x1717, 0x1717, 0xE39A, 0x17F6, 0x1717, 0x1717, 0x1717,
                    0x58F6, 0x1717, 0x1717, 0x1717, 0x59F6, 0x1717, 0x1717, 0x1717, 0x83CB, 0x1717,
                    0x1717, 0x1717, 0xA783, 0x1717, 0x1717, 0x1717, 0xD258, 0x1758, 0x1717, 0x1717,
                    0xCB17, 0x1783, 0x1717, 0x1717, 0x5817, 0x58D2, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0xF617,
                    0x1717, 0x1717, 0x1717, 0x17F6, 0x1717, 0x1717, 0xF617, 0x1717, 0x1717, 0x1717,
                    0xF617, 0x1717, 0x1717, 0x1717, 0x1717, 0xF6F6, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0xF6F6, 0x17F6,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0xF6F6, 0x1717, 0x1717, 0x1717, 0x1717, 0x17F6,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0xF617, 0x1717, 0x1717, 0x1717, 0xF658,
                    0x1717, 0x1717, 0x1717, 0xF659, 0x1717, 0x1717, 0x1717, 0xF683, 0x1717, 0x1717,
                    0x1717, 0xA7A7, 0x1717, 0x1717, 0x5817, 0x7DD2, 0x1717, 0x1717, 0x8317, 0x17D2,
                    0x1717, 0x1717, 0xD258, 0x1783, 0x1717, 0xA7A7, 0x1717, 0x1717, 0x1717, 0xD218,
                    0x1783, 0x1717, 0x1717, 0x5817, 0x28E9, 0x1717, 0x1717, 0x9A17, 0xCC27, 0x1783,
                    0x1717, 0x9A52, 0x5817, 0xA7D2, 0x1717, 0x1717, 0x1717, 0xA718, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x17F6, 0x1717, 0x1717, 0x1717, 0xF617, 0xF6F6, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1758, 0x1717, 0x1717, 0x1717, 0x83D2, 0x1758, 0x1717, 0x1717,
                    0xD258, 0xA7D2, 0x5983, 0x5258, 0x1717, 0x8358, 0xF6CC, 0xF0F6, 0x1717, 0x17F6,
                    0x1717, 0x1717, 0xF617, 0x1717, 0x1717, 0x1717, 0x17F6, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x5817, 0x1776, 0x1717,
                    0x5817, 0xD283, 0x58B8, 0x8359, 0xD2A7, 0x7DD2, 0xF6E2, 0xD2F6, 0x58A7, 0x1717,
                    0x1717, 0x1717, 0xD2A7, 0x1717, 0x1717, 0x8376, 0x58F6, 0x1717, 0x1717, 0xE2BE,
                    0x177D, 0x1717, 0x8317, 0xBED2, 0x1726, 0x1717, 0xF6A7, 0x1759, 0x9A9A, 0x1717,
                    0x58D2, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717, 0x1717,
                    0x1717, 0x1717,};

