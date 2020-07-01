#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

File myFile;

const int LED_PIN_GREEN = 0; // GPIO 0 equals D3
const int LED_PIN_RED = 2;   // GPIO 2 equal D4

String dataRead = "";
String nameFile = "color.txt";

uint8_t addressEprom = 0;

void setup()
{
    pinMode(LED_PIN_GREEN, OUTPUT);
    pinMode(LED_PIN_RED, OUTPUT);

    // start a EEPROM syze 20 Bytes (4 min).
    EEPROM.begin(4);

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
                dataRead = myFile.readString();

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

        // if EPROM != SDCARD then update value EPROM
        if (EEPROM.read(addressEprom) != (dataRead.toInt()))
        {
            EEPROM.write(addressEprom, dataRead.toInt());
            EEPROM.commit();
        }

        EEPROM.end();
    }

    digitalWrite(LED_PIN_GREEN, EEPROM.read(addressEprom) == LED_PIN_GREEN);
    digitalWrite(LED_PIN_RED, EEPROM.read(addressEprom) == LED_PIN_RED);
}

void loop()
{
    // nothing happens after setup
}
