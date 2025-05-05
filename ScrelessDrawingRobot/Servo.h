/*
 * Servo.h
 *
 * Created: 22/04/2025 02:26:06 p. m.
 *  Author: alexy
 */ 


#ifndef SERVO_H
#define SERVO_H

#include "PWM.h"

class Servo : public PWM {
	public:
	/**
	 * Constructor de la clase Servo.
	 * @param timer: Seleccion del temporizador (TIMER0, TIMER1 o TIMER2).
	 * @param channel: Canal de salida PWM (CHANNEL_A o CHANNEL_B).
	 */
	Servo(TimerSelector timer, PWMChannel channel);

  /**
	 * Inicializa el temporizador y canal para generar la senial PWM especifica de un servo.
   * Modo: Phase Correct PWM, Prescaler: 8, Frecuencia: 50 Hz (20 ms de periodo).
	 */
  void init();

	/**
	 * Establece el angulo al cual se posicionara el servo.
	 * @param angle: angulo en grados (de 0 a 180).
	 * Internamente se convierte a un ancho de pulso entre minPulse y maxPulse.
	 */
	void setAngle(uint8_t angle);

	/**
	 * Define el rango de pulsos correspondiente a 0deg y 180deg del servo.
	 * @param min: Pulso minimo en microsegundos (us) correspondiente a 0deg (tipicamente 1000us).
	 * @param max: Pulso miximo en microsegundos (us) correspondiente a 180deg (tipicamente 2000us).
	 */
	void setPulseRange(uint16_t min, uint16_t max);

	/**
	 * Desconecta el servo, deteniendo la senial PWM que lo controla.
	 * Ideal para liberar el temporizador o dejar de controlar el servo.
	 */
	void detach();

	private:
	uint16_t minPulse; // Pulso minimo (en us) correspondiente a 0deg
	uint16_t maxPulse; // Pulso miximo (en us) correspondiente a 180deg

	/**
	 * Convierte un angulo dado a un ancho de pulso correspondiente.
	 * @param angle: angulo en grados (0 a 180).
	 * @return Ancho de pulso en microsegundos (us) proporcional al angulo.
	 */
	uint16_t angleToPulseWidth(uint16_t angle);
};

#endif
