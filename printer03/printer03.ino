#define motor1a 7 
#define motor1b 6 
#define motor2a 5 
#define motor2b 4 
#define leftLedpin 8
#define rightLedpin 9
#define leftSwitchpin 10
#define rightSwitchpin 11
#define Sensorpin 3
int Motor1direction = 1 ;
void initall()
{
 // init motor pin as output 
   pinMode(motor1a,OUTPUT);
   pinMode(motor1b,OUTPUT);
   pinMode(motor2a,OUTPUT);
   pinMode(motor2b,OUTPUT);
 // init motor direction Led output 
   pinMode(leftLedpin,OUTPUT);
   pinMode(rightLedpin,OUTPUT);
 // init motor direction Led output 
   pinMode(leftSwitchpin,INPUT);
   pinMode(rightSwitchpin,INPUT);
//-----------
   digitalWrite(leftLedpin,LOW );
   digitalWrite(rightLedpin,LOW );
//------------
 pinMode(Sensorpin,INPUT);
}
 void setup()
 {
   boolean chkflag ; 
  initall();
   //init serial for debug
Serial.begin(9600);
Serial.println("program start here ");
CheckPaperJam();  // check paper for paperjam
delay(2000);

 }

 void loop()
 {
  boolean chkflag;

  Serial.println("Paper Heto zero for printing ready ....");
  PaperHeadReady();
  Serial.println("Paper Feeding for printing ready ....");
  PaperReady();
  delay(1000);
     chkflag  = CheckSensor() ;

    while(chkflag)
     {
        Serial.println("Paper Feeding ....");
         PaperFeed() ;
        Serial.println("Paper Head Printing ....");
         PaperHeadMove();
         chkflag  = CheckSensor() ;
         delay(500);
     } 
  Serial.println("End printing ready ....");
 }

 void Motor1Stop()
 {
   digitalWrite(motor1a,LOW );
   digitalWrite(motor1b,LOW);
 }
 void Motor2Stop()
 {
   digitalWrite(motor2a,LOW );
   digitalWrite(motor2b,LOW);
 }

 void Motor1Forward()
 {
   digitalWrite(motor1a,HIGH);
   digitalWrite(motor1b,LOW);
 }
 void Motor1Backward()
 {
   digitalWrite(motor1a,LOW );
   digitalWrite(motor1b,HIGH);
 }


 void Motor2Forward()
 {
      
   digitalWrite(motor2a,HIGH);
   digitalWrite(motor2b,LOW);
 }
 void Motor2Backward()
 {
   digitalWrite(motor2a,LOW );
   digitalWrite(motor2b,HIGH);
 }

boolean checkLeft()
{
  boolean tmp = false ;
  if (digitalRead(leftSwitchpin) == HIGH)
  {
     digitalWrite(leftLedpin,HIGH );
     tmp = true  ;
  }
  else
  {
     digitalWrite(leftLedpin,LOW );
     tmp = false  ;
  }
  return (tmp) ;
}  
boolean checkRight()
{
  boolean tmp = false ;
  if (digitalRead(rightSwitchpin) == HIGH)
  {
     digitalWrite(rightLedpin,HIGH );
     tmp = true  ;
  }
  else
  {
     digitalWrite(rightLedpin,LOW );
     tmp = false  ;
  }
  return (tmp) ;
}  

boolean CheckSensor()
{
  boolean tmp = false ;
  if (digitalRead(Sensorpin) == HIGH)
  {
     tmp = false  ;
  }
  else
  {
     tmp = true  ;
  }
  return (tmp) ;
}  

void CheckPaperJam()
{
   boolean chkflag ; 
Serial.println("Paper Jam Checking...");
chkflag  = CheckSensor() ;
    if (CheckSensor())
    {
          // paper is in paper tray , and do feed paper
         while(CheckSensor())
        {
           Motor1Forward();
          chkflag  = CheckSensor() ;
          Serial.println("paper feeding....");
        } 
    }
    Motor1Stop() ; 
  
}
void PaperFeed()
{
   boolean chkflag ; 
//Serial.println("Paper feed for printing...");
Motor1Forward();
  delay(70);
    Motor1Stop() ; 
  
}

void PaperReady()
{
   boolean chkflag ; 
//Serial.println("Paper feed for printing...");
chkflag  = CheckSensor() ;
    if (!CheckSensor())
      // paper is in paper tray , and do feed paper
     {
       while(!CheckSensor())
        {
           Motor1Forward();
          chkflag  = CheckSensor() ;
          Serial.println("paper feeding... for printing ready...");
        } 
     }
    Motor1Stop() ; 
  
}

void PaperHeadReady()
{
   boolean chkflag ; 
    chkflag = checkLeft();
   if (!chkflag)
    {
      while (!chkflag)
      {
         Motor2Backward();
        chkflag = checkLeft();
      }
    } 
    Motor2Stop();
        
  
}

void PaperHeadMove()
{
   boolean chkflag ; 
    chkflag = checkRight();
   if (!chkflag)
    {
      while (!chkflag)
      {
         Motor2Forward();
        chkflag = checkRight();
      }
    } 
    
    chkflag = checkLeft();
   if (!chkflag)
    {
      while (!chkflag)
      {
         Motor2Backward();
        chkflag = checkLeft();
      }
    } 
    Motor2Stop();
        
  
}

