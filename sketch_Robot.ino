
// Global Variables

//motor_A
int IN1 = 2 ;
int IN2 = 3 ;
int velocidadeA = 1;
 
//motor_B
int IN3 = 5 ;
int IN4 = 6 ;
int velocidadeB = 4;
//Button byte

const byte BUTTON_NONE = 0;
const byte BUTTON_LEFT = 1;
const byte BUTTON_UP = 2;
const byte BUTTON_RIGHT = 3;
const byte BUTTON_DOWN = 4;
const byte BUTTON_MIDDLE = 5;

//Button Analog A0
const byte keypadPin = A0;
// Key byte
byte key = 0;
// Array commands
int commands[20]; 

void setup() 
{
  Serial.begin(9600); 
  while (!Serial){;}
  Serial.println(F("Start\n"));
  pinMode(keypadPin, INPUT_PULLUP); // Set keypadPins for input_pullup
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(velocidadeA,OUTPUT);
  pinMode(velocidadeB,OUTPUT);
 }

void loop()
{
    iniCommands(); // remove commands from the array
  
  	addCommands(); // add commands to the array
  
  	executeCommands(); // follow orders
  	Serial.println("Done...");
    delay(1000);
} 
// Clear array from next assignment
void iniCommands() {
  for (int i = 0; i < 20; i++) {
    commands[i] = -1;
  }
}
// Add commands in array from max 20 commands
void addCommands() {
  // read the buttons state
  for (int i = 0; i < 20;) { //max 20 commands
    int key = getKey();
    if (key == BUTTON_MIDDLE) { // if button middle press
      break;
    } else if (key == BUTTON_NONE) { //if no button is pressed
      continue;
    }
    commands[i] = key; // save the button to the array
    delay(1000);
    i++;
  }
}
// execute array commands 20
void executeCommands() {
  // print status to the screen
  Serial.println("Excuting...");

  // read through the array and move accordingly
  for (int i = 0; i < 20; i++) {
    switch (commands[i]) {
      case BUTTON_LEFT:
        Serial.println("Button Left");
        break;
      case BUTTON_RIGHT:
        Serial.println("Button Right");
        break;
      case BUTTON_UP:
        Serial.println("Button Up");
        break;
      case BUTTON_DOWN:
        Serial.println("Button Down");
        break;
      case BUTTON_NONE:
        return;
    }
    // print the current command to the screen
    delay(100);

  }
  
}
/*
Key Values
BUTTON_LEFT / First button = 15
BUTTON_UP / Second button = 72
BUTTON_DOWN / Third = 124
BUTTON_RIGHT / Forth = 170
BUTTON_MIDDLE / Fifth = 212
BUTTON_NONE = 1021
*/
//Get values buttons from analogRead and return in byte
byte getKey()
{
    int val = 0;
    byte button = 0;
    val = analogRead(keypadPin); // read analogPins A0
    button = BUTTON_NONE; // set none
    if ((val >= 40) && (val <= 45)) { button = BUTTON_RIGHT; }
    else if ((val >= 52) && (val <=92)) { button = BUTTON_UP; }
    else if ((val >= 104) && (val <= 144)) { button = BUTTON_DOWN; }   
    else if ((val >= 150) && (val <= 190)) { button = BUTTON_LEFT; } 
    else if ((val >= 0) && (val <=35)){ button = BUTTON_MIDDLE; } 
    return button; 
}  
