//this test gets the reflectance sensor to control the motor
//if the ref. sensor reads a dark color (2500) the motor stops
//if the ref. sensor reads a lighter color (not 2500) the motor keeps going
//this code also includes code for the distance sensor.
//uses switch cases to execute certain actions based off of the "state"

#include <QTRSensors.h>

// This example is designed for use with eight QTR-1RC sensors or the eight sensors of a
// QTR-8RC module.  These reflectance sensors should be connected to digital inputs 3 to 10.
// The QTR-8RC's emitter control pin (LEDON) can optionally be connected to digital pin 2,
// or you can leave it disconnected and change the EMITTER_PIN #define below from 2 to
// QTR_NO_EMITTER_PIN.

// The main loop of the example reads the raw sensor values (uncalibrated).
// You can test this by taping a piece of 3/4" black electrical tape to a piece of white
// paper and sliding the sensor across it.  It prints the sensor values to the serial
// monitor as numbers from 0 (maximum reflectance) to 2500 (minimum reflectance).


#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {
  3
  //, 4, 5, 6, 7, 8, 9, 10
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

bool attackQ = true;

//--------motor stuff
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;

const int ENA = 9;
const int ENB = 8;

//--------distance sensor stuff
// Declare the used sensor pin
int sensorPin = A0;

int state;

char dir;
void setup()
{
  delay(500);
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1000);

  //----motor stuff
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
}



void loop()
{
  // read raw sensor values
  qtrrc.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and
  // 2500 means minimum reflectance
  //  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  //  {
  //    Serial.print(sensorValues[i]);
  //
  //    if (sensorValues[i] = 2500)
  //    {
  //      attackQ = false;
  //    }
  //    else
  //    {
  //      attackQ = true;
  //    }
  //
  //    Serial.print(' ');
  //    Serial.print(attackQ);
  //    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  //  }

  //----distance
  // Read the analog value of the sensor
  int val = analogRead(A0);
  // Print the value over Serial
  Serial.print("dist.: ");
  Serial.println(val);
  // Write the value to the LED using PWM
  //analogWrite(LED, val/4);
  // Wait a little for the data to print
  //delay(100);

  //----reflectance
  Serial.print("ref.: ");
  Serial.print(sensorValues[0]);

  //line detected (2500), motion detected (>600)
  if ((sensorValues[0] == 2500 && val > 600) || (sensorValues[1] == 2500 && val > 600))
  {
    //attackQ = false;
    //stopp();
    state = 0;
  }
  //line detected(2500), no motion detected (<600)
  if ((sensorValues[0] == 2500 && val < 600) || (sensorValues[1] == 2500 && val < 600))
  {
    //attackQ = false;
    //stopp();
    state = 1;
  }
  //no line detected (!2500), motion detected (>600)
  if ((sensorValues[0] != 2500 && val > 600) || (sensorValues[0] != 2500 && val > 600))
  {
    //attackQ = true;
    //forward();
    state = 2;
  }
  //no line detected (!2500), no motion detected (<600)
  if ((sensorValues[0] != 2500 && val < 600) || (sensorValues[0] != 2500 && val < 600))
  {
    //attackQ = true;
    //forward();
    state = 3;
  }

  Serial.print(" state: ");
  Serial.print(state);
  Serial.println();

  delay(250);

  switch (state) {
    case 0: //line detected (2500), motion detected (>600)
      //___ //stop, move away from line, scan?
      stopp();
      otherWay();
      scan();
      break;
    case 1: //line detected(2500), no motion detected (<600)
      //___ //stop, move away from line, scan for opponent
      stopp();
      otherWay();
      scan();
      break;
    case 2: //no line detected (!2500), motion detected (>600)
      //____ //attack
      forward();
      break;
    case 3: //no line detected (!2500), no motion detected (<600)
      //____ //scan for opponent
      scan();
      break;
  }

Serial.print(dir);

} //end loop

//----motor functions

void forward()
{
  //set direction value
  dir = 'f';
  // turn on motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(ENA, i);
    analogWrite(ENB, i);
    //delay(20);
  }
}

void backward()
{
  //set direction value
  dir = 'b';
  // turn on motors
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(ENA, i);
    analogWrite(ENB, i);
    //delay(20);
  }
}

void stopp()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

//change direction
void otherWay()
{
  if (dir = 'f')
  {

    backward();
    delay(2000); //move for 2 seconds
  }

  if (dir = 'b')
  {
    forward();
    delay(2000); //move for 2 seconds
  }
}

void scan()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
 // analogWrite(ENA, 75); //for speed?
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
 // analogWrite(ENB, 75); //for speed?
}

