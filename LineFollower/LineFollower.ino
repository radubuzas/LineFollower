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

int error;

QTRSensors qtr;

const int sensorCount = 6;
uint16_t sensorValues[sensorCount];
int sensors[sensorCount] = {0, 0, 0, 0, 0, 0};

void setup() {
    Serial.begin(9600);

    //  Setup pins
    pinMode(m11Pin, OUTPUT);
    pinMode(m12Pin, OUTPUT);
    pinMode(m21Pin, OUTPUT);
    pinMode(m22Pin, OUTPUT);
    pinMode(m1Enable, OUTPUT);
    pinMode(m2Enable, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    qtr.setTypeAnalog();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorCount);

    delay(500);

    //  Turn on Arduino's LED to indicate we are in calibration mode
    digitalWrite(LED_BUILTIN, HIGH);
    selfCalibrate();
    digitalWrite(LED_BUILTIN, LOW);
}

void selfCalibrate() {
    static const unsigned long calibrateTime = 5000;
    static unsigned long start;

    int calibrateSpeed = 160;

    //  Jiggle the car a little. After the initial jiggle, the sensor reads decent values

    qtr.calibrate();

    setMotorSpeed(calibrateSpeed, -calibrateSpeed);
    for (int i = 1; i <= 4; i++) {
        delay(50);
        qtr.calibrate();
    }

    setMotorSpeed(-calibrateSpeed, calibrateSpeed);
    for (int i = 1; i <= 4; i++) {
        delay(50);
        qtr.calibrate();
    }

    //  Move the car to the highest and lowest possible errors
    start = millis();
    while(millis() - start < calibrateTime) {
        qtr.calibrate();
        updateError();

        if (error > 48) {
            setMotorSpeed(calibrateSpeed, -calibrateSpeed);
        }
        else if(error < -48) {
            setMotorSpeed(-calibrateSpeed, calibrateSpeed);
        }
    }
}

void loop() {
    updateError();
    pidControl();
    setMotorSpeed(m1Speed, m2Speed);
    debug();
}

//  Calculate the error from the current sensor values
void updateError() {
    static const int minSensor = 0;
    static const int maxSensor = 5000;
    static const int minError = -50;
    static const int maxError = 50;

    error = map(qtr.readLineBlack(sensorValues), minSensor, maxSensor, minError, maxError);

    //  If the error is small, ignore it
    if (abs(error) <= 5) {
        error = 0;
    }
}

// Calculate PD value based on error, kp, kd, p and d.
void pidControl() {
    static float kp;
    static float kd;

    static int p;
    static int d;

    static const int minSpeed = -255;
    static const int maxSpeed = 255;

    static int baseSpeed;

    static int lastError;
    static int cnt;

    p = error;
    d = error - lastError;

    if (++cnt > 18) {
        lastError = error;
        cnt = 0;
    }

    //  Increase the speed on a straight line and decrease it in curves
    baseSpeed = map(abs(d), 0, 80, 240, 190);

    //  If you are in a curve take a hard turn
    if (baseSpeed <= 210) {
        kp = 50;
        kd = 10;
    }
    else {
        kp = 5;
        kd = 120;
    }

    int motorSpeed = kp * p + kd * d; // = error in this case

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

//  Print error, motors speed and sensor values for debug
void debug() {
    static unsigned long lastDebugTime = 0;
    static unsigned int debugDelay = 500;

    if (millis() - lastDebugTime > debugDelay) {
        Serial.print("Error: ");
        Serial.println(error);
        Serial.print("M1 speed: ");
        Serial.println(m1Speed);

        Serial.print("M2 speed: ");
        Serial.println(m2Speed);

        for (int i = 0; i < sensorCount; i++)
        {
            Serial.print(sensorValues[i]);
            Serial.print(" ");
        }

        Serial.println();

        lastDebugTime = millis();
    }
}