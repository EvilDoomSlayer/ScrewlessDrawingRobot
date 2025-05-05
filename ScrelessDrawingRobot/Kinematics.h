/*
 * Kinematics.h
 *
 * Created: 23/04/2025 04:50:36 p. m.
 *  Author: alexy
 */ 


#ifndef KINEMATICS_H_
#define KINEMATICS_H_

#include <math.h>
#include <stdint.h>

// Constantes del robot (longitudes en milimetros)
#define L1 35.0f
#define L2 55.13f
#define L3 45.0f
#define L4 13.2f
#define L5 25.8f
#define D1 18.6f
#define D2 25.0f
#define RAD_TO_DEG (180.0f / M_PI)
#define DEG_TO_RAD (M_PI / 180.0f)


/**
	 * Cinematica Inversa de 5-bar parallel robot.
	 * Calcula los angulos de las variables articulares de acuerdo a la posicion del efector final deseada
	 * @param xd: Posicion del efector final deseada en el eje de las x.
	 * @param yd: Posicion del efector final deseada en el eje de las y.
	 * @param q1_deg: Salida de la funcion con el valor articular de la junta 1 en grados.
	 * @param q2_deg: Salida de la funcion con el valor articular de la junta 2 en grados.
	 */
void invKinematics(float xd, float yd, float *q1_deg, float *q2_deg);

#endif /* KINEMATICS_H_ */