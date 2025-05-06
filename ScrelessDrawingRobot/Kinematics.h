/**
 * @file Kinematics.h
 * @brief Librería para el cálculo de cinemática inversa del robot de dibujo
 * 
 * Esta librería contiene las funciones para calcular los ángulos de las articulaciones
 * necesarios para posicionar el efector final en coordenadas cartesianas específicas.
 */


#ifndef KINEMATICS_H_
#define KINEMATICS_H_

#include <math.h>
#include <stdint.h>

// Constantes del robot (longitudes en milimetros)
#define L1 35.0f       // Longitud A-B y C-D
#define L2 55.13f      // Longitud B-F
#define L3 45.0f       // Longitud B-E y D-E
#define L4 13.2f       // Longitud E-F
#define L5 25.8f       // Distancia A-C
#define D1 18.6f       // Offset en X
#define D2 25.0f       // Offset en Y
#define RAD_TO_DEG (180.0f / M_PI)  // Conversión de radianes a grados
#define DEG_TO_RAD (M_PI / 180.0f)  // Conversión de grados a radianes


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