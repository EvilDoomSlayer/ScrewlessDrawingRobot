#include <Arduino.h>
#include "Display.h"
#include "Movement.h"

void drawColon(float x, float y, float scale) {
    raisePen();
    delay(500);
    polynomialInterpolation(x, y + scale * 6.0, LINEAR_STEPS);
    lowerPen();
    delay(500);
    raisePen();
    polynomialInterpolation(x, y + scale * 16.0, LINEAR_STEPS);
    delay(500);
    lowerPen();
    delay(500);
}


void draw0(float x, float y, float scale) {
    raisePen();
    polynomialInterpolation(x, y + scale * 9.0, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Elipse de 0.94 cm de ancho y 1.8 cm de alto
    arcInterpolation(0.0, 360.0, x, y + scale * 4.5, scale * 9.0, 0.53, ARC_STEPS, false);
    delay(500);
}


void draw1(float x, float y, float scale) {
    raisePen();
    // Ubicar en el inferior centro del número
    polynomialInterpolation(x + scale * 5.5, y, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Linea de 1.8cm de alto
    polynomialInterpolation(x + scale * 5.5, y + scale * 18.0, LINEAR_STEPS);
    // Linea inclinada de 5.5cm de ancho y 0.3 cm de alto
    polynomialInterpolation(x, y + scale * 15.0, LINEAR_STEPS);
    delay(500);
}


void draw2(float x, float y, float scale) {
    raisePen();
    // Ubicar en el inferior centro del número
    polynomialInterpolation(x + scale * 9.4, y, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Linea de 0.94 cm de ancho
    polynomialInterpolation(x, y, LINEAR_STEPS);
    // Linea inclinada de 0.94cm de ancho y 1cm de alto
    polynomialInterpolation(x + scale * 9.4, y + scale * 10.0, LINEAR_STEPS);
    // Arco de 180° de radio de 4.7
    arcInterpolation(0.0, 180.0, x + scale * 4.7, y + scale * 10.0, scale * 4.7, 1.0, ARC_STEPS, false);
    delay(500);
}


void draw3(float x, float y, float scale) {
    raisePen();
    // Colocar el puntero en el inicio del 3
    polynomialInterpolation(x + scale * 3.2, y, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Arco de 0.585 cm de ancho y 0.9 cm de alto
    arcInterpolation(270.0, 90.0, x + scale * 3.2, y + scale * 4.5, scale * 4.5, 1.3, ARC_STEPS, false);
    // Arco de 0.585 cm de ancho y 0.9 cm de alto
    arcInterpolation(270.0, 90.0, x + scale * 3.2, y + scale * 13.5, scale * 4.5, 1.3, ARC_STEPS, false);
    delay(500);
}


void draw4(float x, float y, float scale) {
    raisePen();
    // Posicionamiento del origen del 4
    polynomialInterpolation(x + scale * 9.0, y, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Linea vertical de 1.8cm de alto
    polynomialInterpolation(x + scale * 9.0, y + scale * 18.0, LINEAR_STEPS);
    // Linea inclinada de 0.9 cm de ancho y 0.8 cm de alto
    polynomialInterpolation(x, y + scale * 10.0, LINEAR_STEPS);
    // Linea horizontal de 0.9 cm de ancho
    polynomialInterpolation(x + scale * 9.0, y + scale * 10.0, LINEAR_STEPS);
    delay(500);
}


void draw5(float x, float y, float scale) {
    raisePen();
    polynomialInterpolation(x, y, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Arco de 0.9 cm de ancho y 1.2 cm de alto
    arcInterpolation(270.0, 90.0, x, y + scale * 6.0, scale * 6.0, 1.5, ARC_STEPS, false);
    // Linea vertical de 0.6cm de alto
    polynomialInterpolation(x, y + scale * 18.0, LINEAR_STEPS);
    // Linea horizontal de 0.9 cm de ancho
    polynomialInterpolation(x + scale * 9.0, y + scale * 18.0, LINEAR_STEPS);
    delay(500);
}


void draw6(float x, float y, float scale) {
    raisePen();
    polynomialInterpolation(x, y, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Elipse de 0.94 cm de ancho y 0.723 cm de alto
    arcInterpolation(180.0, 179.0, x + scale * 4.7, y + scale * 3.61, scale * 3.61, 1.3, ARC_STEPS, false);
    // Linea inclinada de 0.94 cm de ancho y 1 cm de alto
    polynomialInterpolation(x + scale * 9.4, y + scale * 18.0, LINEAR_STEPS);
    delay(500);
}


void draw7(float x, float y, float scale) {
    raisePen();
    polynomialInterpolation(x, y, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Linea inclinada de 0.94 cm de ancho y 1 cm de alto
    polynomialInterpolation(x + scale * 9.4, y + scale * 18.0, LINEAR_STEPS);
    // Linea horizontal de 0.94 cm de ancho
    polynomialInterpolation(x, y + scale * 18.0, LINEAR_STEPS);
    delay(500);
}


void draw8(float x, float y, float scale) {
    raisePen();
    polynomialInterpolation(x + scale * 4.5, y + scale * 9.0, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Circulo de 9cm de diametro 
    arcInterpolation(90.0, 89.0, x + scale * 4.5, y + scale * 4.5, scale * 4.5, 1.0, ARC_STEPS, false);
    // Circulo de 9cm de diametro 
    arcInterpolation(270.0, 269.0, x + scale * 4.5, y + scale * 13.5, scale * 4.5, 1.0, ARC_STEPS, false);
    delay(500);
}


void draw9(float x, float y, float scale) {
    raisePen();
    polynomialInterpolation(x, y, LINEAR_STEPS);
    delay(500);
    lowerPen();
    // Linea inclinada de 0.94 cm de ancho y 1 cm de alto
    polynomialInterpolation(x + scale * 9.4, y + scale * 13.61, LINEAR_STEPS);
    // Elipse de 0.94 cm de ancho y 0.723 cm de alto
    arcInterpolation(0.0, 360.0, x + scale * 4.7, y + scale * 13.61, scale * 3.61, 1.3, ARC_STEPS, false);
    delay(500);
}


void drawDigit(uint8_t digit, float x, float y, float scale) {
    switch (digit) {
        case 0: draw0(x, y, scale); break;
        case 1: draw1(x, y, scale); break;
        case 2: draw2(x, y, scale); break;
        case 3: draw3(x, y, scale); break;
        case 4: draw4(x, y, scale); break;
        case 5: draw5(x, y, scale); break;
        case 6: draw6(x, y, scale); break;
        case 7: draw7(x, y, scale); break;
        case 8: draw8(x, y, scale); break;
        case 9: draw9(x, y, scale); break;
        default: draw0(x, y, scale); break;
    }
}


void drawTimeDisplay(const uint8_t timeDigits[4], float x, float y, float scale) {
    eraseDisplay();
    // Posición inicial
    polynomialInterpolation(x, y, LINEAR_STEPS);
    float currentX = x;

    // Dibujar H1
    drawDigit(timeDigits[0], currentX, y, scale);
    currentX += scale * DIGIT_SPACING;  // Espacio entre H1 y H2

    // Dibujar H2
    drawDigit(timeDigits[1], currentX, y, scale);
    currentX += scale * COLON_SPACING;  // Espacio entre H2 y ":"

    // Dibujar ":"
    drawColon(currentX, y, scale);
    currentX += scale * COLON_SPACING;  // Espacio entre ":" y M1

    // Dibujar M1
    drawDigit(timeDigits[2], currentX, y, scale);
    currentX += scale * DIGIT_SPACING;  // Espacio entre M1 y M2

    // Dibujar M2
    drawDigit(timeDigits[3], currentX, y, scale);
    
    delay(600);
    goHome();
}