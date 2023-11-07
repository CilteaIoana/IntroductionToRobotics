# Introduction to Robotics (2023 - 2024)

🤖🥁 Welcome to my exploration journey in robotics 🥁🤖

What you can find here:

📋 Homework Assignments 🖋: This repository will host a series of laboratory assignments received during the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each assignment will include the following features:

* Requirements: Detailed instructions on what is expected for each assignment.
* Files: Naming must respect the standard in the requirements.
* Implementation Details (if applicable): Specifics about how the assignment was implemented.
* Picture of the Setup: Visual representations of the project setup.
* Video: Demonstrations or descriptions (or more/less :) ) of the completed assignment.

🥳 Welcome once again, and let's have fun exploring together! 🥳

P.S. I'm happy to receive feedback or advice. 😁
<details>
  <summary><h2> 💥Homework 1: Controlling an RGB LED using individual potentiometers.💥</h2></summary>
  <strong>Technical Task:</strong> Use a separate potentiometer for controlling each color of the RGB LED:Red, Green, and Blue. This control must leverage digital electronics. Specifically, you need to read the potentiometer’s value with Arduino and then write a mapped value to the LED pins.  <br><br/>
  
  <strong>Components:</strong>
  * RGB LED (At least 1)
  * Potentiometers (At least 3)
  * Resistors and wires as needed <br><br/>

  <strong>Setup Picture:</strong>
![hm1](https://github.com/CilteaIoana/robo/assets/115061960/e8d25135-4c66-4c2c-82a2-9829795a449b)

  <strong>Task Showcase:</strong>
  https://www.youtube.com/watch?v=9MZqbJrcT3w&ab_channel=IoanaC.
  
</details>


<details>

<summary><h2>🛗Homework 2: Elevator simulator wannabe </h2></summary>
  <strong>Technical Task:</strong> 
 Design a control system that simulates a 3-floor elevator using the Arduino platform. Here are the specific requirements:<br><br/>
-> LED Indicators: Each of the 3 LEDs should represent one of the 3 floors. The LED corresponding to the current floor should light up. Additionally, another LED should represent the elevator’s operational state. It should blink when the elevator is moving and remain static when stationary.<br><br/>
-> Buttons: Implement 3 buttons that represent the call buttons from the 3 floors. When pressed, the elevator should simulate movement towards the floor after a short interval (2-3 seconds).
-> State Change & Timers: If the elevator is already at the desired floor, pressing the button for that floor should have no effect. Otherwise, after a button press, the elevator should ”wait for the doors to close” and then
”move” to the corresponding floor. If the elevator is in movement, it should either do nothing or it should stack its decision (get to the first programmed floor, open the doors, wait, close them and then go to the next desired floor).<br><br/>
-> Debounce: Remember to implement debounce for the buttons to avoid
unintentional repeated button presses.. <br><br/>

  
  <strong>Components:</strong>
* LEDs (At least 4: 3 for the floors and 1 for the elevator’s operational state)
* Buttons (At least 3 for floor calls)
* Resistors and wires as needed

  <strong>Setup Picture:</strong>
  ![Homework_2](https://github.com/CilteaIoana/robo/assets/115061960/952adde8-da08-45a2-914d-1056cd4100af)

  <strong>Task Showcase:</strong>
  https://www.youtube.com/watch?v=TYBvZ8O9zY4&ab_channel=IoanaC.
  </details>


  <details>

<summary><h2>🛗Homework 3: 7 segment display drawing </h2></summary><br><br/>
  <strong>Summary:</strong> 
 The task involves using a joystick to control the position of a segment and "draw" on a display. The segment's movement should be natural, meaning it can only jump to neighboring positions without passing through obstacles.  <br><br/>
 The initial position must be on the decimal point (DP), and the current position blinks continuously. Using the joystick allows you to move to neighboring positions, and short pressing the button toggles the segment's state from ON to OFF or vice versa.  <br><br/>
 Long pressing the button resets the entire display by turning off all segments and moving the current position back to the decimal point. <br><br/>
  
  <strong>Components:</strong>
* 1 7-segment display
* 1 joystick
* resistors and wires (per logic)

  <strong>Setup Picture:</strong>
![Homework_3](https://github.com/CilteaIoana/IntroductionToRobotics/assets/115061960/b227829b-e34c-44ac-89c1-94128d204988)


  <strong>Task Showcase:</strong>
 https://www.youtube.com/shorts/QK71D3ZvcvM
  </details>
