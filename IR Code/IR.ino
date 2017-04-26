#include <IRremote.h>

int RECV_PIN = 2;
int led1 = 9;
int led2 = 6;
int led3 = 5;
int fan1 = 10;
int fan2 = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(RECV_PIN, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
}

int pwr = 0;
int ara[] = {26775, 12495, 6375, 31365, 4335, 14535, 23205, 17085, 19125, 765, -15811 };
void loop() {
  int data;
  if (irrecv.decode(&results)) {
    data = results.value;

    if (ara[1] == data)
      analogWrite(led1, 200);
    if (ara[4] == data)
      analogWrite(led1, 0);

    if (ara[2] == data)
      analogWrite(led2, 200);
    if (ara[5] == data)
      analogWrite(led2, 0);

    if (ara[3] == data)
      analogWrite(led3, 200);
    if (ara[6] == data)
      analogWrite(led3, 0);

    if (ara[7] == data) {
      digitalWrite(fan1, HIGH);
      digitalWrite(fan2, LOW);
      pwr = 255;
    }
    if (ara[8] == data) {
      digitalWrite(fan1, LOW);
      digitalWrite(fan2, LOW);
      pwr = 0;
    }

    if (ara[9] == data) {
      if (pwr - 80 >= 1) {
        pwr = pwr - 80;
        analogWrite(fan1, pwr);
        analogWrite(fan1, pwr);
      }
    }

    if (ara[10] == data) {
      if (pwr + 80 <= 255 && pwr) {
        pwr = pwr + 80;
        analogWrite(fan1, pwr);
        analogWrite(fan1, pwr);
      }
    }

    Serial.println(data);
    irrecv.resume(); 
  }
  delay(100);
}
