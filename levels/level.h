#ifndef LEVEL
#define LEVEL
#include "../devices.h"
class Level {

protected:

	static uint16_t passed[];

	static uint16_t failed[];

	const char** _messageLines;
	uint8_t _messagePos;
	uint8_t _lineCount;

	bool _completed;
	uint8_t _tickCount = 15;

	void setMessage(uint8_t lineCount, const char** messageLines);
	Adafruit_8x8matrix* matrix(uint x, uint y);
	bool isSet(uint x, uint y);
	void set(uint x, uint y, boolean value);
public:
	Level();
	virtual ~Level();
	virtual void setup();
	virtual void tick();
	virtual uint8_t getDelay();
	bool completed();
	virtual uint8_t next();
	void play(uint8_t noteCount, uint16_t *notes);
};

#endif
