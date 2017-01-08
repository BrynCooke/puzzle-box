#include "devices.h"
#include "levels/level.h"
#include "levels/levels.h"
#include <MemoryFree.h>

Level* level;

void setup() {

	Serial.begin(115200);
	setupMatrices();
	setupLcd();
	setupMcp();
	setupKeypad();
	setupButtons();
	setupLeds();
	setupGryo();
	clearButtons();
	clearLeds();
	level = new Intro();
	level->setup();

}

int counter = 0;
void loop() {

	level->tick();
	if (level->completed()) {
		uint8_t id = level->next();
		delete level;
		switch (id) {
		case INTRO:
			level = new Intro();
			break;
		case ENTER_CODE:
			level = new EnterCode();
			break;
		case AUTH_SUCCESS:
			level = new AuthSuccess();
			break;
		case AUTH_FAILED:
			level = new AuthFailed();
			break;
		case MORSE_CODE:
			level = new MorseCode();
			break;
		case LIGHTS_ON:
			level = new LightsOn();
			break;
		case LIGHT:
			level = new Light();
			break;
		case DISTANCE:
			level = new Distance();
			break;
		case ENCODED_SUM:
			level = new EncodedSum();
			break;
		case DROP_LINE:
			level = new DropLine();
			break;
		case SIMON_SAYS:
			level = new SimonSays();
			break;
		case DECODE_ROT13:
			level = new DecodeROT13();
			break;
		case MAZE:
			level = new Maze();
			break;
		case UPSIDE_DOWN:
			level = new UpsideDown();
			break;
		case VIBRAPHONE:
			level = new Vibraphone();
			break;
		case SOS:
			level = new Sos();
			break;
		}

		level->setup();

	}
	delay(level->getDelay());

}
