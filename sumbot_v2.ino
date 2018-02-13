const int leftForward = 2;
const int leftBackward = 3;
const int rightForward = 4;
const int rightBackward = 5;

void setup() 
{
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);

}

void loop()
{
  forward();
  //stop(3000);
  //back();
}

void forward()
{
 digitalWrite(leftForward , HIGH);
 digitalWrite(leftBackward , LOW);
 digitalWrite(rightForward , HIGH);
 digitalWrite(rightBackward , LOW); 
}

void back()
{
 digitalWrite(leftForward , LOW);
 digitalWrite(leftBackward , HIGH);
 digitalWrite(rightForward , LOW);
 digitalWrite(rightBackward , HIGH); 
}

void stop(int timeDel)
{
 digitalWrite(leftForward , LOW);
 digitalWrite(leftBackward , LOW);
 digitalWrite(rightForward , LOW);
 digitalWrite(rightBackward , LOW); 
  delay(timeDel);
}
