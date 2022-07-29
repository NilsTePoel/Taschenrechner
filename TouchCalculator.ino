#include "CalculatorUI.h"
#include "TouchInput.h"

// LCD
uint16_t model = ILI9486;
uint8_t cs = A3;
uint8_t cd = A2;
uint8_t wr = A1;
uint8_t rd = A0;
uint8_t reset = A4;

// Touchscreen
const uint8_t yp = A3;
const uint8_t xm = A2;
const uint8_t ym = 9;
const uint8_t xp = 8;
const uint16_t rxplate = 300;

LCDWIKI_KBV lcd(model, cs, cd, wr, rd, reset);
TouchInput input(xp, yp, xm, ym, rxplate);
CalculatorUI ui(lcd, input); 

void setup() {
  ui.init();
}

void loop() {
  ui.loop();

  // Kurze Wartezeit, damit ein Tastendruck nicht mehrmals erkannt wird
  delay(100);
}
