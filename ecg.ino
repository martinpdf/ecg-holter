unsigned int val[] = {35, 38, 35, 20, 20, 20, 25, 5, 140, 255, 0, 20, 20, 20, 25, 35, 45, 55, 58, 56, 25};

const int potPin = A0;
int valPot;              
int delayTime;           

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);  // Initialiser la communication série pour débogage
}

void loop()
{
  //Lire la valeur du potentiomètre (de 0 à 1023)
  valPot = analogRead(potPin);
 
  delayTime = map(valPot, 0, 1023, 150, 1000);
 
  digitalWrite(13, HIGH);
  for (int i = 0; i <= 20; i++)
  {
    analogWrite(9, val[i]);
    delay(20);
  }
  digitalWrite(13, LOW);
  analogWrite(9, 0);
 
  delay(delayTime);  // Délai ajusté par la valeur du potentiomètre
}
