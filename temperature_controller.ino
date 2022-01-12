

#define pinA 2
#define pinB 1
#define pinC 4
#define pinD 5
#define pinE 6
#define pinF 8
#define pinG 9
#define minusButton 0
#define plusButton 7
#define MINIMALTEMPERATURE 20
#define MAXIMALTEMPERATURE 29
#define tempPin A0
#define MEASURES_PER_SECOND 100
#define ABSOLUTE_ZERO -273
#define DELTA_FROM_DESIRED_TEMPERATURE 2
#define DELTA_FOR_SENSOR 2
#define pinRed 10
#define pinGreen 11
#define pinBlue 12
#define resistorsPin A1
#define ventilateurPin A2
enum Command {LESS, NORMAL, MORE};
int currentTemperature = 0;
int temperature = 23;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinA, OUTPUT);     
 pinMode(pinB, OUTPUT);     
 pinMode(pinC, OUTPUT);     
 pinMode(pinD, OUTPUT);     
 pinMode(pinE, OUTPUT);     
 pinMode(pinF, OUTPUT);     
 pinMode(pinG, OUTPUT); 
 pinMode(pinRed, OUTPUT);
 pinMode(pinGreen, OUTPUT);
 pinMode(pinBlue, OUTPUT);
  pinMode(resistorsPin, OUTPUT);
   pinMode(ventilateurPin, OUTPUT);
 pinMode(minusButton, INPUT_PULLUP);
 pinMode(plusButton, INPUT_PULLUP);
 
 Serial.begin(9600);
}

int temperatureMode()
{ int frequences[MEASURES_PER_SECOND];
  for(char i=0; i<MEASURES_PER_SECOND; i++)
  {
    frequences[i]=0;
  }
  int temperatures[MEASURES_PER_SECOND];
  for(char i=0; i<MEASURES_PER_SECOND; i++)
  {
    temperatures[i]=ABSOLUTE_ZERO;
  }
  int mode = frequences[0]; 
  int mode_value = temperatures[0];
  for(char i=0; i<MEASURES_PER_SECOND; i++)
  {
    int temp = analogRead(tempPin);
    if(!temp)
    continue;
    temp = temp * 0.48828125;
    int index=0;
    for(;index<MEASURES_PER_SECOND&&temperatures[index]!=ABSOLUTE_ZERO; index++)
    {
      if(temperatures[index]==temp)
      {
        frequences[index]+=1;
        break;
      }
    }
    if (temperatures[index]!=temp)
    {
      temperatures[index]=temp;
      frequences[index]+=1;
    }
    if(mode<frequences[index])
    {
      mode=frequences[index];
      mode_value = temperatures[index];
    }
    delay(1000/MEASURES_PER_SECOND);
  }
  return mode_value;  
}

void writeDigit(int digit)
{
  switch(digit)
  {
    case 1:
    {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    }
     case 2:
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      break;
    }
       case 3:
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      break;
    }
           case 4:
    {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    }
    
           case 5:
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    }
     case 6:
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    }
      case 7:
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    }
      case 8:
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    }
    case 9:
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    }
    case 0:
    {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      break;
    }
  }
}

void colorSygnal(enum Command command)
{
  switch (command)
  {
    case LESS:
    {
      analogWrite(pinRed,   0);
      analogWrite(pinGreen, 0);
      analogWrite(pinBlue,  255);
      break;
    }
    case MORE:
    {
        analogWrite(pinRed,   255);
        analogWrite(pinGreen, 0);
        analogWrite(pinBlue,  0);
        break;
    }
    case NORMAL:
    {
      analogWrite(pinRed,   0);
      analogWrite(pinGreen, 255);
      analogWrite(pinBlue,  0);
    }
    
  }
  
}
void temperatureAction(enum Command command)
{
  switch (command)
  {
    case LESS:
    {
      digitalWrite(ventilateurPin, 1);
      digitalWrite (resistorsPin, 0);
      break;
    }
    case MORE:
    {
        digitalWrite(ventilateurPin, 1);
      digitalWrite (resistorsPin, 1);
      break;
    }
    case NORMAL:
    {
      digitalWrite(ventilateurPin, 0);
      digitalWrite (resistorsPin, 0);
      break;
    }
    
  }
}
void loop() {
  // put your main code here, to run repeatedly:
 
  bool minusState = digitalRead(minusButton);
  bool plusState = digitalRead(plusButton);
  if (minusState==LOW)// IF THE BUTTON FOR MINUS IS PRESSED
  {
    if(temperature-1>=MINIMALTEMPERATURE)
    {
       temperature-=1;
    }
       while (digitalRead(minusButton)==LOW)
    {      
      writeDigit(temperature%10);
    }
  }
  else if (plusState == LOW)
  {
    if(temperature+1<=MAXIMALTEMPERATURE)
    {
      temperature+=1;
    }
    while(digitalRead(plusButton)==LOW)
    {
      writeDigit(temperature%10);
    }
  }
  currentTemperature = temperatureMode();
  Serial.print(currentTemperature);
  Serial.print('\n');
 //Serial.print(temperature);
  writeDigit(temperature%10);
  enum Command type = NORMAL;
  if(currentTemperature>temperature+DELTA_FROM_DESIRED_TEMPERATURE)
  {
    type = LESS;
  }
  else if (currentTemperature<temperature-DELTA_FROM_DESIRED_TEMPERATURE)
  {
    type = MORE;
  }
  colorSygnal(type);
  temperatureAction(type);
  delay(500);
  

}
