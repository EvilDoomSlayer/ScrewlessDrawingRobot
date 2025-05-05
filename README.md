# Screwless Drawing Robot - Reloj Dibujante

![Robot de Dibujo](https://example.com/path/to/image.jpg) <!-- Reemplazar con imagen real del proyecto -->

Un robot de dibujo controlado por Arduino que utiliza cinemática inversa para dibujar la hora actual en una superficie plana, obteniendo la hora de un módulo RTC DS3231.

## Características Principales

- **Dibujo de tiempo**: Muestra la hora actual en formato HH:MM
- **Cinemática inversa**: Movimientos precisos con algoritmos de interpolación
- **Múltiples modos de operación**:
  - Modo normal (muestra la hora)
  - Modo calibración
  - Modo prueba
- **Movimientos suaves**: Interpolaciones lineales, trapezoidales y polinómicas
- **Dibujo de caracteres**: Implementación de todos los dígitos (0-9) y símbolos

## Hardware Requerido

- Placa Arduino (modelo compatible)
- Módulo RTC DS3231
- 2 servomotores para los brazos
- 1 servomotor para el mecanismo de elevación
- Fuente de alimentación adecuada
- Estructura mecánica del robot

## Configuración del Software

1. **Requisitos**:
   - Arduino IDE
   - Librerías:
     - `Wire.h`
     - `DS3231.h`
     - `ServoTimer2.h`

2. **Instalación**:
   - Clonar este repositorio
   - Abrir `ScrewlessDrawingRobot.ino` en Arduino IDE
   - Cargar el programa en la placa Arduino

## Estructura del Código

El proyecto está organizado en varios archivos:

- **ScrewlessDrawingRobot.ino**: Programa principal
- **Display.h/cpp**: Manejo de dibujo de dígitos y tiempo
- **Kinematics.h/cpp**: Implementación de cinemática inversa
- **Movement.h/cpp**: Control de movimientos e interpolaciones
- **Servo.h/cpp**: Clase wrapper para control de servomotores
- **PWM.h/cpp**: Control avanzado de PWM para servos

## Uso

1. **Modo Normal**:
   - El robot dibuja automáticamente la hora actual
   - Actualiza el display cuando cambian los minutos

2. **Modo Calibración**:
   - Ejecuta movimientos predefinidos para calibración

3. **Modo Prueba**:
   - Dibuja una secuencia de prueba (dígitos 5, 4, 3, 2)

## Personalización

- Ajustar constantes en `Movement.h` para modificar:
  - Posición HOME
  - Rango de movimiento del lápiz
  - Parámetros de interpolación

- Modificar `Display.h` para cambiar:
  - Estilo de los dígitos
  - Espaciado entre caracteres
  - Tamaño del display

## Contribuciones

¡Las contribuciones son bienvenidas! Por favor abre un issue o envía un pull request para:
- Mejoras en los algoritmos de movimiento
- Optimizaciones de código
- Nuevas características

## Licencia

Este proyecto está bajo licencia MIT. Ver archivo LICENSE para más detalles.

## Galería

<!-- Incluir imágenes y videos del proyecto en funcionamiento -->
![Ejemplo de dibujo](https://example.com/path/to/drawing_example.jpg)
![Diagrama de hardware](https://example.com/path/to/hardware_diagram.jpg)

## Contacto

Para preguntas o soporte, contactar a [tu email] o abrir un issue en este repositorio.
