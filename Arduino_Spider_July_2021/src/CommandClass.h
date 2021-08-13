#include <Arduino.h>
#include "SpiderClass.h"


class Command {
    #define MAX_NUM_OF_PARAMS 20 // assuming no more than 20 parameters
    #define DUMB_VALUE 9999  // not a valid value
    #define COMMENT 0
    #define COMMAND 1
    #define ILEGAL  2

    public:
    String inputString = "";         // a string to hold incoming data
    boolean stringComplete = false;  // whether the string is complete
    int line_type; // holds the type of the line: command/comment/ilegal
    String cmd_str = "";
    int num_of_params = 0;  
    bool valid_parameters = false;
    bool valid_command_found = false;

    String params[MAX_NUM_OF_PARAMS];
    int delimiters[MAX_NUM_OF_PARAMS]; 
    
    String InString;
    
    void init() {
        inputString.reserve(200);
        Serial.println("Starting init in Command class");
        for ( int i = 0; i < MAX_NUM_OF_PARAMS; i++)  {
            delimiters[i]=DUMB_VALUE; // aka no value
        } // of for loop
    }; // of init()

    void analyze() {
        Serial.print("0) input_string: ");
        Serial.println(inputString);

        //bool found_command = false;
        valid_command_found = false;
        num_of_params = 0;  

        
        if (inputString.indexOf(" ") == 0 ) {
            line_type = ILEGAL;
            Serial.println("ILEGAL");
            return;
        }

        if (inputString.indexOf("#") == 0 ) {
            line_type = COMMENT;
            Serial.println("COMMENT");
            return;
        }

        // Should be a command
        int delim_space = inputString.indexOf(" ");
        int delim_eol   = inputString.indexOf("\n");
        
        if ( delim_space == -1 ) { // one word must be a command
            cmd_str = inputString;
            inputString = "";
            line_type = COMMAND;
        }
        else { // extract the command from the input string
            cmd_str = inputString.substring(0,delim_space); 
            inputString.remove(0,delim_space);
        };
        //Serial.print("1) delimiter:  ");
        //Serial.println(delim_space);
        //Serial.print(" inputString: ");
        //Serial.println(inputString);

        // read pamaters 
        // check if the command is part os the allowed commands
        Serial.print("cmd_str: ");
        Serial.println(cmd_str);

        delim_space = inputString.indexOf(" ");
        delim_eol   = inputString.indexOf("\n");
        //Serial.print("2) delimiter:  ");
        //Serial.println(delim_space);
        //Serial.print(" inputString: ");
        //Serial.println(inputString);
        //Serial.print(" inputString length: ");
        //Serial.println(inputString.length());
        

        // collect all parameters 

        while (inputString.length() > 0) {
            delim_space = inputString.indexOf(" ");
            delim_eol   = inputString.indexOf("\n");
            //Serial.print("..inloop a) delimiter:");
            //Serial.println(delim_space);
            //Serial.print(" inputString:");
            //Serial.println(inputString);

            // remove leading spaces
            if (delim_space == 0 ) // first member is space, then delete it and skip 
            {
                inputString.remove(0,1);
                continue;
            } // of if

            


            // input_string has a value (not empty, no space)
            delim_space = inputString.indexOf(" ");
            delim_eol   = inputString.indexOf("\n");

            //Serial.print("..inloop b) delimiter:  ");
            //Serial.println(delim_space);
            //Serial.print("..inloop b) delimiter EOL:  ");
            //Serial.println(delim_eol);
            //Serial.print(" inputString: ");
            //Serial.println(inputString);

            if (delim_space == -1) { // last parameter
                params[num_of_params++] = inputString;
                inputString = "";
                continue;
            }

            Serial.print("XXXXX ..inloop c) delimiter:  ");
            Serial.println(delim_space);
            Serial.print(" inputString: ");
            Serial.println(inputString);
            Serial.print(" num_of_params: ");
            Serial.println(num_of_params);


            // we have at least one more space
            params[num_of_params++] = inputString.substring(0,delim_space);
            inputString.remove(0,delim_space);
       

        } // of while loop



//                if (CMD_STR == "MOTOR") {
//            Serial.println("motor");
//        }

    };

