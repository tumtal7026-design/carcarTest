#include <Arduino.h>

/* ----------- Pin Tanımları ----------- */
// Motor A
#define ENA 4
#define IN1 5
#define IN2 6

// Motor B
#define ENB 16
#define IN3 7
#define IN4 15

/* ----------- PWM Ayarları ----------- */
#define PWM_FREQ 1000
#define PWM_RESOLUTION 8   // 0-255
#define PWM_CH_A 0
#define PWM_CH_B 1

/* ----------- Fonksiyonlar ----------- */
void motorA(int speed);
void motorB(int speed);
void stopMotors();

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  ledcSetup(PWM_CH_A, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CH_B, PWM_FREQ, PWM_RESOLUTION);

  ledcAttachPin(ENA, PWM_CH_A);
  ledcAttachPin(ENB, PWM_CH_B);

  stopMotors();
  Serial.println("Motor sistemi hazir");
}

void loop() {
  Serial.println("Ileri");
  motorA(50);
  motorB(50);
  delay(3000);

  Serial.println("Geri");
  motorA(-50);
  motorB(-50);
  delay(3000);

  Serial.println("Dur");
  stopMotors();
  delay(2000);
}

/* ----------- Motor Fonksiyonları ----------- */
void motorA(int speed) {
  if (speed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (speed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  ledcWrite(PWM_CH_A, constrain(speed, 0, 255));
}

void motorB(int speed) {
  if (speed > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (speed < 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    speed = -speed;
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  ledcWrite(PWM_CH_B, constrain(speed, 0, 255));
}

void stopMotors() {
  ledcWrite(PWM_CH_A, 0);
  ledcWrite(PWM_CH_B, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
