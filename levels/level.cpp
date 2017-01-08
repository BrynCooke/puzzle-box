#include "level.h"


uint Level::passed[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4 };

uint Level::failed[] = { NOTE_C2, NOTE_D2, NOTE_C2, NOTE_D2, NOTE_C2,
NOTE_D2 };

Level::Level() {
	_completed = false;
}

Level::~Level() {

}

char seps[] = "\n";

void Level::setMessage(uint8_t lineCount, const char** messageLines) {
	 _messageLines = messageLines;
	 _lineCount = lineCount;
}

void Level::setup() {
	lcd.clear();

}

void Level::tick() {
	_tickCount++;
	if (_messageLines && _tickCount >= 15) {
		lcd.setCursor(0, 0);
		lcd.print(_messageLines[_messagePos++]);
		if(_messagePos == _lineCount) {
			_messagePos = 0;;
		}
		_tickCount = 0;
	}

}

uint8_t Level::next() {
	return this;
}

bool Level::completed() {
	return _completed;
}

void Level::play(uint8_t noteCount, uint16_t *notes) {
	for (uint count = 0; count < noteCount; count++) {
		tone(9, notes[count], 100);
		delay(100);
	}
}

uint8_t Level::getDelay() {
	return 100;

}

Adafruit_8x8matrix* Level::matrix(uint x, uint y) {
	if (y >= 16) {
		return &matrix3;
	} else if (y >= 8) {
		return &matrix2;
	} else {
		return &matrix1;
	}
}

bool Level::isSet(uint x, uint y) {
	Adafruit_8x8matrix* m = this->matrix(x, y);
	while (y >= 8) {
		y -= 8;
	}
	return m->getPixel(x, y);
}

void Level::set(uint x, uint y, boolean value) {
	Adafruit_8x8matrix* m = this->matrix(x, y);
	while (y >= 8) {
		y -= 8;
	}

	m->drawPixel(x, y, value);

	m->writeDisplay();
}
