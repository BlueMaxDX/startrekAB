void prints(int8_t x, uint8_t y, const char *message, bool invert) {
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
