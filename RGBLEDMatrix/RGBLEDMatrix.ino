// Define connection pins
const uint8_t DATA                = 10;
const uint8_t LATCH               = 9;
const uint8_t CLOCK               = 8;

// Define time variable
long mTime                        = 0;

//// Colors:
// Color:
// B | 0 | 0 | 0 | 0 | 0 | b | g | r |
//
// 0 - not used
// r - red bit
// g - green bit
// b - blue bit
const uint8_t BLACK     = B00000000;
const uint8_t RED       = B00000001;
const uint8_t GREEN     = B00000010;
const uint8_t BLUE      = B00000100;
const uint8_t YELLOW    = B00000011;
const uint8_t MAGENTA   = B00000101;
const uint8_t CYAN      = B00000011;
const uint8_t WHITE     = B00000111;

// Timing
long lastTime = 0;

// TODO: Change global stage to funciton that hangle any size animation
int stage = 0;

// global variable for one row of colors
unsigned long line = 0;

/*
Line:

 | POWER  |  BLUE  | GREEN  |   RED  |
B|00000000|00000000|00000000|00000000|

POWER:
  ACTIVE - 1
  
RED,
GREEN,
BLUE
  ACTIVE - 0
  
EXAMPLES
OFF STATE:
  B|11111111|11111111|11111111|11111111|
  OR
  B|00000000|XXXXXXXX|XXXXXXXX|XXXXXXXX|
  
ALL WHITE:
  B|11111111|00000000|00000000|00000000|
  
ALL RED:
  B|11111111|11111111|11111111|00000000|
  .
  .
  .
*/

void setOutputLine(uint8_t colors[8]) {
  for(uint8_t i = 0; i < 8; i++) {
    
    // Set red bit on outputs red byte from 
    bitWrite(line, i, !bitRead(colors[i], 0));
    
    // set green
    bitWrite(line, i+8, !bitRead(colors[i], 1));
    
    // set blue
    bitWrite(line, i+16, !bitRead(colors[i], 2));
  }
}

void setScreen(uint8_t screen[5][8]) {
  for(byte j = 0; j < 5; j++) {
    // reset line
    line = 0;
    
    // Since any other power bit is 0 set only proper to 1
    bitWrite(line, 31-j, 1);
    
    // Set colors for line
    setOutputLine(screen[j]);
    byte i = 32;
    while(true){
      i = i - 1;
      sendBit(bitRead(line, i) == 1 ? HIGH : LOW);   
      if(i == 0) break;
    };
    
    // Throw line on display
    sendData();
  }
}

// Send bit to 74hc595s memory
void sendBit(uint8_t aData)
{
  digitalWrite(DATA,  aData);  
  digitalWrite(CLOCK, HIGH);
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA,  LOW);  
}

// Latch 74hc595
void sendData() {
  digitalWrite(LATCH, LOW);
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
}

// My device is 5x5 so last 3 bytes are unused


// TEMP: Test screens
uint8_t screen_different[5][8] = 
{
{BLACK, BLACK, BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA},
{BLACK, BLACK, BLACK, CYAN, RED, GREEN, BLUE, YELLOW},
{BLACK, BLACK, BLACK, BLUE, YELLOW, MAGENTA, CYAN, RED},
{BLACK, BLACK, BLACK, YELLOW, MAGENTA, CYAN, RED, BLUE},
{BLACK, BLACK, BLACK, MAGENTA, CYAN, RED, YELLOW, MAGENTA},
};

uint8_t screen_smile[5][8] = 
{
{BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
{BLACK, BLACK, BLACK, BLACK, RED, BLACK, RED, BLACK},
{BLACK, BLACK, BLACK, BLUE, BLACK, BLACK, BLACK, RED},
{BLACK, BLACK, BLACK, BLACK, MAGENTA, BLACK, RED, BLACK},
{BLACK, BLACK, BLACK, BLACK, BLACK, RED, BLACK, BLACK},
};

uint8_t screen_heart[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK, RED},
  {BLACK, BLACK, BLACK, RED,   BLACK, BLACK, BLACK, RED},
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};

// Screens of animated heart
uint8_t screen_heart_fill1[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
};

uint8_t screen_heart_fill2[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
};

uint8_t screen_heart_fill3[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
};

uint8_t screen_heart_fill4[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};

uint8_t screen_heart_fill5[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};

uint8_t screen_heart_fill6[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, BLUE,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, BLUE,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};

uint8_t screen_heart_fill7[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, RED,   BLUE,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, BLUE,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};


uint8_t screen_heart_fill8[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLUE,   BLACK},
  {BLACK, BLACK, BLACK, RED,   RED,   BLUE,   RED,   RED},
  {BLACK, BLACK, BLACK, RED,   BLUE,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};

uint8_t screen_heart_fill9[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   BLUE,   RED},
  {BLACK, BLACK, BLACK, RED,   RED,   BLUE,   RED,   RED},
  {BLACK, BLACK, BLACK, BLACK, BLUE,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};

uint8_t screen_heart_fill10[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   BLUE},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   BLUE,   RED},
  {BLACK, BLACK, BLACK, BLACK, RED,   BLUE,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};

uint8_t screen_heart_fill11[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   BLUE},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   BLUE,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, BLUE,   BLACK, BLACK},
};

uint8_t screen_heart_fill12[5][8] = 
{
  {BLACK, BLACK, BLACK, BLACK, RED,   BLACK, RED,   BLACK},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, RED,   RED,   RED,   RED,   RED},
  {BLACK, BLACK, BLACK, BLACK, RED,   RED,   RED,   BLACK},
  {BLACK, BLACK, BLACK, BLACK, BLACK, RED,   BLACK, BLACK},
};

void setup() 
{
  //TEMP: Debug
  Serial.begin(9600);
  
  // Setup arduino - 74hc595 connection
  // Reset and write enable are hard soldered to + and - on device level
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  
  // 74hc595 setup
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(DATA, LOW);
  sendData();
  
  // init timing
  lastTime = millis();
}

void loop() 
{  
  // TODO Change stage/step based animation to proper animation handling function
    if(millis() - lastTime > 100) {
      lastTime = millis();
      stage = 1 + stage;
      if(stage > 11) stage = 11;
    }
    
    switch(stage) {
      case 0:
        setScreen(screen_heart_fill1);
        break;
      case 1:
        setScreen(screen_heart_fill2);
        break;
      case 2:
        setScreen(screen_heart_fill3);
        break;
      case 3:
        setScreen(screen_heart_fill4);
        break;
      case 4:
        setScreen(screen_heart_fill5);
        break;
      case 5:
        setScreen(screen_heart_fill6);
        break;
      case 6:
        setScreen(screen_heart_fill7);
        break;
      case 7:
        setScreen(screen_heart_fill8);
        break;
      case 8:
        setScreen(screen_heart_fill9);
        break;
      case 9:
        setScreen(screen_heart_fill10);
        break;
      case 10:
        setScreen(screen_heart_fill11);
        break;
      case 11:
        setScreen(screen_heart_fill12);
        break;
    }    
}


