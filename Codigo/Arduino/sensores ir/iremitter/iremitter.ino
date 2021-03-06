#include <IRremote.h>

#define tempUp  0xD5C3694D
#define tempDw  0xBAF71688
#define on 0x7192B522
#define off 0xD770F1FF

unsigned int pOn[60] = {13674,8650,3950,550,1500,500,500,500,500,500,500,500,1500,500,500,550,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,450,550,450,1550,550,1500,500,1500,400,600,500,500,500,500,450,550,500,500,500,1500,550,1450,500,1550,500};
unsigned int pOff[60] = {15692,8650,3950,550,1500,500,500,500,500,500,500,500,1500,500,500,550,450,550,500,400,1600,500,1500,450,550,500,500,500,500,500,500,450,550,500,500,500,500,500,500,550,450,550,500,500,500,500,1500,500,500,500,1500,450,550,500,500,500,500,500,1500,500};
unsigned int tempU[60] = {14712,8600,3950,600,1450,500,550,450,550,500,500,500,1450,550,500,500,450,500,500,550,500,500,500,500,500,450,550,500,1500,500,500,450,550,550,450,500,1500,550,450,550,450,500,500,550,500,450,550,500,500,500,500,500,500,500,500,450,550,550,450,550};
unsigned int tempD[60] = {16110,8600,4000,550,1450,550,500,500,500,500,500,500,1450,550,500,500,500,500,500,500,500,500,550,500,450,550,500,500,1450,450,600,500,500,500,500,500,500,500,1500,500,1500,450,1550,550,450,550,500,450,550,500,500,500,1450,500,1500,550,1500,450,1550,500};

IRsend irsend;

void setup()
{
  Serial.begin(115200);
  Serial.println("Pronto");
}

void loop() {
  irsend.sendLG(off,32);
  //lerdado();
}

void lerdado(){
   if(Serial.available()){
    String letra = Serial.readString();      
    if(letra == "on"){ 
      irsend.sendLG(on, 16);
      irsend.sendRaw(pOn, 60, 32);
    }   
     if(letra == "off"){ 
      //irsend.sendLG(on, 16);
      irsend.sendRaw(pOff, 60, 32);
    }   
    if(letra == "td"){
        //irsend.sendLG(adress, power);
        irsend.sendRaw(tempD, 60, 32);
    }
    
    if(letra == "tu"){
       //irsend.sendLG(adress, power);
       irsend.sendRaw(tempU, 60, 32);
    }
    Serial.println("Comando: "+letra);
  }
}

