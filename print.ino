int strlenF(FlashStringHelper message) {
  int len = 0;
  const char * pointer = reinterpret_cast<const char *>(message);

  while( pgm_read_byte(pointer + len) != '\0'){
    len++;
  }
  return len;
}

void prints(int8_t x, int8_t y, FlashStringHelper message, bool invert) {
  int length = strlenF(message);

  font3x5.setCursor( x*4+1, y*7 );
  if(invert){
    arduboy.fillRect( x*4, y*7, length*4+1, 7,WHITE);
    font3x5.setTextColor(BLACK);
  } else {
    font3x5.setTextColor(WHITE);
  }
  font3x5.print( message );
}

void prints(int8_t x, int8_t y, char * message, bool invert) {
  font3x5.setCursor( x*4+1, y*7 );
  if(invert){
    arduboy.fillRect( x*4, y*7, strlen(message)*4+1, 7,WHITE);
    font3x5.setTextColor(BLACK);
  } else {
    font3x5.setTextColor(WHITE);
  }
  font3x5.print( message );
}

void prints(int8_t x, uint8_t y, int d, bool invert){
  font3x5.setCursor( x*4+1, y*7 );
  if(invert){
    arduboy.fillRect( x*4, y*7, intlen( d )*4+1, 7,WHITE);
    font3x5.setTextColor(BLACK);
  } else {
    font3x5.setTextColor(WHITE);
  }
  font3x5.print( d );
}

// calculates the length of an integer by number of digits
// ie, 12345 => 5
uint8_t intlen(int num) {
  uint8_t ans = 1;
  while (num > 10) {
    ans++;
    num /= 10;
  }
  return ans;
}
