
/*
  Ultrasonic Theramin v0
  Plays continuous note depending on distance
  LED brightness changes with distance
  by L. Savage, February 2023
*/

// Neo Pixel setup
#include <Adafruit_NeoPixel.h>
#define N_LEDS 5

// Define Pins
const int trigPin = 9;
const int echoPin = 10;
const int soundPin = 6;
const int ledPin = 5;
    
// Ultrasonic variables
long duration;
int distance;
// LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, ledPin, NEO_GRB + NEO_KHZ800);

//Define pins as input or output, start serial
void setup() {
  strip.begin();
  pinMode(ledPin, OUTPUT); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(soundPin, OUTPUT); 
}

void loop() {
  // Clear the trigPin then send a pulse for 10ms
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distance = duration * 0.034 / 2;
  // Delay controls how sensitive it is to motion. A short delay smooths the sound
  delay(70); 
  
// No sound if hand is out of range
  if (distance >= 50) {
     noTone(soundPin);
     setLEDcolor(strip.Color(0, 0, 0));
  }
// Play note that is between apprx 220hz and 700Hz (tolerable pitch range)
// LEDs bringhter the higher the note is (max 50 of 255)
  else if (distance < 50) {
     tone(soundPin, 200 + distance*10);
     setLEDcolor(strip.Color(distance, 0, 0));
     //tone(soundPin, 432);
     }
  else {
    noTone(soundPin);
    setLEDcolor(strip.Color(0, 0, 0));
  }
  
}

// Sets all LEDs one color
static void setLEDcolor(uint32_t c) {
     for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
    }
}
