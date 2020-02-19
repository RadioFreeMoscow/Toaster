//Global Variables
//ultrasonic sensor:
int trigPin = 6;
int echoPin = 7;
long duration,cm;
// include the SD library:
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
TMRpcm audio;

Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 10;


void setup() {
//generate a random number for boot file:

long num = random(1,100);
String ff = ".wav";
String bootnum = String(num);
String bootfile = bootnum + ff;

  
  //Serial Port begin
  Serial.begin (9600);
  Serial.println("Would you like some Toast?");
  delay(100);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(100);
  Serial.println (bootfile);
  delay(100);
  
  Serial.println("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  SD.begin(chipSelect);
  root.openRoot(volume);
  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  audio.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  audio.setVolume(7);
  audio.quality(2);
 
  if (SD.exists(bootfile)) {
    //Serial.println();
    audio.play(bootfile); //the sound file "music" will play each time the arduino powers up, or is reset
  } else {
    Serial.println("Nope");
  }
}

void loop() {
  audio.speakerPin = 9;
  audio.setVolume(5);
  audio.quality(2);
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
   digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  //cleans the sensor
  digitalWrite(trigPin, LOW); 
  
//Read the Signal:
 pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;
  if(cm <=7){
    Serial.print (" Close Enough ");
    Serial.print(cm);
    Serial.print(" cm");
    Serial.println();
    Serial.print("Playing");
    //audio.play("boot.wav");
      }
   else 
    Serial.print (cm);
    Serial.print (" Recorded");
    Serial.println();
    delay (15000);

  }
    
