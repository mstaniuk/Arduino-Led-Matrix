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

void setOutputLine(uint8_t colors[5]) {
  for(uint8_t i = 0; i < 8; i++) {
    if( i > 4) {
      // Set red bit on outputs red byte from 
      bitWrite(line, 7 - i, !bitRead(colors[i], 0));
      // set green
      bitWrite(line, 7 - i + 8, !bitRead(colors[i], 1));
      // set blue
      bitWrite(line, 7 - i+16, !bitRead(colors[i], 2));
    } else {
      // Set unused pins of Shift register
      bitWrite(line, 7 - i, 0);
      bitWrite(line, 7 - i + 8, 0);
      bitWrite(line, 7 - i+16, 0);
    }
  }
}

void setScreen(uint8_t screen[5][5]) {
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

byte NUM_0[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	RED,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	RED,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	RED,	RED},
{	RED,	RED,	RED,	RED,	RED}
};
byte NUM_1[5][5] = 
{
{	RED,	RED,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED}
};
byte NUM_2[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED}
};
byte NUM_3[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED}
};
byte NUM_4[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED}
};
byte NUM_5[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED}
};
byte NUM_6[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED}
};
byte NUM_7[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED}
};
byte NUM_8[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED}
};
byte NUM_9[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED}
};

byte CHAR_SPACE[5][5] = 
{
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK}
};

byte CHAR_DOT[5][5] = 
{
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK}
};
byte CHAR_A[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED}
};
byte CHAR_B[5][5] = 
{
{	RED,	RED,	RED,	RED,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	BLACK}
};
byte CHAR_C[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED}
};
byte CHAR_D[5][5] = 
{
{	RED,	RED,	RED,	RED,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	BLACK}
};
byte CHAR_E[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED}
};
byte CHAR_F[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK}
};
byte CHAR_G[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	BLACK,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED}
};
byte CHAR_H[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED}
};
byte CHAR_I[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED}
};
byte CHAR_J[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	RED,	RED,	RED,	RED}
};
byte CHAR_K[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK}
};
byte CHAR_L[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED}
};
byte CHAR_M[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	BLACK,	RED,	RED},
{	RED,	BLACK,	RED,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED}
};
byte CHAR_N[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	RED,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED}
};
byte CHAR_O[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED}
};
byte CHAR_P[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK}
};
byte CHAR_Q[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	RED,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK}
};
byte CHAR_R[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	RED,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	RED}
};
byte CHAR_S[5][5] = 
{
{	BLACK,	RED,	RED,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	RED,	RED,	RED,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	BLACK}
};
byte CHAR_T[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK}
};
byte CHAR_U[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	RED,	RED,	RED,	RED}
};
byte CHAR_V[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	RED,	BLACK,	RED,	BLACK},
{	BLACK,	BLACK,	BLACK,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK}
};
byte CHAR_W[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	RED,	BLACK,	RED,	BLACK,	RED},
{	RED,	RED,	BLACK,	RED,	RED},
{	RED,	BLACK,	BLACK,	BLACK,	RED}
};
byte CHAR_X[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	RED,	BLACK,	RED,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	RED,	BLACK,	RED,	BLACK},
{	RED,	BLACK,	BLACK,	BLACK,	RED}
};
byte CHAR_Y[5][5] = 
{
{	RED,	BLACK,	BLACK,	BLACK,	RED},
{	BLACK,	RED,	BLACK,	RED,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK}
};
byte CHAR_Z[5][5] = 
{
{	RED,	RED,	RED,	RED,	RED},
{	BLACK,	BLACK,	BLACK,	RED,	BLACK},
{	BLACK,	BLACK,	RED,	BLACK,	BLACK},
{	RED,	RED,	BLACK,	BLACK,	BLACK},
{	RED,	RED,	RED,	RED,	RED}
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
    }
    setScreen(CHAR_SPACE);
    setScreen(CHAR_DOT);
    
    setScreen(NUM_0);
    setScreen(NUM_1);
    setScreen(NUM_2);
    setScreen(NUM_3);
    setScreen(NUM_4);
    setScreen(NUM_5);
    setScreen(NUM_6);
    setScreen(NUM_7);
    setScreen(NUM_8);
    setScreen(NUM_9);
    
    setScreen(CHAR_A);
    setScreen(CHAR_B);
    setScreen(CHAR_C);
    setScreen(CHAR_D);
    setScreen(CHAR_E);
    setScreen(CHAR_F);
    setScreen(CHAR_G);
    setScreen(CHAR_H);
    setScreen(CHAR_I);
    setScreen(CHAR_J);
    setScreen(CHAR_K);
    setScreen(CHAR_K);
    setScreen(CHAR_M);
    setScreen(CHAR_N);
    setScreen(CHAR_O);
    setScreen(CHAR_P);
    setScreen(CHAR_Q);
    setScreen(CHAR_R);
    setScreen(CHAR_S);
    setScreen(CHAR_T);
    setScreen(CHAR_U);
    setScreen(CHAR_V);
    setScreen(CHAR_W);
    setScreen(CHAR_X);
    setScreen(CHAR_Y);
    setScreen(CHAR_Z);
  }


