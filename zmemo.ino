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
  arduboy.fillRoundRect(0, 0, 60, 56, 3, col(ginv));
  point dot[16];
  for (int i = 0; i < 16; i++) {
    dot[i].x = random(56) + 4;
    dot[i].y = random(56);
  }
  for (int j = 0; j < 30; j++) {
    for (int i = 0; i < 16; i++) {
      arduboy.drawPixel( dot[i].x + j * cos(2 * 3.1415 * deg / 360), dot[i].y + j * sin(2 * 3.1415 * deg / 360), col(!ginv));
    }
    arduboy.display();
    delay(SPEED);
  }
  delay(200);
  for (int j = 29; j > 0; j--) {
    for (int i = 0; i < 16; i++) {
      arduboy.drawPixel( dot[i].x + j * cos(2 * 3.1415 * deg / 360), dot[i].y + j * sin(2 * 3.1415 * deg / 360), col(ginv));
    }
    arduboy.display();
    delay(SPEED);
  }
  arduboy.clear();
  
  gdock = 0;

  if (random(5) == 0) damageMechanism();

  quadrant[enterprise.quadrant.x][enterprise.quadrant.y] =
    (quadrant[enterprise.quadrant.x][enterprise.quadrant.y] & 0b10011111) + 32 * gKlingon;
  enterprise.quadrant.x = x;
  enterprise.quadrant.y = y;
  initSector(enterprise.quadrant.x, enterprise.quadrant.y);
  longRangeSensor(enterprise.quadrant.x, enterprise.quadrant.y);
  if ( sBlackhole == 1 ) {
    alert(1,8,2);
  }
  if ( sectorJamming == 1 ) {
    alert(1,8,3);
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
  int done = 0;
  while (done == 0) {
    arduboy.clear();
    arduboy.fillRect(0, 0, 127, 7, WHITE);
    prints(10, 0, "CONFIGURATION", 1);
    for (int i = 0; i < 6; i++) {
      prints(4, i + 2, rfsp( CONFIG_BASE_ID + i), curs == i);
    }
    prints(10, 8, rfsp( CONFIG_BASE_ID + 6), curs == 6);

    font3x5.setTextColor(WHITE);
    font3x5.setCursor(80, 14); font3x5.print( totalKlingon );
    font3x5.setCursor(80, 21); font3x5.print( totalBase );
    prints(20, 4, rfsp( CONFITEM_BASE_ID + supply), 0);
    prints(20, 5, rfsp( CONFITEM_BASE_ID + 2 + existBlackhole), 0);
    prints(20, 6, rfsp( CONFITEM_BASE_ID + 2 + asteroid), 0);
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
          totalKlingon = askAmount( 1, 99, rfsp( ALERT_BASE_ID + 4), totalKlingon, 0 );
          break;
        case 1:
          totalBase = askAmount( 1, 9, rfsp( ALERT_BASE_ID + 4), totalBase, 0 );
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

void selfRepair( int d ) {
  int r;
  for ( int turn = 0; turn < d; turn++) {
    arduboy.clear();
    arduboy.fillRect(0, 0, 127, 7, WHITE);
    prints(8, 0, "SELF REPAIR", 1);
    for (int i = 0; i < 8; i++) {
      prints(6, i + 1, rfsp( MECHANISM_BASE_ID + i), (damage[i] > 0));
      font3x5.print(F("    "));
      font3x5.setTextColor(WHITE);
      if (damage[i] > 0) {
        font3x5.print(damage[i]);
      } else {
        font3x5.print("OK");
      }
    }
    r = random(8);
    prints( 4, r + 1, ">", 0);
    prints(25, r + 1, "<", 0);
    if ( damage[r] > 0 && random(20) == 0) {
      damage[r]--;
      delay(500);
    }
    arduboy.display();
    delay(2);
  }
  waitA();
}

void alert( int lev, int mec, int con ) {
  openWindow();
  if ( lev == 0 ) {
    arduboy.drawRect(16, 14, 96, 7, WHITE);
    font3x5.setCursor(40, 14);
    font3x5.setTextColor( WHITE );
    font3x5.print( F("INFORMATION") );
  } else {
    arduboy.fillRect(16, 14, 96, 7, WHITE);
    font3x5.setCursor(48, 14);
    font3x5.setTextColor( BLACK );
    font3x5.print( F("CAUTION") );
    font3x5.setTextColor( WHITE );
  }
  font3x5.setCursor(28, 24);
  if ( mec < 8 ) {
    font3x5.print( rfsp( MECHANISM_BASE_ID + mec) );
    font3x5.print( rfsp( 47 + con ) );  //is damaged
  } else {
    font3x5.print( rfsp( MESSAGE_BASE_ID + con ) );
  }
  arduboy.display();
  
  waitA();

  closeWindow();
}
