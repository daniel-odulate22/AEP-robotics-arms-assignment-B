# AEP robotics arms Assignment B: Debugging a Sensor-Based Robotic System

## Project Overview

This project uses an HC-SR04 ultrasonic sensor, a servo motor, and a buzzer connected to an Arduino Uno. The sensor measures the distance to an object, the servo changes position according to the measured distance, and the buzzer provides audible alerts.

The assignment focuses on identifying and fixing errors in the original Class 4 program and explaining the corrected implementation.

## Issues Identified

### 1. Pin Conflict

**Original code:**
```cpp
int trigPin = 9;
int buzzerPin = 9;
```

Both the ultrasonic sensor's trigger pin and the buzzer were assigned to Arduino D9.

**Problem:** Two components were configured to use the same pin for different output functions, which could cause interference.

**Solution:** The trigger pin remains on D9, while the buzzer is assigned to D8.

### 2. Incorrect `noTone()` Function Call

**Original code:**
```cpp
noTone(buzzerPin, 1000);
```

**Problem:** The standard Arduino `noTone()` function accepts one argument, the pin number. The additional frequency argument is invalid.

**Solution:**
```cpp
noTone(buzzerPin);
```

This stops tone generation on the selected pin.

## Additional Improvements

- Added a timeout to `pulseIn()` so the program can handle missing echoes more reliably.
- Added a separate Serial Monitor message for a missing echo.
- Corrected the far-distance alert to produce two short beeps, consistent with the original code comment.
- Kept the distance thresholds and servo positions from the original program.

## How the System Works

1. The Arduino sends a short trigger pulse to the HC-SR04 sensor.
2. The sensor returns an echo pulse.
3. The Arduino measures the echo duration and estimates the distance in centimetres.
4. The program compares the measured distance with the specified thresholds.
5. The servo moves to the corresponding angle.
6. The buzzer provides an alert based on the distance condition.
7. The program repeats the measurement cycle.

## Distance Conditions

| Condition | Servo angle | Buzzer behaviour |
|---|---:|---|
| Distance at or below 10 cm, greater than zero | 90° | Continuous 1000 Hz tone during the branch and following delay |
| Greater than 10 cm and at or below 30 cm | 45° | Silent |
| Greater than 30 cm | 0° | Two short beeps |
| No echo detected | 0° | Two-part alert at 2000 Hz and 1000 Hz |

## Testing

The corrected program should be tested in Tinkercad by moving an object through the different distance ranges and checking the servo position, buzzer behaviour, and Serial Monitor output.

**Test results:** To be completed after running the corrected program.

## Files

- `assignment_b.ino`: Corrected Arduino program.
- `README.md`: Bug report, explanation, and testing documentation.

## Conclusion

This debugging exercise demonstrates the importance of assigning unique pins to independent outputs, following the correct syntax of Arduino library functions, and handling missing sensor readings. It also demonstrates how distance measurements can control an actuator and provide audible feedback.
