int BUZZER = P1_3;  // set BUZZER as P1.3 alias
int LMOTOR = P2_1;  // set LMOTOR as P2.1 alias
int RMOTOR = P1_6;  // set RMOTOR as P1.6 alias
int LPHOTO = P1_4;  // set LPHOTO as P1.2 alias
int RPHOTO = P1_7;  // set RPHOTO as P1.7 alias
int MICINP = A5;    // set MICINP as A5   alias

int MPOW   = 240;
int MICTHRESH = 650; // set microphone trigger threshold (possible values 0-1023)

byte generate_buzz = false ;
byte top_light = false ; 
byte bottom_light = false ; 

int i;
int maxval;

void setup()
{
  Serial.begin(9600) ;
  pinMode(LMOTOR, OUTPUT);
  pinMode(RMOTOR, OUTPUT);
  //pinMode(BUZZER, OUTPUT);
  pinMode(LPHOTO, INPUT);
  pinMode(RPHOTO, INPUT);
  analogWrite(LMOTOR,0);  
  analogWrite(RMOTOR,0);
}

void loop()
{
  
   if (Serial.available())
   {
      unsigned char value = Serial.read() ;
      if (value == 's')
      {
         generate_buzz = true ;
      }
      if (generate_buzz == true)
      {
        pinMode(BUZZER, OUTPUT);
        for (i=1; i<5; i++)
        {
          beep(BUZZER, 1000, 100*i);
          delay(100*i);
        }
          
        generate_buzz = false ;
      }
      if (value == 'f')
      {
         analogWrite(LMOTOR, MPOW);
         analogWrite(RMOTOR, MPOW);
         delay(400) ;
         analogWrite(LMOTOR,0);
         analogWrite(RMOTOR,0);
      }
      if (value == 'r')
      {
         analogWrite(RMOTOR, MPOW);
         delay(300) ;
         analogWrite(RMOTOR,0);
      }
      if (value == 'l')
      {
         analogWrite(LMOTOR, MPOW);
         delay(300) ;
         analogWrite(LMOTOR,0);
      }
      if (value == '1')
      {
         top_light = true ; 
      }
      if (top_light == true)
      {
        while (analogRead(RPHOTO) > 100);
        analogWrite(RMOTOR, MPOW);
        delay(2000) ;
        analogWrite(RMOTOR,0);
        top_light = false ; 
      }
      if (value == '2')
      {
         bottom_light = true ; 
      }
      if (bottom_light == true)
      {
        while (analogRead(LPHOTO) > 100);
        analogWrite(LMOTOR, MPOW);
        delay(2000) ;
        analogWrite(LMOTOR,0);
        bottom_light = false ; 
      }
      if (value == 'm')
      {
         //while (1)
         //{
          int maxval = 0;
          for (i=1; i<20; i++)
          {
            int val = analogRead(MICINP);
            if (val > maxval)
            maxval = val;
            delay(1);
          }
          Serial.println(maxval, DEC) ;
          if (maxval > MICTHRESH)
          {
            Serial.println(maxval, DEC) ;
            analogWrite(RMOTOR, MPOW);
            delay(2000) ;
            analogWrite(RMOTOR,0);
          }
      }
   }
}

void beep(int pin, int freq, long ms)  	//generate a square wave at a given frequency for ms miliseconds
{
	int k;
        long semiper = (long) (1000000/(freq*2));
        long loops = (long)((ms*1000)/(semiper*2));
	for (k=0;k<loops;k++)
	{
            digitalWrite(pin, HIGH);  //set buzzer pin high
	    delayMicroseconds(semiper);  //for half of the period
	    digitalWrite(pin, LOW);   //set buzzer pin low
            delayMicroseconds(semiper);  //for the other half of the period
	}
}


