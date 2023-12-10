/* 
Creation & Computation - Experiment 4 Code
Group Members: Vitor Fiacadori, Zubin Isaac, Orus Matteo Castano-Suarez, Matthew Nazarian, Jessica Patel, Yu-Shien Yang

This code was written to detect the presence of a person using a distance sensor. If a person is detected, then "active mode" is 
initiated where an 8-neopixel strip lights up in a linear fashion, displaying one pixel at a time in chronological order. 
When no one is detected, the neopixel strip enters "ambient mode", where all pixels show an even, and subtle display of the same colour.

This code was written by simply referencing the main functions used to initiate the neopixel strip and the distance sensor.
*/

#include <HCSR04.h>
#include <Adafruit_NeoPixel.h>

// The digital pin used to control the pixel strip
int pinNumber = 13;

// The number of pixels in the strip
int pixelcount = 8;

// Setting the neopixel as an object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelcount, pinNumber, NEO_GRB + NEO_KHZ800);

// Initializing distance sensor that uses digital pins 2 and 3
UltraSonicDistanceSensor distanceSensor(2, 3);

void setup () {
    // Initializing serial connection to print values from sensor
    Serial.begin(9600);
    // Setting pixels to off to begin 
    strip.begin();
    strip.show();
}

void loop () {
    // Measuring the distance and printing the value in centimeters every 500 miliseconds
    int distance = distanceSensor.measureDistanceCm();
    Serial.println(distance);
    delay(500);

    int threshold = 150; // Length of step is 1.87m

    // if someone is on a step, the distance sensor reads a distance < 150m and initiates "active mode"
    if (distance < threshold)
    {
      for (int i=0; i<pixelcount; ++i)
      {
        // Setting pixels to green, and then turning off after 100 miliseconds in a for loop to activate one pixel at a time
        strip.setPixelColor(i, 0, 255, 0);
        strip.show();
        delay(100);
        strip.setPixelColor(i, 0, 0, 0);
        strip.show();
      }

    }
    else {
      // otherwise, have "ambient mode", where a subtle green colour shows for all pixels
      for (int i=0; i<pixelcount; ++i)
      {
        strip.setPixelColor(i, 0, 10, 0);
      }
      strip.show();
      delay(100);
    }
}
