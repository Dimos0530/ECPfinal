// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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

int LED = 13; //pin for the actuator (LED)
int LDR = A1; //pin for the sensor(LDR)
int PV = 0; //variable for the pv

int CO; //Control Output Control variable
int SetP = 0; //variable for the setpoint
int Error = 0; //variab;e for the setpoint
float pGain = 0.0; //variable for the pgain
int ScreenNumber; //create a variable for the screennumber 


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

PV = analogRead(LDR); //pv is an analog read


Error = SetP - PV; //equation for the error
CO = pGain * Error; //equation for the CO

/*CAP*/
if (SetP>1023){
  SetP = 1023;//maximum bit value of 1023 for the setpoint
  
}
if (SetP<0){
   SetP = 0; //minimum bit value of 0 for the setpoint
}

analogWrite(LED, CO); //CO is an analog write value

//print the values and variables down below on tghe serial monitor
Serial.print("SP: ");
Serial.print(SetP);
Serial.print("\t");
Serial.print("PV: ");
Serial.print(PV);
Serial.print("\t");
//Serial.print("SSE: ");
//Serial.print(Error);
Serial.println();

/*PUSH BUTTON UP SETTINGS*/  

LastState1 = CurrentState1;
CurrentState1 = digitalRead(PushB1);
 if (LastState1 == 1 && CurrentState1 == 0){
   if(ScreenNumber == 1){
    SetP = SetP + 50;
   }
   if(ScreenNumber == 0){
    pGain = pGain + 0.1; //increase the sp by 50 and the pgain by 0.1 if the screennumber is 1 and the pb1 is high
   }
 }

/*PUSH BUTTON DOWN SETTINGS*/ 

LastState2 = CurrentState2;
CurrentState2 = digitalRead(PushB2);
 if (LastState2 == 1 && CurrentState2 == 0){
   if(ScreenNumber == 1){
    SetP = SetP - 50;
   }
   if(ScreenNumber == 0){
    pGain = pGain - 0.1; ////decrease the sp by 50 and the pgain by 0.1 if the screennumber is 2 and the pb2 is high
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

//print the values and variables down below
  switch(ScreenNumber){
    case 0:
  lcd.setCursor(0, 1);
  lcd.print("PV = ");
  lcd.print(PV);
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print("pGain = ");
  lcd.print(pGain);
  lcd.print(" ");
    break;
    case 1:
     lcd.setCursor(0, 1);
  lcd.print("PV = ");
  lcd.print(PV);
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print("SP = ");
  lcd.print(SetP);
  lcd.print("     ");
  default:
  break;
  }
 /* Serial.print(Error);
  Serial.print("\t");
  Serial.print(PV);
  Serial.print("\t");
  Serial.print(SetP);
  Serial.print("\t");
  Serial.println(CO);
  delay(200);
*/
}
