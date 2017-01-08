#ifndef SETUP
#define SETUP

#include "Arduino.h"
//The setup function is called once at startup of the sketch
#include "pitches.h"
#include <Adafruit_MCP23017.h>
#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <MPU6050.h>
#include <Keypad.h>


#define TRIGGER_PIN  11
#define ECHO_PIN     10
#define MAX_DISTANCE 200

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif

//Keypad
#define I2CADDR 0x20

enum Led {
	Green,
	Yellow,
	Red
};

class I2CKeypad : public Keypad {
public:
	I2CKeypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols) : Keypad(userKeymap, row, col, numRows, numCols) {
	}

	virtual ~I2CKeypad() {

	}

	void pin_mode(byte pinNum, byte mode);
	void pin_write(byte pinNum, boolean level);
	int  pin_read(byte pinNum);
};

extern I2CKeypad keypad;

//Matrix
extern Adafruit_8x8matrix matrix1;
extern Adafruit_8x8matrix matrix2;
extern Adafruit_8x8matrix matrix3;

//LCD
extern LiquidCrystal_I2C lcd; // 0x27 is the I2C bus address for an unmodified backpack

//MCP
extern Adafruit_MCP23017 mcp1;
extern Adafruit_MCP23017 mcp2;

//SONAR
extern NewPing sonar;

//ACCELEROMETER
extern MPU6050 accelgyro;

extern int16_t ax, ay, az;
extern int16_t gx, gy, gz;

void setupMatrices();
void setupLcd();
void setupMcp();
void setupKeypad();
void setupGryo();
void setupLeds();
void setupButtons();

void setButton(uint8_t button, uint8_t value);
bool readButtonLed(uint8_t button);
bool readButton(uint8_t button);
void clearButtons();
void setLed(Led led, uint8_t value);
void clearLeds();
void clearMatrices();
void openLock();



#endif

