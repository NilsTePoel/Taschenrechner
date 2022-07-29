#include "TouchInput.h"

TouchInput::TouchInput(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate)
  : m_yp(yp), m_xm(xm), m_touchScreen(xp, yp, xm, ym, rxplate) {
}

void TouchInput::checkForInput() {
  m_touchPoint = m_touchScreen.getPoint();

  // Pins wieder auf den vom LCD erwarteten Stand zurücksetzen
  pinMode(m_yp, OUTPUT);
  pinMode(m_xm, OUTPUT);
  digitalWrite(m_yp, HIGH);
  digitalWrite(m_xm, HIGH);
}

bool TouchInput::hasInput() const {
  return m_touchPoint.z > 20 && m_touchPoint.z < 1000;
}

Point TouchInput::getPressedPoint(uint8_t numRows, uint8_t numCols) const {
  // Umrechnung in das durch "numRows" und "numCols" festgelegte Koordinatensystem
  int16_t touchRowWidth = 1024 / (numRows + 1);
  int16_t touchColWidth = 1024 / numCols;

  uint8_t row = (numRows - 1) - m_touchPoint.y / touchRowWidth;
  uint8_t col = m_touchPoint.x / touchColWidth;

  return {row, col};
}
