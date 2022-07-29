#pragma once

#include <TouchScreen.h>
#include <Arduino.h>

#include "Input.h"

// Diese Bibliothek ermöglicht es, den Touchscreen zusammen mit dem Display zu benutzen.
// Die Methoden der TouchScreen-Bibliothek können nicht direkt verwendet werden, da sich der Touchscreen Pins mit 
// dem Display teilt und diese anschließend wieder auf den vom Display erwarteten Stand zurückgesetzt werden müssen.
class TouchInput : public Input {
public:
  TouchInput(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplates);

  void checkForInput();
  bool hasInput() const;
  Point getPressedPoint(uint8_t numRows, uint8_t numCols) const;

private:
  const uint8_t m_yp;
  const uint8_t m_xm;
  TouchScreen m_touchScreen;
  TSPoint m_touchPoint;
};
