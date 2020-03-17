void title() {
  arduboy.clear();
  for(int i=0; i < 128; i++){
    arduboy.clear();
    font3x5.setCursor(i-125, 7);
    font3x5.print( rfsp( 0 ) );
    arduboy.display();
    delay(pow(i/8,2));
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON)) {
      arduboy.clear();
      font3x5.setCursor(2,7);
      font3x5.print( rfsp( 0 ) );
      arduboy.display();
      break;
    }
  }
  prints(12, 7, "STARTREK", 1);
  arduboy.display();

  waitA();
}

void toEnterprise( int mes ){

  SlowPrinter printer;
  
  arduboy.clear();
  font3x5.setTextColor(WHITE);
  font3x5.setCursor(12,7);
  if(mes==1){
    printer.slowPrint( rfsp( 1 ) );
    printer.slowPrint( totalKlingon );
    printer.slowPrint( rfsp( 2 ) );
    printer.slowPrint( totalBase );
    printer.slowPrint( rfsp( 3 ) );
  } else {
    printer.slowPrint( rfsp( mes + 2 ) );
  }
  while(1){
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON)) {
      break;
    }
  }
}

void longRangeSensor(byte x, byte y) {
  if(damage[1]==0){
    for (int i = x - (x > 0); i <= x + (x < 7); i++) {
      for (int j = y - (y > 0); j <= y + (y < 7); j++) {
        if (quadrant[i][j] < 128) quadrant[i][j] += 128;
      }
    }
  } else {
    quadrant[enterprise.quadrant.x][enterprise.quadrant.y] += 128;
  }
}

void hitEnterprise( int dam ){
  if( enterprise.shield > dam ){
    enterprise.shield -= dam;
  } else {
    enterprise.energy -= dam - enterprise.shield;
    enterprise.shield = 0;
//    damageMechanism();
  }
}

void dockBase(){
  enterprise.energy = 1500;
  enterprise.shield = 1500;
  enterprise.torpedo = 10;
  for(int i=0; i<8; i++){
    damage[i]=0;
  }
}
