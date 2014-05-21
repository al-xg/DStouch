#include <Servo.h>

int y1 = A0;
int x2 = A1;
int y2 = A2;
int x1 = A3;

boolean flag=0;
int setpoint;
int error;
int deadzone=20;
int lastError;
int currentError;

Servo myservo;


void setup() { 
  Serial.begin(115200);
  myservo.attach(11);
  flag=0;
  lastError=0;
  currentError=0;
} 

int readX(){
  pinMode(y1, INPUT);
  pinMode(x2, OUTPUT);
  pinMode(y2, INPUT);
  pinMode(x1, OUTPUT);

  digitalWrite(x2, LOW);
  digitalWrite(x1, HIGH);

  delayMicroseconds(2); //pause to allow lines to power up

  return analogRead(y1);
}

int readY(){

  pinMode(y1, OUTPUT);
  pinMode(x2, INPUT);
  pinMode(y2, OUTPUT);
  pinMode(x1, INPUT);

  digitalWrite(y1, LOW);
  digitalWrite(y2, HIGH);

  delayMicroseconds(2); //pause to allow lines to power up

  return analogRead(x2);
}

int ServoOutput(int errors){
  int output=map(errors,200,-200,0,180);
  return output;
}
void loop()
{
  int x = readX();
  int y = readY();


  if(x < 900 & y < 900){
    if (flag==0){
      flag=1;
      setpoint=x;
    }
    error=x-setpoint;

    //Serial.println(error);
    if (error>deadzone || error<(-1*deadzone)){
      currentError=lastError+error;
      myservo.write(ServoOutput(currentError));
    }
    /*Serial.print("{XYPLOT|DATA|SeriesName:r#|");
     Serial.print(-x, DEC);
     Serial.print("|");
     Serial.println(y, DEC);
     Serial.print("}");*/
  }
  else {
    flag=0;
    lastError=currentError;
    myservo.write(ServoOutput(lastError));
  }
}


