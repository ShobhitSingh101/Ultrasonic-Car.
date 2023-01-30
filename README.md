# Ultrasonic_Car

In this Project, how to work Arduino based obstacle avoiding robot car. The car uses a servo mounted ultrasonic sensor to detect objects in front of and on either side of the car and an L293D DC motor driver shield to drive four geared motors, one on each wheel. An Arduino Uno underneath the shield controls the motor shield, ultrasonic sensor, and the servo.

The car drives itself forward until an object comes within the range of the sensor. The car then monitors the object until it is within the minimum distance and then stops moving. The servo is then used to turn the ultrasonic sensor left and the right, taking distance measurements in each direction. The car then decides which direction to turn based on which side has more distance available to move, then turns and continues on until the next object is detected. If both sides are blocked, the car will turn around and drive back out the way it came.
