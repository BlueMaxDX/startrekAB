void dispDamage() {
  arduboy.clear();
  arduboy.fillRect(0, 0, 127, 7, WHITE);
  prints(8, 0, "DAMAGE REPORT", 1);
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
  arduboy.display();

  waitA();
}

int dispComputer() {
  int curs = 0;
  int offset = 0;
  int result = 0;
  int ans, r;
  int x, y, c, d;
  float dx, dy, radius;
  int degree, dist;

  if ( damage[7] > 0) {
    offset = 4;
    curs = 4;
  }
  while (1) {
    arduboy.clear();
    arduboy.fillRect(0, 0, 127, 7, WHITE);
    prints(8, 0, "LIBRARY COMPUTER", 1);
    for (int i = offset; i < 6; i++) {
      prints(8, i + 3, rfsp( COMPUTER_BASE_ID + i ), curs == i);
    }
    arduboy.display();

    arduboy.pollButtons();
    if (arduboy.justPressed(UP_BUTTON)) {
      curs = (curs + (5 - offset) ) % ( 6 - offset ) + offset;
    }
    if (arduboy.justPressed(DOWN_BUTTON)) {
      curs = (curs + 1) % ( 6 - offset ) + offset;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      switch (curs) {
        case 0:
          ans = getSector();
          x = ans % 8;
          y = ans / 8;
          dx = x - enterprise.sector.x;
          dy = y - enterprise.sector.y;
          radius = atan2( dy, dx );
          degree = radius / 2 / 3.1415 * 360;
          if (degree < 0) degree += 360;
          dist = sqrt( pow(dx, 2) + pow(dy, 2));
          while (true) {
            c = askAmount( 0, 360, rfsp( ALERT_BASE_ID ), degree, 1 );
            if (c == 360) return 1;
            if (damage[0] > 0) {
              d = askAmount( 0, 2, rfsp( ALERT_BASE_ID + 1), 2, 0 );
            } else {
              d = askAmount( 0, 80, rfsp( ALERT_BASE_ID + 1), dist, 0 );
            }
            if (d == 0) return 1;
            moveEnterprise( c, d );
            break;
          }
          break;
        case 1:
          ans = getQuadrant();
          x = ans % 8;
          y = ans / 8;
          dx = x - enterprise.quadrant.x;
          dy = y - enterprise.quadrant.y;
          radius = atan2( dy, dx );
          degree = radius / 2 / 3.1415 * 360;
          if (degree < 0) degree += 360;
          dist = sqrt( pow(dx, 2) + pow(dy, 2)) * 10 + 5;
          while (true) {
            c = askAmount( 0, 360, rfsp( ALERT_BASE_ID ), degree, 1 );
            if (c == 360) return 1;
            if (damage[0] > 0) {
              d = askAmount( 0, 2, rfsp( ALERT_BASE_ID + 1), 2, 0 );
            } else {
              d = askAmount( 0, 80, rfsp( ALERT_BASE_ID + 1), dist, 0 );
            }
            if (d == 0) return 1;
            moveEnterprise( c, d );
            break;
          }
          break;
        case 2:
          if ( launchTorpedo( 1 ) == 1) {
            return 1;
          }
          break;
        case 3:
          d = askAmount( 0, enterprise.energy, rfsp( ALERT_BASE_ID + 2), 100, 0 );
          if (d == 0) {
            return 1;
          } else {
            selfRepair( d );
          }
          break;
        case 4:
          arduboy.clear();
          updateMain();
          arduboy.display();
          return 1;
        //          break;
        case 5:
          arduboy.clear();
          arduboy.display();
          gloop = 2;
          break;
      }
      return 0;
      //      break;
    }
  }
}

void dispGalaxy() {

  quadrant[enterprise.quadrant.x][enterprise.quadrant.y] =
    (quadrant[enterprise.quadrant.x][enterprise.quadrant.y] & 0b10011111) + 32 * gKlingon;

  arduboy.clear();
  drawGalaxy();
  arduboy.display();

  while (1) {
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON)) {
      break;
    }
  }
}

