#define trigger 13
#define echo 14

void setup() {
  Serial.begin(115200);
  pinMode(trigger, INPUT);
  pinMode(echo, OUTPUT);
}

void loop() {

}

int checkLevel() {
  flaot distance, cent;
  int len = 20; //Assumed length of the box
  float level = 0.0;
  digitalWrite(trigger, LOW); //low pulse first to ensure a clean high pulse.
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delayMicroseconds(10);

  distance = pulseIn(ep1, HIGH);
  // convert the time into a distance
  cent = microToCms(d1);
  //calculate percentage
  level = cent/len;
  level = 100 - level * 100;
  return ((int)level);
}

long microToCms(long microseconds) {
  return microseconds / 29 / 2;
}
