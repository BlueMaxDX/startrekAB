// NAV PRO PHA TOR SHE MAP DAM COM
// REP SRS LRS MAP PHA TOR NAV

// engene
// LR sensor
// SR eensor
// Phaser
// torpedo
// computer
// probe

//compute quadrant
//compute sector
//torpedo attack
//self repair
//quit game

void warpQuadrant( byte x, byte y, int deg ) {
  deg += 180;
  arduboy.fillRect(0, 0, 60, 56, BLACK);
  point dot[16];
  for (int i = 0; i < 16; i++) {
    dot[i].x = random(56) + 4;
    dot[i].y = random(56);
  }
  for (int j = 0; j < 30; j++) {
    for (int i = 0; i < 16; i++) {
      arduboy.drawPixel( dot[i].x + j * cos(2 * 3.1415 * deg / 360), dot[i].y + j * sin(2 * 3.1415 * deg / 360), WHITE);
    }
    arduboy.display();
    delay(SPEED);
  }
  delay(200);
  for (int j = 29; j > 0; j--) {
    for (int i = 0; i < 16; i++) {
      arduboy.drawPixel( dot[i].x + j * cos(2 * 3.1415 * deg / 360), dot[i].y + j * sin(2 * 3.1415 * deg / 360), BLACK);
    }
    arduboy.display();
    delay(SPEED);
  }
  gdock = 0;

  if (random(5) == 0) damageMechanism();

  quadrant[enterprise.quadrant.x][enterprise.quadrant.y] =
    (quadrant[enterprise.quadrant.x][enterprise.quadrant.y] & 0b10011111) + 32 * gKlingon;
  enterprise.quadrant.x = x;
  enterprise.quadrant.y = y;
  initSector(enterprise.quadrant.x, enterprise.quadrant.y);
  longRangeSensor(enterprise.quadrant.x, enterprise.quadrant.y);
  if( sBlackhole == 1 ){
    openWindow();
    font3x5.setTextColor(WHITE);
    font3x5.setCursor(20, 20);
    font3x5.print(F("STRONG GRAVITY\nFIELD OBSERVED"));
    arduboy.display();
    waitA();
    closeWindow();
  }
  if( sectorJamming == 1 ){
    openWindow();
    font3x5.setTextColor(WHITE);
    font3x5.setCursor(20, 20);
    font3x5.print(F("JAMMING DETECTED"));
    arduboy.display();
    waitA();
    closeWindow();
  }
}

void waitA() {
  while (1) {
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON)) {
      break;
    }
  }
}

void updateMain() {
  drawSRS(0);
  drawStatus();
  drawMenu();
}

void configuration() {
  int curs = 6;
//  char buf[16];
  int done = 0;
  while (done == 0) {
    arduboy.clear();
    arduboy.fillRect(0, 0, 127, 7, WHITE);
    prints(10, 0, "CONFIGURATION", 1);
    for (int i = 0; i < 6; i++) {
//      strcpy_P( buf, (char*)pgm_read_word(&(config_table[i])));
      prints(4, i + 2, rfsp( CONFIG_BASE_ID + i), curs == i);
    }
//    strcpy_P( buf, (char*)pgm_read_word(&(config_table[6])));
    prints(10, 8, rfsp( ALERT_BASE_ID + 6), curs == 6);

    font3x5.setTextColor(WHITE);
    font3x5.setCursor(80, 14); font3x5.print( totalKlingon );
    font3x5.setCursor(80, 21); font3x5.print( totalBase );
//    strcpy_P( buf, (char*)pgm_read_word(&(confItem_table[0 + supply])));
    prints(20, 4, rfsp( CONFITEM_BASE_ID + supply), 0);
//    strcpy_P( buf, (char*)pgm_read_word(&(confItem_table[2 + existBlackhole])));
    prints(20, 5, rfsp( CONFITEM_BASE_ID + 2 + existBlackhole), 0);
//    strcpy_P( buf, (char*)pgm_read_word(&(confItem_table[2 + asteroid])));
    prints(20, 6, rfsp( CONFITEM_BASE_ID + 2 + asteroid), 0);
//    strcpy_P( buf, (char*)pgm_read_word(&(confItem_table[4 + jamming])));
    prints(20, 7, rfsp( CONFITEM_BASE_ID + 4 + jamming), 0);
    arduboy.display();

    arduboy.pollButtons();
    if (arduboy.justPressed(UP_BUTTON)) {
      curs = (curs + 6) % 7;
    }
    if (arduboy.justPressed(DOWN_BUTTON)) {
      curs = (curs + 1) % 7;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      switch (curs) {
        case 0:
//          strcpy_P( buf, (char*)pgm_read_word(&(string_table[4])));
          totalKlingon = askAmount( 1, 99, rfsp( ALERT_BASE_ID + 4), totalKlingon, 0 );
          break;
        case 1:
//          strcpy_P( buf, (char*)pgm_read_word(&(string_table[4])));
          totalBase = askAmount( 0, 9, rfsp( ALERT_BASE_ID + 4), totalBase, 0 );
          break;
        case 2:
          supply = !supply;
          break;
        case 3:
          existBlackhole = !existBlackhole;
          break;
        case 4:
          asteroid = !asteroid;
          break;
        case 5:
          jamming = !jamming;
          break;
        case 6:
          done = 1;
          break;
      }
    }
  }
}

void selfRepair( int d ){
//  char buf[13];
  int r;
  for( int turn = 0; turn < d; turn++){
    arduboy.clear();
    arduboy.fillRect(0, 0, 127, 7, WHITE);
    prints(8, 0, "SELF REPAIR", 1);
    for (int i = 0; i < 8; i++) {
//      strcpy_P( buf, (char*)pgm_read_word(&(mechanism_table[i])));
      prints(6, i + 1, rfsp( MECHANISM_BASE_ID + i), (damage[i] > 0));
      font3x5.print(F("    "));
      font3x5.setTextColor(WHITE);
      if (damage[i] > 0) {
        font3x5.print(damage[i]);
      } else {
        font3x5.print("OK");
      }
    }
    r=random(8);
    prints( 4,r+1,">",0);
    prints(25,r+1,"<",0);
    if( damage[r] > 0 && random(20)==0){
      damage[r]--;
      delay(500);
    }
    arduboy.display();
    delay(2);
  }
  waitA();
}
