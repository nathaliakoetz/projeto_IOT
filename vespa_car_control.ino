#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
#endif

BluetoothSerial SerialBT;

// Pinos de controle para o Motor Esquerdo (ajuste conforme sua fiação)
const int motorLeft1 = 16; // Exemplo de pino IN1 da ponte H para o motor esquerdo
const int motorLeft2 = 17; // Exemplo de pino IN2 da ponte H para o motor esquerdo

// Pinos de controle para o Motor Direito (ajuste conforme sua fiação)
const int motorRight1 = 18; // Exemplo de pino IN3 da ponte H para o motor direito
const int motorRight2 = 19; // Exemplo de pino IN4 da ponte H para o motor direito

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Vespa_Carro"); // Nome do dispositivo Bluetooth (visível no App Inventor)
  Serial.println("O dispositivo Bluetooth 'Vespa_Carro' está pronto para emparelhar.");

  // Configura os pinos dos motores como saída
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);

  // Garante que os motores estejam parados no início
  stopMotors();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.print("Comando recebido: ");
    Serial.println(command);

    switch (command) {
      case 'F': // Frente
        moveForward();
        break;
      case 'B': // Trás
        moveBackward();
        break;
      case 'L': // Esquerda
        turnLeft();
        break;
      case 'R': // Direita
        turnRight();
        break;
      case 'P': // Parar
        stopMotors();
        break;
      default:
        // Comando desconhecido, parar por segurança
        stopMotors();
        break;
    }
  }
}

void moveForward() {
  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);
}

void moveBackward() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, HIGH);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, HIGH);
}

void turnLeft() {
  digitalWrite(motorLeft1, LOW);  // Motor esquerdo para trás
  digitalWrite(motorLeft2, HIGH);
  digitalWrite(motorRight1, HIGH); // Motor direito para frente
  digitalWrite(motorRight2, LOW);
}

void turnRight() {
  digitalWrite(motorLeft1, HIGH); // Motor esquerdo para frente
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);  // Motor direito para trás
  digitalWrite(motorRight2, HIGH);
}

void stopMotors() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, LOW);
}

