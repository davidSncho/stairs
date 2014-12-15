const int nbLeds= 9 ; 
const int offset= 4 ; 
const int delayInMs = 100 ; 
const int fullLightTime = 1500; 
const int switchCheckPeriod = 200 ; 
const int dropDelay=400;

//with nbLeds and offset properly defined 
//this allow to index bottom led as 0 in the code 
int translate(int ledIdx)
{
  return (nbLeds-1 + offset - ledIdx) ; 
}

//DS =>downstairs
int checkDSSwitch()
{
  return (1 - digitalRead(3)) ;
}

//provides a signal blinking led 
// indexed by input argument
//helpful to understand state of the system 
void blink(int ledIdx)
{
  for(int i=0; i < 5 ; ++i )
  {
    digitalWrite(translate(ledIdx), HIGH); 
    delay(delayInMs);
    digitalWrite(translate(ledIdx), LOW);
    delay(delayInMs);    
  } 
}

//Sensor remains "ON" for about 30seconds 
//animation of light may be shorter
// this method makes sure that sensor is off
void waitForSwitchOff(){
  while ( checkDSSwitch() )
  {
    delay(switchCheckPeriod) ;
  }
  //blink bottom led to notify that 
  //sensor is ready 
  blink(ledIdx) ; 
}

int stepHighDelay(int i){
  //purpose is to have animation for any step 
  //to take the same amount of time defined by dropDelay
  return dropDelay/(nbLeds - i) ; 
}

//animation
void spaceship()
{
  int bottom= 0 ; 
  for(int i=0; i < nbLeds ; ++i )
  {
    for(int j= nbLeds-1 ; j >= bottom ; --j)
    {
      digitalWrite(translate(j), HIGH); 
      delay(stepHighDelay(i));
      if (j!= bottom)
      {
        digitalWrite(translate(j), LOW); 
      }      
    }
    bottom+=1 ;
  }  
}

void lightOff()
{
  for(int i=0; i < nbLeds ; ++i )
  {
    digitalWrite(translate(i), LOW); 
    delay(delayInMs) ; 
  }
}

void light(int direction)
{  
  for(int i=0; i < nbLeds ; ++i )
  {
    digitalWrite(translate(i), HIGH); 
    delay(delayInMs) ; 
  }

}


void welcome_animation() 
{
  for(int i=0; i < nbLeds ; ++i )
  {
    digitalWrite(translate(i), HIGH); 
    delay(delayInMs) ; 
    digitalWrite(translate(i), LOW); 
  }  
  for(int i=0; i < nbLeds ; ++i )
  {
    digitalWrite(translate( nbLeds - i), HIGH); 
    delay(delayInMs) ; 
    digitalWrite(translate(nbLeds - i), LOW); 
  }  
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setup()
{
  Serial.begin(9600);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  welcome_animation(); 
  waitForSwitchOff(); 
}

void loop()
{
  if (checkDSSwitch())
  {
    if (0 == random(2) )
    {
      light(1) ; 
    }
    else
    {
      spaceship() ;
    }
    delay(fullLightTime); 
    lightOff();
    //make sure here that switch is turned off 
    //before entering next loop
    waitForSwitchOff(); 
  }
}
