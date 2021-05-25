#define COM1 0x04
#define COM2 0x09
#define COM3 0x0c
#define COM4 0x0d
#define COM5 0x0e
#define COM6 0x0f
#define COM7 0x12
#define COM8 0x13
#define COM9 0x14
#define COM10 0x15
#define COM11 0x3b
#define COM12 0x3c
#define COM13 0x3d
#define COM14 0x3e
#define COM15 0x40
#define COM16 0x41
#define COM17 0x42

#define REG_SLOP 0x7a
#define REG_GAM_BASE 0x7b

#define REG_MTX1 0x4f
#define REG_MTX2 0x50
#define REG_MTX3 0x51
#define REG_MTX4 0x52
#define REG_MTX5 0x53
#define REG_MTX6 0x54
#define REG_MTXS 0x58

#define REG_LAST 0xc9

struct regval_list {
  unsigned char reg;
  unsigned char value;
};

const struct regval_list reset[] {
  
  {COM7, 0x80}, // reset
  { 0xff, 0xff }  // END MARKER
  
  };

const struct regval_list qvga_rgb565[]{

  /* resolution and colour format */
  {COM7, 0x04 | 0x10 }, //RGB, qvga
  {COM15, 0x10}, // RGB 565
  {0x8c, 0x00}, // disable rgb 444

  /* qvga */
  {COM14, 0x19},  
  {0x70, 0x20},
  {0x71, 0x20},
  {0x72, 0x11},
  {0x73, 0xf1},
  {0xa2, 0x02},

  /* I've been looking for this for a 1 month - it disable black and white format of image*/
  {0xb0, 0x84},  // magical register that allows colours
  {COM17, 0x04}, // enable DSP color bar
  

  /* Clock pre-scaler */
  {0x6b, 0x00}, // bypass PLL

  /* banding filter - default - not use */

  /*AEC, AGC, AWB */
  {COM8, 0x00}, // disable

  /*i use default settings of sync signals*/
  {COM10, 0x01},

  /*i do not use strobe - i use default settings*/

  /*ABLC*/
  {0xb1, 0x00}, //disable ABLC, i use default settings of BLC
  {0xb5, 0x00}, // stable range of black level is 0
  
  /* i use default settings of WB*/

  /* Gamma curve lines - from Adafruit Ov7670 library */
  {REG_SLOP, 0x20},
  {REG_GAM_BASE, 0x1C},
  {REG_GAM_BASE + 1, 0x28},
  {REG_GAM_BASE + 2, 0x3C},
  {REG_GAM_BASE + 3, 0x55},
  {REG_GAM_BASE + 4, 0x68},
  {REG_GAM_BASE + 5, 0x76},
  {REG_GAM_BASE + 6, 0x80},
  {REG_GAM_BASE + 7, 0x88},
  {REG_GAM_BASE + 8, 0x8F},
  {REG_GAM_BASE + 9, 0x96},
  {REG_GAM_BASE + 10, 0xA3},
  {REG_GAM_BASE + 11, 0xAF},
  {REG_GAM_BASE + 12, 0xC4},
  {REG_GAM_BASE + 13, 0xD7},
  {REG_GAM_BASE + 14, 0xE8},

/* matrix settings*/
  {REG_MTX1, 0x4f},
  {REG_MTX2, 0x42},
  {REG_MTX3, 0x0d},
  {REG_MTX4, 0x13}, 
  {REG_MTX5, 0x25},
  {REG_MTX6, 0x38},
  {REG_MTXS, 0x1e},

/* sharpness control - i use default settings*/

/* De-noise Treeshold is set to 0x00 defautly and is set to manual mode */

/* Auto Color Saturation Adjustment */
{0xc9, 0x0c }, // default value

/* Defect pixel correction */
  {0x76, 0x01}, // disable

/* Lens correction */
  {0x66, 0x00}, // disable lens correction

/* brightness and contrast */
  {0x55, 0x00}, // no brightness adjustment
  {0x56, 0x40}, // no contrast adjustment
  {0x57, 0x80}, // center luminance for contrast control - set manually (defaultly MTX[7] = 0)  
  
/* end */
  { 0xff, 0xff }  // END MARKER
  };
