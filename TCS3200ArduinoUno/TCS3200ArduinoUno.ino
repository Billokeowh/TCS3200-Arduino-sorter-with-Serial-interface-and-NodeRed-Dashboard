
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#include <Servo.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo servocolour;
Servo servorotate;

int Redfrequency = 0;
int Bluefrequency = 0;
int Greenfrequency = 0; //Setting up integer to store Red, Green and Blue values in.
int angle = 0;          //Setting up integer to store angle values in.
int colourselection = 0;
int redtotal = 1000;
int greentotal = 1000;
int bluetotal = 1000; //Setting up integer to store Total Red, Green and Blue values in.
int sensorState = 0;  //Setting up integer for proximity sensor state
int hoppercounter = 0; //Setting up integer to store hopper level in.
int systemstate = 0;  //Setting up integer to store Machin Run/Not Run state.
int switchState = 0;  //Setting up integer to store switch state in.
const int buttonPin = 2;     // the number of the switch
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {

  pinMode(ledPin, OUTPUT); // initialize the LED pin as an output:
  pinMode(buttonPin, INPUT);    // initialize the pushbutton pin as an input:
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT); // Setting all colour sensors as output devices.
  pinMode(0, INPUT);   // Setting Proximitiy sensor as an input
  pinMode(buttonPin, INPUT);  // Setting switch as an input
  pinMode(ledPin, OUTPUT);    // Setting LED as an output
  servocolour.attach(9);
  servorotate.attach(10);    // Defining Servo names and pins
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);     //Sets the output frequence scaling to 20%


  lcd.init();                      // initialize the lcd
  lcd.backlight();                  // initialize the backlight
  digitalWrite(0, LOW);             // initialize the priximity sensor in low state

}

