
// #include <AFMotor.h>

// Define input and PWM pins
#define LEFT_MOTOR_CONTACT_ONE 2  // contact pins correspond to the positive and negative leads on the motor
#define LEFT_MOTOR_CONTACT_TWO 3  // two pins handle direction. One must be low and the other high in order for current to flow through
#define RIGHT_MOTOR_CONTACT_ONE 4 // if contact one is high and contact two is low than the motor will spin forward
#define RIGHT_MOTOR_CONTACT_TWO 5 // if contact two is high and contact one is low than the motor will spin in reverse

// these two pins will be used later on to set our speed for the corresponding motor
#define LEFT_MOTOR 9
#define RIGHT_MOTOR 10

// indicator LED's
#define POWER_INDICATOR_LED 11 // a Green Led that is on indicated power to the system
#define BT_STATUS_LED 12       // a blue led that is off indicated that the BT module is not connected.
#define ERROR_LED 13           // a Red Led that is on indicated that our void loop has not yet run

// led logic flipper
#define LED_OFF HIGH
#define LED_ON LOW

// the maximum speed that the car can go
#define MAX_SPEED 225

char command;
float speedSetting = 1.0;
float adjustedSpeed = speedSetting * MAX_SPEED;

void setup()
{
    // set led's to their starting state
    digitalWrite(POWER_INDICATOR_LED, LED_ON); // signifies power to the circuit
    digitalWrite(BT_STATUS_LED, LED_OFF);      // off until the bluetooth module is powered
    digitalWrite(ERROR_LED, LED_ON);           // on until the loop is reached

    // Set pwn pins as output pins
    pinMode(RIGHT_MOTOR_CONTACT_ONE, OUTPUT);
    pinMode(RIGHT_MOTOR_CONTACT_TWO, OUTPUT);
    pinMode(LEFT_MOTOR_CONTACT_ONE, OUTPUT);
    pinMode(LEFT_MOTOR_CONTACT_TWO, OUTPUT);
    pinMode(RIGHT_MOTOR, OUTPUT);
    pinMode(LEFT_MOTOR, OUTPUT);

    // status led's
    pinMode(POWER_INDICATOR_LED, OUTPUT); // the power indicator should always be on as long as the system is powered on (Should always be on)
    pinMode(BT_STATUS_LED, OUTPUT);       // this indicator is off until communication with the bluetooth module can be made (Turn this LED off first in the loop)
    pinMode(ERROR_LED, OUTPUT);           // the program has not yet reached the main logic loop so the error led is on until then (Turn this on in the loop)

    Serial.begin(9600); // Set the baud rate to your Bluetooth module. (default for bt = 38400)
}

void loop()
{

    digitalWrite(BT_STATUS_LED, LED_ON); // start with the BT status led off (HIGH = OFF)
    digitalWrite(ERROR_LED, LED_OFF);    // the main logic loop has been reached

    if (Serial.available() > 0) // checks to see if data is coming from the serial port
    {
        // automatedMovement()

        digitalWrite(BT_STATUS_LED, LED_ON); // the led turns on if the BT receiver is on (LOW = ON)
        stop(1);                             // start with motors stoped
        command = Serial.read();

        // this switch will run any inputs sent by the controller (these are controller specific)
        // To match letters with their corrsponding actions reference: command_&_actions_of_controller.png
        switch (command)
        {
        case 'F':
            forward(0.1);
            break;
        case 'B':
            backward(0.1);
            break;
        case 'L':
            left(0.1);
            break;
        case 'R':
            right(0.1);
            break;
        case 'G':
            forwardLeft(0.1);
            break;
        case 'I':
            forwardRight(0.1);
            break;
        case 'H':
            backwardLeft(0.1);
            break;
        case 'J':
            backwardRight(0.1);
            break;
        case 'S':
            stop(1);
            break;
        case '1':
            speedSetting = 0.1;
            break;
        case '2':
            speedSetting = 0.2;
            break;
        case '3':
            speedSetting = 0.3;
            break;
        case '4':
            speedSetting = 0.4;
            break;
        case '5':
            speedSetting = 0.5;
            break;
        case '6':
            speedSetting = 0.6;
            break;
        case '7':
            speedSetting = 0.7;
            break;
        case '8':
            speedSetting = 0.8;
            break;
        case '9':
            speedSetting = 0.9;
            break;
        }
    }
}

