#include <SPI.h>
#include <SD.h>
File myFile;

const int LED_PIN_GREEN = 0; // GPIO 0 equals D3
const int LED_PIN_RED = 2;   // GPIO 2 equal D4

String dataRead = "";
String nameFile = "color.txt";

void setup()
{
    pinMode(LED_PIN_GREEN, OUTPUT);
    pinMode(LED_PIN_RED, OUTPUT);

    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.print("Initializing SD card...");

    if (!SD.begin(10))
    {
        Serial.println("initialization failed!");
    }
    else
    {
        Serial.println("initialization done.");
        // open the file. note that only one file can be open at a time,
        // so you have to close this one before opening another.
        myFile = SD.open(nameFile);
        // if the file opened okay, read to it:
        if (myFile)
        {
            Serial.print("Reading from ");
            Serial.println(nameFile);

            while (myFile.available())
            {
                dataRead = myFile.readString();
            }
            // close the file:
            myFile.close();
            Serial.println("done.");
        }
        else
        {
            // if the file didn't open, print an error:
            Serial.print("error opening ");
            Serial.println(nameFile);
        }
        if (dataRead.equals("GREEN"))
        {
            digitalWrite(LED_PIN_GREEN, HIGH);
            digitalWrite(LED_PIN_RED, LOW);
        }
        else
        {
            digitalWrite(LED_PIN_GREEN, LOW);
            digitalWrite(LED_PIN_RED, HIGH);
        }
    }
}
void loop()
{
    // nothing happens after setup
}
