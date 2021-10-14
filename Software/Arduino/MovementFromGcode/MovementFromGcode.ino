








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
    

    NewData = false;
    
  }


  
}
