#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 //OLED display width, in pixels
#define SCREEN_HEIGHT 64

//Define pins
#define startBtnPIN 2//D2
#define selectBtnPIN 3 //D3
#define upBtnPIN 4 //D4
#define downBtnPIN 5 //D5
#define servoBtnPIN 6//d6

#define OLED_RESET      -1 //Reset pin #(or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D // <See datasheet for Address; 0x3D for 128x64, 0x3c for 128x32>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


bool stateStartBtn=0;
bool stateSelectBtn=0;
bool stateUpBtn=0;
bool stateDownBtn=0;
bool mode=0;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
/*Programa arduino desde cero*/
Servo servo1;
int PINSERVO=7;
int PULSOMIN=1000;
int PULSOMAX=2000;

int pos = 0;    // variable to store the servo position


void setup() {
  //Las entradas analogicas no requieren inicialización
  // put your setup code here, to run once:
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  servo1.attach(PINSERVO,PULSOMIN,PULSOMAX);
  Serial.begin(9600);
  Wire.begin();

  //SSD1306_SWITCHCAPVCC=generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC,SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);//Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  //setup button
  pinMode(startBtnPIN,INPUT_PULLUP);
  pinMode(selectBtnPIN,INPUT_PULLUP);
  pinMode(upBtnPIN,INPUT_PULLUP);
  pinMode(downBtnPIN, INPUT_PULLUP);

  //Mensaje1();

}

void loop() {

//Servomotor();
  // put your main code here, to run repeatedly:
  readButtons();

}

void readButtons()
{
  //======== servoPIN =======

 if(digitalRead(servoBtnPIN)==LOW)
  {
     stateStartBtn=1;
    Serial.println("start button is pressed");
    if(mode==0)
    {      
       MensajeServoON();
       ServoProgram();
       //Servomotor();
    }
   
  }
  else if(digitalRead(servoBtnPIN)==HIGH)
  {
   
    MensajeServoOFF();
  }

}


void screenReady()
{
  //Display start
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("....Hola");
  display.println("      ");
  display.println("press Start button");
  display.println("      ");
  display.println("select to configure");
  display.display();
  delay(1000);
}

void Mensaje1()
{
  display.setCursor(0,0);
  display.println("..Pograma1_Servomotor");
  display.println("      ");
  display.println("press Start button");
  display.println("      ");
  display.println("select to configure");
  display.display();
  delay(1000);
}

void MensajeServoON()
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("....SERVOMOTOR ON....");
  display.display();
  //delay(1000);
}

void MensajeServoOFF()
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("....SERVOMOTOR OFF...");
  display.display();
  //delay(1000);
}


void Servomotor()
{
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}


void MensajeStart()
{
  display.clearDisplay();
      display.setCursor(0,0);
      display.println("The process");
      display.println("        ");
      display.println("has started LLUIS!");
      display.display();
}

void ServoProgram()
{
  servo1.write(0);
  delay(2000);
  servo1.write(180);
  delay(2000);
 
}
