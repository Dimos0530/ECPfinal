
#include <LiquidCrystal.h>

int PV; //Storable value which will be the LDR value
int CO; //Control Output Control variable
int SetP = 0; //variable for the setpoint
int Hys = 50; //create a variable and set a value for hysteresis
int ScreenNumber; //create a variable for the screennumber


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
  
PV = analogRead(LDR); //pv is an analog read

/*HYSTERISIS SETTINGS*/
if(PV <= SetP-Hys){ // if the pv is  smaller than the sp-hys the CO will be 255
    CO = 255;
  //analogWrite(LED, CO);  
}
  if(PV >= SetP+Hys){ // if the pv is  smaller than the sp-hys the CO will be 255
    CO = 0;
 // analogWrite(LED, CO);  
}
analogWrite(LED, CO); //CO is an analog write
/*CAP*/
if (SetP>1023){
  SetP = 1023;//maximum bit value of 1023 for the setpoint
  
}
if (SetP<0){
   SetP = 0; //minimum bit value of 0 for the setpoint
}




/*PUSH BUTTON UP SETTINGS*/ 

LastState1 = CurrentState1;
CurrentState1 = digitalRead(PushB1);
 if(LastState1 == 1 && CurrentState1 == 0){
   if(ScreenNumber == 1){  //increase the sp by 50 and the hys if the screennumber is 1 and the pb1 is high
    SetP = SetP + 50;
   }
   if(ScreenNumber == 0){
    Hys++;
   }
 }

/*PUSH BUTTON DOWN SETTINGS*/ 

LastState2 = CurrentState2;
CurrentState2 = digitalRead(PushB2);
 if(LastState2 == 1 && CurrentState2 == 0){
   if(ScreenNumber == 1){ //decrease the sp by 50 and the hys if the screennumber is 2 and the pb2 is high
    SetP = SetP - 50;
   }
   if(ScreenNumber == 0){
    Hys--;
   }
 }

/*PUSH BUTTON CHANGE PAGE SETTINGS*/ 

LastState3 = CurrentState3;
CurrentState3 = digitalRead(PushB3);
 if(LastState3 == 1 && CurrentState3 == 0){
  ScreenNumber = ScreenNumber + 1;
  if(ScreenNumber > 1){
    ScreenNumber = 0; //if the current state of the pb3 is 1 change LCD screen
  }
 }


  switch(ScreenNumber){
    case 0:
  lcd.setCursor(0, 1); //set the cursor to 0,1
  lcd.print("PV = ");//print PV =
  lcd.print(PV); //print the value of PV
  lcd.print(" ");
  lcd.setCursor(0, 0); //set the cursor to 0,0
  lcd.print("Hyst = ");//print hys = 
  lcd.print(Hys); //print the value of hys
  lcd.print(" ");
    break;
    case 1:
  lcd.setCursor(0, 1); //set the cursor to 0,1
  lcd.print("PV = "); //print pv =
  lcd.print(PV); //print the value of pv
  lcd.print("    ");
  lcd.setCursor(0, 0); //set the cursor to 0,0
  lcd.print("SP = "); //print SP = 
  lcd.print(SetP); //print the value of setpoint
  lcd.print("    ");
  default:
  break;
  }
int PVdisplay = map(PV, 0, 1023, 0, 255); //map the value of pv
Serial.print(SetP); //print the value of sp
Serial.print("\t");
Serial.print(Hys); //print the value of hys
Serial.print("\t");
Serial.println(PV); //print the value of pv


}
