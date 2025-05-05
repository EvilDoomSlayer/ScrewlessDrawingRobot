/**
 * @file Display.h
 * @brief Funciones para dibujar dígitos y mostrar la hora
 * 
 * Este archivo contiene las funciones para dibujar los dígitos del 0 al 9,
 * los dos puntos del separador de hora, y la función para mostrar la hora completa.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

// Configuración de espaciado
#define DIGIT_SPACING 10.0  // Espacio entre dígitos
#define COLON_SPACING 6.5   // Espacio alrededor de ":"

/**
 * Dibuja dos puntos para representar ":"
 * @param x Posición X del centro
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void drawColon(float x, float y, float scale);

/**
 * Dibuja un dígito específico (0-9)
 * @param digit Dígito a dibujar (0-9)
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void drawDigit(uint8_t digit, float x, float y, float scale);

/**
 * Dibuja un display de tiempo completo (HH:MM)
 * @param timeDigits Array con los 4 dígitos [H1, H2, M1, M2]
 * @param x Posición X inicial
 * @param y Posición Y inicial
 * @param scale Factor de escala
 */
void drawTimeDisplay(const uint8_t timeDigits[4], float x, float y, float scale);

/**
 * Dibuja el dígito 0
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw0(float x, float y, float scale);

/**
 * Dibuja el dígito 1
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw1(float x, float y, float scale);

/**
 * Dibuja el dígito 2
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw2(float x, float y, float scale);

/**
 * Dibuja el dígito 3
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw3(float x, float y, float scale);

/**
 * Dibuja el dígito 4
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw4(float x, float y, float scale);

/**
 * Dibuja el dígito 5
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw5(float x, float y, float scale);

/**
 * Dibuja el dígito 6
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw6(float x, float y, float scale);

/**
 * Dibuja el dígito 7
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw7(float x, float y, float scale);

/**
 * Dibuja el dígito 8
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw8(float x, float y, float scale);

/**
 * Dibuja el dígito 9
 * @param x Posición X de la base izquierda
 * @param y Posición Y de la base
 * @param scale Factor de escala
 */
void draw9(float x, float y, float scale);

#endif