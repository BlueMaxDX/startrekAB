int getSector() {
  point sectorCurs;
  sectorCurs.x = enterprise.sector.x;
  sectorCurs.y = enterprise.sector.y;
  while (1) {
    arduboy.clear();
    arduboy.pollButtons();

    updateMain();

    arduboy.drawFastVLine(sectorCurs.x * 7 + 5, 0, 56, WHITE);
    arduboy.drawFastHLine(1, sectorCurs.y * 7 + 3, 59, WHITE);

    if (arduboy.justPressed(LEFT_BUTTON)) {
      sectorCurs.x = (sectorCurs.x + 7) % 8;
    }
    if (arduboy.justPressed(RIGHT_BUTTON)) {
      sectorCurs.x = (sectorCurs.x + 1) % 8;
    }
    if (arduboy.justPressed(UP_BUTTON)) {
      sectorCurs.y = (sectorCurs.y + 7) % 8;
    }
    if (arduboy.justPressed(DOWN_BUTTON)) {
      sectorCurs.y = (sectorCurs.y + 1) % 8;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      return sectorCurs.x + sectorCurs.y * 8;
    }
    arduboy.display();
  }
}

int getQuadrant() {
  point curs;

  curs.x = enterprise.quadrant.x;
  curs.y = enterprise.quadrant.y;
  arduboy.clear();

  quadrant[enterprise.quadrant.x][enterprise.quadrant.y] =
    (quadrant[enterprise.quadrant.x][enterprise.quadrant.y] & 0b10011111) + 32 * gKlingon;

  while (1) {
    arduboy.pollButtons();
    arduboy.clear();

    drawGalaxy();

    arduboy.drawRect(curs.x * 16, (curs.y + 1) * 7, 15, 7, WHITE);

    if (arduboy.justPressed(RIGHT_BUTTON)) {
      curs.x = (curs.x + 1) % 8;
    }
    if (arduboy.justPressed(LEFT_BUTTON)) {
      curs.x = (curs.x + 7) % 8;
    }
    if (arduboy.justPressed(DOWN_BUTTON)) {
      curs.y = (curs.y + 1) % 8;
    }
    if (arduboy.justPressed(UP_BUTTON)) {
      curs.y = (curs.y + 7) % 8;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      return curs.x + curs.y * 8;
    }
    if (arduboy.justPressed(B_BUTTON)) {
      break;
    }
    arduboy.display();
  }
}

void damageMechanism(){
  int r = random(8);
  damage[r] += 5 + random(10);
  if(r == 5){
    enterprise.energy += enterprise.shield;
    enterprise.shield = 0;
  }
  alert(1,r,0);
}

void repairMechanism(){
  for(int i=0; i<8; i++){
    if( damage[i] == 1 ){
      alert(0,i,1);
    }
  }
  for(int i=0; i<8; i++){
    if( damage[i] > 0 ){
      damage[i]--;
    }
  }
}