void loop() {

  sensorState = digitalRead(0); // Check the hopper leve at the start of each loop

  if (sensorState == LOW) {           //If the sensor detects presence of sweet then set value to 3.
    hoppercounter = 3;
    delay(1000);
  }
  if ((sensorState == HIGH) && (hoppercounter >= 1))  { //If the sensor doesn't detects sweet and the hopper counter
    hoppercounter--;                                    // is still greater than zero then deduct 1 from hopper level each loop
    delay(1000);
  }



  buttonState = digitalRead(buttonPin);               // Read state of switch


  if (buttonState == HIGH) {        // check if the switch is on. If it is, the buttonState is HIGH + turn on LED.
    digitalWrite(ledPin, HIGH);


    //On AND EMPTY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    if  (hoppercounter == 0) {      // If there is nothing in hopper then tell the user via Serial and LCD
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Sweet hopper");
      lcd.setCursor(0, 2);
      lcd.print("is empty");
      delay(1000);
      systemstate = 1;

    }

    //On AND FULL +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    if  (hoppercounter > 0)  {                                // If switch is on and hopper is full then we can begin out sorting process


      //LOAD POSITION
      servorotate.write(140); //Servo to load position
      delay(200);
      servorotate.write(142); //Servo to load position
      delay(200);
      servorotate.write(144); //Servo to load position
      delay(200);
      // jiggle cassette to ensure sweet in cassette

      lcd.setCursor(0, 0);
      lcd.print("Load position");
      delay(1000);
      lcd.clear();
      //END OF LOADING                                        // Tell user sweet loaded via LCD.


      //CHECK POSITION
      servorotate.write(120); //Servo to check position
      delay(500);                                        // Servo to move sweet to camera view location


      lcd.setCursor(0, 0);
      lcd.print("Check position");
      delay(1000);
      lcd.clear();                                        // Tell user sweet is in check position via LCD.

      //READ POSITION
      servorotate.write(10);
      //Serial.println("Servo Set to read position");
      lcd.setCursor(0, 0);
      lcd.print("Read position");
      delay(500);                                        // Tell user sweet is in rad location via LCD.
      //END OF READ POSITION



      // Setting red filtered photodiodes to be read
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);

      /* --------------RED COLOUR--------------*/

      // Reading the output frequency
      Redfrequency = pulseIn(sensorOut, LOW);
      Redfrequency = map(Redfrequency, 273, 279, 255, 0);
      Redfrequency = Redfrequency * (-1);        // Inverting output result
      delay(100);
      digitalWrite(S2, HIGH);                   // Setting Green filtered photodiodes to be read
      digitalWrite(S3, HIGH);

      /* --------------Green COLOUR--------------*/

      // Reading the output frequency
      Greenfrequency = pulseIn(sensorOut, LOW);
      Greenfrequency = map(Greenfrequency, 321, 328, 255, 0);
      Greenfrequency = Greenfrequency * (-1);
      delay(100);
      digitalWrite(S2, LOW);                     // Setting Blue filtered photodiodes to be read
      digitalWrite(S3, HIGH);

      /* --------------Blue COLOUR--------------*/

      // Reading the output frequency
      Bluefrequency = pulseIn(sensorOut, LOW);
      //Remaping the value of the frequency to the RGB Model of 0 to 255
      Bluefrequency = map(Bluefrequency, 268, 275, 255, 0);
      Bluefrequency = Bluefrequency * (-1);
      delay(100);

      /* Servo to load sweet into colour sensing chamber */
      delay(1000);

      //RED
      if ((Redfrequency < Bluefrequency) && (Redfrequency < Greenfrequency)) {
        //Serial.println("Red sweet");
        //Serial.println("Moving to Red");
        servocolour.write(0);
        lcd.setCursor(0, 1);
        lcd.print("Red");
        delay(500);
        lcd.clear();
        redtotal++;                                      //If redfrequency is the highest then its a red sweet and we increment red counter
        //and distribute to red servo position


      }

      //GREEN
      if ((Greenfrequency < Bluefrequency) && (Greenfrequency < Redfrequency)) {
        //Serial.println("Green sweet");
        //Serial.println("Moving to Green");
        servocolour.write(90);
        lcd.setCursor(0, 1);
        lcd.print("Green");
        delay(500);
        lcd.clear();
        greentotal++;                                   //If Greenfrequency is the highest then its a green sweet and we increment green counter
        //and distribute to green servo position


      }

      //BLUE
      if ((Bluefrequency < Redfrequency) && (Bluefrequency < Greenfrequency)) {
        //Serial.println("Blue sweet");
        //Serial.println("Moving to Blue");
        servocolour.write(180);
        lcd.setCursor(0, 1);
        lcd.print("Blue");
        delay(500);
        lcd.clear();
        bluetotal++;                                   //If Bluefrequency is the highest then its a blue sweet and we increment blue counter
        //and distribute to blue servo position

      }
      servorotate.write(0);
      delay(500);
      //Serial.println("Servo set to distribute position");
      lcd.setCursor(0, 0);
      lcd.print("Distribute position");
      lcd.clear();                                            // Tell user sweet is in distribute position via LCD.


      redtotal = redtotal - 1000;
      lcd.setCursor(0, 1);
      lcd.print("Red: ");
      lcd.setCursor(5, 1);
      lcd.print(redtotal);
      redtotal = redtotal + 1000;      // Format data correctly for displaying to LCD and then reformat bofore sendin to NodeRed via serial

      greentotal = greentotal - 1000;
      lcd.setCursor(0, 2);
      lcd.print("Green: ");
      lcd.setCursor(6, 2);
      lcd.print(greentotal);
      greentotal = greentotal + 1000;      // Format data correctly for displaying to LCD and then reformat bofore sendin to NodeRed via serial

      bluetotal = bluetotal - 1000;
      lcd.setCursor(0, 3);
      lcd.print("Blue: ");
      lcd.setCursor(5, 3);
      lcd.print(bluetotal);
      bluetotal = bluetotal + 1000;      // Format data correctly for displaying to LCD and then reformat bofre sendin to NodeRed via serial
      systemstate = 2;                   // Set system state
      delay(1000);

    }



  } else {
    // OFF AND EMPTY +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    digitalWrite(ledPin, LOW);          // indicator LED off

    if (hoppercounter == 0)  {         // If the switch and th ehopper is empty is off then tell the user via Serial and LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please switch the");
      lcd.setCursor(0, 1);
      lcd.print("Start switch");
      lcd.setCursor(0, 2);
      lcd.print("and fill hopper");
      delay(1000);
      //Serial.println("Off AND EMPTY");
      systemstate = 3;                   // Set system state

    }


    // OFF AND FULL +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    if (hoppercounter > 0)   {                  // If the switch is off then tell the user via Serial and LCD
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("To run, move switch");
      lcd.setCursor(0, 2);
      lcd.print("to on position");
      delay(1000);
      //Serial.println("Off AND FULL");
      systemstate = 4;                        // Set system state

    }

  }

  Serial.print("R");
  Serial.print(redtotal);
  Serial.print(greentotal);
  Serial.print(bluetotal);
  Serial.print(hoppercounter);
  Serial.print(systemstate);             //Output the vital stats of the machine as one string.


  Serial.println("");                   // New string is always on new line
}
