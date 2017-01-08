#include "levels.h"

void Intro::tick() {
	lcd.clear();
	lcd.print("Vault-Tec");
	lcd.setCursor(0, 1);        // go to start of 2nd line
	lcd.print("Initialising");
	delay(3000);
	lcd.clear();
	_completed = true;
}

uint8_t Intro::next() {
	return ENTER_CODE;
}

void EnterCode::setup() {
	lcd.clear();
	lcd.print("Enter code");
	lcd.setCursor(0, 1);        // go to start of 2nd line
	lcd.print("> ");
}

void EnterCode::tick() {
	char key = keypad.getKey();
	if (key != NO_KEY) {
		_input[_pos++] = key;
		lcd.print(key);
	}
	if (_pos == 4) {
		_completed = true;
	}
}

uint8_t EnterCode::next() {

	if (strcmp(_input, "5603") == 0) {
		play(5, passed);
		return AUTH_SUCCESS;
	} else {
		play(6, failed);
		return AUTH_FAILED;
	}

}

void AuthSuccess::setup() {
	lcd.clear();
	lcd.print("Authorised");
	openLock();
	lcd.clear();
	lcd.setBacklight(LOW);

}

void AuthFailed::tick() {
	lcd.clear();
	lcd.print("Authorisation");
	lcd.setCursor(0, 1);        // go to start of 2nd line
	lcd.print("FAILED");
	delay(3000);
	lcd.clear();
	lcd.print("Verify identity");
	lcd.setCursor(0, 1);        // go to start of 2nd line
	delay(3000);
	lcd.clear();
	_completed = true;
}

uint8_t AuthFailed::next() {
	return MORSE_CODE;
}

const char* MORSE_CODE_MESSAGE[] = { "Lost at sea     ", "current position",
		"-.-.            ", "... . ...- . -. " };

void MorseCode::setup() {

	setMessage(4, MORSE_CODE_MESSAGE);
}

void MorseCode::tick() {
	Level::tick();
	char key = keypad.getKey();
	if (key != NO_KEY) {

		if (_lastKey == 'C' && key == '7') {
			_completed = true;
		}
		_lastKey = key;
	}
}

uint8_t MorseCode::next() {
	play(5, passed);
	return LIGHTS_ON;
}

const char* LIGHTS_ON_MESSAGE[] = { "When you cast 5 ", "shadows you may ",
		"pass            " };
void LightsOn::setup() {
	Level::setup();

	setMessage(3, LIGHTS_ON_MESSAGE);
	clearButtons();
}

void LightsOn::tick() {
	Level::tick();
	int out = 32;
	if (readButton(0)) {
		out ^= 19;
	}
	if (readButton(1)) {
		out ^= 21;
	}
	if (readButton(2)) {
		out ^= 28;
	}
	if (readButton(3)) {
		out ^= 5;
	}
	if (readButton(4)) {
		out ^= 3;
	}

	boolean button0 = (out >> 0) & 1;
	boolean button1 = (out >> 1) & 1;
	boolean button2 = (out >> 2) & 1;
	boolean button3 = (out >> 3) & 1;
	boolean button4 = (out >> 4) & 1;

	setButton(0, button0);
	setButton(1, button1);
	setButton(2, button2);
	setButton(3, button3);
	setButton(4, button4);

	if (button0 && button1 && button2 && button3 && button4) {
		_completed = true;
	}

}

uint8_t LightsOn::next() {
	play(5, passed);
	clearButtons();
	return LIGHT;
}

void Distance::setup() {
	lcd.clear();
}

void Distance::tick() {
	int distance = sonar.ping_cm(100);
	lcd.setCursor(0, 0);

	if (distance > 25 || distance == 0) {
		lcd.print("Too far       ");
		_count = 0;
	} else if (distance < 20) {
		lcd.print("Too near      ");
		_count = 0;
	} else {
		lcd.print("Just right    ");
		_count++;
	}
	if (_count == 0) {
		setLed(Red, false);
		setLed(Yellow, false);
		setLed(Green, false);
	}
	if (_count > 1) {
		setLed(Red, true);
	}
	if (_count > 10) {
		setLed(Yellow, true);
	}
	if (_count > 20) {
		setLed(Green, true);
		lcd.clear();
		_completed = true;
	}
}

uint8_t Distance::next() {
	play(5, passed);
	clearLeds();
	return ENCODED_SUM;
}

uint8_t shift(uint8_t source) {
	return ((uint8_t) source >> 1) | (source << 7);
}