void dispMain() {
  int go = 0;
  int c, d;
  double total;
  point sectorCurs;
  while ( gloop == 0) {
    arduboy.clear();
    arduboy.pollButtons();
    updateMain();
    if (arduboy.justPressed(LEFT_BUTTON)) {
      gcurs = (gcurs + 7) % 8;
    }
    if (arduboy.justPressed(RIGHT_BUTTON)) {
      gcurs = (gcurs + 1) % 8;
    }
    if (arduboy.justPressed(A_BUTTON)) {
      switch ( gcurs ) {
        case 0: //Map of Galaxy
          //            dispGalaxy();
          dispGalaxy();
          arduboy.clear();
          updateMain();
          arduboy.display();
          break;
        case 1: //warp engine
          while (true) {
            c = askAmount( 0, 360, rfsp( ALERT_BASE_ID ), 0, 1 );
            if (c == 360) break;
            if (damage[0] > 0) {
              d = askAmount( 0, 2, rfsp( ALERT_BASE_ID + 1), 2, 0 );
            } else {
              d = askAmount( 0, 80, rfsp( ALERT_BASE_ID + 1), 2, 0 );
            }
            if (d == 0) break;
            moveEnterprise( c, d );
            repairMechanism();
            klingonAttack();
            break;
          }
          break;
        case 2: //photon torpedo
          if ( launchTorpedo( 0 ) == 1) {
            break;;
          } else {
            repairMechanism();
            klingonAttack();
            break;
          }
        case 3: //phaser
          if ( damage[4] > 0 ) {
            alert(0, 4, 2);
          } else {
            while (true) {
              d = askAmount( 0, enterprise.energy, rfsp( ALERT_BASE_ID + 2), enterprise.energy / 5, 0 );
              if (d == 0) break;
              firePhaser( d );
              repairMechanism();
              klingonAttack();
              break;
            }
          }
          break;
        case 4: //shield
          if ( damage[5] > 0 ) {
            alert(0, 5, 2);
          } else {
            c = askAmount( 0, 100, rfsp( ALERT_BASE_ID + 3), 50, 0 );
            total = enterprise.energy + enterprise.shield;
            enterprise.shield = total * c / 100;
            enterprise.energy = total * ( 100 - c ) / 100;
            drawStatus();
          }
          break;
        case 5: //damage report
          dispDamage();
          break;
        case 6: //probe
          if ( damage[6] > 0 ) {
            alert(0, 6, 2);
          } else if ( sectorJamming == 1) {
            alert(0, 8, 0);
          } else {
            probe();
          }
          break;
        case 7: //library computer
          if ( dispComputer() == 0 ) {
            repairMechanism();
            klingonAttack();
          }
          break;
      }
      days--;
      if ( days < 0 ) gloop = 1;
      if ( enterprise.energy < 0 ) gloop = 2;
      if ( totalKlingon == 0 ) gloop = 3;
    }
    arduboy.display();
  }
}

