// Define connection pins
const uint8_t DATA                = 10;
const uint8_t LATCH               = 9;
const uint8_t CLOCK               = 8;

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


int stage = 0;
int substage = 0;


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

void setOutputLine(byte colors[5]) {
  for(uint8_t i = 0; i < 8; i++) {
    if( i <= 4) {
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

void setScreen(byte screen[5][5]) {
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
void sendBit(byte aData)
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

byte NUM_0[5][5]={{RED,RED,RED,RED,RED},{RED,RED,BLACK,BLACK,RED},{RED,BLACK,RED,BLACK,RED},{RED,BLACK,BLACK,RED,RED},{RED,RED,RED,RED,RED}};
byte NUM_1[5][5]={{RED,RED,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{RED,RED,RED,RED,RED}};
byte NUM_2[5][5]={{RED,RED,RED,RED,RED},{BLACK,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{RED,RED,RED,RED,RED}};
byte NUM_3[5][5]={{RED,RED,RED,RED,RED},{BLACK,BLACK,BLACK,BLACK,RED},{BLACK,RED,RED,RED,RED},{BLACK,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED}};
byte NUM_4[5][5]={{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED},{BLACK,BLACK,BLACK,BLACK,RED},{BLACK,BLACK,BLACK,BLACK,RED}};
byte NUM_5[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{RED,RED,RED,RED,RED},{BLACK,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED}};
byte NUM_6[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED}};
byte NUM_7[5][5]={{RED,RED,RED,RED,RED},{BLACK,BLACK,BLACK,BLACK,RED},{BLACK,BLACK,BLACK,BLACK,RED},{BLACK,BLACK,BLACK,BLACK,RED},{BLACK,BLACK,BLACK,BLACK,RED}};
byte NUM_8[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED}};
byte NUM_9[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED},{BLACK,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED}};
byte CHAR_SPACE[5][5]={{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK}};
byte CHAR_DOT[5][5]={{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK}};
byte CHAR_A[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED}};
byte CHAR_B[5][5]={{RED,RED,RED,RED,BLACK},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,BLACK},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,BLACK}};
byte CHAR_C[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{RED,BLACK,BLACK,BLACK,BLACK},{RED,BLACK,BLACK,BLACK,BLACK},{RED,RED,RED,RED,RED}};
byte CHAR_D[5][5]={{RED,RED,RED,RED,BLACK},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,BLACK}};
byte CHAR_E[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{RED,RED,RED,RED,BLACK},{RED,BLACK,BLACK,BLACK,BLACK},{RED,RED,RED,RED,RED}};
byte CHAR_F[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{RED,RED,RED,RED,BLACK},{RED,BLACK,BLACK,BLACK,BLACK},{RED,BLACK,BLACK,BLACK,BLACK}};
byte CHAR_G[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{RED,BLACK,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED}};
byte CHAR_H[5][5]={{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED}};
byte CHAR_I[5][5]={{RED,RED,RED,RED,RED},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{RED,RED,RED,RED,RED}};
byte CHAR_J[5][5]={{RED,RED,RED,RED,RED},{BLACK,BLACK,BLACK,BLACK,RED},{BLACK,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{BLACK,RED,RED,RED,RED}};
byte CHAR_K[5][5]={{RED,BLACK,BLACK,RED,RED},{RED,BLACK,RED,BLACK,BLACK},{RED,RED,BLACK,BLACK,BLACK},{RED,BLACK,RED,BLACK,BLACK},{RED,BLACK,BLACK,RED,RED}};
byte CHAR_L[5][5]={{RED,BLACK,BLACK,BLACK,BLACK},{RED,BLACK,BLACK,BLACK,BLACK},{RED,BLACK,BLACK,BLACK,BLACK},{RED,BLACK,BLACK,BLACK,BLACK},{RED,RED,RED,RED,RED}};
byte CHAR_M[5][5]={{RED,BLACK,BLACK,BLACK,RED},{RED,RED,BLACK,RED,RED},{RED,BLACK,RED,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED}};
byte CHAR_N[5][5]={{RED,BLACK,BLACK,BLACK,RED},{RED,RED,BLACK,BLACK,RED},{RED,BLACK,RED,BLACK,RED},{RED,BLACK,BLACK,RED,RED},{RED,BLACK,BLACK,BLACK,RED}};
byte CHAR_O[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED}};
byte CHAR_P[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{RED,BLACK,BLACK,BLACK,BLACK}};
byte CHAR_Q[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,RED,BLACK,RED},{RED,RED,RED,RED,RED},{BLACK,BLACK,RED,BLACK,BLACK}};
byte CHAR_R[5][5]={{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED},{RED,BLACK,BLACK,RED,BLACK},{RED,BLACK,BLACK,BLACK,RED}};
byte CHAR_S[5][5]={{BLACK,RED,RED,RED,RED},{RED,BLACK,BLACK,BLACK,BLACK},{BLACK,RED,RED,RED,BLACK},{BLACK,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,BLACK}};
byte CHAR_T[5][5]={{RED,RED,RED,RED,RED},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK}};
byte CHAR_U[5][5]={{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,RED,RED,RED,RED}};
byte CHAR_V[5][5]={{RED,BLACK,BLACK,BLACK,RED},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,RED,BLACK,RED,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK}};
byte CHAR_W[5][5]={{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,BLACK,BLACK,RED},{RED,BLACK,RED,BLACK,RED},{RED,RED,BLACK,RED,RED},{RED,BLACK,BLACK,BLACK,RED}};
byte CHAR_X[5][5]={{RED,BLACK,BLACK,BLACK,RED},{BLACK,RED,BLACK,RED,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,RED,BLACK,RED,BLACK},{RED,BLACK,BLACK,BLACK,RED}};
byte CHAR_Y[5][5]={{RED,BLACK,BLACK,BLACK,RED},{BLACK,RED,BLACK,RED,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK}};
byte CHAR_Z[5][5]={{RED,RED,RED,RED,RED},{BLACK,BLACK,BLACK,RED,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{RED,RED,BLACK,BLACK,BLACK},{RED,RED,RED,RED,RED}};
byte CHAR_COLON[5][5]={{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK},{BLACK,BLACK,RED,BLACK,BLACK},{BLACK,BLACK,BLACK,BLACK,BLACK}};

void setChar(byte target[5][5], char character) {
  switch(character) {
    case ' ': memcpy(target, CHAR_SPACE, sizeof(CHAR_SPACE)); break;
    case ':': memcpy(target, CHAR_COLON, sizeof(CHAR_COLON)); break;
    case '0': memcpy(target, NUM_0, sizeof(NUM_0)); break;
    case '1': memcpy(target, NUM_1, sizeof(NUM_1)); break;
    case '2': memcpy(target, NUM_2, sizeof(NUM_2)); break;
    case '3': memcpy(target, NUM_3, sizeof(NUM_3)); break;
    case '4': memcpy(target, NUM_4, sizeof(NUM_4)); break;
    case '5': memcpy(target, NUM_5, sizeof(NUM_5)); break;
    case '6': memcpy(target, NUM_6, sizeof(NUM_6)); break;
    case '7': memcpy(target, NUM_7, sizeof(NUM_7)); break;
    case '8': memcpy(target, NUM_8, sizeof(NUM_8)); break;
    case '9': memcpy(target, NUM_9, sizeof(NUM_9)); break;
    case 'a': case 'A': memcpy(target, CHAR_A, sizeof(CHAR_A)); break;
    case 'b': case 'B': memcpy(target, CHAR_B, sizeof(CHAR_B)); break;
    case 'c': case 'C': memcpy(target, CHAR_C, sizeof(CHAR_C)); break;
    case 'd': case 'D': memcpy(target, CHAR_D, sizeof(CHAR_D)); break;
    case 'e': case 'E': memcpy(target, CHAR_E, sizeof(CHAR_E)); break;
    case 'f': case 'F': memcpy(target, CHAR_F, sizeof(CHAR_F)); break;
    case 'g': case 'G': memcpy(target, CHAR_G, sizeof(CHAR_G)); break;
    case 'h': case 'H': memcpy(target, CHAR_H, sizeof(CHAR_H)); break;
    case 'i': case 'I': memcpy(target, CHAR_I, sizeof(CHAR_I)); break;
    case 'j': case 'J': memcpy(target, CHAR_J, sizeof(CHAR_J)); break;
    case 'k': case 'K': memcpy(target, CHAR_K, sizeof(CHAR_K)); break;
    case 'l': case 'L': memcpy(target, CHAR_L, sizeof(CHAR_L)); break;
    case 'm': case 'M': memcpy(target, CHAR_M, sizeof(CHAR_M)); break;
    case 'n': case 'N': memcpy(target, CHAR_N, sizeof(CHAR_N)); break;
    case 'o': case 'O': memcpy(target, CHAR_O, sizeof(CHAR_O)); break;
    case 'p': case 'P': memcpy(target, CHAR_P, sizeof(CHAR_P)); break;
    case 'q': case 'Q': memcpy(target, CHAR_Q, sizeof(CHAR_Q)); break;
    case 'r': case 'R': memcpy(target, CHAR_R, sizeof(CHAR_R)); break;
    case 's': case 'S': memcpy(target, CHAR_S, sizeof(CHAR_S)); break;
    case 't': case 'T': memcpy(target, CHAR_T, sizeof(CHAR_T)); break;
    case 'u': case 'U': memcpy(target, CHAR_U, sizeof(CHAR_U)); break;
    case 'v': case 'V': memcpy(target, CHAR_V, sizeof(CHAR_V)); break;
    case 'w': case 'W': memcpy(target, CHAR_W, sizeof(CHAR_W)); break;
    case 'x': case 'X': memcpy(target, CHAR_X, sizeof(CHAR_X)); break;
    case 'y': case 'Y': memcpy(target, CHAR_Y, sizeof(CHAR_Y)); break;
    case 'z' : case 'Z' : memcpy(target, CHAR_Z, sizeof(CHAR_Z)); break;
    default: memcpy(target, CHAR_DOT, sizeof(CHAR_DOT));
  }
}

void writeText(String text) {
  if(millis() - lastTime > 200) {
    
    lastTime = millis();
    
    if(stage >= text.length()) {
      stage = 0;
    } else {
      stage += 1;
    }
  }
  
  char character = text.charAt(stage);
  byte charMatrix[5][5];
  setChar(charMatrix, character);
  
  setScreen(charMatrix);
}

void slideText(String text) {
  slideText(text, 0);
}

void slideText(String text, byte space) {
  int slideTime = 750;
  if(millis() - lastTime > slideTime) {
    
    lastTime = millis();
    substage = 0;
    
    if(stage >= text.length()-1) {
      stage = 0;
    } else {
      stage += 1;
    }
  } else if ((millis() - lastTime) / (slideTime / (5 + space)) > substage) {
    substage += 1;
  }
  
  char character = text.charAt(stage);
  char nextCharacter = text.charAt(stage+1);
  char i = 0;
  char j = 0;
  char k = 0;
  byte charMatrix[5][5];
  byte nextCharMatrix[5][5];
  byte finalCharMatrix[5][5];
  
  setChar(charMatrix, character);
  if(stage == text.length()-1) {
    setChar(nextCharMatrix, ' ');
  } else {
    setChar(nextCharMatrix, nextCharacter);
  }

  for(; i<5; i++) {
      byte newRow[5] = {0, 0, 0, 0, 0};
      memcpy(newRow, charMatrix[i] + min(max(0, substage),5) * sizeof(byte), sizeof(newRow) - min(max(0, substage),5) * sizeof(byte));
      memcpy(newRow + (5 - min(max(0, substage - space),5)) * sizeof(byte), nextCharMatrix[i], min(max(0, substage - space),5) * sizeof(byte));

      memmove(finalCharMatrix[i], newRow, sizeof(newRow));
  }
  
  setScreen(finalCharMatrix);
}

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
  slideText(" Quick brown fox jumped over the lazy dog ", 3);
}



