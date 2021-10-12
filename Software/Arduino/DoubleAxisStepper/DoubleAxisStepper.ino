/*
 * 
 *  Driver1 / Stepper Motor 1 is assigned to the X axis
 * 
 *  Driver2 / Stepper Motor 2 is assigned to the Y axis
 * 
 *  TBD: 
 *  
 *  Conversion of digitalWrite to Port Manipulation:
 *  When it comes to speed, port manipulation will be defintely be faster than the 
 *  
 *  
 *  
 *  
 *  
 *  
 */
 


const int Driver1StepPin = 6;
const int Driver1DirPin = 7;

const int Driver2StepPin = 8;
const int Driver2DirPin = 9;

const byte NumChars = 128;

char ReceivedChars[NumChars];
boolean NewData = false;
boolean NewDataNotDealtWith = false;

int count;
unsigned long CurrentMillis;
unsigned long PreviousStepperMillis;
unsigned long PreviousXStepperMillis;
unsigned long PreviousYStepperMillis;


byte FastStepperInterval = 1;
byte SlowStepperInterval = 3; 
byte StepperInterval = 1;

boolean XMovementFlag = false;

boolean LeftMovementFlag = false;
boolean RightMovementFlag = false;

boolean YMovementFlag = false;

boolean UpMovementFlag = false;
boolean DownMovementFlag = false;

boolean FlipX = false;
boolean FlipY = false;

boolean UpLeftMovementFlag = false;
boolean UpRightMovementFlag = false;
boolean DownLeftMovementFlag = false;
boolean DownRightMovementFlag = false;

boolean DiagonalMovementFlag = false;

//int 

const float PulleyDiameter = 12.15;



int StepperCount;


void setup() {
  // put your setup code here, to run once:
  
  //Driver Pin Output Setup
  pinMode(Driver1StepPin, OUTPUT);
  pinMode(Driver1DirPin, OUTPUT);
  pinMode(Driver2StepPin, OUTPUT);
  pinMode(Driver2DirPin, OUTPUT);

  //Serial communication begin
  Serial.begin(115200);
  Serial.print("<Arduino Is Ready>");
}

void loop() {
  // put your main code here, to run repeatedly:

  CurrentMillis = millis();
  ReceiveCharsWithStartAndEndMarkers();
  Decoder();
  MovementDecoder();
  if(DiagonalMovementFlag == false){
    ConvertedUpMovement();
    ConvertedDownMovement();
    ConvertedLeftMovement();
    ConvertedRightMovement();
  }
  else if(DiagonalMovementFlag == true){
    ConvertedUpLeftMovement();
    ConvertedUpRightMovement();
    ConvertedDownLeftMovement();
    ConvertedDownRightMovement();
  }
  // The 4 axis of movement
  /*
  LeftMovement();
  RightMovement();
  UpMovement();
  DownMovement();
  */
  //Converted Movements
  //ConvertedUpLeftMovement();

  

  
}

void ReceiveCharsWithStartAndEndMarkers() {

  static boolean ReceiveInProgress = false;
  static byte count = 0;
  char StartMarker = '<';
  char EndMarker = '>';
  char ReceivedCharacter;

  while (Serial.available() > 0 && NewData == false) {

    ReceivedCharacter = Serial.read();

    if (ReceiveInProgress == true) {

      if (ReceivedCharacter != EndMarker) {

        ReceivedChars[count] = ReceivedCharacter;
        count++;

        if (count >= NumChars) {

          count = NumChars - 1;

        }

      }
      else {
        ReceivedChars[count] = '\0';
        ReceiveInProgress = false;
        count = 0;
        NewData = true;
      }
    }
    else if (ReceivedCharacter == StartMarker) {

      ReceiveInProgress = true;

    }

  }

}