void forward(int runTimeInSeconds)
{
    // pins have to be turned on and off in a specific order due to the nature of the L293 Chip
    // multiply the max speed (200) by the speed set by the user
    // the speedSetting will determine what fraction of the max speed the motor will spin at (0.5 speedSetting * 200 MAX_SPEED = 100 power sent to the motor)

    analogWrite(RIGHT_MOTOR, adjustedSpeed);
    analogWrite(LEFT_MOTOR, adjustedSpeed);
    digitalWrite(RIGHT_MOTOR_CONTACT_ONE, HIGH);
    digitalWrite(RIGHT_MOTOR_CONTACT_TWO, LOW);
    digitalWrite(LEFT_MOTOR_CONTACT_ONE, HIGH);
    digitalWrite(LEFT_MOTOR_CONTACT_TWO, LOW);

    // debug print statements
    /*
    Serial.print("\n");
    Serial.print("speedSetting = ");
    Serial.println(speedSetting);

   // Serial.print("MAX_SPEED = ");
   // Serial.println(adjustedSpeed);

    Serial.print("adjustedSpeed = ");
    Serial.println(adjustedSpeed);

    Serial.print("MAX_SPEED*speedSetting = ");
    Serial.println(MAX_SPEED*speedSetting);
    //Serial.print("\n");
    */

    delay(runTimeInSeconds * 1000); // 1 sec = 1,000 ms

    void backward(int runTimeInSeconds)
    {
        analogWrite(RIGHT_MOTOR, adjustedSpeed);
        analogWrite(LEFT_MOTOR, adjustedSpeed);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, HIGH);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, HIGH);

        delay(runTimeInSeconds * 1000);
    }

    void left(int runTimeInSeconds)
    {
        // if the right motor spins forward and the left motor spins backwards, than the car will turn left
        analogWrite(RIGHT_MOTOR, adjustedSpeed);
        analogWrite(LEFT_MOTOR, adjustedSpeed);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, HIGH);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, HIGH);

        delay(runTimeInSeconds * 1000);
    }

    void right(int runTimeInSeconds)
    {
        // if the left motor spins forward and the right motor spins backwards, than the car will turn right
        analogWrite(RIGHT_MOTOR, adjustedSpeed);
        analogWrite(LEFT_MOTOR, adjustedSpeed);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, HIGH);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, HIGH);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, LOW);

        delay(runTimeInSeconds * 1000);
    }

    void forwardLeft(int runTimeInSeconds)
    {
        // the right motor moves at normal speed while the left motor works at half speed, turning the vehicle left
        analogWrite(RIGHT_MOTOR, adjustedSpeed);
        analogWrite(LEFT_MOTOR, adjustedSpeed * 0.3);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, HIGH);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, HIGH);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, LOW);

        delay(runTimeInSeconds * 1000);
    }

    void forwardRight(int runTimeInSeconds)
    {
        // the left motor moves at normal speed while the right motor works at half speed, turning the vehicle right
        analogWrite(RIGHT_MOTOR, adjustedSpeed * 0.3);
        analogWrite(LEFT_MOTOR, adjustedSpeed);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, HIGH);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, HIGH);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, LOW);

        delay(runTimeInSeconds * 1000);
    }

    void backwardRight(int runTimeInSeconds)
    {
        // if the vehicle is moving backwards and the left motor is spinning at half of the normal speed, that the vehicle will turn to the right
        analogWrite(RIGHT_MOTOR, adjustedSpeed);
        analogWrite(LEFT_MOTOR, adjustedSpeed * 0.3);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, HIGH);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, HIGH);

        delay(runTimeInSeconds * 1000);
    }

    void backwardLeft(int runTimeInSeconds)
    {
        // if the vehicle is moving backwards and the right motor is spinning at half of the normal speed, that the vehicle will turn to the left
        analogWrite(RIGHT_MOTOR, adjustedSpeed * 0.3);
        analogWrite(LEFT_MOTOR, adjustedSpeed);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, HIGH);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, HIGH);

        delay(runTimeInSeconds * 1000);
    }

    // this method is intended to serve as a test to verify that the correct motor is spinning
    void leftOnly(int runTimeInSeconds)
    {
        analogWrite(LEFT_MOTOR, adjustedSpeed);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, HIGH);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, LOW);

        delay(runTimeInSeconds * 1000);
    }

    // this method is intended to serve as a test to verify that the correct motor is spinning
    void rightOnly(int runTimeInSeconds)
    {
        analogWrite(RIGHT_MOTOR, adjustedSpeed);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, HIGH);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, LOW);

        delay(runTimeInSeconds * 1000);
    }

    void stop(int runTimeInSeconds)
    {
        analogWrite(RIGHT_MOTOR, 0);
        analogWrite(LEFT_MOTOR, 0);
        digitalWrite(RIGHT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(RIGHT_MOTOR_CONTACT_TWO, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_ONE, LOW);
        digitalWrite(LEFT_MOTOR_CONTACT_TWO, LOW);

        delay(runTimeInSeconds * 1000);
    }

    void automatedMovement()
    {
        // intended for debugging with automated movements without the need for the bluetooth module

        leftOnly(2);
        // stop(2);
        delay(2000);
        rightOnly(2);
        delay(2000);
        forward(2);
        delay(2000);
        backward(2);
        delay(2000);
        left(2);
        delay(2000);
        right(2);
        delay(2000);
        forwardLeft(2);
        delay(2000);
        backwardLeft(2);
        delay(2000);
        backwardRight(2);
        delay(2000);
    }
}