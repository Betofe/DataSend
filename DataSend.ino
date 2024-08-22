// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial espSerial(1);
byte character = 0;
const unsigned int MAX_MESSAGE_LENGTH = 12;
int value1;
float value2, value3;

void setup()
{
    Serial.begin(115200);
    espSerial.begin(115200, SERIAL_8N1, 18, 19);
}

// Add the main program code into the continuous loop() function
void loop()
{
    //Serial.println("hello");
    espSerial.write("request\n");
    //Serial.write("hellooooo\n");
    while (espSerial.available()) {

        //Create a place to hold the incoming message
        static char message[MAX_MESSAGE_LENGTH];
        static unsigned int message_pos = 0;

        //Read the next available byte in the serial receive buffer
        char inByte = espSerial.read();

        //Message coming in (check not terminating character) and guard for over message size
        if (inByte != '!' && (message_pos < MAX_MESSAGE_LENGTH - 1))
        {
            //Add the incoming byte to our message
            message[message_pos] = inByte;
            message_pos++;
        }
        //Full message received...
        else
        {
            //Add null character to string
            message[message_pos] = '\0';

            // Convert the received message to float values
            int parsedValues = sscanf(message, "%d,%f,%f", &value1, &value2, &value3);

            if (parsedValues == 3) {
                // Print the received values
                Serial.print("Value 1: ");
                Serial.println(value1);
                Serial.print("Value 2: ");
                Serial.println(value2);
                Serial.print("Value 3: ");
                Serial.println(value3);
            }
            else {
                Serial.println("Error parsing values from message");
            }

            //Reset for the next message
            message_pos = 0;
        }
    }
    delay(500);
}
