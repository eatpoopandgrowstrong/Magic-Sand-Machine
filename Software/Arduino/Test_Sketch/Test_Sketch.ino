const int StepPin = 6;
const int DirPin = 7;
int count;
int DelayIntervalMicroseconds = 1000;
int DelayIntervalMilliseconds = 10;

void setup() {
  // put your setup code here, to run once:  
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  digitalWrite(DirPin, HIGH);
  //delay(500);
  digitalWrite(StepPin, LOW);
  delayMicroseconds(DelayInterval);
  digitalWrite(StepPin, HIGH);
  delayMicroseconds(DelayInterval);
  */
  /*
  digitalWrite(DirPin, HIGH);
  delay(50);
  for(count = 0; count<200; count++){
    
    digitalWrite(StepPin, LOW);
    delayMicroseconds(DelayIntervalMicroseconds);
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(DelayIntervalMicroseconds);
  }
  */
  /*
  digitalWrite(DirPin, LOW);
  delay(50);
  for(count = 0; count<200; count++){
    
    digitalWrite(StepPin, LOW);
    delayMicroseconds(DelayIntervalMicroseconds);
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(DelayIntervalMicroseconds);
  }
  */
  /*
    digitalWrite(StepPin, LOW);
    delayMicroseconds(DelayIntervalMicroseconds);
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(DelayIntervalMicroseconds);
    */
    digitalWrite(StepPin, LOW);
    delay(DelayIntervalMilliseconds);
    digitalWrite(StepPin, HIGH);
    delay(DelayIntervalMilliseconds);
 
}