void Maze::setup() {
	lcd.clear();
	lcd.setBacklight(LOW);
	matrix1.clear();
	matrix1.displaybuffer[0] = shift(0xFF);
	matrix1.displaybuffer[1] = shift(0xA0);
	matrix1.displaybuffer[2] = shift(0x8D);
	matrix1.displaybuffer[3] = shift(0xB9);
	matrix1.displaybuffer[4] = shift(0xA3);
	matrix1.displaybuffer[5] = shift(0xAC);
	matrix1.displaybuffer[6] = shift(0xA1);
	matrix1.displaybuffer[7] = shift(0xFF);
	matrix1.writeDisplay();
	matrix2.displaybuffer[0] = shift(0xFF);
	matrix2.displaybuffer[1] = shift(0x31);
	matrix2.displaybuffer[2] = shift(0x8C);
	matrix2.displaybuffer[3] = shift(0xB9);
	matrix2.displaybuffer[4] = shift(0xE3);
	matrix2.displaybuffer[5] = shift(0x2C);
	matrix2.displaybuffer[6] = shift(0x81);
	matrix2.displaybuffer[7] = shift(0xFF);
	matrix2.writeDisplay();
	matrix3.displaybuffer[0] = shift(0xFF);
	matrix3.displaybuffer[1] = shift(0x89);
	matrix3.displaybuffer[2] = shift(0x23);
	matrix3.displaybuffer[3] = shift(0xF9);
	matrix3.displaybuffer[4] = shift(0x8D);
	matrix3.displaybuffer[5] = shift(0x31);
	matrix3.displaybuffer[6] = shift(0xA5);
	matrix3.displaybuffer[7] = shift(0xEF);
	matrix3.writeDisplay();

}

void Maze::tick() {

	_positionLit = !_positionLit;
	char key = keypad.getKey();
	uint currentX = _x;
	uint currentY = _y;

	if (key != NO_KEY) {
		if (key == '4') {
			currentX--;
		}
		if (key == '6') {
			currentX++;
		}
		if (key == '2') {
			currentY--;
		}
		if (key == '8') {
			currentY++;
		}

		if ((currentX != _x || currentY != _y) && !isSet(currentX, currentY)) {
			set(_x, _y, false);
			_x = currentX;
			_y = currentY;
		}
	}

	set(_x, _y, _positionLit);
	if (_x == 7) {
		_completed = true;
		clearMatrices();
	}
}

uint8_t Maze::next() {
	play(5, passed);
	lcd.setBacklight(HIGH);
	return UPSIDE_DOWN;
}

const char* LIGHT_MESSAGE[] = { "You cannot see  ", "me, hear me, or ",
		"touch me. I lie ", "behind the      ", "stars and alter ",
		"what is real.   ", "What am I?      " };
void Light::setup() {
	Level::setup();

	setMessage(7, LIGHT_MESSAGE);

}

void Light::tick() {
	Level::tick();
	int value = analogRead(A0);
	if (value > 700) {
		_completed = true;
	}

}

uint8_t Light::next() {
	play(5, passed);
	return DISTANCE;
}

const char* UPSIDE_DOWN_MESSAGE[] = { "Do you come from", "a land          ",
		"down under      " };

void UpsideDown::setup() {
	Level::setup();
	setMessage(3, UPSIDE_DOWN_MESSAGE);

}

void UpsideDown::tick() {
	Level::tick();
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	if (az > 15000) {
		_count++;
	} else {
		_count = 0;
		clearLeds();
	}
	if (_count > 1) {
		setLed(Red, true);
	}
	if (_count > 10) {
		setLed(Yellow, true);
	}
	if (_count > 20) {
		setLed(Green, true);
		lcd.clear();
		_completed = true;
	}

}

uint8_t UpsideDown::next() {
	play(5, passed);
	clearLeds();
	return SOS;
}

const char* ENCODED_SUM_MESSAGE[] = { "BEGIN    ", "23 8 1 20       ",
		"9 19            ", "14 9 14 5       ", "16 12 21 19     ",
		"19 9 24         ", "END             " };

void EncodedSum::setup() {

	setMessage(7, ENCODED_SUM_MESSAGE);
}

void EncodedSum::tick() {
	Level::tick();
	char key = keypad.getKey();
	if (key != NO_KEY) {

		if (_lastKey == '1' && key == '5') {
			_completed = true;
		}
		_lastKey = key;
	}
}

uint8_t EncodedSum::next() {
	play(5, passed);
	return DROP_LINE;
}

void DropLine::setup() {
	lcd.setBacklight(LOW);
	lcd.clear();
	set(4, 23, true);
}

void DropLine::tick() {
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	if(_x != 4 || _y < 22 - _score) {
		set(_x, _y, false);
	}
	if (_y == 23) {
		_y = -1;
	}
	_y++;
	if (ay < 1000 && _x < 7) {
		_x++;
	}
	if (ay > -1000 && _x > 0) {
		_x--;
	}

	set(_x, _y, true);
	if (_x == 4 && _y == 22 - _score) {
		_score++;
		_x = 0;
		_y = -1;
	}
	if (_score == 7) {
		_completed = true;
	}

}

