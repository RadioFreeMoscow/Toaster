//Global Variables
//ultrasonic sensor:
int trigPin = 6;
int echoPin = 7;
int analogPin = A3;
long duration, cm;


// include the SD library:
#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
TMRpcm audio;
const int chipSelect = 10;
Sd2Card card;
SdVolume volume;
SdFile root;
long num;

void setup() {

  //Boot Sequence - Boot upa0 the Serial; Print some text to the monitor and check the SD Card
  Serial.begin (9600);
  randomSeed(analogRead(0)); // New Random Seed for Every Boot
  Serial.println("Would you like some Toast?");
  delay(100);
  
  //Define inputs and outputs for the Distance Checker
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  delay(100);

  // Setup the File Structure for the Boot Sound.
  num = random(1, 3);
  String ff = ".wav";
  String bootnum = String(num);
  String bootfile = bootnum + ff;
  Serial.println (bootfile);


  Serial.println("\nInitializing SD card...");
  //Initialise the SD Card using the chipSelect Var.
  SD.begin(chipSelect);
  root.openRoot(volume);
  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);

  // Setup the Speaker using the TMRpcm library.
  audio.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  audio.setVolume(7);
  audio.quality(2);

  if (SD.exists(bootfile)) {
    Serial.println(bootfile);
    audio.play(bootfile.c_str()); //passes the bootfile in raw c_str to the file.
  } else {
    Serial.println("Attempted to play: " + bootfile + "but it wasn't found. ");
  }
}

void loop() {
  //initiate a new random seed on each loop:
  num = random(4, 21);
  String ff = ".wav";
  String bootnum = String(num);
  String bootfile = bootnum + ff;
  Serial.println (bootfile);


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
  cm = (duration / 2) / 29.1;
  int maxdist = 20;
  if (cm <= (maxdist))
  {
    Serial.print("Distance:" + cm);
    Serial.println();
    Serial.print("Playing");
    audio.play(bootfile.c_str());
    while (audio.isPlaying()) {
      // Do nothing
    }
  }
  else
    Serial.println ("Distance " + cm);
    Serial.println ("Looping");

}
