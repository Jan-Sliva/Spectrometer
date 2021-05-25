#define DATA_DDR      DDRF
#define DATA_PORT     PORTF
#define DATA_PINS     PINF

// control pins --------------------
#define OV_VSYNC            _BV(4) //PINE
#define OV_VSYNC_digital    2

#define FIFO_WREN          _BV(3)          // Write Enable (active low), PINH
#define FIFO_RCLK          _BV(6)          // Read clock, PINH
#define FIFO_WRST          _BV(4)          // Write Reset (active low), PINH
#define FIFO_RRST          _BV(5)          // Read Reset (active low), PINB

#define WREN_DDR          DDRH
#define WREN_PORT         PORTH

#define RCLK_DDR          DDRH
#define RCLK_PORT         PORTH

#define WRST_DDR          DDRH
#define WRST_PORT         PORTH

#define RRST_DDR          DDRB
#define RRST_PORT         PORTB

#define VSYNC_PIN         PINE
#define VSYNC_DDR         DDRE
#define VSYNC_PORT        PORTE

#define GET_VSYNC          (VSYNC_PIN & OV_VSYNC) 

#define DISABLE_RRST        RRST_PORT|=FIFO_RRST
#define ENABLE_RRST          RRST_PORT&=~FIFO_RRST 

#define DISABLE_WRST        WRST_PORT|=FIFO_WRST
#define ENABLE_WRST          WRST_PORT&=~FIFO_WRST 

#define SET_RCLK_H            RCLK_PORT|=FIFO_RCLK   
#define SET_RCLK_L          RCLK_PORT&=~FIFO_RCLK

#define ENABLE_WREN         WREN_PORT |= FIFO_WREN
#define DISABLE_WREN         WREN_PORT &= ~FIFO_WREN


// *************************************
void static inline Pins_config() {
  DATA_DDR  = 0;  // set pins as INPUTS
  
  WREN_DDR  |= FIFO_WREN; // set pin as OUTPUT
  RCLK_DDR  |= FIFO_RCLK; // set pin as OUTPUT
  RRST_DDR  |= FIFO_RRST; // set pin as OUTPUT
  WRST_DDR  |= FIFO_WRST; // set pin as OUTPUT
  
  pinMode(OV_VSYNC_digital, INPUT_PULLUP);
}
