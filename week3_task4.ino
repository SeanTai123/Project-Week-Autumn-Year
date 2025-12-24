
#include <SoftwareSerial.h>

// ---------- 1. BLUETOOTH CONNECTION ----------
// Arduino A5 (RX) -> Connect to HC-05 TX
// Arduino A4 (TX) -> Connect to HC-05 RX
SoftwareSerial myBT(A5, A4); 


#define enA 11  // PWM Speed Control
#define in1 1   // WARNING: You MUST unplug this wire when uploading code!
#define in2 2

// Right Motor
#define enB 3   // PWM Speed Control
#define in3 12
#define in4 13  // WARNING: Wheel will spin briefly on startup (LED pin)

int carSpeed = 150; 
char command;       

void setup() {
  
  myBT.begin(9600); 

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  stopCar();
  
}

void loop() {
  if (myBT.available()) {
    command = myBT.read(); 
    if (command == 'F') {
      forward();
    }
    else if (command == 'B') {
      backward();
    }
    else if (command == 'L') {
      left();
    }
    else if (command == 'R') {
      right();
    }
    else if (command == 'S' || command == '0') {
      stopCar();
    }
  }
}


void forward() {
  
    digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, carSpeed);

  // Right Motor Forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, carSpeed);
}

void backward() {
  // Left Motor Backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, carSpeed);

  // Right Motor Backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, carSpeed);
}

void left() {
  // TANK TURN LEFT: Left wheels back, Right wheels forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, carSpeed);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, carSpeed);
}

void right() {
  // TANK TURN RIGHT: Left wheels forward, Right wheels back
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, carSpeed);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, carSpeed);
}

void stopCar() {
  // Turn everything OFF
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}