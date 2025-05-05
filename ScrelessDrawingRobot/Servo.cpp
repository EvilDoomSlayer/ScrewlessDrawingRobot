/*
 * Servo.cpp
 *
 * Created: 22/04/2025 02:26:17 p. m.
 *  Author: alexy
 */ 

#include "Servo.h"

Servo::Servo(TimerSelector timer, PWMChannel channel): PWM(timer, channel), minPulse(1000), maxPulse(2000) {}

void Servo::init() {
	// Configuracion inicial tipica para servos
	setMode(PHASE_CORRECT_PWM);
	setOutput(NON_INVERTED);
	setPrescaler(8);
	setFrequency(50); // 50 Hz para servos (20 ms de periodo)
	start();
}

void Servo::setPulseRange(uint16_t min, uint16_t max) {
	if (min < max) {
		minPulse = min;
		maxPulse = max;
	}
	minPulse = min;
	maxPulse = max;
}

uint16_t Servo::angleToPulseWidth(uint16_t angle) {
	return minPulse + ((uint32_t)(maxPulse - minPulse) * angle) / 180;
}

void Servo::setAngle(uint8_t angle) {
	if (angle > 180) angle = 180;
	uint16_t pulseWidth = angleToPulseWidth(angle);
	setPulseWidthMicroseconds(pulseWidth);
}

void Servo::detach() {
	stop();
}

