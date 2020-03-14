void initQuadrant() {
  byte counter=0;
  int rx,ry;
//  totalKlingon = 25;
//  totalBase = 3;

  memset(&quadrant, 0, sizeof(quadrant));
  
  while( counter < totalKlingon ){
    rx = random(8);
    ry = random(8);
    if( numOfKlingon(quadrant[rx][rx]) < 3 ){
      quadrant[rx][ry] += 32;
      counter++;
    }
  }
  counter=0;
  while( counter < totalBase ){
    rx = random(8);
    ry = random(8);
    if( numOfBase(quadrant[rx][rx]) < 1 ){
      quadrant[rx][ry] += 16;
      counter++;
    }
  }
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      quadrant[i][j] += random(8)+1;
    }
  }
}

void initEnterprise() {
  enterprise.quadrant.x = random(8);
  enterprise.quadrant.y = random(8);
  enterprise.energy = 1500;
  enterprise.shield = 1500;
  enterprise.torpedo = 10;
  for( int i=0; i<8; i++){
    damage[i]=0;
  }
  longRangeSensor( enterprise.quadrant.x, enterprise.quadrant.y );
}

void initSector(byte mx, byte my) {
  byte k = numOfKlingon(quadrant[mx][my]);
  byte b = numOfBase(quadrant[mx][my]);
  byte s = numOfStar(quadrant[mx][my]);
  int rx, ry;
  int counter = 0;
  sBlackhole = 0;
  sectorJamming = 0;
  
  memset(&sector, 0, sizeof(sector));
/*
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      sector[i][j]=0;
    }
  }
*/
  if( existBlackhole == 1){
    if(random(10) == 0){
      counter = 0;
      while (counter < 1) {
        rx = random(8);
        ry = random(8);
        if (sector[rx][ry] == 0) {
          sBlackhole = 1;
          blackhole.x = rx;
          blackhole.y = ry;
          counter++;
        }
      }
    }
  }

  if( k>0 && jamming == 1 && sBlackhole == 0 && random(10)==0){
    sectorJamming = 1;
  } else {
    sectorJamming = 0;
  }

  if( asteroid ==1 && random(8)==0 ){
    rx=random(4)+2;
    switch(random(2)){
      case 0:
        for( int i=0; i<8; i++){
          sector[i][rx]=12;
        }
        break;
      case 1:
        for( int i=0; i<8; i++){
          sector[rx][i]=12;
        }
        break;
    }
  }
  counter = 0;
  while (counter < 1) {
    rx = random(8);
    ry = random(8);
    if (sector[rx][ry] == 0) {
      sector[rx][ry] = 1;
      enterprise.sector.x = rx;
      enterprise.sector.y = ry;
      counter++;
    }
  }
  counter = 0;
  while (counter < k) {
    rx = random(8);
    ry = random(8);
    if (sector[rx][ry] == 0) {
      sector[rx][ry] = 2+counter;
      klingon[counter].sector.x = rx;
      klingon[counter].sector.y = ry;
      klingon[counter].energy = 200;
      klingon[counter].torpedo = 2;
      counter++;
    }
  }

  counter = 0;
  while (counter < b) {
    rx = random(8);
    ry = random(8);
    if (sector[rx][ry] == 0) {
      sector[rx][ry] = 10;
      base.x = rx;
      base.y = ry;
      counter++;
    }
  }

  counter = 0;
  while (counter < s) {
    rx = random(8);
    ry = random(8);
    if (sector[rx][ry] == 0) {
      sector[rx][ry] = 11;
      counter++;
    }
  }
//  if( k > 0 && jamming == 1 && sBlackhole == 0 ) sectorJamming = 1;
  gKlingon = k;
}
