int y1 = A0;
int x2 = A1;
int y2 = A2;
int x1 = A3;

void setup() { 
  Serial.begin(115200);
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

void loop()
{
  int x = readX();
  int y = readY();


  if(x < 900 & y < 900){  
  Serial.print("{XYPLOT|DATA|SeriesName:r#|");
  Serial.print(-x, DEC);
  Serial.print("|");
  Serial.println(y, DEC);
  Serial.print("}");
  }
}
