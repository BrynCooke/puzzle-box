#ifndef LEVELS
#define LEVELS
#include "level.h"
#define INTRO 0
#define ENTER_CODE 1
#define AUTH_SUCCESS 2
#define AUTH_FAILED 3
#define MORSE_CODE 4
#define LIGHTS_ON 5
#define LIGHT 6
#define DISTANCE 7
#define ENCODED_SUM 8
#define DROP_LINE 9
#define SIMON_SAYS 10
#define DECODE_ROT13 11
#define MAZE 12
#define UPSIDE_DOWN 13
#define VIBRAPHONE 14
#define SOS 15

class Intro: public Level {
protected:

public:

	void tick();
	uint8_t next();

};

class EnterCode: public Level {
protected:
	char _input[5];
	uint8_t _pos;
public:
	void setup();
	void tick();
	uint8_t next();
};

class AuthSuccess: public Level {
protected:

public:

	void setup();

};

class AuthFailed: public Level {
protected:

public:

	void tick();
	uint8_t next();

};

class MorseCode: public Level {
	char _lastKey;

protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class LightsOn: public Level {

protected:

public:
	void setup();
	void tick();
	uint8_t next();

};



class Distance: public Level {

	int _count;
protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class Light: public Level {

	int _count;
protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class Maze: public Level {

private:
	bool _positionLit;
	uint _x = 6;
	uint _y = 1;


protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class UpsideDown: public Level {
private:
	uint _count;
protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class EncodedSum: public Level {
private:
	char _lastKey;
protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class DropLine: public Level {
private:
	uint _x = 0;
	uint _y = -1;
	uint _score = 0;
protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class DecodeROT13: public Level {
private:
	char _input[6];
	uint8_t _inputSize;
protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class SimonSays: public Level {
private:
	uint8_t _pos;
	uint8_t _last[5];
	uint8_t _sequence[10];
	uint8_t _sequenceSize;
	void playSequence();
protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class Vibraphone: public Level {
private:
	static uint16_t TUNE[];
	static uint16_t NOTES[];
	uint _position;
protected:

public:
	void setup();
	void tick();
	uint8_t next();

};

class Sos: public Level {
private:
	uint _position;
	uint _count;
	char _message[10];
protected:

public:
	void setup();
	void tick();
	uint8_t next();
	uint8_t getDelay();

};

#endif
