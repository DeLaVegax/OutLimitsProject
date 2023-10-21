
//Barrier Parking Code of @OutLimits

//Using MicroServo SG90

//Developed by David Morales Arellano
//Date: 12/10/23

//LIBRERIAS
#include <Servo.h>

Servo servoMotor;  


//VARIABLES
const int Trigger01 = 12;   //Pin digital 12 for Trigger01
const int Echo01 = 13;   //Pin digital 13 for Echo01

const int Trigger02 = 2;   //Pin digital 2 for Trigger02
const int Echo02 = 3;   //Pin digital 3 for Echo02

int redPin = 4;     //Pin digital 4 for Red Pin
int greenPin = 5;     //Pin digital 5 for Green Pin
int bluePin = 6;     //Pin digital 6 for Blue Pin
int delayTime = 10;
int timeSet = 0;


long t01; 
long d01;

long t02; 
long d02;


//FUNCIONES
void serial_data(){

  Serial.print("Distancia 01: ");
  Serial.print(d01);     
  Serial.print("cm");
  Serial.println();
  Serial.print("Distancia 02: ");
  Serial.print(d02);     
  Serial.print("cm");
  Serial.println();
  Serial.println();
  delay(500);
}


void proximity() { 

    digitalWrite(Trigger01, HIGH);
    delayMicroseconds(10); 
    digitalWrite(Trigger01, LOW);

    t01 = pulseIn(Echo01, HIGH);
    d01 = t01/59;  


    digitalWrite(Trigger02, HIGH);
    delayMicroseconds(10); 
    digitalWrite(Trigger02, LOW);
    
    t02 = pulseIn(Echo02, HIGH);   
    d02 = t02/59;          
    
    serial_data(); //Serial Data incoming
  } 


void setup() {

  Serial.begin(9600);  //Starting up comunication

  pinMode(Trigger01, OUTPUT); //pin as exit (01)
  pinMode(Echo01, INPUT); //pin as entrance (01)
  digitalWrite(Trigger01, HIGH);  //Starting up pin (01)

  pinMode(Trigger02, OUTPUT); //pin as exit (02)
  pinMode(Echo02, INPUT); //pin as entrance (02)
  digitalWrite(Trigger02, HIGH);  //Starting up pin (02)
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);


  servoMotor.attach(31);
}


void loop() {

  proximity();
  servoMotor.write(0);

  if (d01<=20 || d02 <=20){

    digitalWrite(redPin,0);
    digitalWrite(greenPin,255);
    digitalWrite(bluePin,0);

    servoMotor.write(100); 

    delay(4000);

    while (d01<=20 || d02 <=20) {
      
      proximity();
      delay(100);
      timeSet += 1;
      
      if (timeSet >=20){
        //EASTER EGG
        for (int i = 0; i <= 255; i++) {
          setRGBColor(i, 255 - i, 0); 
          delay(delayTime);
        }
        for (int i = 0; i <= 255; i++) {
          setRGBColor(0, i, 255 - i); 
          delay(delayTime);
        }
        for (int i = 0; i <= 255; i++) {
          setRGBColor(i, 0, 255 - i);
          delay(delayTime);
        }
      }
    }
    
    timeSet = 0;

    digitalWrite(redPin,255);
    digitalWrite(greenPin,0);
    digitalWrite(bluePin,0);

    servoMotor.write(0);

  }
}


void setRGBColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
