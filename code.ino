#include <SoftwareSerial.h>


SoftwareSerial mySerial(3, 2); 
String bullshit;
int led = 5;
String number;
bool isallowed = false;
String allowed[] = {"01147407649", "01143299025", "01114878581", "01550700517"};
int len = sizeof(allowed)/sizeof(String);

String temp;
int counter = 0;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Initializing..."); 
  //mySerial.println("AT+IPR=9600\rAT&W\r");
  delay(100);
}

void loop()
{
  updateSerial();
}

void dowateveryes() { // do watever you want if the number is allowed

  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);

  
}



void dowateverno() { // do watever you want if the number is not allowed
  for (int h = 0; h<7; h++) {
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
  }
  
}

String getnum(String incoming) {
  String numb;
  for (int k = 0; k < incoming.length(); k++) {
    if (bullshit[k] == '"') {
      k += 1;
      while (bullshit[k] != '"') {
        numb.concat(bullshit[k]);
        k+=1;
      }
      return numb;
    }
  }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    bullshit = mySerial.readString();
   // Serial.println(bullshit);
    for (int i = 2; i< 6; i++){
      temp.concat(bullshit[i]);
    }
    if (temp == "RING"){
      mySerial.println("ATH");
      number = getnum(x);
      for (int j = 0; j < len; j++) {
        if (number == allowed[j]) {
          isallowed = true;
        }
      }
      if (isallowed) {
        dowateveryes();
        Serial.print(number);
        Serial.println(" is ringing and allowed");
      }
      else {
        dowateverno();
        Serial.print(number);
        Serial.println(" is ringing and NOT allowed");
      }
    }
    isallowed = false;
    bullshit = "";
    temp = "";
    number = "";
  }
}

