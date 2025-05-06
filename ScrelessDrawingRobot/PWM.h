/**
 * @file PWM.h
 * @brief Generación de señales PWM utilizando temporizadores hardware
 * 
 * Esta librería permite generar señales PWM utilizando los temporizadores
 * del microcontrolador ATmega, con soporte para diferentes modos y configuraciones.
 */

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

/// Frecuencia del reloj por defecto (16MHz)
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz
#endif

/// Selector de temporizador
enum TimerSelector { TIMER0, TIMER1, TIMeR2 };

/// Modos de operación PWM
enum PWMMode {
	UNDEFINED,
	FAST_PWM,
	PHASE_CORRECT_PWM,
	PHASE_FREQ_CORRECT_PWM,
	_8_BIT_FAST_PWM,
	_8_BIT_PHASE_CORRECT_PWM,
	_9_BIT_FAST_PWM,
	_9_BIT_PHASE_CORRECT_PWM,
	_10_BIT_FAST_PWM,
	_10_BIT_PHASE_CORRECT_PWM
};

/// Modo de salida PWM
enum PWMOutput { NON_INVERTED, INVERTED };

/// Canal PWM
enum PWMChannel { CHANNEL_A, CHANNEL_B };

/**
 * @class PWM
 * @brief Clase para generación de señales PWM
 */
class PWM {
	public:
	/**
	 * Constructor de la clase PWM.
	 * Inicializa el temporizador y canal seleccionados, y configura el pin correspondiente como salida.
	 * @param _timer: Selecciona el temporizador (TIMER0, TIMER1, TIMER2).
	 * @param _channel: Selecciona el canal del PWM (CHANNEL_A o CHANNEL_B).
	 */
	PWM(TimerSelector _timer, PWMChannel _channel);

	/**
	 * Destructor de la clase PWM.
	 * Detiene el temporizador si estaba en funcionamiento.
	 */
	~PWM();

	/**
	 * Define el modo de operacion del temporizador para generar la se�al PWM.
	 * @param _mode: Tipo de PWM (FAST_PWM, PHASE_CORRECT_PWM, etc.).
	 */
	void setMode(PWMMode _mode);

	/**
	 * Define si la senial PWM es invertida o no invertida.
	 * @param _output: Modo de salida (NON_INVERTED o INVERTED).
	 */
	void setOutput(PWMOutput _output);

	/**
	 * Configura el prescaler del temporizador, que afecta la frecuencia de la se�al PWM.
	 * @param _value: Valor del prescaler (1, 8, 64, 256, 1024).
	 */
	void setPrescaler(uint16_t _value);

	/**
	 * Define el valor superior (TOP) del temporizador, usado para controlar la resoluci�n del PWM.
	 * Solo aplicable para TIMER1 en modos con ICR1.
	 * @param _top: Valor entero del TOP (ej. ICR1).
	 */
	void setTopValue(uint16_t _top);

	/**
	 * Establece la frecuencia deseada para la senial PWM.
	 * @param _frequency: Frecuencia en Hertz (Hz). La precisi�n depende del prescaler y el modo PWM.
	 */
	void setFrequency(uint32_t _frequency);

	/**
	 * Define el ciclo de trabajo de la senial PWM.
	 * @param _percent: Valor en porcentaje (0.0 a 100.0) que representa el tiempo de encendido respecto al periodo total.
	 */
	void setDutyCycle(float _percent);

	/**
	 * Establece el ancho de pulso en microsegundos para la senial PWM.
	 * @param _microseconds: Duracion del pulso en microsegundos (us).
	 */
	void setPulseWidthMicroseconds(uint16_t _microseconds);

	/**
	 * Inicia la generacion de la senial PWM configurando los registros del temporizador correspondiente.
	 */
	void start();

	/**
	 * Detiene la se�al PWM limpiando los bits de control del temporizador.
	 */
	void stop();


	private:
	/**
	 * Selector del temporizador utilizado (TIMER0, TIMER1, TIMER2).
	 */
	TimerSelector timer;

	/**
	 * Canal del temporizador utilizado para la senial PWM (CHANNEL_A o CHANNEL_B).
	 */
	PWMChannel channel;

	/**
	 * Modo actual de operacion PWM configurado (FAST_PWM, PHASE_CORRECT_PWM, etc.).
	 */
	PWMMode mode;

	/**
	 * Tipo de salida PWM configurada (NON_INVERTED o INVERTED).
	 */
	PWMOutput output;

	/**
	 * Frecuencia de reloj del microcontrolador (por defecto, F_CPU).
	 */
	uint32_t clockFrequency;

	/**
	 * Valor superior (TOP) del temporizador para el conteo. Determina la resolucion del PWM.
	 */
	uint16_t topValue;

	/**
	 * Valor del prescaler del temporizador, que ajusta la frecuencia del PWM.
	 */
	uint16_t prescaler;

	/**
	 * Frecuencia actual de la senial PWM, calculada a partir de los par�metros configurados.
	 */
	float currentFreq;

	/**
	 * Configura el pin de salida del PWM como salida digital dependiendo del temporizador y canal.
	 */
	void configurePin();

	/**
	 * Inicializa el temporizador 0 con la configuracion PWM establecida.
	 */
	void initTimer0();

	/**
	 * Inicializa el temporizador 1 con la configuracion PWM establecida.
	 */
	void initTimer1();

	/**
	 * Inicializa el temporizador 2 con la configuracion PWM establecida.
	 */
	void initTimer2();

	/**
	 * Establece el valor de comparacion para el temporizador correspondiente y canal,
	 * lo cual determina el ciclo de trabajo del PWM.
	 * @param _compare: Valor de comparacion calculado en funcion del duty cycle o pulso.
	 */
	void setCompareValue(uint16_t _compare);

	/**
	 * Aplica el prescaler configurado al temporizador correspondiente,
	 * ajustando asi la frecuencia de conteo del mismo.
	 */
	void applyPrescaler();
};

#endif
