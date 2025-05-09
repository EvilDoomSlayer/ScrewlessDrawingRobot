/**
 * @file ScrewlessDrawingRobot.ino
 * @brief Programa principal para el robot de dibujo de reloj con cinemática inversa
 * 
 * Este programa controla un robot de dos brazos servo-accionados que dibuja la hora actual
 * obtenida de un módulo RTC DS3231. Incluye funciones para dibujar números, borrar la pantalla
 * y varios algoritmos de interpolación para movimientos suaves.
 */


// Librerías estándar
#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include <ServoTimer2.h>

// Librerías personalizadas
#include "Servo.h"
#include "Kinematics.h"
#include "Movement.h"
#include "Display.h"

// Variables globales
uint8_t lastDisplayedTime[4] = {0};  // Almacena el último tiempo dibujado [H1, H2, M1, M2]

// Instancias de hardware
// Servomotores
Servo rightArm(TIMER1, CHANNEL_A);    // Brazo derecho
Servo leftArm(TIMER1, CHANNEL_B);     // Brazo izquierdo
ServoTimer2 liftServo;                // Servo de elevación
RTClib rtc;                           // Reloj de Tiempo Real (RTC)

// Estados del sistema
enum SystemState {
    NORMAL_OPERATION,    // Operación normal (muestra la hora)
    CALIBRATION_MODE,    // Modo de calibración
    TEST_MODE           // Modo de prueba
};

SystemState currentState = NORMAL_OPERATION; // Estado inicial
const uint8_t testDigits[4] = {5, 4, 3, 2};  // Dígitos para modo prueba


// Prototipos de funciones
// Funciones para manejar estados
void handleNormalOperation();
void handleCalibrationMode();
void handleTestMode();



/**
 * @brief Configuración inicial del sistema
 */
void setup() {
    // Inicialización de servomotores
    liftServo.attach(3);  
    rightArm.init();
    leftArm.init();
    rightArm.setPulseRange(560, 2480);
    leftArm.setPulseRange(550, 2430);
    
    // Inicialización de comunicación
    Serial.begin(9600);
    Wire.begin();
    
    // Configuración inicial - llevar a posición HOME
    liftServo.write(ERASER_UP);
    moveTo(HOME_X, HOME_Y);
    delay(1000);
    lowerEraser();
    delay(5000);
    
    currentState = NORMAL_OPERATION;
}

/**
 * @brief Bucle principal del sistema
 */
void loop() {
    switch (currentState) {
        case NORMAL_OPERATION: handleNormalOperation(); break;
        case CALIBRATION_MODE: handleCalibrationMode(); break;
        case TEST_MODE: handleTestMode(); break;
    }
}


/**
 * Actualiza el display de tiempo si ha cambiado
 */
void updateTimeDisplay() {
    DateTime now = rtc.now();
    uint8_t currentTime[4] = {
        now.hour() / 10,    // H1
        now.hour() % 10,    // H2
        now.minute() / 10,  // M1
        now.minute() % 10   // M2
    };

    // Verificar si el tiempo ha cambiado
    bool needsUpdate = false;
    for (int i = 0; i < 4; ++i) {
        if (currentTime[i] != lastDisplayedTime[i]) {
            needsUpdate = true;
            break;
        }
    }

    if (needsUpdate) {
        memcpy(lastDisplayedTime, currentTime, sizeof(currentTime)); // Actualizar registro
        drawTimeDisplay(currentTime, 15.5, 28.0, 1.0); // Dibujar nuevo tiempo
    }
}


/**
 * @brief Maneja el modo de operación normal
 */
void handleNormalOperation() {
  updateTimeDisplay();
}

/**
 * @brief Maneja el modo de calibración
 */
void handleCalibrationMode() {
  raiseEraser();
  delay(2000);
  lowerEraser();
  delay(2000);
  raisePen();
  delay(2000);
  lowerPen();
  delay(2000);
  /*
  // Movimientos de calibración
  polynomialInterpolation(70.85, 27.59, LINEAR_STEPS);
  delay(3000);
  polynomialInterpolation(-5.37, 29.02, LINEAR_STEPS);
  delay(3000);
  */
}

/**
 * @brief Maneja el modo de prueba
 */
void handleTestMode() {
  // Secuencia de prueba
  lowerPen();
  moveTo(HOME_X, HOME_Y);
  delay(3000);
  polynomialInterpolation(55.0, 45.0, LINEAR_STEPS);
  delay(500);
  polynomialInterpolation(5.5, 45.0, LINEAR_STEPS);
  delay(500);
  raisePen();
  polynomialInterpolation(5.5, 28.0, LINEAR_STEPS);
  delay(500);
  polynomialInterpolation(20.0, 30.0, LINEAR_STEPS);
  lowerPen();
  delay(500);
  goHome();
  eraseDisplay();
  drawTimeDisplay(testDigits, 15.5, 28.0, 1.0);
  polynomialInterpolation(HOME_X, HOME_Y, LINEAR_STEPS);
}



