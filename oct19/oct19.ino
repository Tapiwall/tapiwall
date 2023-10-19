#include <Servo.h> 

#define S0 6 //sensor de color S0 R 
#define S1 7 //sensor de color S1 naranja
#define S2 8 //sensor de color S2 naranja
#define S3 9 //sensor de color S3 R
#define sensorOut 10 //sensor de color OUT azul
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
________________________________________________DECLARACIONES
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
Servo topservo;
Servo bottomservo;
//Valores del sensor de color
int R = 0, G = 0, B = 0;
int frequency = 0;
//Servos
int pos_0 = 0, pos_1 = 30, pos_2 = 60, pos_3 = 90;
int color = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//al detectar una tapa se se declarara como "true" y se va a parar la cinta que mueva las tapas
bool tapa = false;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MINIMO_RGB=3000, MAXIMO_RGB=0;
int maximoR =MAXIMO_RGB, minimoR =MINIMO_RGB, maximoG =MAXIMO_RGB, minimoG =MINIMO_RGB, maximoB =MAXIMO_RGB, minimoB =MINIMO_RGB;
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__________________________________________________ARRAY
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int rojo[2];
int verde[2]
int azul[2];
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__________________________________________________SETUP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void setup() {
  
  setPines();
  setServo();

  Serial.begin(9600);
}

void setPines(){
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void setServo(){
  topservo.attach(3);
  bottomservo.attach(2);
}
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
___________________________________________________LOOP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void loop() {
  resetServo();
  color = readColor(maximoR, minimoR, maximoG, minimoG, maximoB, minimoB);
  interruptor(color);// hacer array de 7 valores, color y los maximos y minimos para que sus valores no se reseteen///////////////////////////////////////////
}

void resetServo(){
  tapa = false;
  topservo.write(pos_0);
  delay(500);
}
// Custom Function - readColor()
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_________________________________________________READ COLOR
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int readColor(int maximoR, int minimoR, int maximoG, int minimoG, int maximoB, int minimoB) {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(500);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(500);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");
  Serial.print(frequency);
  Serial.println("  ");
  delay(500);

  if (maximoR < R){
    maximoR = R;
  }
  if (minimoR > R){
    minimoR = R;
  }
  if (maximoG < G){
    maximoG = G;
  }
  if (minimoG > G){
    minimoG = G;
  }
  if (maximoB < B){
    maximoB = B;
  }
  if (minimoB > B){
    minimoB = B;
  }
  Serial.print("max rojo: ");
  Serial.print(maximoR);
  Serial.print("  ");
  Serial.print("min rojo: ");
  Serial.print(minimoR);
  Serial.print("  ");
  Serial.print("max verde: ");
  Serial.print(maximoG);
  Serial.print("  ");
  Serial.print("min verde: ");
  Serial.print(minimoG);
  Serial.print("  ");
  Serial.print("max azul: ");
  Serial.print(maximoB);
  Serial.print("  ");
  Serial.print("min azul: ");
  Serial.print(minimoB);
  Serial.print("  ");

/______________________________________________IF  (COLORES)/
  if 
  (R<45 && G<65 && G>55) {
    Serial.println("Rojo");
    tapa = true;
    color = 0;
    } 
  else if (R<40 && R>20 && G<60 && G>45) {
    Serial.println("Verde");
    tapa = true;
    color = 1;
  } 
  else if (G<50 && G>30 && B>26) {
    Serial.println("Azul");
    tapa = true;
    color = 2;
  }
  return(color);
}
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
________________________________________________INTERRUPTOR
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void interruptor(int color){

  switch (color) {
    case 0:
    bottomservo.write(0);
    break;
    case 1:
    bottomservo.write(30);
    break;
    case 2:
    bottomservo.write(60);
    break;
    case 3:
    bottomservo.write(90);
    break;
  }
  delay(300);
}