#include <Arduino.h>
#include "Movement.h"
#include <ServoTimer2.h>
#include <math.h>

// Variables de estado del robot
volatile double currentX = HOME_X;
volatile double currentY = HOME_Y;
volatile int penPosition = PEN_UP;

// Referencias a los servos
extern Servo rightArm;
extern Servo leftArm;
extern ServoTimer2 liftServo;

void linearInterpolation(float targetX, float targetY, int steps) {
    for (int i = 0; i <= steps; i++) {
        float progress = (float)i / steps;
        float x = currentX + progress * (targetX - currentX);
        float y = currentY + progress * (targetY - currentY);

        float q1, q2;
        invKinematics(x, y, &q1, &q2);
        leftArm.setAngle(q1);
        rightArm.setAngle(q2);
    }
    currentX = targetX;
    currentY = targetY;
}

void trapezoidalInterpolation(float targetX, float targetY, int steps) {
    for (int i = 0; i <= steps; i++) {
        float progress = (float)i / steps;
        float accelerationFactor;
        
        // Perfil trapezoidal (suaviza inicio y fin)
        if (progress < 0.2) {
            accelerationFactor = 5 * progress * progress;  // Aceleración
        } else if (progress > 0.8) {
            accelerationFactor = 1 - 5 * (1 - progress) * (1 - progress);  // Desaceleración
        } else {
            accelerationFactor = 0.5 + (progress - 0.2) * 1.25;  // Velocidad constante
        }
        
        float x = currentX + accelerationFactor * (targetX - currentX);
        float y = currentY + accelerationFactor * (targetY - currentY);
        
        float q1, q2;
        invKinematics(x, y, &q1, &q2);
        leftArm.setAngle(q1);
        rightArm.setAngle(q2);
    }
    currentX = targetX;
    currentY = targetY;
}

void polynomialInterpolation(float targetX, float targetY, int steps) {
    for (int i = 0; i <= steps; i++) {
        float progress = (float)i / steps;
        // Polinomio cúbico para movimiento suave
        float smoothProgress = 3 * progress * progress - 2 * progress * progress * progress;
        
        float x = currentX + smoothProgress * (targetX - currentX);
        float y = currentY + smoothProgress * (targetY - currentY);
        
        float q1, q2;
        invKinematics(x, y, &q1, &q2);
        leftArm.setAngle(q1);
        rightArm.setAngle(q2);
    }
    currentX = targetX;
    currentY = targetY;
}

void arcInterpolation(float startAngle, float endAngle, float centerX, float centerY, 
                     float radius, float squeezeFactor, int steps, bool clockwise) {
    // Ajustar dirección del arco
    float angleStep;
    if (clockwise) {
        // Para movimiento horario
        if (endAngle > startAngle) {
            endAngle -= 360.0f;
        }
        angleStep = (endAngle - startAngle) * DEG_TO_RAD / steps;
    } else {
        // Para movimiento anti-horario
        if (endAngle < startAngle) {
            endAngle += 360.0f;
        }
        angleStep = (endAngle - startAngle) * DEG_TO_RAD / steps;
    }
    
    float currentAngle = startAngle * DEG_TO_RAD;
    for (uint16_t i = 0; i < steps; i++) {
        // Convertir coordenadas polares a cartesianas
        float x = centerX + radius * squeezeFactor * cosf(currentAngle);
        float y = centerY + radius * sinf(currentAngle);
        
        // Calcular cinemática inversa
        float q1, q2;
        invKinematics(x, y, &q1, &q2);
        leftArm.setAngle(q1);
        rightArm.setAngle(q2);
        currentAngle += angleStep;
        currentX = x;
        currentY = y;
    }
}

void moveTo(float targetX, float targetY) {
    float q1, q2;
    invKinematics(targetX, targetY, &q1, &q2);
    leftArm.setAngle(q1);
    rightArm.setAngle(q2);
    currentX = targetX;
    currentY = targetY;
}

void raisePen() {
    if (penPosition != PEN_UP) {
        const int steps = 30;  // Pasos para suavizar el movimiento
        for (int i = 0; i <= steps; i++) {
            int pos = penPosition + (PEN_UP - penPosition) * i / steps;
            liftServo.write(pos);
            delay(10);
        }
        penPosition = PEN_UP;
    }
}

void lowerPen() {
    if (penPosition != PEN_DOWN) {
        const int steps = 30;  // Pasos para suavizar el movimiento
        for (int i = 0; i <= steps; i++) {
            int pos = penPosition - (penPosition - PEN_DOWN) * i / steps;
            liftServo.write(pos);
            delay(10);
        }
        penPosition = PEN_DOWN;
    }
}


void raiseEraser() {
    if (penPosition != ERASER_UP) {
        const int steps = 30;  // Pasos para suavizar el movimiento
        for (int i = 0; i <= steps; i++) {
            int pos = penPosition + (ERASER_UP - penPosition) * i / steps;
            liftServo.write(pos);
            delay(10);
        }
        penPosition = ERASER_UP;
    }
}

void lowerEraser() {
    if (penPosition != ERASER_DOWN) {
        const int steps = 30;  // Pasos para suavizar el movimiento
        for (int i = 0; i <= steps; i++) {
            int pos = penPosition - (penPosition - ERASER_DOWN) * i / steps;
            liftServo.write(pos);
            delay(10);
        }
        penPosition = ERASER_DOWN;
    }
}

void goHome() {
    raiseEraser();
    delay(500);
    polynomialInterpolation(HOME_X, HOME_Y, LINEAR_STEPS);
    delay(500);
    lowerEraser();
    delay(1000);
}

void eraseDisplay() {
    polynomialInterpolation(5.5, HOME_Y, LINEAR_STEPS);
    polynomialInterpolation(5.5, 35.0, LINEAR_STEPS);
    polynomialInterpolation(60.0, 35.0, LINEAR_STEPS);
    polynomialInterpolation(60.0, 28.0, LINEAR_STEPS);
    polynomialInterpolation(5.5, 28.0, LINEAR_STEPS);
    delay(500);
    polynomialInterpolation(HOME_X, HOME_Y, LINEAR_STEPS);
    delay(600);
    raisePen();
}