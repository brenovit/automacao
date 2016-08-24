#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

RF24 radio(7, 8);

int arduino = 0;
byte endereco[][6] = {"COM4", "COM5"};

void setup() {
  Serial.begin(9600);

  printf_begin();
  radio.begin();  //inicia o radio
  radio.setPALevel(RF24_PA_LOW); //define a potencia (energia) do transceiver, por padrão é alto.

  // verifica qual arduino é este e define
  if (arduino == 1) {
    radio.openWritingPipe(endereco[1]);     //o end. de envio de um no -> Pt1
    radio.openReadingPipe(1, endereco[0]);  //e o end. de recebiemnto de um no -> Pt2
  } else {
    radio.openWritingPipe(endereco[0]);     //Pt2 -> end. de envio do outro
    radio.openReadingPipe(1, endereco[1]);  //Pt1 -> end. de recebimento do outro
  }

  radio.startListening(); //inicia a troca de dados
  //radio.printDetails(); //mostra os detalhes do equipamento.
  printf("Pronto...\n");
}

void loop() {
  if (Serial.available()){
    char texto = Serial.read();
    if (!enviarMensagem(texto)) {
      printf("Falha ao enviar a mensagem!\n");
    }
    texto = "";
  }
  receberMensagem();
}

/*
  void enviarMensagem2() {
  radio.stopListening();                             // primeiro, para de ouvir para começar a falar

  if (!radio.write(letra, sizeof(letra))) { // se não conseguir enviar o dado
    printf("Dado não foi enviado\n");
  }

  radio.startListening();                            // agora ele ouve.

  unsigned long tempo_inicio = micros();             // cria uma variavel que vai receber o tempo que ele iniciou em microsegundos
  boolean tempoAcabou = false;                       // cria uma variavel que vai indicar se recebeu ou não resposta

  while (!radio.available()) {                       // Enquanto nada for recebido
    if (micros() - tempo_inicio > 200000) {          // e o tempo de espera ultrapassar 200ms
      tempoAcabou = true;                            // indica que o tempo experiou
      break;                                         // e sai do loop
    }
  }

  if (tempoAcabou) {
    printf("O tempo de resposta expirou\n");
  } else {
    char dadoRecebido;
    radio.read(&dadoRecebido, sizeof(dadoRecebido));
    printf("Enviei: %c e Recebi: %c\n", letra, dadoRecebido);
  }
  }
*/

int enviarMensagem(char message) {
  radio.stopListening();
  radio.write(&message, sizeof(message));
  printf("\nME: %c", message);
  delay(1000);
  radio.startListening();
  return 1;
}

void receberMensagem() {
  unsigned char dadoRecebido;
  if (radio.available()){
    while (radio.available()){ 
      radio.read(&dadoRecebido, sizeof(dadoRecebido));
      printf("\nHIM: %c",dadoRecebido);
    }
  }
}

/*int receberMensagem() {
  int messageLength = 12;
  int msg[1];
  int lastmsg = 1;
  String theMessage = "";
  bool finish = false;
  radio.startListening();
  while (!finish) {
    if (radio.available()) {
      radio.read(msg, sizeof(msg));
      char theChar = msg[0];
      if (msg[0] != 2) {
        theMessage.concat(theChar);
      } else {
        Serial.println("HIM: " + theMessage);
        finish = true;
      }
    }else{
      finish = true;
    }
    return 1;
  }
  return 0;
  }*/
