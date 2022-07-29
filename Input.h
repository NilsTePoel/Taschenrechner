#pragma once

struct Point {
  uint8_t row;
  uint8_t col;
};

// Interface für eine allgemeine Eingabe
// Es sind verschiedene Implementierungen möglich, z. B. Toucheingabe oder Eingabe über Knöpfe
class Input {
public:
  virtual void checkForInput() = 0;
  virtual bool hasInput() const = 0;
  virtual Point getPressedPoint(uint8_t numRows, uint8_t numCols) const = 0;
};
