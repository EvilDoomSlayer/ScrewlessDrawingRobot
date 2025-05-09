/**
 * @file Movement.h
 * @brief Control de movimiento del robot de dibujo con cinemática inversa
 * 
 * Este archivo define las funciones para controlar los movimientos del robot,
 * incluyendo interpolaciones lineales, trapezoidales, polinómicas y de arco.
 * También gestiona el levantamiento y bajada del lápiz.
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Kinematics.h"
#include "Servo.h"

// Configuración de pasos para interpolaciones
#define LINEAR_STEPS 200  // Pasos para interpolación lineal/polinomial
#define ARC_STEPS 600     // Pasos para interpolación de arcos

// Posiciones del servo de elevación
#define PEN_UP 1600       // Posición levantada (lápiz arriba)
#define PEN_DOWN 1910     // Posición bajada (lápiz abajo)
#define ERASER_UP  1500
#define ERASER_DOWN 1850

// Posición HOME del robot
const double HOME_X = 72.9; // Coordenada X de la posición home
const double HOME_Y = 41.0; // Coordenada Y de la posición home

// Memoria de la posición actual del robot
extern volatile double currentX;  // Última posición X conocida
extern volatile double currentY;  // Última posición Y conocida
extern volatile int penPosition;  // Última posición del lápiz conocida

/**
 * Interpolación lineal entre la posición actual y el objetivo
 * @param targetX Coordenada X objetivo
 * @param targetY Coordenada Y objetivo
 * @param steps Número de pasos para la interpolación
 */
void linearInterpolation(float targetX, float targetY, int steps);

/**
 * Interpolación trapezoidal (aceleración/desaceleración suave)
 * @param targetX Coordenada X objetivo
 * @param targetY Coordenada Y objetivo
 * @param steps Número de pasos para la interpolación
 */
void trapezoidalInterpolation(float targetX, float targetY, int steps);

/**
 * Interpolación polinómica (movimiento suave)
 * @param targetX Coordenada X objetivo
 * @param targetY Coordenada Y objetivo
 * @param steps Número de pasos para la interpolación
 */
void polynomialInterpolation(float targetX, float targetY, int steps);

/**
 * Interpolación para movimientos de arco
 * @param startAngle Ángulo inicial en grados
 * @param endAngle Ángulo final en grados
 * @param centerX Coordenada X del centro del arco
 * @param centerY Coordenada Y del centro del arco
 * @param radius Radio del arco
 * @param squeezeFactor Factor de compresión (para elipses)
 * @param steps Número de pasos para la interpolación
 * @param clockwise Sentido horario (true) o antihorario (false)
 */
void arcInterpolation(float startAngle, float endAngle, float centerX, float centerY,
                     float radius, float squeezeFactor, int steps, bool clockwise);

/**
 * Mueve el robot directamente a la posición objetivo (sin interpolación)
 * @param targetX Coordenada X objetivo
 * @param targetY Coordenada Y objetivo
 */
void moveTo(float targetX, float targetY);

/**
 * Levanta el lápiz (movimiento suavizado)
 */
void raisePen();

/**
 * Baja el lápiz (movimiento suavizado)
 */
void lowerPen();

/**
 * Levanta el lápiz para que entre en el borrador (movimiento suavizado)
 */
void raiseEraser();

/**
 * Baja el lápiz para que entre en el borador(movimiento suavizado)
 */
void lowerEraser();

/**
 * Mueve el robot a la posición HOME y levanta el lápiz
 */
void goHome();

/**
 * Borra el área de dibujo (movimientos predefinidos)
 */
void eraseDisplay();

#endif