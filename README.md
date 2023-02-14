# Embedded Systems - Project
The project has been made as a part of Embedded Systems course for Military University of Technology

# Description
* System U1

After loading the program, the microprocessor simulates the operation of a telephone - after entering the 9 digits and pressing the * button, a 
simulated call will start using the diode (there will be 4 longer diode flashes, which symbolise a call signal, and then there will be a "disconnection" in 
the form of 2 fast diode flashes). In addition, if someone considers that he/she has made a mistake while entering a telephone number, using the # button, 
he/she can clear the previously entered telephone number - this will be signalled by a short double flash of the diode. The program also detects if the phone 
number has been entered too long or too short and, after pressing *, two cycles of short flashes of the diode will occur to symbolise the error. 
In addition, when a numbered key is pressed, the diode indicates which key was pressed by lighting up as many times as the number on the key. 
The duration of the flashes is arbitrary, but the flashes symbolising a signal should be longer than the flashes of the diode symbolising disconnection, reset or errors.

* System U3

The program, when loaded, causes the microprocessor to count down using a 7 segment display from 10 to 0 and then display the word "HI". 
When the button is pressed, using an interrupt, the countdown is reset, and once the writing is displayed, it should continue to be displayed until the button is pressed.

* System U8

The programme, when loaded, causes the microprocessor to display a 'Loading Screen' on the LCD, which shows the loading animation and, when 100% is reached, 
will display a caption and animation with the robot.

* System U5

The programme plays the role of a "blank programme".
