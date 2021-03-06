#include <SPI.h>
#include <SD.h>

File myFile;

String contentWrite = "GREEN";
String nameFile = "color.txt";

void setup()
{
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
        myFile = SD.open(nameFile, FILE_WRITE);
        // if the file opened okay, write to it:
        if (myFile)
        {
            Serial.print("Writing to ");
            Serial.println(nameFile);

            myFile.println(contentWrite);

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
    }
}
void loop()
{
    // nothing happens after setup
}
