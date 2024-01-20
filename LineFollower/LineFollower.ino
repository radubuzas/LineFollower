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
float kp = 20;
float ki = 0;
float kd = 2;

int p;
int i;
int d;

int error;

const int maxSpeed = 255;
const int minSpeed = -255;

int baseSpeed = 200;

QTRSensors qtr;

const int sensorCount = 8;

uint16_t sensorValues[sensorCount];
int      sensors[sensorCount] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
    Serial.begin(9600);

    // pinMode setup
    pinMode(m11Pin, OUTPUT);
    pinMode(m12Pin, OUTPUT);
    pinMode(m21Pin, OUTPUT);
    pinMode(m22Pin, OUTPUT);
    pinMode(m1Enable, OUTPUT);
    pinMode(m2Enable, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, sensorCount);

    delay(500);

    //  turn on Arduino's LED to indicate we are in calibration mode
    digitalWrite(LED_BUILTIN, HIGH);
    selfCalibrate();
    digitalWrite(LED_BUILTIN, LOW);
}

void selfCalibrate()
{
    const unsigned long timeToCalibrateMs = 5000;
    unsigned long start = millis();
    int speed = 160;

    while (millis() - start < timeToCalibrateMs) {
        Serial.print("Hay\n");
        qtr.calibrate();
        updateError();
        if (error > 45) {
            setMotorSpeed(speed, -speed);
            continue;
        }
        if (error < -45) {
            setMotorSpeed(-speed, speed);
            continue;
        }

    }
}

void loop()
{
    updateError();
    pidControl();
    setMotorSpeed(m1Speed, m2Speed);
    debug();
}

const int minError = -50;
const int maxError = 50;

void updateError()
{
    const int minSensor = 0;
    const int maxSensor = 5000;

    error = map(qtr.readLineBlack(sensorValues), minSensor, maxSensor, minError, maxError);
}

// calculate PID value based on error, kp, kd, ki, p, i and d.
void pidControl()
{
    static int lastError;
    static int cnt = 0;

    // if (abs(error) <= 5){
    //     error = 0;
    // }

    p = error;
    i = i + error;
    d = error - lastError; //  TO MODIFY

    if (++cnt == 10) {
        lastError = error;
        cnt = 0;
    }

    baseSpeed = map(abs(d), 0, 50, 200, 140);

    if (baseSpeed < 160) {
        kp = 40;
        kd = 0;
    }
    else {
        kp = 20;
        kd = 100;
    }

    int motorSpeed = kp * p + ki * i + kd * d; // = error in this case

    m1Speed = baseSpeed;
    m2Speed = baseSpeed;

    if (error < 0)
    {
        m1Speed += motorSpeed;
    }
    else if (error > 0)
    {
        m2Speed -= motorSpeed;
    }

    m1Speed = constrain(m1Speed, minSpeed, maxSpeed);
    m2Speed = constrain(m2Speed, minSpeed, maxSpeed);
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
    static unsigned long lastDebugTime = 0;
    static unsigned int debugDelay = 500;

    if (millis() - lastDebugTime > debugDelay) {
        Serial.print("Error: ");
        Serial.println(error);
        Serial.print("M1 speed: ");
        Serial.println(m1Speed);

        Serial.print("M2 speed: ");
        Serial.println(m2Speed);

        for (int i = 0; i < 8; i++)
        {
            Serial.print(sensorValues[i]);
            Serial.print(" ");
        }

        Serial.println();

        lastDebugTime = millis();
    }
}