void moveEnterprise( int deg, int dist ) {
  int xa;
  int ya;
  int xs;
  int ys;
  int x = enterprise.sector.x * 7 + 4;
  int y = enterprise.sector.y * 7;
  int warp = 0;
  int hit, r;

  float brad;
  int bdeg, dd;

  gdock = 0;
  enterprise.energy -= dist;
  if ( dist > 9 ) {
    warp = dist;
    dist = 2;
  }

  if (sBlackhole == 1) {
    brad = atan2( blackhole.y - enterprise.sector.y, blackhole.x - enterprise.sector.x );
    bdeg = brad / 2 / 3.1415 * 360;
    if (bdeg < 0) bdeg += 360;
    if ( (deg - bdeg + 360) % 360 < 180) {
      dd = 359;
    } else if ((deg - bdeg + 360) % 360 == 180) {
      dd = 0;
    } else {
      dd = 1;
    }
  } else {
    dd = 0;
  }

  for ( int n = 0; n < dist * (7 + (dist < 5)); n++) {
    sector[enterprise.sector.x][enterprise.sector.y] = 0;
    deg = (deg + dd) % 360;
    xa = n * cos(2 * 3.1415 * deg / 360);
    ya = n * sin(2 * 3.1415 * deg / 360);

    xs = (x + xa - 4 + 3) / 7;
    ys = (y + ya + 3 ) / 7;

    if (xs < 0) {
      warpQuadrant( (enterprise.quadrant.x + 7) % 8, enterprise.quadrant.y, deg );
      warp = 0;
      break;
    } else if (xs > 7) {
      warpQuadrant( (enterprise.quadrant.x + 1) % 8, enterprise.quadrant.y, deg );
      warp = 0;
      break;
    } else if (ys < 0) {
      warpQuadrant( enterprise.quadrant.x, (enterprise.quadrant.y + 7) % 8, deg );
      warp = 0;
      break;
    } else if (ys > 7) {
      warpQuadrant( enterprise.quadrant.x, (enterprise.quadrant.y + 1) % 8, deg );
      warp = 0;
      break;
    }
    if (sector[xs][ys] > 1) {
      hit = sector[xs][ys];
      xs = (x + (n - 4) * cos(2 * 3.1415 * deg / 360) - 1 ) / 7;
      ys = (y + (n - 4) * sin(2 * 3.1415 * deg / 360) + 4 ) / 7;
      sector[xs][ys] = 1;
      enterprise.sector.x = xs;
      enterprise.sector.y = ys;
      warp = 0;
      if ( hit > 1 && hit < 10 ) {
        crashAnimation();
        r = random(200);
        klingon[hit - 2].energy -= r;
        hitEnterprise( random( 200 ) );
        if (klingon[hit - 2].energy < 0) {
          bombAnimation(klingon[hit - 2].sector.x, klingon[hit - 2].sector.y);
          sector[klingon[hit - 2].sector.x][klingon[hit - 2].sector.y] = 0;
          gKlingon--; //quadrant[enterprise.quadrant.x][enterprise.quadrant.y] -= 32;
          if (gKlingon == 0) sectorJamming = 0;
          totalKlingon--;
        }
        if (enterprise.shield == 0) damageMechanism();
      } else if (hit == 10) {
        gdock = 1;
        dockBase(); //dock base
        if ( supply == 1 ) {
          sector[base.x][base.y] = 0;
          quadrant[enterprise.quadrant.x][enterprise.quadrant.y] -= 16;
          totalBase -= 1;
          gdock = 0;
        }
      } else {
        hitEnterprise( random( 200 ) );
        crashAnimation();
        if (enterprise.shield == 0) damageMechanism();
      }
      break;
    }
    font3x5.setCursor(x + xa, y + ya);
    font3x5.setTextColor( !ginv );
    font3x5.print('E');
    arduboy.display();
    delay(SPEED);
    arduboy.fillRoundRect(0, 0, 60, 56, 3, col(!ginv));
    drawSRS(0);
    sector[xs][ys] = 1;
    enterprise.sector.x = xs;
    enterprise.sector.y = ys;
  }
  drawSRS(0);
  if ( warp > 0) {
    int dx = warp * cos(2 * 3.1415 * deg / 360) / 10;
    int dy = warp * sin(2 * 3.1415 * deg / 360) / 10;
    warpQuadrant( (enterprise.quadrant.x + (8 + dx)) % 8, (enterprise.quadrant.y + (8 + dy)) % 8, deg);
  }
}

int launchTorpedo( int m ) {
  int ans;
  int x, y, c, d;
  float dx, dy, radius;
  int degree, dist;

  if ( damage[3] > 0 ) {
    alert(0, 3, 2);
    return 1;
  } else if ( enterprise.torpedo == 0) {
    alert(0, 8, 1);
    return 1;
  } else {
    if ( m == 0 ) {
      c = askAmount( 0, 360, rfsp( ALERT_BASE_ID ), 0, 1 );
      if (c == 360) {
        return 1;
      } else {
        fireTorpedo( c );
        return 0;
      }
    } else {
      ans = getSector();
      x = ans % 8;
      y = ans / 8;
      dx = x - enterprise.sector.x;
      dy = y - enterprise.sector.y;
      radius = atan2( dy, dx );
      degree = radius / 2 / 3.1415 * 360;
      if (degree < 0) degree += 360;
      c = askAmount( 0, 360, rfsp( ALERT_BASE_ID ), degree, 1 );
      if (c == 360) {
        return 1;
      } else {
        fireTorpedo( c );
        return 0;
      }
    }
  }
}

