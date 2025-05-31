#include <Wire.h>
#include <MPU6050.h>
#include "PIDControl.h"
#include <BluetoothSerial.h>

int PID_MODE = 3; //Variable de control 
float dt = 0.005; //Periodo de actualizacion del void loop, EN SEGUNDOS
unsigned long dt_us = dt * 1e6; //Lo pasamos a microsegundos

MPU6050 mpu;
BluetoothSerial SerialBT;

const int AIN1 = 0, AIN2 = 2, PWMA = 5;
const int BIN1 = 4, BIN2 = 16, PWMB = 17;
const int STBY = 15;

//Valores, para el estado 0
float setpoint = 0.0;
float measured_value = 0.0;
float output = 0;

float desplazamientoX = 0.0;
float desplazamientoY = 0.0;

//Constantes del pid a implementar
float kp =50.0, ki = 1, kd = 20.0;

//Definimos un objeto pid, por ahora no asigmanos ninguo
PID* pid = nullptr;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Khibita");  // Nombre del dispositivo Bluetooth
  Wire.begin();
  mpu.initialize();

  //AINX y BINX pines de direccion de vel, mientras PWMX modulo de velocidad
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT); pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT); pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT); digitalWrite(STBY, HIGH);

  switch (PID_MODE) { //Elegir cual de las 3 implementacion usar
    case 1:
      pid = new PID_Discreto(kp, ki, kd, dt);
      break;
    case 2:
      pid = new PID_IIR(kp, ki, kd, dt);
      break;
    case 3:
    default:
      pid = new PID_Filtrado(kp, ki, kd, dt, 5.0);
      break;
  }
}

float getAngle() { //angulo para el plano YZ, EN GRADOS
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  return atan2(ay, az) * 180 / PI;
}

void applyMotorA(float pwm) {
  pwm = constrain(pwm, -255, 255);
  digitalWrite(AIN1, pwm > 0 ? HIGH : LOW);
  digitalWrite(AIN2, pwm > 0 ? LOW : HIGH);
  analogWrite(PWMA, abs(pwm));
}

void applyMotorB(float pwm) {
  pwm = constrain(pwm, -255, 255);
  digitalWrite(BIN1, pwm > 0 ? HIGH : LOW);
  digitalWrite(BIN2, pwm > 0 ? LOW : HIGH);
  analogWrite(PWMB, abs(pwm));
}



void loop() {
  static unsigned long lastControl = 0;
  unsigned long now = micros(); //Devuelve los msec 
  if (now - lastControl >= dt_us) { 
    lastControl = now;

    measured_value = getAngle();
    output = pid->compute(setpoint, measured_value);
    output = constrain(output, -255, 255); // normalizar a los rangos de los motroes

    if (SerialBT.available()) { //En caso de tener Comunicacion bluethoot
      String datos = SerialBT.readStringUntil('\n');
      int sep = datos.indexOf(',');
      if (sep > 0) {
        float x = datos.substring(0, sep).toFloat();
        float y = datos.substring(sep + 1).toFloat();
        desplazamientoX = x;
        desplazamientoY = y;
        setpoint += desplazamientoY * 0.03;
      }
    }

    float pwmGiro = desplazamientoX * 2.55;
    
    //Valors para los dos motores , se resta o se suma dependiendo del sentido de giro
    applyMotorA(output - pwmGiro);
    applyMotorB(output + pwmGiro);
     
     
     
        // Enviar valores de vuelta por Bluetooth
    SerialBT.print("Recibido -> X: ");
    SerialBT.print(desplazamientoX, 2); // dos decimales
    SerialBT.print(" Y: ");
    SerialBT.println(desplazamientoY, 2);
  }
}
