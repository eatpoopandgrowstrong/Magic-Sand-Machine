const int Driver1StepPin = 6;
const int Driver1DirPin = 7;

const int Driver2StepPin = 8;
const int Driver2DirPin = 9;

const byte NumChars = 128;

char ReceivedChars[NumChars];
boolean NewData = false;
boolean NewDataNotDealtWith = false;

unsigned long CurrentMillis;

unsigned long PreviousXStepperMillis;
unsigned long PreviousYStepperMillis;

unsigned long XNumberOfSteps;
unsigned long YNumberOfSteps;

int XStepperInterval;
int YStepperInterval;

boolean XStepperMovementFlag = false;
boolean YStepperMovementFlag = false;

boolean XStepperDirection;
boolean YStepperDirection;

boolean XStepperMovementCompleteFlag = false;
boolean YStepperMovementCompleteFlag = false;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(Driver1StepPin, OUTPUT);
  pinMode(Driver1DirPin, OUTPUT);
  pinMode(Driver2StepPin, OUTPUT);
  pinMode(Driver2DirPin, OUTPUT);



  Serial.begin(115200);
  Serial.print("<Arduino Is Ready>");
}

void loop() {
  // put your main code here, to run repeatedly:
  CurrentMillis = millis();
  ReceiveCharsWithStartAndEndMarkers();
  Decoder();
  XStepperMovement();
  YStepperMovement();
  MovementCompletionReadback();
  
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
    //Serial.print(ReceivedString);
    
    if(ReceivedString == "Comm Check"){

      Serial.print("<Readback>");
      
    }
    if(ReceivedString[0] == 'M'){

      // Convert Steps For X
      //delay(60);
      XNumberOfSteps = ReceivedString.substring(2,9).toInt();
      Serial.print("XNUMBEROFSTEPS IS :");
      Serial.print(XNumberOfSteps);
    
      //delay(60);
      // Convert XStepperInterval
      XStepperInterval = ReceivedString.substring(9,13).toInt();
      //XStepperInterval = 1;

      // Set the XStepperDirection

      //Serial.print(ReceivedString.substring(1,2));
      
      if(ReceivedString.substring(1,2)=="+"){
        //Serial.print("Positive");
        XStepperDirection = HIGH;
      }
      else if(ReceivedString.substring(1,2) == "-"){
        //Serial.print("Negative");
        XStepperDirection = LOW;
      }

      // Convert Steps For Y
      //delay(60);
      YNumberOfSteps = ReceivedString.substring(14,21).toInt();
      
      //Serial.print(YNumberOfSteps);
      //delay(60);
      //Convert YStepperInterval
      YStepperInterval = ReceivedString.substring(21,25).toInt();
      //YStepperInterval = 1;

      //Set the YStepperDirection

      if(ReceivedString.substring(13,14)=="+"){
        YStepperDirection = HIGH;
      }
      else if(ReceivedString.substring(13,14)=="-"){
        YStepperDirection = LOW;
      }

      
      // Start the XStepperMovement by setting the flag
      XStepperMovementFlag = true;
      // Start the YStepperMovement by setting the flag
      YStepperMovementFlag = true;

   
      
      
    }
    

    NewData = false;
    
  }


  
}

void XStepperMovement(){

  if(CurrentMillis - PreviousXStepperMillis >= XStepperInterval && XStepperMovementFlag == true){

    Serial.print("X Firing");
    static unsigned long count = 0;
    static boolean Status = LOW;

    if(count == 0){                           // When starting the movement, set the direction of the movement

      if(XStepperDirection == LOW){   
        digitalWrite(Driver1DirPin, LOW);
      }
      else if(XStepperDirection == HIGH){
        digitalWrite(Driver1DirPin, HIGH);
      }
      
    }
    if(count<XNumberOfSteps){
      
      if (Status == LOW) {

        digitalWrite(Driver1StepPin, HIGH);
        Status = HIGH;

      }
      else if (Status == HIGH) {

        digitalWrite(Driver1StepPin, LOW);
        Status = LOW;
        count++;

      }
      
    }
    else if(count == XNumberOfSteps){

      count = 0;
      XStepperMovementFlag = false;
      XStepperMovementCompleteFlag = true;
     // Serial.print("X DONE");
      
    }
    PreviousXStepperMillis = CurrentMillis;
    
  }

}

void YStepperMovement(){

  if(CurrentMillis - PreviousYStepperMillis >= YStepperInterval && YStepperMovementFlag == true){

    Serial.print("Y Firing");
    static unsigned long count = 0;
    static boolean Status = LOW;

    if(count == 0){                           // When starting the movement, set the direction of the movement

      if(YStepperDirection == LOW){   
        digitalWrite(Driver2DirPin, LOW);
      }
      else if(YStepperDirection == HIGH){
        digitalWrite(Driver2DirPin, HIGH);
      }
      
    }
    
    if(count<YNumberOfSteps){
      
      if (Status == LOW) {

        digitalWrite(Driver2StepPin, HIGH);
        Status = HIGH;

      }
      else if (Status == HIGH) {

        digitalWrite(Driver2StepPin, LOW);
        Status = LOW;
        count++;

      }
      
    }
    else if(count == YNumberOfSteps){

      count = 0;
      YStepperMovementFlag = false;
      YStepperMovementCompleteFlag = true;
     // Serial.print("Y DONE");
      
    }
    PreviousYStepperMillis = CurrentMillis;
    
  }

}

void MovementCompletionReadback(){

  if(XStepperMovementCompleteFlag == true && YStepperMovementCompleteFlag == true){
    
    XStepperMovementCompleteFlag = false;
    YStepperMovementCompleteFlag = false;
    Serial.print("Movement Complete");
    
    
  }

  
}
