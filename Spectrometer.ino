#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Arduino.h"

#define TFT_DC  A13
#define TFT_CS  A15
#define TFT_MOSI 51
#define TFT_CLK 52
#define TFT_RST A14
#define TFT_MISO 50
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);


#include "Fifo.h"
#include "Sensor_config.h"
#include <Wire.h>

static const uint16_t fW = 320;
static const uint16_t fH = 240;

uint16_t rowBuf[fW];
byte byteBuf[fW*2];
bool NewFrame = false;
bool SendData = false;
byte ReadByte;

void setup()
{
  Serial.begin(500000);
  
  tft.begin();
  tft.setRotation(3);
  yield();

  Pins_config();
  Sensor_config();
  fifo_rrst();
  fifo_wrst();
  delay(100);
}

void loop()
{ 
  
    while (!GET_VSYNC); // wait for a frame to end
    while (GET_VSYNC);  // wait for a new frame to start
    ENABLE_WREN; //start of reading a frame
    while (!GET_VSYNC); // wait for a frame to end
    DISABLE_WREN; // end of reading a frame

    
    while (Serial.available()){
      ReadByte = Serial.read();
        if (ReadByte == 1){
          SendData = true;
        }
        else if (ReadByte == 2){
          SendData = false;
        }
      }
    if(!Serial){
      SendData = false;
    }

    fifo_rrst();
    
    //skip first byte
    SET_RCLK_H;
    delayMicroseconds(8);
    SET_RCLK_L;
    
    if (SendData){
      for (int i = 0; i < fH; i++){
         fifo_readTwoBytes(rowBuf, byteBuf, fW);
         tft.drawRGBBitmap(0, i, rowBuf, fW, 1);
         Serial.flush();
         Serial.write(byteBuf, fW*2);
      }
    }
    else{
      for (int i = 0; i < fH; i++){
         fifo_readTwoBytes(rowBuf, byteBuf, fW);
         tft.drawRGBBitmap(0, i, rowBuf, fW, 1);
      }
    }
    fifo_wrst();
}
