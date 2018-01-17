//motor 1\\
int m1Dir1 = 1; //input pin 1 from motor sets direction to pin #?
int m1Dir2 = 2; //sets direction to pin #?
int m1En = 3; //enable to pin #?

//motor 2\\
int m2Dir1 = 1; //input pin 1 from motor sets direction to pin #?
int m2Dir2 = 2; //sets direction to pin #?
int m2En = 3; //enable to pin #?

void setup() {
  //motor 1\\
  pinMode(m1Dir1,OUTPUT); //set as output
  pinMode(m1Dir2,OUTPUT); //set as output
  pinMode(m1En, OUTPUT); //set as output

  //motor 2\\
  pinMode(m2Dir1,OUTPUT); //set as output
  pinMode(m2Dir2,OUTPUT); //set as output
  pinMode(m2En, OUTPUT); //set as output

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

