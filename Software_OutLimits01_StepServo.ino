
//Barrier Parking Code of @OutLimits

//Developed by David Morales Arellano
//Date: 21/10/23

#include <Stepper.h>

const int Trigger01 = 2;   //Pin digital 2 para el Trigger del sensor 01
const int Echo01 = 3;   //Pin digital 3 para el Echo del sensor 01

const int StepsRevolution = 2048;
const int MovementSteps90 = StepsRevolution/4;

long t03; 
long d03;

long t02; 
long d02;

Stepper stepperName = Stepper(StepsRevolution, 8, 10, 9, 11);


void proximity() { 

    digitalWrite(Trigger01, HIGH);
    delayMicroseconds(10); 
    digitalWrite(Trigger01, LOW);  

    t03 = pulseIn(Echo01, HIGH); 
    d03= t03/59;

    t02 = pulseIn(Echo01, HIGH); 
    d02= t02/59;  
         
    
    Serial.print("Distancia 01: ");
    Serial.print(d03);     
    Serial.print("cm");
    Serial.println();
    Serial.print(d02);
    Serial.print("cm");
    Serial.println();
    Serial.println();
    delay(500);
  } 


void setup() {

  Serial.begin(9600);  //iniciailzamos la comunicación (Ultrasonidos 01)
  pinMode(Trigger01, OUTPUT); //pin como salida (Ultrasonidos 01)
  pinMode(Echo01, INPUT); //pin como entrada (Ultrasonidos 01)
  digitalWrite(Trigger01, HIGH);  //Inicializamos el pin con 0 (Ultrasonidos 01)
  
  stepperName.setSpeed(15); //RPM servo

}

void loop() {

  proximity();

  if (d03<=20){

    stepperName.step(-MovementSteps90); 
    delay(4000);

    while (d03<=20) {
      
      proximity();
      delay(100);
    }
  
    stepperName.step(MovementSteps90);

  }
}