void fireTorpedo( int deg ) {
  int xa;
  int ya;
  byte xs = enterprise.sector.x;
  byte ys = enterprise.sector.y;
  int x = enterprise.sector.x * 7 + 4;
  int y = enterprise.sector.y * 7;
  int n = 0;

  float brad;
  int bdeg, dd;

  if (sBlackhole == 1) {
    brad = atan2( blackhole.y - enterprise.sector.y, blackhole.x - enterprise.sector.x );
    bdeg = brad / 2 / 3.1415 * 360;
    if (bdeg < 0) bdeg += 360;
    if ( (deg - bdeg + 360) % 360 < 180) {
      dd = 359;
    } else if ((deg - bdeg + 360) % 360 == 180) {
      dd = 0;
    } else {
      dd = 1;
    }
  } else {
    dd = 0;
  }

  enterprise.torpedo -= 1;
  while (1) {
    //    arduboy.drawCircle( blackhole.x * 4 + 4+3, blackhole.y * 7+3, 3, WHITE);
    deg = (deg + dd) % 360;
    xa = n * cos(2 * 3.1415 * deg / 360);
    ya = n * sin(2 * 3.1415 * deg / 360);

    xs = (x + xa - 4 + 3) / 7;
    ys = (y + ya + 3 ) / 7;

    if (xs < 0 || xs > 7 || ys < 0 || ys > 7) {
      break;  //miss
    }

    if (sector[xs][ys] > 1 && sector[xs][ys] < 10) {
      bombAnimation( xs, ys );
      klingon[sector[xs][ys] - 2].energy -= random(300);
      if (klingon[sector[xs][ys] - 2].energy < 0) {
        sector[xs][ys] = 0;
        gKlingon--; //quadrant[enterprise.quadrant.x][enterprise.quadrant.y] -= 32;
        if (gKlingon == 0) sectorJamming = 0;
        totalKlingon--;
      }
      break;
    } else if (sector[xs][ys] == 10) {
      bombAnimation( xs, ys );
      sector[xs][ys] = 0;
      quadrant[enterprise.quadrant.x][enterprise.quadrant.y] -= 16;
      totalBase--;
      break;
    } else if (sector[xs][ys] == 11) {
      bombAnimation( xs, ys );
      sector[xs][ys] = 0;
      quadrant[enterprise.quadrant.x][enterprise.quadrant.y] -= 1;
      break;  //hit star!
    }
    font3x5.setCursor(x + xa, y + ya);
    font3x5.setTextColor(!ginv);
    font3x5.print('#');
    arduboy.drawRect(xs * 7 + 2, ys * 7, 7, 7, col(!ginv));
    arduboy.drawLine(xs * 7 + 2, ys * 7, xs * 7 + 2 + 6, ys * 7, col(!ginv));
    arduboy.drawLine(xs * 7 + 2, ys * 7 + 6, xs * 7 + 2 + 6, ys * 7 + 6, col(!ginv));
    arduboy.display();
    delay(SPEED);
    arduboy.fillRoundRect(0, 0, 60, 56, 3, col(!ginv));
    drawSRS(0);
    n++;
  }
  drawSRS(0);
}

void firePhaser( int energy ) {
  int dx, dy, chk;
  enterprise.energy -= energy;
  byte k = numOfKlingon(quadrant[enterprise.quadrant.x][enterprise.quadrant.y]);
  for (byte i = 0; i < k; i++) {
    dx = abs(klingon[i].sector.x - enterprise.sector.x);
    dy = abs(klingon[i].sector.y - enterprise.sector.y);
    if ( (damage[2] == 0 || damage[6] == 0) && sectorJamming == 0) {
      chk = 1;
    } else {
      chk = ((dx * dy == 1) || (dx + dy == 1));
    }
    if ((klingon[i].energy > 0) && (chk == 1)) {
      phaserAnimation(klingon[i].sector.x, klingon[i].sector.y);
      bombAnimation( klingon[i].sector.x, klingon[i].sector.y);
      //    int r = energy / numOfKlingon(quadrant[enterprise.quadrant.x][enterprise.quadrant.y]);
      klingon[i].energy -= random( energy );
      if (klingon[i].energy < 0) {
        sector[klingon[i].sector.x][klingon[i].sector.y] = 0;
        gKlingon--;
        if (gKlingon == 0) sectorJamming = 0;
        totalKlingon--;
      }
    }
  }
}

