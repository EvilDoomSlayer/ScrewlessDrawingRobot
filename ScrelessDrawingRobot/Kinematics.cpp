/*
 * Kinematics.cpp
 *
 * Created: 23/04/2025 04:50:51 p. m.
 *  Author: alexy
 */ 

#include "Kinematics.h"
#include <math.h>


// Funcion que calcula los angulos q1 y q2 a partir de xd, yd
void invKinematics(float xd, float yd, float *q1_deg, float *q2_deg) {
  
  float Fx1 = xd - D1;
	float Fy1 = yd + D2;
	float Fx1_sq = Fx1 * Fx1;
	float Fy1_sq = Fy1 * Fy1;
	float r1_sq = Fx1_sq + Fy1_sq;
	
	float L1_sq = L1 * L1;
	float L2_sq = L2 * L2;
	float L3_sq = L3 * L3;
	float L4_sq = L4 * L4;
	float L5_sq = L5 * L5;

	float A = Fx1;
	float B = Fy1;
	// Cinematica Inv Primer Servo
	float C = (r1_sq + L1_sq - L2_sq) * 0.5f / L1;
	float sqrt1 = sqrtf(r1_sq - C*C);
	float q1 = 2.0f * atan2f(Fy1 + sqrt1, Fx1 + C);
	
	// Angulo intermedio
	float C2 = (r1_sq + L2_sq - L1_sq) * 0.5f / L2;
	float sqrt2 = sqrtf(r1_sq - C2*C2);
	float theta1 = 2.0f * atan2f(Fy1 - sqrt2, Fx1 + C2);
	float acos_arg = (L2_sq + L3_sq - L4_sq) / (2.0f * L2 * L3);
	if (acos_arg > 1.0f) acos_arg = 1.0f;           // Clamp for safety
	else if (acos_arg < -1.0f) acos_arg = -1.0f;
	float phi = theta1 - acosf(acos_arg);
	
	// Coordenadas de la junta E
	float cos_q1 = cosf(q1), sin_q1 = sinf(q1);
	float cos_phi = cosf(phi), sin_phi = sinf(phi);
	float Ex1 = L1 * cos_q1 + L3 * cos_phi;
	float Ey1 = L1 * sin_q1 + L3 * sin_phi;

	
	// Cinematica inversa para el segundo servo
	float A3 = Ex1 - L5;
	float A3_sq = A3 * A3;
	float Ex1_sq = Ex1 * Ex1;
	float Ey1_sq = Ey1 * Ey1;
	float C3 = (Ex1_sq + Ey1_sq + L1_sq + L5_sq - L3_sq - 2.0f * Ex1 * L5) * 0.5f / L1;
	float sqrt3 = sqrtf(Ey1_sq + A3_sq - C3*C3);
	float q2 = 2.0f * atanf((Ey1 - sqrt3) / (A3 + C3));
  
	// Conversion a grados
	*q1_deg = q1 * RAD_TO_DEG;
	*q2_deg = q2 * RAD_TO_DEG;
}