#pragma once

enum class MathOperator {
  NOT_SET, ADD, SUBTRACT, MULTIPLY, DIVIDE
};

class Calculator {
public:
  Calculator();

  void addToCurrentOperand(float number);
  void negateCurrentOperand();
  void squareCurrentOperand();
  void takeSquareRootOfCurrentOperand();
  void enableDecimalPoint();
  void setOperator(MathOperator op);
  void calculate();
  void reset();

  float getCurrentOperand();
  float getPreviousOperand();
  bool isPreviousOperandPresent();
  bool isDecimalPointSet();
  MathOperator getOperator();

private:
  float m_currentOperand;
  float m_previousOperand;
  bool m_decimalPointSet;
  unsigned int m_numDecimalDigits;
  MathOperator m_operator;
};
