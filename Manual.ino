/*Include library*/ 
#include <LiquidCrystal.h> //Include LCD library

/*Assign the variable*/ 
int PV; //Storable value which will be the LDR value
int CO; //Control Output Control
int ScreenNumber;

/*INPUT/Button settings*/ 
const int PushB1 = 10; //pin for the first pb 
const int PushB2 = 9;  //pin for the second pb
const int PushB3 = 8;  //pin for the third pb

int LastState1; //state for the first pb
int LastState2; //state for the second pb
int LastState3; //state for the third pb

int CurrentState1;  //state for the first pb
int CurrentState2;  //state for the second pb
int CurrentState3;  //state for the third pb

/*OUTPUT settings*/ 
int LED = 13; //pin for the actuator (LED)
int LDR = A1; //pin for the sensor(LDR)

/*LCD settings*/ 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //pins that the LCD is connected to


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //baud rate of 9600
lcd.begin(16,2); //format of the LCD
pinMode(PushB1, INPUT_PULLUP); //identifying PushB1 as an input
pinMode(PushB2, INPUT_PULLUP); //identifying PushB2 as an input
pinMode(PushB3, INPUT_PULLUP); //identifying PushB3 as an input
pinMode(LED, OUTPUT); //identifying LED as an output
}

void loop() {
  // put your main code here, to run repeatedly:



PV = analogRead(LDR); //PV is an analog read
analogWrite(LED, CO); //CO is an analog write

/*CAP*/
if (SetP>255){ 
  SetP = 255; //maximum value of 255 for the setpoint
  
}
if (SetP<0){
   SetP = 0; //minimum value of 0 for the setpoint
}


/*PUSH BUTTON UP SETTINGS*/ 

LastState1 = CurrentState1;  
CurrentState1 = digitalRead(PushB1);
 if (LastState1 == 1 && CurrentState1 == 0){
   if(ScreenNumber == 1){ //if the current state of the pb1 is 1 add 25 to the CO
    CO = CO + 25;
   }
   
 }

/*PUSH BUTTON DOWN SETTINGS*/ 

LastState2 = CurrentState2;
CurrentState2 = digitalRead(PushB2);
 if (LastState2 == 1 && CurrentState2 == 0){
   if(ScreenNumber == 1){ //if the current state of the pb2 is 1 substract from to the CO
    CO = CO - 25;
   }
   
 }
 

/*PUSH BUTTON CHANGE PAGE SETTINGS*/ 

LastState3 = CurrentState3;
CurrentState3 = digitalRead(PushB3);
 if (LastState3 == 1 && CurrentState3 == 0){
  ScreenNumber = ScreenNumber + 1;
  if(ScreenNumber > 1){ //if the current state of the pb3 is 1 change LCD screen
    ScreenNumber = 0;
  }
 }

  switch(ScreenNumber){
    case 0:
  lcd.setCursor(0, 1); //set the cursor to 0,1
  lcd.print("PV = "); //print PV = 
  lcd.print(PV); //print the value of PV 
  lcd.print(" "); 
    break;
    case 1:
    lcd.setCursor(0, 1); //set the cursor to 0,1
  lcd.print("CO = "); //print CO = 
  lcd.print(CO); //print the value of CO
  lcd.print("    ");
  default:
  break;
  }

}
