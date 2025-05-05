#include "PWM.h"

PWM::PWM(TimerSelector _timer, PWMChannel _channel) : timer(_timer), channel(_channel), clockFrequency(F_CPU), mode(UNDEFINED), output(NON_INVERTED), prescaler(1), topValue(0), currentFreq(0.0f) {
	configurePin();
}

void PWM::configurePin() {
	switch (timer) {
		case TIMER0:
		if (channel == CHANNEL_A) DDRD |= (1 << DDD6);
		else DDRD |= (1 << DDD5);
		break;
		case TIMER1:
		if (channel == CHANNEL_A) DDRB |= (1 << DDB1);
		else DDRB |= (1 << DDB2);
		break;
		case TIMeR2:
		if (channel == CHANNEL_A) DDRB |= (1 << DDB3);
		else DDRD |= (1 << DDD3);
		break;
	}
}

PWM::~PWM() {
	stop();
}

void PWM::setMode(PWMMode _mode) {
	this->mode = _mode;
}

void PWM::setOutput(PWMOutput _output) {
	this->output = _output;
}

void PWM::setPrescaler(uint16_t _value) {
	prescaler = _value;
}

void PWM::setTopValue(uint16_t _top) {
	topValue = _top;
}


void PWM::setFrequency(uint32_t _frequency) {
	if (timer == TIMER1)
	{
		this->currentFreq = (float)_frequency;
		if (mode == FAST_PWM) {
			topValue = (clockFrequency / (currentFreq * prescaler)) - 1;
			} else if (mode == PHASE_CORRECT_PWM || mode == PHASE_FREQ_CORRECT_PWM) {
			topValue = (clockFrequency / (2 * currentFreq * prescaler)) - 1;
		}
	}
	else {
		if (mode == FAST_PWM) {
			this->currentFreq = clockFrequency/(prescaler * 256);
			} else if (mode == PHASE_CORRECT_PWM || mode == PHASE_FREQ_CORRECT_PWM) {
			this->currentFreq = clockFrequency/(prescaler * 510);
		}
	}
}

void PWM::setDutyCycle(float _percent) {
	if (_percent < 0.0f) _percent = 0.0f;
	else if (_percent > 100.0f) _percent = 100.0f;
	uint16_t compareValue = (uint16_t)(topValue * (_percent / 100.0f));
	setCompareValue(compareValue);
}

void PWM::setPulseWidthMicroseconds(uint16_t _microseconds) {
	float period = 1 / currentFreq * 1e6;
	float compareValue = topValue / period * _microseconds;
	setCompareValue((uint16_t)compareValue);
}

void PWM::setCompareValue(uint16_t _compare) {
	switch (timer) {
		case TIMER0:
		if (channel == CHANNEL_A) OCR0A = _compare;
		else OCR0B = _compare;
		break;
		case TIMER1:
		if (channel == CHANNEL_A) OCR1A = _compare;
		else OCR1B = _compare;
		break;
		case TIMeR2:
		if (channel == CHANNEL_A) OCR2A = _compare;
		else OCR2B = _compare;
		break;
	}
}

void PWM::initTimer0() {
	// Clear current mode
	TCCR0A &= ~(0x03);
	TCCR0B &= ~(0x08);
	
	switch (mode) {
		case FAST_PWM:
			TCCR0A |= (1 << WGM00) | (1 << WGM01);
			TCCR0B |= (1 << WGM02);
		break;
		case PHASE_CORRECT_PWM:
			TCCR0A |= (1 << WGM00);
			TCCR0B |= (1 << WGM02);
		break;
		case _8_BIT_FAST_PWM:
		TCCR0A |= (1 << WGM00) | (1 << WGM01);
		break;
		case _8_BIT_PHASE_CORRECT_PWM:
		TCCR0A |= (1 << WGM00);
		break;
	}
	if (output == NON_INVERTED)
	{
		if (channel == CHANNEL_A) TCCR0A |= (1 << COM0A1);
		else TCCR0A |= (1 << COM0B1);
	}
	else {
		if (channel == CHANNEL_A) TCCR0A |= (1 << COM0A0) | (1 << COM0A1);
		else TCCR0A |= (1 << COM0B0) | (1 << COM0B1);
	}
	applyPrescaler();
}

