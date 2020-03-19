#include <Arduboy2.h>
#include "src/fonts/Font3x5.h"
#include "FlashStringHelper.h"
#include "strings.h"

#define numOfKlingon(q) (q & 0b01100000)>>5
#define numOfBase(q)    (q & 0b00010000)>>4
#define numOfStar(q)    (q & 0b00001111)
#define rfsp(id)        (readFlashStringPointer(&string[ id ]))

#define SPEED 10
/*
galaxy[x,y]=0b00000000;
              || ||
              || |Star(0-8(max 15))
              || base(0-1)
              |klingon(0-3)
              known(0-1)
*/
Arduboy2Base arduboy;
Font3x5 font3x5 = Font3x5();


//struct
struct point {
  byte x;
  byte y;
};

struct ship {
  point sector;
  int energy;
  int torpedo;
};

struct player {
  point quadrant;
  point sector;
  int energy;
  int shield;
  int torpedo;
};

// globals
byte quadrant[8][8] = {};
byte sector[8][8] = {};
byte totalKlingon = 25, totalBase = 3;
byte gcurs=0, gKlingon=0;
int days=250;
bool gdock = false;
int gloop=0;
int damage[8]={0,0,0,0,0,0,0,0};

bool resupplyOnlyOnce = false;
bool existBlackhole = false;
bool sBlackhole = false;
bool jamming = false;
bool sectorJamming = false;
bool asteroid = false;

ship klingon[3];
point base;
player enterprise;

point blackhole;

//class
class SlowPrinter {
private:
  bool quick = false;

  void checkDelay() {
    if(!quick) {
      delay(100);
      arduboy.pollButtons();
      if (arduboy.justPressed(A_BUTTON)) {
        quick = true;
      }
    }
  }

public:
  void slowPrint(FlashStringHelper message) {
    const char * pointer = reinterpret_cast<const char *>(message);

    while(true) {
      char c = pgm_read_byte(pointer);
      ++pointer;

      if(c == '\0')
        break;

      font3x5.print(c);
      arduboy.display();

      checkDelay();
    }
  }

  void slowPrint(uint8_t value) {
    if(value == 0) {
      font3x5.print('0');
      arduboy.display();
      checkDelay();
      return;
    }

    uint8_t digits[3];

    for(uint8_t i = 0; i < 3; ++i) {
      digits[(3 - 1) - i] = (value % 10);
      value /= 10;
    }

    for(uint8_t i = 0; i < 3; ++i) {
      if(digits[i] > 0) {
        printDigit(digits[i]);
        arduboy.display();
      }

      checkDelay();
    }
  }

  void printDigit(uint8_t digit) {
    static constexpr char digits[] PROGMEM {
      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    font3x5.print(static_cast<char>(pgm_read_byte(&digits[digit & 0x0F])));
  }
};

//ARDUBOY_NO_USB

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
}

void loop() {
  days = 250;
  totalKlingon = 25;
  totalBase = 3;
  title();
  configuration();
  initQuadrant();
  initEnterprise();
  initSector(enterprise.quadrant.x, enterprise.quadrant.y);
  toEnterprise(1);
  dispMain();
  toEnterprise( gloop + 1 );
  gloop=0;
}
