#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Calibración del rango de pulsos para los servos
#define SERVOMIN 130
#define SERVOMAX 520

// Variable global para guardar estado
String estado = "detener"; 

// Función para invertir sentido de giro en ciertos canales
bool esInvertido(uint8_t canal) {
  return (canal == 0 || canal == 1 || canal == 5); 
}

// Función que mueve un servo a un ángulo
void setServo(uint8_t canal, int angulo) {
  if (esInvertido(canal)) angulo = 180 - angulo;
  int pulso = map(angulo, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(canal, 0, pulso);
}

// Función para postura neutral
void posturaReposo() {
  for (uint8_t i = 0; i < 8; i++) {
    setServo(i, 90);
  }
}

// Funciones de movimiento
void moverAdelante() {
  // Fase 1: Levantar y adelantar patas diagonales (trasera derecha y delantera izquierda)
  setServo(2, 60);  // Rodilla trasera derecha: levanta
  setServo(7, 60);  // Rodilla delantera izquierda: levanta
  delay(150);
  setServo(0, 130); // Torso trasera derecha: adelanta
  setServo(5, 50);  // Torso delantera izquierda: adelanta
  delay(200);
  setServo(2, 90);  // Rodilla trasera derecha: baja
  setServo(7, 90);  // Rodilla delantera izquierda: baja
  delay(150);

  // Fase 2: Levantar y adelantar patas contrarias
  setServo(3, 60);  // Rodilla trasera izquierda: levanta
  setServo(6, 60);  // Rodilla delantera derecha: levanta
  delay(150);
  setServo(1, 50);  // Torso trasera izquierda: adelanta
  setServo(4, 130); // Torso delantera derecha: adelanta
  delay(200);
  setServo(3, 90);  // Rodilla trasera izquierda: baja
  setServo(6, 90);  // Rodilla delantera derecha: baja
  delay(150);

  // Vuelve a la postura neutral
  posturaReposo();
}


void moverAtras() {
  // Fase 1: Levantar y atrasar trasera derecha + delantera izquierda
  setServo(2, 60);  // Rodilla trasera derecha
  setServo(7, 60);  // Rodilla delantera izquierda
  delay(150);
  setServo(0, 50);  // Torso trasera derecha: hacia atrás
  setServo(5, 130); // Torso delantera izquierda: hacia atrás
  delay(200);
  setServo(2, 90);  // Baja
  setServo(7, 90);
  delay(150);

  // Fase 2: Levantar y atrasar trasera izquierda + delantera derecha
  setServo(3, 60);
  setServo(6, 60);
  delay(150);
  setServo(1, 130); // Torso trasera izquierda: hacia atrás
  setServo(4, 50);  // Torso delantera derecha: hacia atrás
  delay(200);
  setServo(3, 90);
  setServo(6, 90);
  delay(150);

  posturaReposo();
}

void girarIzquierda() {
  // Fase 1: Levantar patas laterales
  setServo(2, 60);  // Rodilla trasera derecha
  setServo(7, 60);  // Rodilla delantera izquierda
  delay(150);
  setServo(0, 130); // Torso trasera derecha: adelante
  setServo(5, 130); // Torso delantera izquierda: atrás
  delay(200);
  setServo(2, 90);
  setServo(7, 90);
  delay(150);

  // Fase 2
  setServo(3, 60);
  setServo(6, 60);
  delay(150);
  setServo(1, 50);  // Torso trasera izquierda: atrás
  setServo(4, 50);  // Torso delantera derecha: adelante
  delay(200);
  setServo(3, 90);
  setServo(6, 90);
  delay(150);

  posturaReposo();
}


void girarDerecha() {
  // Fase 1
  setServo(3, 60);  // Rodilla trasera izquierda
  setServo(6, 60);  // Rodilla delantera derecha
  delay(150);
  setServo(1, 130); // Torso trasera izquierda: adelante
  setServo(4, 130); // Torso delantera derecha: atrás
  delay(200);
  setServo(3, 90);
  setServo(6, 90);
  delay(150);

  // Fase 2
  setServo(2, 60);
  setServo(7, 60);
  delay(150);
  setServo(0, 50);  // Torso trasera derecha: atrás
  setServo(5, 50);  // Torso delantera izquierda: adelante
  delay(200);
  setServo(2, 90);
  setServo(7, 90);
  delay(150);

  posturaReposo();
}


void detener() {
  posturaReposo();
}


void darPatitaDerecha() {
  // Elevar el hombro derecho
  setServo(4, 150);   // Levantar un poco el hombro
  delay(200);
  // Estirar la rodilla derecha
  setServo(6, 20);   // Patita adelante
  delay(500);
  // Volver a la postura normal
  setServo(6, 90);
  setServo(4, 90);

  delay(3000);
  posturaReposo();
}

void darPatitaIzquierda() {
  // Elevar el hombro izquierdo
  setServo(5, 180);  // Levantar un poco el hombro
  delay(200);
  // Estirar la rodilla izquierda
  setServo(7, 140);  // Patita adelante
  delay(500);
  // Volver a la postura normal
  setServo(7, 90);
  setServo(5, 90);

  delay(3000);
  posturaReposo();
}

void moverCabezaIzquierda() {
  setServo(8, 60);  // Gira a la izquierda
  delay(500);
  setServo(8, 90);  // Vuelve al centro
  delay(200);
}

void moverCabezaDerecha() {
  setServo(8, 120); // Gira a la derecha
  delay(500);
  setServo(8, 90);  // Vuelve al centro
  delay(200);
}

void setup() {
  Serial.begin(9600);  // Velocidad del UART
  pwm.begin();
  pwm.setPWMFreq(50);
  posturaReposo();
}

void loop() {
  // Leer comando solo si hay datos en el serial
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toLowerCase();

    // Comandos de movimiento continuo
    if (cmd == "adelante" || cmd == "atras" || cmd == "izquierda" || cmd == "derecha" || cmd == "detener") {
      estado = cmd;  // Solo guardamos el estado si es un movimiento continuo
    }

    // Comandos de acción puntual
    else if (cmd == "patita_derecha") darPatitaDerecha();
    else if (cmd == "patita_izquierda") darPatitaIzquierda();
    else if (cmd == "cabeza_izquierda") moverCabezaIzquierda();
    else if (cmd == "cabeza_derecha") moverCabezaDerecha();
  }

  // Ejecutar continuamente el movimiento correspondiente
  if (estado == "adelante") moverAdelante();
  else if (estado == "atras") moverAtras();
  else if (estado == "izquierda") girarIzquierda();
  else if (estado == "derecha") girarDerecha();
  else if (estado == "detener") detener();
}

