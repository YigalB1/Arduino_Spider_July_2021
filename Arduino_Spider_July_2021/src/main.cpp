#include <Arduino.h>
#include "CommandClass.h"

// Sep 5
//Adafruit_PWMServoDriver servos_control = Adafruit_PWMServoDriver();
Command current_command = Command();
spider_anatomy my_spider = spider_anatomy();


int RED_LED  = 5; // red led
int YELLOW_LED  = 6; // yellow led
int GREEN_LED  = 7; // Green Led 



String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String commandString = "";
boolean isConnected = false;
int serialData;

int stage; // 0: wait for line. 1: got Servo num, wait for angle
            // 2 got angle, wait for time, 3: got time, wait for EOL.

//void getCommand();
bool led_stat = false;
bool red_led_on = false;  // to toggle with every communication
bool yellow_led_on = false; 



void setup() {
  
  my_spider.servos_control.begin();
  my_spider.servos_control.setPWMFreq(60);

  inputString.reserve(200); // reserve 200 bytes for the inputString:

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  //boolean isConnected = false;
  Serial.begin(9600);
  Serial.println("I am Arduino. I am alive.");

  my_spider.leds.led_green = GREEN_LED;
  my_spider.leds.led_yellow = YELLOW_LED;
  my_spider.leds.led_red = RED_LED;

  my_spider.leds.set_led_on(RED_LED);
  my_spider.leds.set_led_on(YELLOW_LED);
  my_spider.leds.set_led_on(GREEN_LED);
  delay(500);
  my_spider.leds.set_led_off(RED_LED);
  my_spider.leds.set_led_off(YELLOW_LED);
  my_spider.leds.set_led_off(GREEN_LED);

/*
  // show signs of life
  //for (int i=0;i<2;i++) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(400);
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(400);   
  //} // end of for loop
  */
} // end of SETUP





void loop() {


current_command.inputString ="MOTOR 11 22 33 44"; // for debug 
current_command.analyze();
current_command.execute_command(my_spider);
delay (2000);
current_command.inputString ="LED GREEN ON"; // for debug 
current_command.analyze();
current_command.execute_command(my_spider);
delay (2000);
current_command.inputString ="LED GREEN OFF"; // for debug 
current_command.analyze();
current_command.execute_command(my_spider);
delay (2000);
current_command.inputString ="LED YELLOW ON"; // for debug 
current_command.analyze();
current_command.execute_command(my_spider);
delay (2000);
current_command.inputString ="LED YELLOW OFF"; // for debug 
current_command.analyze();
current_command.execute_command(my_spider);
delay (2000);
current_command.inputString ="LED RED ON"; // for debug 
current_command.analyze();
current_command.execute_command(my_spider);
delay (2000);
current_command.inputString ="LED RED OFF"; // for debug 
current_command.analyze();
current_command.execute_command(my_spider);
delay (2000);

current_command.inputString ="MOTOR 0 0 060 0200"; // for debug 
current_command.analyze();
current_command.execute_command(my_spider);

delay (2000);



return;




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


} // of LOOP




/*
void getCommand()
{
  if(inputString.length()>0)
  {
     commandString = inputString.substring(1,5);
  }
} // of getCommand()
*/

void serialEvent() {
  if (stringComplete) 
    return; // at first, stop reading commands until prev command was parsed

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
