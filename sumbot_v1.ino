//motor 1\\
int m1Dir1 = 1; //input pin 1 from motor sets direction to pin #?
int m1Dir2 = 2; //sets direction to pin #?
int m1En = 3; //enable to pin #?

//motor 2\\
int m2Dir1 = 1; //input pin 1 from motor sets direction to pin #?
int m2Dir2 = 2; //sets direction to pin #?
int m2En = 3; //enable to pin #?

boolean SensorAlwaysOpen=true; //the value to control sensor mode
                            //true: Sensor always open
                            //false: Sensor only open when ReadIRDistence is executed
#define IRDistenceEn 8    //digital pin 8
#define IRDistenceRead A0 //Analog pin A0
//3.6-2  10-20cm
//2-1.5  20-30cm
//1.5-1  30-50cm
#define IRRateArrayLength 3
float IRDistenceRate[]={6.25,20.0,40,0};//Data base on https://www.pololu.com/file/download/gp2y0a60szxf_e.pdf?file_id=0J812 
                                        //Rate equal to Distence/Voltage
                                        //The data is base on 5V input
float IRDistenceThreshold[]={2,1.5,1,0};


void setup() {
  //motor 1\\
  pinMode(m1Dir1,OUTPUT); //set as output
  pinMode(m1Dir2,OUTPUT); //set as output
  pinMode(m1En, OUTPUT); //set as output

  //motor 2\\
  pinMode(m2Dir1,OUTPUT); //set as output
  pinMode(m2Dir2,OUTPUT); //set as output
  pinMode(m2En, OUTPUT); //set as output

  pinMode(IRDistenceEn, OUTPUT);
  if(SensorAlwaysOpen){
    digitalWrite(IRDistenceEn,HIGH);
  }
}


void loop() {

//nothing here to see\\

}

//methods\\

//motor 1 forward (counter colck wise)
void m1Forward()
{
  digitalWrite(m1Dir1,LOW);
  digitalWrite(m1Dir2,HIGH);
  analogWrite(m1En,255);
}

//motor 2 forward (counter colck wise)
void m2Forward()
{
  digitalWrite(m2Dir1,LOW);
  digitalWrite(m2Dir2,HIGH);
  analogWrite(m2En,255);
}

//motor 1 back (colck wise)
void m1Back()
{
  digitalWrite(m1Dir1,HIGH);
  digitalWrite(m1Dir2,LOW);
  analogWrite(m1En,255);
}

//motor 2 back (colck wise)
void m2Back()
{
  digitalWrite(m2Dir1,HIGH);
  digitalWrite(m2Dir2,LOW);
  analogWrite(m2En,255);
}

//break
void breakk()
{
  digitalWrite(m1Dir1,HIGH);
  digitalWrite(m1Dir2,HIGH);

  digitalWrite(m2Dir1,HIGH);
  digitalWrite(m2Dir2,HIGH);
}
//The function is use to get data from IR distence sensor and calculate the distence.
//It will return a float value of distence in cm.
//If it return 0, the sensor is either too close or too far from the object.
float ReadIRDistence(){
  if(!SensorAlwaysOpen){
    digitalWrite(IRDistenceEn,HIGH);
    delay(21);
  }
  int V1 = analogRead(IRDistenceRead);
  float vol = V1*(5.0 / 1023.0);
  float rate=0;
  for(int i=0;i<IRRateArrayLength;i++){
    if(vol>=IRDistenceThreshold[i]){
      rate=IRDistenceRate[i];
      break;
    }
  }
  float distence=vol*rate;
  if(!SensorAlwaysOpen){
    digitalWrite(IRDistenceEn,LOW);
  }
  return distence;
}
//This funciton is use to change the IR distence sensor working mode
void ChangeIRDistenceSensorMode(){
  SensorAlwaysOpen=!SensorAlwaysOpen;
  if(!SensorAlwaysOpen){
    digitalWrite(IRDistenceEn,LOW);
  }
}

