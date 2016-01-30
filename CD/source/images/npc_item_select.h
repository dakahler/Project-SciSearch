/**********************************************\
*       npc_item_select.h                                   *
*          by dovotos pcx->gba program         *
/**********************************************/
#define  npc_item_select_WIDTH   16
#define  npc_item_select_HEIGHT  16


const u16 npc_item_selectData[] = {
                    0xFAFA, 0xFAFA, 0xFAFA, 0xFAFA, 0x17FA, 0x1717, 0xDD17, 0xDDDD, 0x17FA, 0x1717,
                    0xDD17, 0x1717, 0x17FA, 0x1717, 0xDD17, 0x1717, 0x17FA, 0x1717, 0xDD17, 0x1717,
                    0x17FA, 0xDD17, 0xDD17, 0xDDDD, 0x17FA, 0xDD17, 0x17DD, 0xDD17, 0x17FA, 0x1717,
                    0xDDDD, 0xDD17, 0xFAFA, 0xFAFA, 0xFAFA, 0xFAFA, 0xDDDD, 0x17DD, 0x1717, 0xFA17,
                    0x1717, 0x17DD, 0x1717, 0xFA17, 0x1717, 0x17DD, 0x1717, 0xFA17, 0x1717, 0x17DD,
                    0x1717, 0xFA17, 0xDDDD, 0x17DD, 0x1717, 0xFA17, 0x1717, 0x1717, 0xDDDD, 0xFA17,
                    0x1717, 0xDD17, 0x17DD, 0xFA17, 0x17FA, 0x1717, 0xDD17, 0xDDDD, 0x17FA, 0x1717,
                    0x1717, 0xDD17, 0x17FA, 0x1717, 0x1717, 0xDD17, 0x17FA, 0x1717, 0x1717, 0xDDDD,
                    0x17FA, 0x1717, 0xFF17, 0xFFFF, 0x17FA, 0x1717, 0xDD17, 0x17DD, 0x17FA, 0x1717,
                    0xDD17, 0x1717, 0xFAFA, 0xFAFA, 0xFAFA, 0xFAFA, 0xDDDD, 0xDDDD, 0x1717, 0xFA17,
                    0xDDFF, 0x1717, 0x1717, 0xFA17, 0x17FF, 0x1717, 0x1717, 0xFA17, 0x17FF, 0x1717,
                    0x1717, 0xFA17, 0xFFFF, 0xFFFF, 0x1717, 0xFA17, 0xDDFF, 0x17DD, 0x1717, 0xFA17,
                    0x17FF, 0x17DD, 0x1717, 0xFA17, 0xFAFA, 0xFAFA, 0xFAFA, 0xFAFA,};

const u16 npc_item_selectPalette[] = {
                    0x0000, 0x0842, 0x1084, 0x2108, 0x294A, 0x39CE, 0x4631, 0x56B5, 0x5EF7, 0x6F7B,
                    0x77BD, 0x0800, 0x1000, 0x2000, 0x2800, 0x3800, 0x4400, 0x5400, 0x5C00, 0x6C00,
                    0x7400, 0x0040, 0x0080, 0x0100, 0x0140, 0x01C0, 0x0220, 0x02A0, 0x02E0, 0x0360,
                    0x03A0, 0x0002, 0x0004, 0x0008, 0x000A, 0x000E, 0x0011, 0x0015, 0x0017, 0x001B,
                    0x001D, 0x1800, 0x3000, 0x4C00, 0x6400, 0x7C00, 0x00C0, 0x18C0, 0x30C0, 0x4CC0,
                    0x64C0, 0x7CC0, 0x0180, 0x1980, 0x3180, 0x4D80, 0x6580, 0x7D80, 0x0260, 0x1A60,
                    0x3260, 0x4E60, 0x6660, 0x7E60, 0x0320, 0x1B20, 0x3320, 0x4F20, 0x6720, 0x7F20,
                    0x03E0, 0x1BE0, 0x33E0, 0x4FE0, 0x67E0, 0x7FE0, 0x0006, 0x1806, 0x3006, 0x4C06,
                    0x6406, 0x7C06, 0x00C6, 0x18C6, 0x30C6, 0x4CC6, 0x64C6, 0x7CC6, 0x0186, 0x1986,
                    0x3186, 0x4D86, 0x6586, 0x7D86, 0x0266, 0x1A66, 0x3266, 0x4E66, 0x6666, 0x7E66,
                    0x0326, 0x1B26, 0x3326, 0x4F26, 0x6726, 0x7F26, 0x03E6, 0x1BE6, 0x33E6, 0x4FE6,
                    0x67E6, 0x7FE6, 0x000C, 0x180C, 0x300C, 0x4C0C, 0x640C, 0x7C0C, 0x00CC, 0x18CC,
                    0x30CC, 0x4CCC, 0x64CC, 0x7CCC, 0x018C, 0x198C, 0x318C, 0x4D8C, 0x658C, 0x7D8C,
                    0x026C, 0x1A6C, 0x326C, 0x4E6C, 0x666C, 0x7E6C, 0x032C, 0x1B2C, 0x332C, 0x4F2C,
                    0x672C, 0x7F2C, 0x03EC, 0x1BEC, 0x33EC, 0x4FEC, 0x67EC, 0x7FEC, 0x0013, 0x1813,
                    0x3013, 0x4C13, 0x6413, 0x7C13, 0x00D3, 0x18D3, 0x30D3, 0x4CD3, 0x64D3, 0x7CD3,
                    0x0193, 0x1993, 0x3193, 0x4D93, 0x6593, 0x7D93, 0x0273, 0x1A73, 0x3273, 0x4E73,
                    0x6673, 0x7E73, 0x0333, 0x1B33, 0x3333, 0x4F33, 0x6733, 0x7F33, 0x03F3, 0x1BF3,
                    0x33F3, 0x4FF3, 0x67F3, 0x7FF3, 0x0019, 0x1819, 0x3019, 0x4C19, 0x6419, 0x7C19,
                    0x00D9, 0x18D9, 0x30D9, 0x4CD9, 0x64D9, 0x7CD9, 0x0199, 0x1999, 0x3199, 0x4D99,
                    0x6599, 0x7D99, 0x0279, 0x1A79, 0x3279, 0x4E79, 0x6679, 0x7E79, 0x0339, 0x1B39,
                    0x3339, 0x4F39, 0x6739, 0x7F39, 0x03F9, 0x1BF9, 0x33F9, 0x4FF9, 0x67F9, 0x7FF9,
                    0x001F, 0x181F, 0x301F, 0x4C1F, 0x641F, 0x7C1F, 0x00DF, 0x18DF, 0x30DF, 0x4CDF,
                    0x64DF, 0x7CDF, 0x019F, 0x199F, 0x319F, 0x4D9F, 0x659F, 0x7D9F, 0x027F, 0x1A7F,
                    0x327F, 0x4E7F, 0x667F, 0x7E7F, 0x033F, 0x1B3F, 0x333F, 0x4F3F, 0x673F, 0x7F3F,
                    0x03FF, 0x1BFF, 0x33FF, 0x4FFF, 0x67FF, 0x7FFF,};