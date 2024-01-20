#include <QTRSensors.h>
const int m11Pin   = 7;
const int m12Pin   = 6;
const int m21Pin   = 5;
const int m22Pin   = 4;
const int m1Enable = 11;
const int m2Enable = 10;

// OUTPUT 1-2 -> Motor Dreapta

int m1Speed = 0;
int m2Speed = 0;

// increase kp’s value and see what happens
float kp = 2;
float ki = 0.1;
float kd = 4;

int p;
int i;
int d;

const int maxSpeed = 255;
const int minSpeed = -255;

const int baseSpeed = 200;

QTRSensors qtr;

const int sensorCount = 6;

uint16_t sensorValues[sensorCount];
int      sensors[sensorCount] = {0, 0, 0, 0, 0, 0};

void setup()
{

    // pinMode setup
    pinMode(m11Pin, OUTPUT);
    pinMode(m12Pin, OUTPUT);
    pinMode(m21Pin, OUTPUT);
    pinMode(m22Pin, OUTPUT);
    pinMode(m1Enable, OUTPUT);
    pinMode(m2Enable, OUTPUT);

    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorCount);

    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

    // calibrate the sensor. For maximum grade the line follower should do the movement itself,
    // without human interaction.
    selfCalibrate();
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(9600);
}

void loop()
{
    int error = readError();
    pidControl(error);
    setMotorSpeed(m1Speed, m2Speed);

    // debug();
}

void readError()
{
    const int minSensor = 0;
    const int maxSensor = 5000;

    const int minError = -30;
    const int maxError = 30;

    uint16_t linePosition = qtr.readLineBlack(sensorValues);
    return map(linePosition, minSensor, maxSensor, minError, maxError);
}

void selfCalibrate()
{
    const int speed = 100;

    for (uint16_t i = 0; i < 400; i++)
    {
        qtr.calibrate();
    }
}

// calculate PID value based on error, kp, kd, ki, p, i and d.
void pidControl(int error)
{
    static int lastError;

    p = error;
    i = i + error;
    d = error - lastError; //  TO MODIFY

    int motorSpeed = kp * p + ki * i + kd * d; // = error in this case

    m1Speed = baseSpeed;
    m2Speed = baseSpeed;

    if (abs(error) <= 5) {
        m1Speed = maxSpeed;
        m2Speed = maxSpeed;
    }

    //  asa se trateaza curbele extreme (90º)
    if (error >= 20)
    {
        m1Speed = minSpeed;
        m2Speed = maxSpeed;
    }
    else if (error <= -20)
    {
        m1Speed = maxSpeed;
        m2Speed = minSpeed;
    }
    else
    {

        if (error < 0)
        {
            m1Speed += motorSpeed;
        }
        else if (error > 0)
        {
            m2Speed -= motorSpeed;
        }
    }

    m1Speed = constrain(m1Speed, minSpeed, maxSpeed);
    m2Speed = constrain(m2Speed, minSpeed, maxSpeed);

    lastError = error;
}

// each arguments takes values between -255 and 255. The negative values represent the motor speed
// in reverse.
void setMotorSpeed(int motor1Speed, int motor2Speed)
{
    // remove comment if any of the motors are going in reverse
    //  motor1Speed = -motor1Speed;
    //  motor2Speed = -motor2Speed;
    if (motor1Speed == 0)
    {
        digitalWrite(m11Pin, LOW);
        digitalWrite(m12Pin, LOW);
        analogWrite(m1Enable, motor1Speed);
    }
    else if (motor1Speed > 0)
    {
        digitalWrite(m11Pin, HIGH);
        digitalWrite(m12Pin, LOW);
        analogWrite(m1Enable, motor1Speed);
    }
    else
    {
        digitalWrite(m11Pin, LOW);
        digitalWrite(m12Pin, HIGH);
        analogWrite(m1Enable, -motor1Speed);
    }

    if (motor2Speed == 0)
    {
        digitalWrite(m21Pin, LOW);
        digitalWrite(m22Pin, LOW);
        analogWrite(m2Enable, motor2Speed);
    }
    else if (motor2Speed > 0)
    {
        digitalWrite(m21Pin, HIGH);
        digitalWrite(m22Pin, LOW);
        analogWrite(m2Enable, motor2Speed);
    }
    else
    {
        digitalWrite(m21Pin, LOW);
        digitalWrite(m22Pin, HIGH);
        analogWrite(m2Enable, -motor2Speed);
    }
}

void debug()
{
    Serial.print("Error: ");
    Serial.println(error);
    Serial.print("M1 speed: ");
    Serial.println(m1Speed);

    Serial.print("M2 speed: ");
    Serial.println(m2Speed);

    for (int i = 0; i < 6; i++)
    {
        Serial.print(sensorValues[i]);
        Serial.print(" ");
    }

    Serial.println();
}
