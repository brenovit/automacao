#include <IRremote.h>

#define adress      0x4004     // Panasonic address (Pre data) 
#define volu  0x1000405
#define vold  0x1008485
#define power 0x100BCBD

unsigned int volUp[100] = {14058, 3550, 1650, 500, 350, 500, 1200, 550, 350, 500, 350, 500, 350, 500, 350, 550, 350, 500, 350, 500, 350, 500, 400, 450, 400, 500, 350, 500, 350, 550, 1200, 500, 350, 500, 350, 500, 400, 500, 350, 500, 350, 500, 350, 550, 350, 500, 350, 550, 300, 550, 1200, 500, 350, 500, 350, 550, 350, 500, 350, 500, 350, 550, 300, 500, 400, 500, 350, 550, 300, 500, 350, 500, 400, 500, 350, 550, 300, 500, 1250, 500, 350, 550, 300, 500, 400, 500, 350, 500, 350, 550, 300, 500, 400, 500, 1200, 500, 400, 500, 1200, 550};
unsigned int volDown[100] = {12618, 3500, 1700, 450, 400, 450, 1250, 500, 400, 450, 400, 450, 400, 500, 350, 500, 400, 450, 400, 450, 400, 500, 350, 500, 400, 450, 400, 450, 400, 500, 1250, 450, 400, 500, 350, 500, 400, 450, 400, 450, 400, 500, 350, 500, 400, 450, 400, 450, 400, 500, 1250, 450, 400, 450, 400, 500, 350, 500, 400, 450, 400, 450, 400, 500, 400, 450, 400, 450, 1250, 500, 400, 450, 400, 450, 400, 500, 350, 500, 1250, 450, 400, 500, 350, 500, 1250, 450, 400, 500, 400, 450, 400, 450, 400, 500, 1250, 450, 400, 450, 1250, 500};

IRsend irsend;

void setup()
{
  Serial.begin(9600);
  Serial.println("Pronto");
}

void loop() {
 if(Serial.available()){
    String letra = Serial.readString();      
    if(letra == "m"){
      for(int i = 0; i < 10; i++){
        irsend.sendPanasonic(adress, volu);
      }
    }
    if(letra == "n"){
      for(int i = 0; i < 10; i++){
        irsend.sendPanasonic(adress, vold);
      }
    }
    if(letra == "p"){
        irsend.sendPanasonic(adress, power);
    }
    Serial.println("Comando: "+letra); 
  }
}