uint8_t DropLine::next() {
	play(5, passed);
	clearMatrices();
	lcd.setBacklight(HIGH);
	return SIMON_SAYS;
}

void DecodeROT13::setup() {

	lcd.clear();
	lcd.print("GEROYR=Treble");
	lcd.setCursor(0, 1);
	lcd.print("OYNQR=");
}

void DecodeROT13::tick() {
	char key = keypad.getKey();
	if (key != NO_KEY) {
		_input[_inputSize++] = key;
		lcd.print(key);
	}
	if (_inputSize == 5) {
		if (strcmp(_input, "B1AD3") == 0) {
			_completed = true;
		} else {
			play(6, failed);
			setup();
			_inputSize = 0;
		}
	}
}

uint8_t DecodeROT13::next() {
	play(5, passed);
	return MAZE;
}

void SimonSays::setup() {
	lcd.clear();
	playSequence();
}

void SimonSays::tick() {

	for (uint count = 0; count < 5; count++) {
		bool current = readButton(count);
		if (current != _last[count]) {
			_last[count] = current;
			setButton(count, !readButtonLed(count));
			if (_sequence[_pos] == count) {
				_pos++;
				if (_pos == _sequenceSize) {
					if (_sequenceSize == 10) {
						_completed = true;
					} else {
						play(5, passed);
						playSequence();
					}
				}
			} else {
				play(6, failed);
				_sequenceSize = 0;
				playSequence();
			}

		}
	}

}

void SimonSays::playSequence() {
	clearButtons();
	delay(1000);
	_sequence[_sequenceSize++] = random(5);
	lcd.clear();
	lcd.print(11 - _sequenceSize);
	lcd.print(" to go");
	for (uint count = 0; count < _sequenceSize; count++) {
		uint8_t button = _sequence[count];
		setButton(button, !readButtonLed(button));
		delay(1000);
	}
	clearButtons();
	for (uint count = 0; count < 5; count++) {
		_last[count] = readButton(count);
	}
	_pos = 0;
}

uint8_t SimonSays::next() {
	clearButtons();
	play(5, passed);
	return DECODE_ROT13;
}

uint16_t Vibraphone::NOTES[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4,
		NOTE_A4,
		NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5 };

uint16_t Vibraphone::TUNE[] = { NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C4, NOTE_G4 };

void Vibraphone::setup() {
	clearButtons();
	lcd.clear();
	lcd.print("Talk to aliens");
	for (uint count = 0; count < 5; count++) {
		tone(9, TUNE[count], 700);
		delay(700);
	}
	delay(1000);

	for (uint count = 0; count < 5; count++) {
		tone(9, TUNE[count], 700);
		delay(700);
	}
	delay(1000);

	for (uint count = 0; count < 5; count++) {
		tone(9, TUNE[count], 700);
		delay(700);
	}
	delay(1000);
}

void Vibraphone::tick() {

	long distance = sonar.ping_cm(100);

	if (distance > 0 && distance < 50) {
		distance = distance / 4;
		distance = max(distance, 0);
		distance = min(distance, 11);

		if (TUNE[_position] == NOTES[distance]) {
			setButton(4 - _position, true);
			_position++;
		} else {
			clearButtons();
			_position = 0;
			if (TUNE[_position] == NOTES[distance]) {
				setButton(4 - _position, true);
				_position++;
			}
		}
		tone(9, NOTES[distance], 1000);
		delay(1000);
		if (_position == 5) {
			_completed = true;
		}
	}
}

uint8_t Vibraphone::next() {
	play(5, passed);
	clearButtons();
	return AUTH_SUCCESS;
}

void Sos::setup() {

	lcd.clear();
	lcd.print("Emergency at sea");
	lcd.setCursor(0, 1);
	lcd.print("> ");
}

void Sos::tick() {
	Level::tick();

	int value = analogRead(A0);
	if (value > 600) {
		tone(9, NOTE_C4, 100);
		delay(100);
		_count++;
	} else {
		if (_count > 0) {
			if (_count < 3) {
				_message[_position++] = '.';
				lcd.print('.');
			} else {
				_message[_position++] = '-';
				lcd.print('-');
			}
			_count = 0;
		}
	}
	if (_position == 9) {
		if (strcmp(_message, "...---...") == 0) {
			_completed = true;
		} else {
			play(6, failed);
			setup();
			_position = 0;
		}
	}
}

uint8_t Sos::getDelay() {
	return 0;
}

uint8_t Sos::next() {
	play(5, passed);
	return VIBRAPHONE;
}