void klingonAttack() {
  float radian;
  int x, y, xa, ya, n = 7;
  float xd, yd;
  byte xs, ys;
  byte k = numOfKlingon(quadrant[enterprise.quadrant.x][enterprise.quadrant.y]);

  updateMain();

  for (byte i = 0; i < k; i++) {
    if ( klingon[i].energy > 0) {
      xd = enterprise.sector.x - klingon[i].sector.x;
      yd = enterprise.sector.y - klingon[i].sector.y;
      radian = atan2( yd, xd );

      x = klingon[i].sector.x * 7 + 4;
      y = klingon[i].sector.y * 7;
      klingon[i].torpedo -= 1;
      while (1) {
        xa = n * cos( radian );
        ya = n * sin( radian );

        xs = (x + xa - 4 + 3) / 7;
        ys = (y + ya + 3 ) / 7;

        if (xs < 0 || xs > 7 || ys < 0 || ys > 7) {
          break;  //miss
        }

        if (sector[xs][ys] == 1) {
          bombAnimation( xs, ys );
          hitEnterprise( random(200) );
          break;  //hit enterprise!
        } else if (sector[xs][ys] > 1 && sector[xs][ys] < 10) {
          bombAnimation( xs, ys );
          klingon[sector[xs][ys] - 2].energy -= random(200);
          if (klingon[sector[xs][ys] - 2].energy < 0) {
            sector[xs][ys] = 0;
            gKlingon--; //quadrant[enterprise.quadrant.x][enterprise.quadrant.y] -= 32;
            if (gKlingon == 0) sectorJamming = 0;
            totalKlingon--;
          }
          break;
        } else if (sector[xs][ys] == 10) {
          bombAnimation( xs, ys );
          sector[xs][ys] = 0;
          quadrant[enterprise.quadrant.x][enterprise.quadrant.y] -= 16;
          totalBase--;
          break;
        } else if (sector[xs][ys] == 11) {
          bombAnimation( xs, ys );
          sector[xs][ys] = 0;
          quadrant[enterprise.quadrant.x][enterprise.quadrant.y] -= 1;
          break;  //hit star!
        }
        if ( damage[2] == 0 && sectorJamming == 0) {
          font3x5.setCursor(x + xa, y + ya);
          font3x5.setTextColor(!ginv);
          font3x5.print('#');
          arduboy.drawRect(xs * 7 + 2, ys * 7, 7, 7, col(!ginv));
          arduboy.drawLine(xs * 7 + 2, ys * 7, xs * 7 + 2 + 6, ys * 7, col(!ginv));
          arduboy.drawLine(xs * 7 + 2, ys * 7 + 6, xs * 7 + 2 + 6, ys * 7 + 6, col(!ginv));
        }
        arduboy.display();
        delay(SPEED);
        arduboy.fillRoundRect(0, 0, 60, 56, 3, col(!ginv));
        drawSRS(0);
        n++;
      }
      n = 7;
      drawSRS(0);
    }
  }
}

void probe() {
  openWindow();
  arduboy.fillRect(16, 14, 96, 7, WHITE);
  font3x5.setCursor(40, 14);
  font3x5.setTextColor( BLACK );
  font3x5.println( F("PROBE SENSOR") );
  font3x5.setTextColor( WHITE );

  for (int i = 0; i < numOfKlingon(quadrant[enterprise.quadrant.x][enterprise.quadrant.y]); i++) {
    if ( klingon[i].energy < 0 ) {
      continue;
    }
    font3x5.setCursor(24, 23 + i * 7);
    font3x5.print( F("SECTOR:") );
    font3x5.print( klingon[i].sector.x );
    font3x5.print( '-' );
    font3x5.print( klingon[i].sector.y );
    font3x5.print( F("   ") );
    font3x5.print( klingon[i].energy );
  }
  arduboy.display();
  waitA();
  closeWindow();
}
