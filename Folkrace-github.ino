#define ML_Ctrl 4
#define ML_PWM 5
#define MR_Ctrl 2
#define MR_PWM 9

#include <Ultrasonic.h>

#define TRIG_PIN_CENTER 12
#define ECHO_PIN_CENTER 13
#define TRIG_PIN_LEFT 11
#define ECHO_PIN_LEFT A3
#define TRIG_PIN_RIGHT A5
#define ECHO_PIN_RIGHT A4

const int servoPin = 10;

Ultrasonic ultrasonic_left(TRIG_PIN_LEFT, ECHO_PIN_LEFT);
Ultrasonic ultrasonic_center(TRIG_PIN_CENTER, ECHO_PIN_CENTER);
Ultrasonic ultrasonic_right(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT);

long lDist, cDist, rDist, crDist, clDist;
long lastlDist, lastcDist, lastrDist;
int staycount = 0;
void setup() {
  Serial.begin(9600);
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
  delay(300);

  setServo(90);
}

void loop() {
  avoid();
}

void avoid() {
  lDist = getLeftDist();
  cDist = getCenterDist();
  rDist = getRightDist();

  Serial.print(static_cast<int>(floor(lDist)));
  Serial.print(" ");
  Serial.print(static_cast<int>(floor(cDist)));
  Serial.print(" ");
  Serial.print(static_cast<int>(floor(rDist)));
  Serial.println("");
  Serial.print(lastlDist);
  Serial.print(" ");
  Serial.print(lastcDist);
  Serial.print(" ");
  Serial.print(lastrDist);
  Serial.println("");

  // asaqidaki if ilisende qurtarmaq ucundu
  // if (
  //   // lastlDist == static_cast<int>(floor(lDist)) && lastcDist == static_cast<int>(floor(cDist)) && lastrDist == static_cast<int>(floor(rDist))
  //   abs(lastlDist - lDist) ==0 && abs(lastcDist - cDist) ==0 && abs(lastrDist - rDist) ==0) {
  //   if (staycount == 100) {
  //     staycount == 0;


  //     car_Stop();
  //     setServo(45);
  //     crDist = getCenterDist();
  //     setServo(135);
  //     clDist = getCenterDist();
  //     setServo(90);
  //     car_back();
  //     delay(800);

  //     unsigned long turnDuration2 = 300;
  //     unsigned long startTime2 = millis();

  //     if (crDist < clDist) {
  //       while (millis() - startTime2 < turnDuration2) {
  //         car_left_sharph();
  //       }
  //       startTime2 = millis();
  //       while (millis() - startTime2 < turnDuration2) {
  //         car_right();
  //       }
  //     } else {
  //       while (millis() - startTime2 < turnDuration2) {
  //         car_right_sharph();
  //       }
  //       startTime2 = millis();
  //       while (millis() - startTime2 < turnDuration2) {
  //         car_left();
  //       }
  //     }

  //   } else {
  //     staycount++;
  //   }
  // }


  if (cDist <= 30 && cDist > 15) {


    car_Stop();
    setServo(45);
    crDist = getCenterDist();
    setServo(135);
    clDist = getCenterDist();
    setServo(90);



    unsigned long turnDuration2 = 450;
    unsigned long startTime2 = millis();

    if (crDist < clDist) {
      while (millis() - startTime2 < turnDuration2) {
        car_left_sharph();
      }
      startTime2 = millis();
      while (millis() - startTime2 < turnDuration2*2) {
        car_front();
        if (cDist <= 15) break;
      }
      startTime2 = millis();
      while (millis() - startTime2 < turnDuration2) {
        car_right();
      }
    } else {
      while (millis() - startTime2 < turnDuration2) {
        car_right_sharph();
      }
      startTime2 = millis();
      while (millis() - startTime2 < turnDuration2*2) {
        car_front();
        if (cDist <= 15) break;
      }
      startTime2 = millis();
      while (millis() - startTime2 < turnDuration2) {
        car_left();
      }
    }
  }

  if (cDist <= 15) {
    car_Stop();
    delay(300);
    car_back();
    delay(500);
    car_Stop();
    setServo(45);
    crDist = getCenterDist();
    setServo(135);
    clDist = getCenterDist();
    setServo(90);

    unsigned long turnDuration2 = 550;
    unsigned long startTime2 = millis();

    if (crDist < clDist) {
      while (millis() - startTime2 < turnDuration2) {
        car_left_sharph();
      }
      startTime2 = millis();
      while (millis() - startTime2 < turnDuration2*2) {
        car_front();
        if (cDist <= 15) break;
      }
      startTime2 = millis();
      while (millis() - startTime2 < turnDuration2) {
        car_right();
      }
    } else {
      while (millis() - startTime2 < turnDuration2) {
        car_right_sharph();
      }
      startTime2 = millis();
      while (millis() - startTime2 < turnDuration2*2) {
        car_front();
        if (cDist <= 15) break;
      }
      startTime2 = millis();
      while (millis() - startTime2 < turnDuration2) {
        car_left();
      }
    }
  }


  if (abs(rDist - lDist) > 10) {
    unsigned long turnDuration = abs(rDist - lDist) * 10;
    unsigned long startTime = millis();

    if (rDist > lDist) {
      while (millis() - startTime < turnDuration) {
        car_right();
      }
    } else {
      while (millis() - startTime < turnDuration) {
        car_left();
      }
    }
  } else {
    car_front();
  }


  lastlDist = getLeftDist();
  lastcDist = getCenterDist();
  lastrDist = getRightDist();
}

void car_front() {
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 230);
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 230);
}

void car_back() {
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 150);
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 150);
}

void car_left() {
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 200);
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 30);
}

void car_right() {
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 30);
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 200);
}

void car_left_sharph() {
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 255);
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 30);
}

void car_right_sharph() {
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 30);
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 255);
}

void car_Stop() {
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 0);
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 0);
  delay(60);
}

long getLeftDist() {
  return ultrasonic_left.read();
}
long getCenterDist() {
  return ultrasonic_center.read();
}
long getRightDist() {
  return ultrasonic_right.read();
}


void setServo(int angle) {
  for (int i = 0; i < 30; i++) {
    int pulsewidth = (angle * 11) + 500;
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servoPin, LOW);
    delay(20 - pulsewidth / 1000);
  }
}

// Function to calculate dynamic turn time based on motor PWM difference
unsigned long calculateTurnTime(float angle, int left_pwm, int right_pwm, float turning_radius) {

  const float wheelbase = 10.5;   // Distance between the wheels in cm
  const float motor_speed = 5.0;  // Speed in cm/sec (adjust based on PWM)

  // Convert angle to radians
  float angle_rad = radians(angle);

  // Calculate the arc length each wheel would cover for the specified angle
  float left_wheel_distance = turning_radius * angle_rad;                 // Distance traveled by the left wheel
  float right_wheel_distance = (turning_radius + wheelbase) * angle_rad;  // Distance for the right wheel

  // Estimate the time for each wheel to cover its distance based on PWM speed
  // PWM = 0 -> no movement; PWM = 255 -> max speed (motor_speed)
  float left_wheel_time = (left_wheel_distance / motor_speed) * (255.0 / left_pwm);
  float right_wheel_time = (right_wheel_distance / motor_speed) * (255.0 / right_pwm);

  // Return the average time for the turn
  unsigned long turn_time = (left_wheel_time + right_wheel_time) / 2.0;

  return (unsigned long)(turn_time * 1000);  // Convert to milliseconds
}