//
// Example of displaying 1 or 2 touch points
// on a SSD1306 128x64 OLED display
//
// Assumes that the display uses the default I2C
// address of 0x3c and that both the FT6236 and OLED
// are sharing the same I2C bus
//
// written by Larry Bank
// March 14, 2023
//
#include <FT6236G.h>
#include <OneBitDisplay.h>

#define I2C_SCL -1
#define I2C_SDA -1

ONE_BIT_DISPLAY obd;
FT6236G ct; // capacitive touch

int getTouch(uint16_t *pPoints)
{
  TOUCHINFO ti;
  if (ct.getSamples(&ti) != FT_SUCCESS)
     return 0; // something went wrong
    if (pPoints) {
      // swap X/Y since the display is used 90 degrees rotated
      pPoints[0] = ti.x[0];
      pPoints[1] = ti.y[0]; 
      pPoints[2] = ti.x[1];
      pPoints[3] = ti.y[1];
    }
  return ti.count;
} /* getTouch() */

void setup() {
  obd.I2Cbegin(OLED_128x64);
  obd.fillScreen(OBD_WHITE);
  obd.setFont(FONT_12x16);
  obd.print("FT6x36 Demo");
  ct.init(I2C_SDA, I2C_SCL, false, 400000);
} /* setup() */

void loop() {
 uint16_t points[4];
 int i;

 while (1) {
   if (i = getTouch(points)) {
      obd.setCursor(0,24);
      obd.printf("A %d, %d   \n", points[0], points[1]);
      if (i == 2) {
        obd.printf("B %d, %d   \n", points[2], points[3]);
      } else {
        obd.printf("B -, -     \n");
      }
   } else {
      obd.setCursor(0,24);
      obd.printf("A -, -     \n");
      obd.printf("B -, -     \n");    
   }
 }
} /* loop() */