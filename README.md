### Folkrace Code for Keyestudio Car Model (Robotex Competition)

Hello everyone! Here is the Folkrace code for Arduino. This code works with the Keyestudio car model, but you can adjust and reuse it for your own robot projects.

![Keyestudio Car Model](https://m.media-amazon.com/images/I/71HGmulkStL.jpg)

---

#### **Overview**

This code provides the basic control logic for an autonomous robot car using ultrasonic sensors to avoid obstacles and navigate through a course. It’s designed to work with the **Keyestudio 4WD BT Multi-purpose Smart Car v2.0** but can be adapted to other similar Arduino-based robot kits.

#### **Features**
- **Obstacle avoidance**: The robot uses ultrasonic sensors (left, center, right) to detect obstacles and decide on turning or reversing actions.
- **Sharp turns**: The robot can make sharp turns when necessary to navigate through tight spaces.
- **PWM control for motors**: The robot’s motors are controlled using PWM for speed adjustments.
- **Servo control for direction**: The robot adjusts its servo motor for turning based on sensor readings.

---

#### **Hardware Requirements**
- **Keyestudio 4WD BT Multi-purpose Smart Car v2.0** or any similar Arduino-based robot car kit.
- **Ultrasonic sensors** (left, center, right) for obstacle detection.
- **Servo motor** for directional adjustments.

---

#### **Pin Configuration**
- **Motor Pins**:
  - `ML_Ctrl`: Motor Left Control Pin
  - `ML_PWM`: Motor Left PWM Pin
  - `MR_Ctrl`: Motor Right Control Pin
  - `MR_PWM`: Motor Right PWM Pin
- **Ultrasonic Sensor Pins**:
  - `TRIG_PIN_CENTER`, `ECHO_PIN_CENTER`: For the center ultrasonic sensor.
  - `TRIG_PIN_LEFT`, `ECHO_PIN_LEFT`: For the left ultrasonic sensor.
  - `TRIG_PIN_RIGHT`, `ECHO_PIN_RIGHT`: For the right ultrasonic sensor.
- **Servo Pin**: Pin for the servo motor.

---

#### **Installation & Setup**
1. Connect your robot car model to the Arduino according to the pin configuration.
2. Install the **Ultrasonic** library in the Arduino IDE.
3. Upload the code to the Arduino board.
4. Power up your robot and place it in an obstacle-rich environment to see it in action.

---

#### **How to Use the Code**
1. **Start the robot**: The robot will begin by checking distances using its ultrasonic sensors.
2. **Obstacle Avoidance**: If the center sensor detects an obstacle within 30 cm, the robot will stop and check distances on the left and right sides. Based on the readings, it will decide to turn left, right, or move forward.
3. **Sharp Turns**: If a more drastic turn is needed, the robot will make a sharp turn either left or right.
4. **Reversal**: If the robot is too close to an obstacle (less than 15 cm), it will reverse for a short period before trying again.

---

#### **Code Explanation**
- **Motor Control**: The robot uses PWM (Pulse Width Modulation) to control the motor speeds. Higher values (close to 255) make the robot move faster, and lower values slow it down.
- **Servo Control**: The servo adjusts the direction of the robot by rotating to specified angles.
- **Obstacle Avoidance**: The logic compares the distances from the left, center, and right ultrasonic sensors to determine if the robot should turn, stop, or reverse.

---

#### **Code Usage**

```cpp
void loop() {
  avoid(); // This function handles the movement logic based on sensor input
}

void avoid() {
  lDist = getLeftDist(); // Get the distance from the left sensor
  cDist = getCenterDist(); // Get the distance from the center sensor
  rDist = getRightDist(); // Get the distance from the right sensor

  if (cDist <= 30 && cDist > 15) { 
    // Obstacle detection and decision making
    // Stop, check left and right distances, and choose a turn
    // For example, turning left or right based on sensor readings
  }

  if (cDist <= 15) {
    // If too close to an obstacle, reverse and recheck distances
  }

  if (abs(rDist - lDist) > 10) {
    // Adjust robot direction if left and right sensors differ significantly
  }
}
```

---

#### **Troubleshooting**
- **Robot not moving**: Ensure that all motor connections are correct, and the motor driver is properly powered.
- **Inconsistent sensor readings**: Check that the ultrasonic sensors are correctly aligned and free of obstructions.
- **Sharp turns not working**: Ensure that the servo motor is working correctly and can rotate to the specified angles.

---

#### **Contributing**
Feel free to fork this repository and contribute improvements, bug fixes, or enhancements. Make sure to test your changes thoroughly before submitting a pull request.



Happy coding, and good luck with your Folkrace! 🚗💨
