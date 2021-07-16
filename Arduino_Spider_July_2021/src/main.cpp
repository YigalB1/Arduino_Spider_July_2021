#include <Arduino.h>

int RED_LED  = 5; // red led
int YELLOW_LED  = 6; // yellow led
int GREEN_LED  = 7; // Green Led 
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  boolean isConnected = false;
  Serial.begin(9600);

  // show signs of life
  for (int i=0;i<2;i++) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(400);
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(400);   
  }
}


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";
boolean isConnected = false;
int serialData;

int stage; // 0: wait for line. 1: got Servo num, wait for angle
            // 2 got angle, wait for time, 3: got time, wait for EOL.

void getCommand();
bool led_stat = false;
bool red_led_on = false;  // to toggle with every communication
bool yellow_led_on = false; 


void loop() {

  if (yellow_led_on) {
    digitalWrite(YELLOW_LED, LOW);
    yellow_led_on = false;
  }
  else {
    digitalWrite(YELLOW_LED, HIGH);
    yellow_led_on = true;
  }
  delay(500);




   if (Serial.available()) {
     serialData = Serial.read();
     if (red_led_on) {
      digitalWrite(RED_LED, LOW);
      red_led_on = false;
     }
     else {
       digitalWrite(RED_LED, HIGH);
       red_led_on = true;
     }

     if (led_stat) {
       digitalWrite(LED_BUILTIN, LOW);
       led_stat = false;
       //digitalWrite(YELLOW_LED, HIGH);
       digitalWrite(GREEN_LED, LOW);
     }
     else {
       digitalWrite(LED_BUILTIN, HIGH);
       led_stat = true;
       //digitalWrite(YELLOW_LED, LOW);
       digitalWrite(GREEN_LED, HIGH);
     }
   } // of if Serial.available()

    

    //serialData = Serial.read();
    //if(serialData == '1'){
    //  digitalWrite(LED_BUILTIN, HIGH);
    //}
    //else {
    //  digitalWrite(LED_BUILTIN, LOW);
    //}
//  }
 
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
  //delay(500);                       // wait for half a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
  //delay(500);        




  return;


} // of loop





void getCommand()
{
  if(inputString.length()>0)
  {
     commandString = inputString.substring(1,5);
  }
} // of getCommand()

/*
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
} // of serial event
*/