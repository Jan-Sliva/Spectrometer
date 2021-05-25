#include "Pins_config.h"

void fifo_readTwoBytes(uint16_t *destBuf, byte *byteBuf, unsigned long TwonBytes)
{
  uint16_t i;
    while (TwonBytes > 0) {
        SET_RCLK_H;
        delayMicroseconds(8);
        i = (uint16_t)DATA_PINS;
        *byteBuf++ = (byte)DATA_PINS;
        SET_RCLK_L;
        delayMicroseconds(15);

        i <<= 8;

        SET_RCLK_H;
        delayMicroseconds(8);
        *destBuf++ = i|(uint16_t)DATA_PINS;
        *byteBuf++ = (byte)DATA_PINS;
        SET_RCLK_L;
        delayMicroseconds(15);
        
        TwonBytes--;
    }
}


// Reset the fifo read pointer 
void fifo_rrst(void)
{
      ENABLE_RRST;
    delayMicroseconds(10);
    SET_RCLK_H;
    delayMicroseconds(10);
    SET_RCLK_L;
    delayMicroseconds(10);
    DISABLE_RRST;
}


// Reset the fifo write pointer 
void fifo_wrst(void)
{
    ENABLE_WREN;
    delayMicroseconds(10);
    ENABLE_WRST;
    delayMicroseconds(10);
    DISABLE_WREN;
    delayMicroseconds(10);
    DISABLE_WRST;
    delayMicroseconds(10);
}
