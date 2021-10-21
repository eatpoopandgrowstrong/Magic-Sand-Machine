const int Driver1StepPin = 6;
const int Driver1DirPin = 7;

const int Driver2StepPin = 8;
const int Driver2DirPin = 9;

unsigned long CurrentMillis;
unsigned long PreviousStepperMillis;
int StepperInterval = 5;

void setup() {
  // put your setup code here, to run once:
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
  CurrentMillis = micros();
  StepperMovement();
  
}

void StepperMovement(){
  if(CurrentMillis - PreviousStepperMillis >= StepperInterval){

    static boolean Status = 0;
    digitalWrite(Driver1DirPin, HIGH);
     if(Status == LOW){
      digitalWrite(Driver1StepPin, HIGH);
      Status = HIGH;
     }
     else if(Status == HIGH){
      digitalWrite(Driver1StepPin, LOW);
      Status = LOW;
      
     }
     PreviousStepperMillis = CurrentMillis;
  }
  
}
