void prints(int x, int y, FlashStringHelper message, bool inv) {
  int counter=0;
  const char * pointer;
  pointer = reinterpret_cast<const char *>(message);
  
  while(true)
  if( pgm_read_byte(pointer + counter)=='\0'){
    break;
  } else {
    counter++;
  }
  font3x5.setCursor( x*4+1, y*7 );
  if(inv == 0){
    font3x5.setTextColor(WHITE);
    font3x5.print( message );
  } else {
    arduboy.fillRect( x*4, y*7, counter*4+1, 7,WHITE);
    font3x5.setTextColor(BLACK);
    font3x5.print( message );
  }
}

void prints(int x, int y, char * message, bool inv) {
  font3x5.setCursor( x*4+1, y*7 );
  if(inv == 0){
    font3x5.setTextColor(WHITE);
    font3x5.print( message );
  } else {
    arduboy.fillRect( x*4, y*7, strlen(message)*4+1, 7,WHITE);
    font3x5.setTextColor(BLACK);
    font3x5.print( message );
  }
}

void prints(int x, int y, int d, bool inv){
  font3x5.setCursor( x*4+1, y*7 );
  if(inv == 0){
    font3x5.setTextColor(WHITE);
    font3x5.print( d );
  } else {
    arduboy.fillRect( x*4, y*7, order( d )*4+1, 7,WHITE);
    font3x5.setTextColor(BLACK);
    font3x5.print( d );
  }
}

byte order(int num) {
  byte ans = 1;
  while (num > 10) {
    ans++;
    num /= 10;
  }
  return ans;
}
