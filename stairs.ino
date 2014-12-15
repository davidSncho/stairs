const int nbLeds= 9 ; 
const int offset= 4 ; 

const int delayInMs = 100 ; 
const int fullLightTime = 1500; 
const int switchCheckPeriod = 200 ; 

const int dropDelay=400;


//with nbLeds and offset properly defined 
//this allow to index bottom led as 0 in the code 
int translate(int idx)
{
  return (nbLeds-1 + offset - idx) ; 
}


//DS =>downstairs
int checkDSSwitch()
{
  return (1 - digitalRead(3)) ;
}

void blink()
{
  for(int i=0; i < 5 ; ++i )
  {
    digitalWrite(translate(0), HIGH); 
    delay(delayInMs);
    digitalWrite(translate(0), LOW);
    delay(delayInMs);    
  }
  
}


void waitForSwitchOff(){
  while ( checkDSSwitch() )
  {
    Serial.print("I m waiting \n") ; 
    delay(switchCheckPeriod) ;
  }
  blink() ; 
}



int stepHighDelay(int i){
  //purpose is to have animation for any step 
  //to take the same amount of time defined by dropDelay
  return dropDelay/(nbLeds - i) ; 
}

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

//void welcome(){
//  light(1) ; 
//    lightOff();
//  spaceship() ; 
//  lightOff();
//}


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
    waitForSwitchOff(); 
  }

}





