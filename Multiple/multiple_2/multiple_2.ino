const int pwPin1 = 11;
const int pwPin2 = 9;
const int pwPin3 = 7;
const int pwPin4 = 5;

void setup () {
  Serial.begin(57600);
  pinMode(pwPin1, INPUT);
  pinMode(pwPin2, INPUT);
  pinMode(pwPin3, INPUT);
  pinMode(pwPin4, INPUT);
}

void read_sensor(int pwPin, byte c){
  long pulse = pulseIn(pwPin, HIGH);
  byte sensor = pulse/147
  Serial.print(c);
  Serial.write(sensor);
}

void loop () {
  read_sensor(pwPin1, 1);
  delay(50);
  read_sensor(pwPin2, 2);
  delay(50);
  read_sensor(pwPin3, 3);
  delay(50);
  read_sensor(pwPin4, 4);
  delay(50);
}


