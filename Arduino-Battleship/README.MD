Super Battleship
@[DLukeNelson](https://github.com/DLukeNelson)
@[AkashPatelUAlberta](https://github.com/AkashPatelUAlberta)

This is a remake of the classic board game Battleship, for play across two
serially connected Arduino boards. Done as a project for our intro level
programming course. Posted with permission.

Total Accessories:
* 2 Arduino Mega Board 2560
* 2 USB cable (Power source)
* 2 Adafruit LCD screens (LCD)
* 2 Joysticks
* 2 Piezo Buzzer
* 20 LED (10 Green and 10 Red)
* 2 RGB LED
* 28 560 Ohm Resistor
* 2 Pushbutton
* 75 Wires

Mutual Wiring Instructions:
LCD <--> Arduino BB
JS <--> Arduino BB (Pins away from board)
Arduino GND <--> Negative BUS
Arduino 5V <--> Positive BUS
LCD GND <--> Negative BUS
LCD VVC <--> Positive BUS
LCD Reset <--> Pin 8
LCD D/C <--> Pin 7
LCD CARD_CS <--> Pin 5
LCD TFT_CS <--> Pin 6
LCD MOSI <--> Pin 51
LCD SCK <--> Pin 52
LCD MISO <--> Pin 50
LCD LITE <--> Positive BUS
JS VCC <--> Positive BUS
JS VERT <--> Pin A0
JS HORZ <--> Pin A1
JS SEL <--> Pin 9
JS GND <--> Negative BUS
Negative Bus <--> Pushbutton <--> Pin 3
Negative Bus <--> Piezo Buzzer <--> Pin 2
[RGB LED lead labeled from flat side (closest to flat side = LED Lead 1,
 followed by 2, then 3, and 4 is farthest from flat edge)]
Pin 38 <--> Resistor <--> LED Lead 1
Pin 37 <--> Resistor <--> LED Lead 3
Pin 36 <--> Resistor <--> LED Lead 4
LED Lead 2 <--> Negative BUS
Negative BUS <(Resistor)> (flat side) LED Green (round side) <--> Pin 30
Negative BUS <(Resistor)> (flat side) LED Green (round side) <--> Pin 28
Negative BUS <(Resistor)> (flat side) LED Green (round side) <--> Pin 26
Negative BUS <(Resistor)> (flat side) LED Green (round side) <--> Pin 24
Negative BUS <(Resistor)> (flat side) LED Green (round side) <--> Pin 22
Negative BUS <(Resistor)> (flat side) LED Red (round side) <--> Pin 23
Negative BUS <(Resistor)> (flat side) LED Red (round side) <--> Pin 25
Negative BUS <(Resistor)> (flat side) LED Red (round side) <--> Pin 27
Negative BUS <(Resistor)> (flat side) LED Red (round side) <--> Pin 29
Negative BUS <(Resistor)> (flat side) LED Red (round side) <--> Pin 31
USB Cable <--> Arduino Board

Additional Wiring Instructions:
PLAYER 1: Pin 13 <(Resistor)> Positive BUS
PLAYER 2: Pin 13 <(Resistor)> GND
PLAYER 1 Pin TX3 14 <--> PLAYER 2 Pin RX3 15
PLAYER 2 Pin TX3 14 <--> PLAYER 1 Pin RX3 15
PLAYER 1 GND <--> PLAYER 2 GND
(Check all wiring with 'Wiring_Schematic.png')

Instructions for use: (From the ubuntu VM we used in class)
1 - Upload the contents from 'SDCARDFILES' onto a microSD card then insert it
		into the LCD screen.
2 - Run the contents of the file by typing "make upload" in the terminal, from
		the directory where it is located.
		(upload onto both Arduinos)
3 - Once title screen is displayed click Joystick to begin the game
4 - Each player has to place down all 5 of their ships, the pushbutton may be
		pressed to switch orientation between horizontal and vertical.
		Click down the joystick to place ships.
5 - Once all ships are placed on both Arduinos the 2 boards will connect.
6 - The players will take turns shooting the other player's boards trying to
		sink their ships.
7 - The first player to sink all of the opponent's ships is the winner.
8 - Once the game is over, user may hold down the Joystick to restart a new game.

Assumptions/Extra Info:
- This program allows the same location to be shot multiple times.
	This is intentional as in reality there is nothing to prevent someone from
	firing at a target they have already fired at before.
- This game is best played with 3 long wires used for connecting the 2 Arduinos
	as it allows for distance between the 2 boards, preventing the users from
	looking at each others boards.
- The 2 Arduinos will only connect if both Arduinos are running the code before
	either player completes placing ships. This is because the Serial line is
	cleared at the start of the program.
