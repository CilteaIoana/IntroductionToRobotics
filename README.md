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
 ![Homework_1](https://github.com/CilteaIoana/IntroductionToRobotics/assets/115061960/e3c95c93-4003-4204-866c-65283cf11b56)

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
![Homework_2](https://github.com/CilteaIoana/IntroductionToRobotics/assets/115061960/a7c8601c-b7da-43ee-97cd-8969e4bdb5f2)


  <strong>Task Showcase:</strong>
  https://www.youtube.com/watch?v=TYBvZ8O9zY4&ab_channel=IoanaC.
  </details>


  <details>

<summary><h2>🕹️Homework 3: 7 segment display drawing </h2></summary>
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

  <details>

<summary><h2>🕹️Homework 4: Stopwatch Timer </h2></summary>
  <strong>Summary:</strong> 
 The project involves creating a stopwatch timer using a 4-digit 7-segment display and three buttons.
 The timer counts in tenths of a second and includes a lap-saving feature akin to basic phone stopwatch functions. <br><br/>

The initial display value is "000.0," and the buttons have specific functions:

Button 1: Starts or pauses the timer.<br><br/>
Button 2: Resets (if in pause mode) and resets saved laps (if in lap viewing mode).<br><br/>
Button 3: Saves laps (if in counting mode) and cycles through the last four saved laps.<br><br/>

<strong>The workflow includes:</strong> 

The display shows "000.0." Pressing the Start button initiates the timer.
During the timer, pressing the lap button saves the timer's value in memory (up to 4 laps). The 5th press overrides the 1st saved lap. Resetting during the timer or pressing pause has specific outcomes.
In Pause Mode, the lap button is inactive. Pressing reset sets the display to "000.0."
After a reset, pressing the lap button cycles through saved laps. Continuous pressing cycles through laps continuously. Resetting in this state clears all flags and sets the timer to "000.0."

<strong>Key considerations:</strong> 

-> Ensure a dot separates seconds from tenths of a second.
-> Display all digits; for instance, "20.4" seconds should display as "020.4." <br><br/>
  
  <strong>Components:</strong>
* 1 4-digit 7-segment display
* 3 buttons
* resistors and wires (per logic)
  
  <strong>Setup Picture:</strong>
![Homework_4](https://github.com/CilteaIoana/IntroductionToRobotics/assets/115061960/7ba225b7-830e-419f-b632-7a69d0e67c46)



  <strong>Task Showcase:</strong>
  https://www.youtube.com/watch?v=QGhUVrdu3Q8&ab_channel=IoanaC.
  </details>
