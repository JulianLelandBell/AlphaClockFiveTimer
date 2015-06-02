 #include <Time.h> 

#define startBut 2
#define stopBut 3
#define flashLights 48
#define redLight 50
#define grnLight 52

int digitsDisplayed = 5;
char header = 0xff;
String thingToSend = "     ";
int colonConfig = 2;

void setup() {
  // set up 2 as green button, 3 as red
  Serial1.begin(19200); //Start serial comms
  Serial1.print(header);
  Serial1.print("B0011*******"); // set brightness to maximum
  pinMode(startBut, INPUT);
  pinMode(stopBut, INPUT);
  pinMode(redLight, OUTPUT);
  pinMode(grnLight, OUTPUT);
  pinMode(flashLights, OUTPUT);
  digitalWrite(startBut, HIGH);
  digitalWrite(stopBut, HIGH);
  digitalWrite(flashLights, LOW);
}

void loop() {
  // block before start button is hit
  sendToClock("READY", 0);
  digitalWrite(grnLight, HIGH);
  int go = 0;
  while (go == 0) {
    if (digitalRead(startBut) == LOW) {
      go = 1;
    }
  }
  // run the timer until red button is hit
  setTime(0);
  digitalWrite(grnLight, LOW);
  digitalWrite(redLight, HIGH);
  digitalWrite(flashLights, HIGH);
  while (go == 1) {
    colonConfig = 2;
    String s = String(second());
    String m = String(minute());
    if (s.length() < 2) s = "0" + s;
    if (m == "0") {
      m = "  ";
      colonConfig = 1;
    }
    else if (m.length() < 2) m = " " + m;
    thingToSend = m + s + (millis()/100)%10;
    sendToClock(thingToSend, colonConfig);
    if (digitalRead(stopBut) == LOW) go = 0;
    delay(50);
  }
  digitalWrite(flashLights, LOW);
  // do the thing at the end of the game
  for(int i=0; i<3; i++) {
    sendToClock(thingToSend, colonConfig);
    digitalWrite(redLight, LOW);
    digitalWrite(grnLight, HIGH);
    delay(250);
    digitalWrite(grnLight, LOW);
    digitalWrite(redLight, HIGH);
    delay(250);
    sendToClock("     ", 0);
    digitalWrite(redLight, LOW);
    digitalWrite(grnLight, HIGH);
    delay(250);
    digitalWrite(grnLight, LOW);
    digitalWrite(redLight, HIGH);
    delay(250);
    digitalWrite(redLight, LOW);
  }
}

void sendToClock(String value, int colons) { // value is the text to display, colons is the configuration of dots on the screen
  Serial1.print(header);
  Serial1.print("A");
  Serial1.print(0);
  Serial1.print(value);
  if (colons == 0) Serial1.print("-----");
  else if (colons == 1) Serial1.print("---1-");
  else Serial1.print("-121-");
}