void Decoder(){

  if(NewData == true){
    
    String ReceivedString = ReceivedChars;

    
    if(ReceivedString == "Comm Check"){

      Serial.print("<Readback>");
      
    }
    else if(ReceivedString == "Left"){

      //XMovementFlag = true;
      LeftMovementFlag = true;
      
    }
    else if(ReceivedString == "XStop"){

      LeftMovementFlag = false;
      RightMovementFlag = false;
      
    }
    
    else if(ReceivedString == "Right"){
      
      RightMovementFlag = true;

    }

    else if(ReceivedString == "Up"){

      UpMovementFlag = true;

    }
    else if(ReceivedString == "Down"){
      
      DownMovementFlag = true;
      
    }
    else if(ReceivedString == "YStop"){

      UpMovementFlag = false;
      DownMovementFlag = false;

    }

    else if(ReceivedString == "DefaultX"){

      FlipX = false;
      
    }
    else if(ReceivedString == "FlipX"){

      FlipX = true;
      
    }
    else if(ReceivedString == "DefaultY"){

      FlipY = false;
      
    }
    else if(ReceivedString == "FlipX"){

      FlipY = true;
      
    }

    NewData = false;
    
  }


  
}

void MovementDecoder(){

    
    if(UpMovementFlag == true && LeftMovementFlag == true){

      //Serial.println("Firing");
      DiagonalMovementFlag = true;
      UpLeftMovementFlag = true;
    
    }
    else if(UpMovementFlag == true && RightMovementFlag == true){

      DiagonalMovementFlag = true;
      UpRightMovementFlag = true;
    }
    else if(DownMovementFlag == true && LeftMovementFlag == true){

      DiagonalMovementFlag = true;
      DownLeftMovementFlag = true;

    }
    else if(DownMovementFlag == true && RightMovementFlag == true){

      DiagonalMovementFlag = true;
      DownRightMovementFlag = true;

    }
}
/*
void XMovement(){

  static boolean Status = LOW;

  //The code can be made shorter by using a 'X movement flag'
  //if x movement flag == true,
  // then depending on whether the flag = left or right, the dir pin can be changed instead
  // probably better than using two functions for the individual left and right????
  // debugging will be harder with this no?
  
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && XMovementFlag == true){

    if(LeftMovementFlag == true){
      digitalWrite(Driver1DirPin, LOW);
    }
    else if(RightMovementFlag == true){
      digitalWrite(Driver1DirPin, HIGH);
    }

    if(Status == LOW){

      digitalWrite(Driver1StepPin, HIGH);
      Status == HIGH;
      
    }
    else if(Status == HIGH){

      digitalWrite(Driver1StepPin, LOW);
      Status == LOW;
      
    }
    
  PreviousXStepperMillis = CurrentMillis; 
  }
  
}

void YMovement(){

  static boolean Status = LOW;

  if(CurrentMillis - PreviousYStepperMillis >= StepperInterval && YMovementFlag == true){

    if(UpMovementFlag == true){
      digitalWrite(Driver2DirPin, LOW);
    }
    else if(DownMovementFlag == true){
      digitalWrite(Driver2DirPin, HIGH);
    }

    if(Status == LOW){

      digitalWrite(Driver2StepPin, HIGH);
      Status == HIGH;
      
    }
    else if(Status == HIGH){

      digitalWrite(Driver2StepPin, LOW);
      Status == LOW;
      
    }
    
  PreviousYStepperMillis = CurrentMillis; 
  }
  
}
*/

void LeftMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && LeftMovementFlag == true){
     
     digitalWrite(Driver1DirPin, LOW);
     if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      Status = LOW;
     }
     
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;

  }

  
}

void RightMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && RightMovementFlag == true){
     
     digitalWrite(Driver1DirPin, HIGH);
     if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      Status = LOW;
     }
     
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  }

}

void UpMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousYStepperMillis >= StepperInterval && UpMovementFlag == true){
     
     digitalWrite(Driver2DirPin, LOW);
     if(Status == LOW){
      digitalWrite(Driver2StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver2StepPin, LOW);
      Status = LOW;
     }
     
  PreviousYStepperMillis = CurrentMillis;

  }

}

void DownMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis >= StepperInterval && DownMovementFlag == true){
     
     digitalWrite(Driver2DirPin, HIGH);
     if(Status == LOW){
      digitalWrite(Driver2StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver2StepPin, LOW);
      Status = LOW;
     }

  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;

  }

}

void ConvertedUpMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis >= StepperInterval && UpMovementFlag == true){

    digitalWrite(Driver1DirPin, LOW);
    digitalWrite(Driver2DirPin, LOW);
    
    if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      digitalWrite(Driver2StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      digitalWrite(Driver2StepPin, LOW); 
      Status = LOW;
     }
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  }
  
}

void ConvertedDownMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis && DownMovementFlag == true){

    digitalWrite(Driver1DirPin, HIGH);
    digitalWrite(Driver2DirPin, HIGH);
    
    if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      digitalWrite(Driver2StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      digitalWrite(Driver2StepPin, LOW); 
      Status = LOW;
     }
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  }
  
}

void ConvertedLeftMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis >= StepperInterval && LeftMovementFlag == true){

    digitalWrite(Driver1DirPin, LOW);
    digitalWrite(Driver2DirPin, HIGH);
    
    if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      digitalWrite(Driver2StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      digitalWrite(Driver2StepPin, LOW); 
      Status = LOW;
     }
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  }
}

void ConvertedRightMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis >= StepperInterval && RightMovementFlag == true){

    digitalWrite(Driver1DirPin, HIGH);
    digitalWrite(Driver2DirPin, LOW);
    
    if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      digitalWrite(Driver2StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      digitalWrite(Driver2StepPin, LOW); 
      Status = LOW;
     }
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  }
  
}


void ConvertedUpLeftMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis >= StepperInterval && UpLeftMovementFlag == true){

    //Serial.println("Up Left Function Firing");
    digitalWrite(Driver1DirPin, LOW);
     if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      Status = LOW;
     }
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  DiagonalMovementFlag = false;
  UpLeftMovementFlag = false;
  }
  
}

void ConvertedUpRightMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis >= StepperInterval && UpRightMovementFlag == true){

    //Serial.println("Up Right Function Firing");
    digitalWrite(Driver2DirPin, LOW);
     if(Status == LOW){
      digitalWrite(Driver2StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver2StepPin, LOW);
      Status = LOW;
     }
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  DiagonalMovementFlag = false;
  UpRightMovementFlag = false;
  }
  
}

void ConvertedDownLeftMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis >= StepperInterval && DownLeftMovementFlag == true){

    //Serial.println("Down Left Function Firing");
    digitalWrite(Driver2DirPin, HIGH);
     if(Status == LOW){
      digitalWrite(Driver2StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver2StepPin, LOW);
      Status = LOW;
     }
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  DiagonalMovementFlag = false;
  DownLeftMovementFlag = false;
  }
  
}

void ConvertedDownRightMovement(){

  static boolean Status = LOW;
  if(CurrentMillis - PreviousXStepperMillis >= StepperInterval && CurrentMillis - PreviousYStepperMillis >= StepperInterval && DownRightMovementFlag == true){

    //Serial.println("Down Right Function Firing");
    digitalWrite(Driver1DirPin, HIGH);
     if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      Status = LOW;
     }
  PreviousXStepperMillis = CurrentMillis;
  PreviousYStepperMillis = CurrentMillis;
  DiagonalMovementFlag = false;
  DownRightMovementFlag = false;
  }
  
}

// TESTING FUNCTIONS FOR RELATIVE/ABSOLUTE MOVEMENT INSTEAD OF USER CONTROLLED

// Problem is the understanding of how to control this "CoreXY"-like thing with its kinematics

//Idea is to just develop 1 algo?

void MovementAlgoTesting(){

  
  
}
