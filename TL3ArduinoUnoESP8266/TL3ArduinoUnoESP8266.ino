#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600
#define SERVO_FREQ 50
#define ANGULO_MAX 140 

String estado = "detener";

// canales invertidos
bool esCanalInvertido(uint8_t canal) {
  return (canal == 1 || canal == 2 || canal == 5 || canal == 6);
}

void setCanalAngulo(uint8_t canal, int angulo) {
  // Invertir si corresponde
  if (esCanalInvertido(canal)) {
    angulo = ANGULO_MAX - angulo;
  }

  // Limitar el ángulo a ANGULO_MAX
  angulo = constrain(angulo, 0, ANGULO_MAX);

  // Convertir a pulso
  uint16_t pulso = map(angulo, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(canal, 0, pulso);
  Serial.print("Canal ");
  Serial.print(canal);
  Serial.print(" | Ángulo: ");
  Serial.print(angulo);
  Serial.print("° | Pulso: ");
  Serial.println(pulso);
}

void ponerReposo(){
  setCanalAngulo(0, 90);   // Hombro trasero derecho
  setCanalAngulo(1, 80);   // Hombro trasero izquierdo
  setCanalAngulo(2, 100);  // Rodilla trasera derecha
  setCanalAngulo(3, 90);  // Rodilla trasera izquierda
  setCanalAngulo(4, 90);   // Hombro delantera derecha
  setCanalAngulo(5, 55);   // Hombro delantera izquierda
  setCanalAngulo(6, 70);  // Rodilla delantera derecha
  setCanalAngulo(7, 80);  // Rodilla delantera izquierda
}


// CAMINATA cuadrúpeda lenta corregida
void moverAdelante() {
  // ============================
  // PASO A: avanza pierna 3 y 6 (trasera izq + delantera der)
  // ============================

  // Levantar rodillas
  setCanalAngulo(3, 60);  // rodilla trasera izq arriba
  setCanalAngulo(6, 80);  // rodilla delantera der arriba
  delay(150);

  // Avanzar hombros (las patas en el aire)
  setCanalAngulo(1, 80);   // hombro trasero izq adelante
  setCanalAngulo(4, 120);  // hombro delantero der adelante

  // Retroceder patas de soporte (trasera der + delantera izq)
  setCanalAngulo(0, 60);   // hombro trasero derecho atrás
  setCanalAngulo(5, 50);   // hombro delantero izquierdo atrás
  delay(200);

  // Apoyar rodillas
  setCanalAngulo(3, 110);  // rodilla trasera izq baja
  setCanalAngulo(6, 60);   // rodilla delantera der baja
  delay(250);


  // ============================
  // PASO B: avanza pierna 2 y 7 (trasera der + delantera izq)
  // ============================

  // Levantar rodillas
  setCanalAngulo(2, 60);   // rodilla trasera der arriba
  setCanalAngulo(7, 110);  // rodilla delantera izq arriba
  delay(150);

  // Avanzar hombros (las patas en el aire)
  setCanalAngulo(0, 120);  // hombro trasero derecho adelante
  setCanalAngulo(5, 80);   // hombro delantero izquierdo adelante

  // Retroceder patas de soporte
  setCanalAngulo(1, 60);   // hombro trasero izq atrás
  setCanalAngulo(4, 60);   // hombro delantero derecho atrás
  delay(200);

  // Apoyar rodillas
  setCanalAngulo(2, 100);  // rodilla trasera derecha baja
  setCanalAngulo(7, 40);   // rodilla delantera izquierda baja
  delay(200);
}
void girarIzquierda() {
  // Paso A: mover pierna 2 y 4 (trasera derecha + delantera derecha)

  // 1. Levantar rodillas
  setCanalAngulo(2, 60);  // rodilla trasera derecha
  setCanalAngulo(6, 20);  // rodilla delantera derecha
  delay(200);

  // 2. Avanzar hombros derechos
  setCanalAngulo(0, 120); // hombro trasero derecho hacia adelante
  setCanalAngulo(4, 120); // hombro delantera derecha hacia adelante
  delay(200);

  // 3. Apoyar patas
  setCanalAngulo(2, 100);
  setCanalAngulo(6, 60);
  delay(300);

  // Paso B: mover hombros izquierdos un poco hacia atrás para facilitar el giro
  setCanalAngulo(1, 60);  // hombro trasero izquierdo
  setCanalAngulo(5, 60);  // hombro delantera izquierda
  delay(200);
}

void girarDerecha(){
  // Paso A: mover pierna 3 y 5 (trasera izquierda + delantera izquierda)

  // 1. Levantar rodillas
  setCanalAngulo(3, 60);  // rodilla trasera izquierda
  setCanalAngulo(7, 100); // rodilla delantera izquierda
  delay(200);

  // 2. Avanzar hombros izquierdos
  setCanalAngulo(1, 120); // hombro trasero izquierdo adelante
  setCanalAngulo(5, 120); // hombro delantero izquierdo adelante
  delay(200);

  // 3. Apoyar patas
  setCanalAngulo(3, 90);  // rodilla trasera izquierda baja
  setCanalAngulo(7, 70);  // rodilla delantera izquierda baja
  delay(300);

  // Paso B: mover hombros derechos hacia atrás para acompañar el giro
  setCanalAngulo(0, 60);  // hombro trasero derecho
  setCanalAngulo(4, 60);  // hombro delantero derecho
  delay(200);
}

void detener() {
  ponerReposo();
}

void darPatitaDerecha() {
  setCanalAngulo(4, 140);
  delay(300);
  setCanalAngulo(6, 130);
  delay(600);
  setCanalAngulo(6, 90);
  setCanalAngulo(4, 90);
  delay(3000);
  ponerReposo();
}

void darPatitaIzquierda() {
  setCanalAngulo(5, 100);
  delay(300);
  setCanalAngulo(7, 100);
  delay(600);
  setCanalAngulo(7, 90);
  setCanalAngulo(5, 70);
  delay(3000);
  ponerReposo();
}

void moverCabezaIzquierda() {
  setCanalAngulo(8, 130);
  delay(500);
  setCanalAngulo(8, 100);
  delay(200);
}

void moverCabezaDerecha() {
  setCanalAngulo(8, 50);
  delay(500);
  setCanalAngulo(8, 100);
  delay(200);
}

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  ponerReposo();
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toLowerCase();
    if (cmd == "adelante" || cmd == "izquierda" || cmd == "derecha" ||
        cmd == "patita_derecha" || cmd == "patita_izquierda" ||
        cmd == "cabeza_derecha" || cmd == "cabeza_izquierda") {
      estado = cmd;
    }
  }

  if (estado == "adelante") {
    moverAdelante();
  } else if (estado == "izquierda") {
    girarIzquierda();
    estado = "detener";
  } else if (estado == "derecha") {
    girarDerecha();
    estado = "detener";
  } else if (estado == "patita_derecha") {
    darPatitaDerecha();
    estado = "detener";
  } else if (estado == "patita_izquierda") {
    darPatitaIzquierda();
    estado = "detener";
  } else if (estado == "cabeza_derecha") {
    moverCabezaDerecha();
    estado = "detener";
  } else if (estado == "cabeza_izquierda") {
    moverCabezaIzquierda();
    estado = "detener";
  } else {
    ponerReposo();
  }
}
