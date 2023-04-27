#include <Arduino.h>

const int AIA = 5; // (pwm) pin 5 connected to pin A-IA
const int AIB = 6; // (pwm) pin 6 connected to pin A-IB
const int BIA = 10; // (pwm) pin 10 connected to pin B-IA
const int BIB = 11; // (pwm) pin 11 connected to pin B-IB

void motorSetup();
void backward(byte speed);
void forward(byte speed);
void STOP();