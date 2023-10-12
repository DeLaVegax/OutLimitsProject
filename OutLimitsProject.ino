
//Barrier Parking Code of @OutLimits

//Developed by David Morales Arellano
//Date: 12/10/23

#include <Stepper.h>

const int Trigger = 12;   //Pin digital 2 para el Trigger del sensor
const int Echo = 13;   //Pin digital 3 para el Echo del sensor


const int StepsRevolution = 2048;
const int MovementSteps90 = StepsRevolution/4;

Stepper stepperName = Stepper(StepsRevolution, 8, 10, 9, 11);


void setup() {

  Serial.begin(9600);  //iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT); //pin como entrada
  digitalWrite(Trigger, HIGH);  .//Inicializamos el pin con 0
  
  stepperName.setSpeed(15); //Set the RPM of the stepper motor

}

void loop() {

  long t; 
  long d; 

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);         
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); 
  d = t/59;             
  
  Serial.print("Distancia: ");
  Serial.print(d);     
  Serial.print("cm");
  Serial.println();
  delay(2000);        


  if (d<=20){
    stepperName.step(-MovementSteps90);
    delay(4000);
    stepperName.step(MovementSteps90);
  }
}
  


