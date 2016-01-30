#ifndef __newArray__
#define __newArray__
#define newArray_WIDTH 16
#define newArray_HEIGHT 16

const USHORT newArraypal[] = {
         0x0000,0x0842,0x1084,0x2108,0x294a,0x39ce,0x4631,0x56b5,0x5ef7,0x6f7b,0x77bd,0x0800,0x1000,0x2000,0x2800,0x3800,0x4400,
         0x5400,0x5c00,0x6c00,0x7400,0x0040,0x0080,0x0100,0x0140,0x01c0,0x0220,0x02a0,0x02e0,0x0360,0x03a0,0x0002,0x0004,0x0008,
         0x000a,0x000e,0x0011,0x0015,0x0017,0x001b,0x001d,0x1800,0x3000,0x4c00,0x6400,0x7c00,0x00c0,0x18c0,0x30c0,0x4cc0,0x64c0,
         0x7cc0,0x0180,0x1980,0x3180,0x4d80,0x6580,0x7d80,0x0260,0x1a60,0x3260,0x4e60,0x6660,0x7e60,0x0320,0x1b20,0x3320,0x4f20,
         0x6720,0x7f20,0x03e0,0x1be0,0x33e0,0x4fe0,0x67e0,0x7fe0,0x0006,0x1806,0x3006,0x4c06,0x6406,0x7c06,0x00c6,0x18c6,0x30c6,
         0x4cc6,0x64c6,0x7cc6,0x0186,0x1986,0x3186,0x4d86,0x6586,0x7d86,0x0266,0x1a66,0x3266,0x4e66,0x6666,0x7e66,0x0326,0x1b26,
         0x3326,0x4f26,0x6726,0x7f26,0x03e6,0x1be6,0x33e6,0x4fe6,0x67e6,0x7fe6,0x000c,0x180c,0x300c,0x4c0c,0x640c,0x7c0c,0x00cc,
         0x18cc,0x30cc,0x4ccc,0x64cc,0x7ccc,0x018c,0x198c,0x318c,0x4d8c,0x658c,0x7d8c,0x026c,0x1a6c,0x326c,0x4e6c,0x666c,0x7e6c,
         0x032c,0x1b2c,0x332c,0x4f2c,0x672c,0x7f2c,0x03ec,0x1bec,0x33ec,0x4fec,0x67ec,0x7fec,0x0013,0x1813,0x3013,0x4c13,0x6413,
         0x7c13,0x00d3,0x18d3,0x30d3,0x4cd3,0x64d3,0x7cd3,0x0193,0x1993,0x3193,0x4d93,0x6593,0x7d93,0x0273,0x1a73,0x3273,0x4e73,
         0x6673,0x7e73,0x0333,0x1b33,0x3333,0x4f33,0x6733,0x7f33,0x03f3,0x1bf3,0x33f3,0x4ff3,0x67f3,0x7ff3,0x0019,0x1819,0x3019,
         0x4c19,0x6419,0x7c19,0x00d9,0x18d9,0x30d9,0x4cd9,0x64d9,0x7cd9,0x0199,0x1999,0x3199,0x4d99,0x6599,0x7d99,0x0279,0x1a79,
         0x3279,0x4e79,0x6679,0x7e79,0x0339,0x1b39,0x3339,0x4f39,0x6739,0x7f39,0x03f9,0x1bf9,0x33f9,0x4ff9,0x67f9,0x7ff9,0x001f,
         0x181f,0x301f,0x4c1f,0x641f,0x7c1f,0x00df,0x18df,0x30df,0x4cdf,0x64df,0x7cdf,0x019f,0x199f,0x319f,0x4d9f,0x659f,0x7d9f,
         0x027f,0x1a7f,0x327f,0x4e7f,0x667f,0x7e7f,0x033f,0x1b3f,0x333f,0x4f3f,0x673f,0x7f3f,0x03ff,0x1bff,0x33ff,0x4fff,0x67ff,
         0x7fff};

const USHORT newArraydata[] = {
         0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,
         0xa1a1,0xa1a1,0xfafa,0xfafa,0xa1fa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfaa1,0xa1fa,0xa1a1,0xfafa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,
         0xfaa1,0xa1fa,0xa1a1,0xfafa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfaa1,0xa1fa,0xa1a1,0xfafa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfaa1,
         0xfafa,0xa1a1,0xa1fa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfafa,0xfafa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfaa1,
         0xfafa,0xa1fa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1fa,0xfaa1,0xfafa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfaa1,0xa1fa,0xa1a1,
         0xfafa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfaa1,0xa1fa,0xa1a1,0xfafa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfaa1,0xa1fa,0xa1a1,0xfafa,
         0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xfafa,0xfafa,0xa1fa,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,
         0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1,0xa1a1};

#endif
