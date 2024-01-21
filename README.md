# Line Follower Documentation :robot:


<details>
<summary> 
Project Description
</summary>

## Project Description
Meet **Jerry**, the Line Follower robot with a great personality. Designed to follow dark lines, this robot combines coding with a great sense of adventure. **Jerry** possesses a brain (powered by a nano Arduino board), a heart (a trusty battery), and two legs (equipped with motors and wheels). Just like any dedicated racer, it takes a few moments to prepare before starting its line-following journey, after which it run the path with speed and precision.

</details>

<details>
<summary> 
Components
</summary>

## Components

### Non-electronic:

- 1 ball caster
- Cardboard for the chassis
- 2 Wheels
- Bolts & nuts
- Zip ties (for keeping the components in place)


### Electronic:

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
Design Description
</summary>

## Design Description

The main body was designed for a lightweight machine. The two motors with wheels are attached to the bottom of the body, while the Arduino, the breadboard and the battery are placed on top. The IR sensor is placed at the front of the car. This structure allows the cables and the connectors to be easyly organized. At the end of the car is the a 3rd ball which is used for stability and smoothness of the movement.The Arduino board is programmed to receive the signals from the IR sensors and adjust the speed and direction of the motors accordingly. All these components are building **Jerry**, the line follower.

</details>


<details>
<summary> 
Setup
</summary>

## Setup

![Jerry, the line follower](Jerry.webp)

</details>

<details>
<summary> 
Functionality
</summary>

## Functionality

### Line Following Algorithm

**"Jerry"** employs infrared (IR) sensors to detect and follow dark lines on a contrasting surface. The line-following algorithm ensures smooth navigation, allowing the robot to stay on course with precision.

### Speed Control

The two motors with wheels provide motion control. The speed and direction of the motors are adjusted based on the input from the IR sensors, enabling the robot to maintain its path and follow the line at an optimal speed.

### Start-up Sequence

Upon activation, **"Jerry"** undergoes a brief start-up sequence, preparing itself for the line-following adventure. This adds a touch of personality to the robot's behavior.

</details>

<details>
<summary> 
Operation and Customization
</summary>

## Operation

1. **Power On:**
   - Turn on the robot by connecting the battery.

2. **Start-up Sequence:**
   - Observe the beautiful start-up sequence as **Jerry** prepares for its journey.

3. **Line Following:**
   - Place the robot on a surface with a visible dark line.
   - Admire **"Jerry"** follows the line with agility and precision.

4. **Speed Adjustment:**
   - The robot dynamically adjusts its speed based on the complexity of the line-following task.

## Customization

Feel free to customize **Jerry** by adjusting the line-following algorithm parameters, tweaking motor speeds, or even adding additional features to enhance its personality.
