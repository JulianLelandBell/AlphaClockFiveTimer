int startButton = 2;
boolean count = false;
boolean buttonPressed = false;
long currentTime = 0;
long startTime = 0;
long stopTime = 0;
long elapsedTime = 0;
int digitsDisplayed = 5;
char header = 0xff;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(19200); //Start serial comms

}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  elapsedTime = elapsedTime + currentTime - startTime;
  sendToClock(elapsedTime);
  delay(100);
}

void sendToClock(long timeValue) {
  String timeString = "0";
  char timeChar[6];
  /*String newTimeString[digitsDisplayed];
  timeString = char(timeValue/100);
  int x = 0;
  for(int i = sizeof(timeString); i >> sizeof(timeString - digitsDisplayed); i --){
    newTimeString[x] = timeString[i];
    x =+ 1;
  }*/
  timeString = String(timeValue);
  if(timeString.length() > 5){
    int distance = timeString.length()-5;
    timeString.remove(0,distance);
  }  
  timeString.toCharArray(timeChar, 6);
  Serial1.print(header);
  Serial1.print("A");
  Serial1.print(0);
  Serial1.print(timeChar);
  Serial1.print("---1-");
  //Serial.println(timeValue);
}