    void execute_command(spider_anatomy _spider) {
        Serial.print(" *** in execute_command. cmd_str = ");
        Serial.println(cmd_str);
        Serial.print(" params[0]: ");
        Serial.print(params[0]);
        Serial.print(" params[1]: ");
        Serial.println(params[1]);



        if (cmd_str == "MOTOR") {
            valid_command_found = true;
            execute_motor_command(_spider);
            return;
        } // of MOTOR command detect

        if (cmd_str == "LED") {
            valid_command_found = true;
            execute_led_command(_spider);
            Serial.println(" *** in execute_command. LED identified");
            return;
        } // of MOTOR command detect




        Serial.println("Command not recognized");

    } // of execute_command()

    // ************************************************

    void execute_motor_command(spider_anatomy __spider) {
        valid_parameters = true;
        Serial.print("In execute_motor_command. params[0]: "); 
        Serial.print(params[0]);
        Serial.print(" params[1]: ");
        Serial.println(params[1]);


        Serial.println("Command is MOTOR");
        if (num_of_params!=4) {
            Serial.println("ERROR: 4 pamaters are required for MOTOR command");                
            return;
        } // of if
            
        // check params are numeric
        for (int i=0;i<4;i++) {
            if (!is_str_numeric(params[0])) {
                Serial.println("ERROR in MOTOR command: not a numeric parameter");
                return;     
            } // of if
        } // of for loop
            
        int leg_num = params[0].toInt();
        int motor_num = params[1].toInt();
        int angle_num = params[2].toInt();
        int time_num = params[3].toInt();

        //__spider.left_back.motor.

        // TBD: activate servo motor accordingly
             
    } // of execute_motor_command()


    void execute_led_command(spider_anatomy __spider) {

        Serial.println("+++Command is: LED");
        Serial.print("In execute_led_command. params[0]: "); 
        Serial.print(params[0]);
        Serial.print(" params[1]: ");
        Serial.println(params[1]);





            if (num_of_params!=2) {
                valid_parameters = false;
                Serial.println("ERROR: 2 pamaters are required for LED command");                
                return;
            } // of if
            // check params and execute the command
             if (params[0] != "GREEN" && params[0] != "YELLOW" && params[0] != "RED") {
                 valid_parameters = false;
                 Serial.println("ERROR in LED command: color is wrong");
                 return;
             } // of if

             if (params[1] != "ON" && params[1] != "OFF" ) {
                 valid_parameters = false;
                 Serial.println("ERROR in LED command: should be ON or OFF");
                 return;
             } // of if



             if (params[0] == "GREEN" && params[1] == "ON") {
                __spider.leds.set_led_on(__spider.leds.led_green);
                return;
             }
             if (params[0] == "GREEN" && params[1] == "OFF") {
                __spider.leds.set_led_off(__spider.leds.led_green);
                return;
             }

            if (params[0] == "YELLOW" && params[1] == "ON") {
                __spider.leds.set_led_on(__spider.leds.led_yellow);
                return;
             }
             if (params[0] == "YELLOW" && params[1] == "OFF") {
                __spider.leds.set_led_off(__spider.leds.led_yellow);
                return;
             }

             if (params[0] == "RED" && params[1] == "ON") {
                __spider.leds.set_led_on(__spider.leds.led_red);
                return;
             }
             if (params[0] == "RED" && params[1] == "OFF") {
                __spider.leds.set_led_off(__spider.leds.led_red);
                return;
             }


            // shouldnt arrive this point
            Serial.println("What am I doing here???");

    } // of execute_led_command()




    bool is_str_numeric(String _instr) {
        
        for (int i=0;i<_instr.length();i++) {
            if (!isdigit(_instr.charAt(i))) {
                return false;
            }
        }

        return true;
    }

}; // of class command