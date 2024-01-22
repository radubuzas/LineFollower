# Line Follower Documentation :robot:


<details>
<summary> 
Project Description :page_facing_up:
</summary>

## Project Description :page_facing_up:
Meet **Jerry**, the Line Follower robot with a great personality. Designed to follow dark lines, this robot combines coding with a great sense of adventure. **Jerry** possesses a brain (powered by a nano Arduino board), a heart (a trusty battery), and two legs (equipped with motors and wheels). Just like any dedicated racer, it takes a few moments to prepare before starting its line-following journey, after which it run the path with speed and precision.

</details>

<details>
<summary> 
Components :wrench:
</summary>

## Components :wrench:

### Non-electronic: :hammer:

- 1 ball caster
- Cardboard for the chassis
- 2 Wheels
- Bolts & nuts
- Zip ties (for keeping the components in place)


### Electronic:  :electric_plug:

- Arduino Nano
- Mini Breadboard
- Infrared (IR) Sensors for Line Detection
- 1 LiPo Battery for Power
- L293D motor driver
- 2 DC Motors
- Wires and Connectors

</details>

<details>
<summary> 
Design Description :pencil2:
</summary>

## Design Description :pencil2:

The main body was designed for a lightweight machine. The two motors with wheels are attached to the bottom of the body, while the Arduino, the breadboard and the battery are placed on top. The IR sensor is placed at the front of the car. This structure allows the cables and the connectors to be easyly organized. In the middle of the car is the a 3rd ball which is used for stability and smoothness of the movement.The Arduino board is programmed to receive the signals from the IR sensors and adjust the speed and direction of the motors accordingly. All these components are building **Jerry**, the line follower.

</details>

<details>
<summary> 
PID Controller :straight_ruler:
</summary>

## PID Controller :straight_ruler:
**Jerry** uses a PID (Proportional-Integral_Derivate) controller to adjust the speed of its motors. It is based on the error between the current position and the ideal position. The PID is calculted with the following constants:kp, ki and kd.
### 1. kp - proportional constant. 
It is used to adjust the speed of the motors based on the error. The higher the kp, the faster the robot will react to the error.
### 2. ki - integral constant.
It is used to adjust the speed of the motors based on the sum of the errors. The higher the ki, the faster the robot will react to the sum of the errors.
### 3. kd - derivative constant. 
This is used to adjust the speed of the motors based on the difference between the current error and the previous error. The higher the kd, the faster the robot will react to the difference between the current error and the previous error.
### 4. The PID is calculated as follows:

motorSpeed = kp * p + ki * i + kd * d;

Our initial values for the PID are:

kp = 5;
ki = 0;
kd = 120;
where p is the current error, i is the sum of the errors and d is the difference between the current error and the previous error.
</details>
<details>
<summary> 
Setup :wrench:
</summary>

## Setup :wrench:

![Jerry, the line follower](/Photos/frontJerry.jpg)

![Jerry, the real line follower](/Photos/upJerry.jpg)

![Jerry, the ultimate line follower](/Photos/hotJerry.jpg) 

</details>

<details>
<summary> 
Final Track :checkered_flag:
</summary>

## Final Track :checkered_flag:

![Final Track](/Photos/route.jpg)

</details>

<details>
<summary> 
Functionality :gear:
</summary>

## Functionality :gear:
 
### Line Following Algorithm :straight_ruler:

**"Jerry"** employs infrared (IR) sensors to detect and follow dark lines on a contrasting surface. The line-following algorithm ensures smooth navigation, allowing the robot to stay on course with precision.

### Speed Control :rabbit2:

The two motors with wheels provide motion control. The speed and direction of the motors are adjusted based on the input from the IR sensors, enabling the robot to maintain its path and follow the line at an optimal speed.

### Start-up Sequence :rocket:

Upon activation, **"Jerry"** fires up a great start-up sequence, preparing itself for the line-following adventure. This adds a touch of personality to the robot's behavior.

</details>

<details>
<summary> 
Best time 17.59 :stopwatch:
</summary>


Watch **Jerry** in action [here](https://youtu.be/8WgI_KXrATU).

</details>

<details>
<summary> 
Operation and Customization :computer:
</summary>

## Operation :computer:

1. **Power On:**
   - Turn on the robot by connecting the battery.

2. **Start-up Sequence:**
   - Observe the beautiful start-up sequence as **Jerry** prepares for its journey.

3. **Line Following:**
   - Place the robot on a surface with a visible dark line.
   - Admire **"Jerry"** follows the line with agility and precision.

4. **Speed Adjustment:**
   - The robot dynamically adjusts its speed based on the complexity of the line-following task.

## Customization :computer:

Feel free to customize **Jerry** by adjusting the line-following algorithm parameters, tweaking motor speeds, or even adding additional features to enhance its personality.
