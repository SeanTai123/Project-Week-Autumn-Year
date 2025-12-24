// ---------- Ultrasonic ----------
#define TRIG A5
#define ECHO A4


#define enA 11
#define enB 3

#define in1 1  
#define in2 2

#define in3 12
#define in4 13

const int OBSTACLE_THRESHOLD = 15; 
const int TURN_SPEED = 180;
const int FORWARD_SPEED = 200;

void setup() {

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  analogWrite(enA, FORWARD_SPEED);
  analogWrite(enB, FORWARD_SPEED);
}

void right() {
  analogWrite(enA, TURN_SPEED);
  analogWrite(enB, TURN_SPEED);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left() {
  analogWrite(enA, TURN_SPEED);
  analogWrite(enB, TURN_SPEED);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void forward() {
  analogWrite(enA, FORWARD_SPEED);
  analogWrite(enB, FORWARD_SPEED);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backward() {
  analogWrite(enA, FORWARD_SPEED);
  analogWrite(enB, FORWARD_SPEED);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
}

void stopCar() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000); 
  
  if (duration == 0) return 999; 

  return duration * 0.034 / 2;
}

void loop() {
  long distance = getDistance();

  if (distance <= OBSTACLE_THRESHOLD) {

    stopCar();
    delay(200); 
    backward();
    delay(200);
    right();
    
    long turn_distance = 0;
    int scan_count = 0;
    do {
      delay(250); 
      stopCar();
      delay(100); 
      turn_distance = getDistance();

      if (turn_distance <= OBSTACLE_THRESHOLD) {
        right();
        scan_count++;
      }
      if (scan_count > 20) {
        stopCar(); 
        break; 
      }

    } while (turn_distance <= OBSTACLE_THRESHOLD);
  } 
  else {
    forward();
  }
}