void PWM::initTimer1() {
	// Clear current mode
	TCCR1A &= ~(0x03);
	TCCR1B &= ~(0x18);

	switch (mode) {
		case FAST_PWM:
			TCCR1A |= (1 << WGM11);
			TCCR1B |= (1 << WGM12) | (1 << WGM13);
			ICR1 = topValue;
		break;
		case PHASE_CORRECT_PWM:
			TCCR1A |= (1 << WGM11);
			TCCR1B |= (1 << WGM13);
			ICR1 = topValue;
		break;
		case PHASE_FREQ_CORRECT_PWM:
			TCCR1B |= (1 << WGM13);
			ICR1 = topValue;
		break;
		case _8_BIT_FAST_PWM:
			TCCR1A |= (1 << WGM10);
			TCCR1B |= (1 << WGM12);
		break;
		case _8_BIT_PHASE_CORRECT_PWM:
			TCCR1A |= (1 << WGM10);
		break;
		case _9_BIT_FAST_PWM:
			TCCR1A |= (1 << WGM11);
			TCCR1B |= (1 << WGM12);
		break;
		case _9_BIT_PHASE_CORRECT_PWM:
			TCCR1A |= (1 << WGM11);
		break;
		case _10_BIT_FAST_PWM:
			TCCR1A |= (1 << WGM10) | (1 << WGM11);
			TCCR1B |= (1 << WGM12);
		break;
		case _10_BIT_PHASE_CORRECT_PWM:
			TCCR1A |= (1 << WGM10) | (1 << WGM11);
		break;
	}
	if (output == NON_INVERTED)
	{
		if (channel == CHANNEL_A) TCCR1A |= (1 << COM1A1);
		else TCCR1A |= (1 << COM1B1);
	}
	else {
		if (channel == CHANNEL_A) TCCR1A |= (1 << COM1A0) | (1 << COM1A1);
		else TCCR1A |= (1 << COM1B0) | (1 << COM1B1);
	}
	applyPrescaler();
}


void PWM::initTimer2() {
	// Clear current mode
	TCCR2A &= ~(0x03);
	TCCR2B &= ~(0x08);
	
	switch (mode) {
		case FAST_PWM:
			TCCR2A |= (1 << WGM21) | (1 << WGM20);
			TCCR2B |= (1 << WGM22);
		break;
		case PHASE_CORRECT_PWM:
			TCCR2A |= (1 << WGM20);
			TCCR2B |= (1 << WGM22);
		break;
		case _8_BIT_FAST_PWM:
			TCCR2A |= (1 << WGM20) | (1 << WGM21);
		break;
		case _8_BIT_PHASE_CORRECT_PWM:
			TCCR2A |= (1 << WGM20);
		break;
	}
	if (output == NON_INVERTED)
	{
		if (channel == CHANNEL_A) TCCR2A |= (1 << COM2A1);
		else TCCR2A |= (1 << COM2B1);
	}
	else {
		if (channel == CHANNEL_A) TCCR2A |= (1 << COM2A0) | (1 << COM2A1);
		else TCCR2A |= (1 << COM2B0) | (1 << COM2B1);
	}
	applyPrescaler();
}


void PWM::applyPrescaler() {
	uint8_t cs_bits = 0;

	switch (prescaler) {
		case 1:   cs_bits = 0x01; break;
		case 8:   cs_bits = 0x02; break;
		case 64:  cs_bits = 0x03; break;
		case 256: cs_bits = 0x04; break;
		case 1024:cs_bits = 0x05; break;
		default:  cs_bits = 0x01; break; // valor por defecto = 1
	}

	switch (timer) {
		case TIMER0:
		TCCR0B &= ~(0x07); // Limpia CS02, CS01, CS00
		TCCR0B |= (cs_bits & 0x07);
		break;
		case TIMER1:
		TCCR1B &= ~(0x07); // Limpia CS12, CS11, CS10
		TCCR1B |= (cs_bits & 0x07);
		break;
		case TIMeR2:
		TCCR2B &= ~(0x07); // Limpia CS22, CS21, CS20
		TCCR2B |= (cs_bits & 0x07);
		break;
	}
}

void PWM::start() {
	if (mode == PWMMode::UNDEFINED) {
		mode = PWMMode::FAST_PWM;
	}
	if (topValue == 0) {
		topValue = 0xFF;
	}
	applyPrescaler(); // Si se hab�a detenido, reanuda el prescaler
	switch(timer) {
		case TIMER0:
		initTimer0();
		break;
		case TIMER1:
		initTimer1();
		break;
		case TIMeR2:
		initTimer2();
		break;
	}
}

void PWM::stop() {
	switch (timer) {
		case TIMER0:
			if (channel == CHANNEL_A) TCCR0A &= ~(1 << COM0A0 | 1 << COM0A1);
			else TCCR0A &= ~(1 << COM0B0 | 1 << COM0B1);
		break;
		case TIMER1:
			if (channel == CHANNEL_A) TCCR1A &= ~(1 << COM1A0 | 1 << COM1A1);
			else TCCR1A &= ~(1 << COM1B0 | 1 << COM1B1);
		break;
		case TIMeR2:
			if (channel == CHANNEL_A) TCCR2A &= ~(1 << COM2A0 | 1 << COM2A1);
			else TCCR2A &= ~(1 << COM2B0 | 1 << COM2B1);
		break;
	}
}
