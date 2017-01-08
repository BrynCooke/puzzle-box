#include "devices.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = { { '1', '2', '3', 'A' }, { '4', '5', '6', 'B' }, { '7',
		'8', '9', 'C' }, { '*', '0', '#', 'D' } };
byte rowPins[ROWS] = { 8, 9, 10, 11 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 12, 13, 14, 15 }; //connect to the column pinouts of the keypad

I2CKeypad keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//Matrix
Adafruit_8x8matrix matrix1 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix3 = Adafruit_8x8matrix();

//LCD
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7); // 0x27 is the I2C bus address for an unmodified backpack

//MCP
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;

//SONAR
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

//ACCELEROMETER
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setupMatrices() {
	matrix1.begin(0x71); // pass in the address
	matrix2.begin(0x70); // pass in the address
	matrix3.begin(0x74); // pass in the address
	matrix1.clear();
	matrix2.clear();
	matrix3.clear();
	matrix1.setRotation(1);
	matrix2.setRotation(1);
	matrix3.setRotation(1);
	matrix1.writeDisplay();
	matrix2.writeDisplay();
	matrix3.writeDisplay();
}

void setupLcd() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2); // for 16 x 2 LCD module
	lcd.setBacklightPin(3, POSITIVE);
	lcd.setBacklight(HIGH);
}

void setupMcp() {
	mcp1.begin(0);
	mcp2.begin(1);

	//
	mcp2.pinMode(8, OUTPUT);
	mcp2.digitalWrite(8, LOW);

}

void setupLeds() {
	//Setup and  clear the green buttons
	mcp2.pinMode(9, OUTPUT);
	mcp2.pinMode(10, OUTPUT);
	mcp2.pinMode(11, OUTPUT);
	clearLeds();
}

void setupButtons() {
	//Setup and  clear the green buttons
	for (uint8_t i = 3; i < 9; i++) {
		mcp1.pinMode(i, OUTPUT);
		pinMode(i, INPUT);
	}clearButtons
	();
}

void setupKeypad() {

}

void setupGryo() {
	Wire.begin();
	accelgyro.initialize();
}

void clearButtons() {
	for (uint8_t count = 0; count < 5; count++) {
		setButton(count, LOW);
	}
}

void setButton(uint8_t button, uint8_t value) {
	if (button < 5) {
		mcp1.digitalWrite(button + 3, value);
	}
}

bool readButtonLed(uint8_t button) {
	if (button < 5) {
		return mcp1.digitalRead(button + 3) == HIGH;
	}
	return false;
}

bool readButton(uint8_t button) {
	if (button < 5) {
		if (button > 2) {
			button++;
		}
		return digitalRead(button + 3) == HIGH;
	}
	return false;
}

void clearLeds() {
	for (uint8_t count = 0; count < 3; count++) {
		setLed(static_cast<Led>(count), LOW);
	}
}

void setLed(Led led, uint8_t value) {
	if (led < 3) {
		mcp2.digitalWrite(led + 9, value);
	}
}

void openLock() {
	mcp2.digitalWrite(8, HIGH);
	delay(10000);
	mcp2.digitalWrite(8, LOW);
}

void I2CKeypad::pin_mode(byte pinNum, byte mode) {
	if (mode == INPUT_PULLUP) {
		mcp1.pinMode(pinNum, INPUT);
		mcp1.pullUp(pinNum, HIGH);
	} else {
		mcp1.pinMode(pinNum, mode);
	}
}
void I2CKeypad::pin_write(byte pinNum, boolean level) {
	mcp1.digitalWrite(pinNum, level);
}
int I2CKeypad::pin_read(byte pinNum) {
	return mcp1.digitalRead(pinNum);
}

void clearMatrices() {
	matrix1.clear();
	matrix2.clear();
	matrix3.clear();
	matrix1.writeDisplay();
	matrix2.writeDisplay();
	matrix3.writeDisplay();
}

