/*
 * Código de controle para a Robocore Vespa com suporte a Bluetooth
 * e controle via Monitor Serial.
 *
 * Comandos (via Serial ou Bluetooth):
 * 'F' - Frente
 * 'B' - Trás
 * 'L' - Esquerda (girar no eixo)
 * 'R' - Direita (girar no eixo)
 * 'P' - Parar
 */

#include "RoboCore_Vespa.h"
#include "BluetoothSerial.h"

// Objeto para controle dos motores
VespaMotors motores;

// Objeto para a comunicação Bluetooth
BluetoothSerial SerialBT;

// Velocidade padrão dos motores (0 a 255)
const int velocidade = 150;

void setup() {
  Serial.begin(115200);
  
  // Inicia o Bluetooth com o nome "RoboVespa"
  SerialBT.begin("RoboVespa");
  
  Serial.println("Robo pronto para receber comandos via Serial ou Bluetooth.");
  Serial.println("Conecte-se ao dispositivo Bluetooth 'RoboVespa'.");
  
  motores.stop();
}

void loop() {
  // Verifica se há comando vindo do Monitor Serial (USB)
  if (Serial.available()) {
    char comando = Serial.read();
    executarComando(comando);
  }

  // Verifica se há comando vindo do Bluetooth
  if (SerialBT.available()) {
    char comando = SerialBT.read();
    executarComando(comando);
  }
}

// Função central que processa os comandos recebidos
void executarComando(char comando) {
  Serial.print("Comando recebido: ");
  Serial.println(comando);

  switch (comando) {
    case 'F':
    case 'f':
      Serial.println("Movendo para FRENTE");
      motores.forward(velocidade);
      break;
      
    case 'B':
    case 'b':
      Serial.println("Movendo para TRAS");
      motores.backward(velocidade);
      break;
      
    case 'L':
    case 'l':
      Serial.println("Virando para ESQUERDA");
      // Para virar à esquerda, o motor esquerdo vai para trás e o direito para frente
      motores.setSpeedLeft(-velocidade);
      motores.setSpeedRight(velocidade);
      break;

    case 'R':
    case 'r':
      Serial.println("Virando para DIREITA");
      // Para virar à direita, o motor esquerdo vai para frente e o direito para trás
      motores.setSpeedLeft(velocidade);
      motores.setSpeedRight(-velocidade);
      break;

    case 'P':
    case 'p':
      Serial.println("Motores PARADOS");
      motores.stop();
      break;
  }
}