#pragma once

#include <avr/pgmspace.h>

#define   MENU_BASE_ID      (7)
#define   COMPUTER_BASE_ID  (15)
#define   MECHANISM_BASE_ID (21)
#define   CONFIG_BASE_ID    (29)
#define   CONFITEM_BASE_ID  (36)
#define   ALERT_BASE_ID     (42)
#define   MESSAGE_BASE_ID   (50)

const char string_0[] PROGMEM = 
  "                ,------*------,\n"
  ",-------------   '---  ------'\n"
  " '-------- --'      / /\n"
  "     ,---' '-------/ /--,\n"
  "      '----------------'";
const char string_1[] PROGMEM = //order
    "TO ENTERPRISE:\n\n"
    "  DESTROY ";
const char string_2[] PROGMEM = 
    " KLINGONS IN\n"
    "  250 DAYS. THERE ARE ";
const char string_3[] PROGMEM = 
    "\n"
    "  BASES.";
const char string_4[] PROGMEM = //time is out
    "TO ENTERPRISE:\n\n"
    "  \n"
    "  TIME IS OVER...\n"
    "  ";

const char string_5[] PROGMEM = //destroyed
    "TO ENTERPRISE:\n\n"
    "  YOU HAS BEEN DESTROYED.\n"
    "  THE FEDERATION WILL BE\n"
    "  CONQUERED.";

const char string_6[] PROGMEM = //win
    "TO ENTERPRISE:\n\n"
    "  THE LAST KLINGON HAS BEEN\n"
    "  DESTROYED. THE FEDERATION\n"
    "  HAS BEEN SAVED !";

const char string_7[] PROGMEM = "MAP";
const char string_8[] PROGMEM = "NAV";
const char string_9[] PROGMEM = "TOR";
const char string_10[] PROGMEM = "PHA";
const char string_11[] PROGMEM = "SHI";
const char string_12[] PROGMEM = "DAM";
const char string_13[] PROGMEM = "PRO";
const char string_14[] PROGMEM = "COM";

const char string_15[] PROGMEM = "COMPUTE TRAJECTORY";
const char string_16[] PROGMEM = " COMPUTE QUADRAT  ";
const char string_17[] PROGMEM = "   LOCK TORPEDO   ";
const char string_18[] PROGMEM = "    SELF REPAIR   ";
const char string_19[] PROGMEM = "      RETURN      ";
const char string_20[] PROGMEM = " GIVE UP MISSION  ";

const char string_21[] PROGMEM = "WARP ENGINES";
const char string_22[] PROGMEM = "L.R. SONSORS";
const char string_23[] PROGMEM = "S.R. SENSORS";
const char string_24[] PROGMEM = "PHOTON TUBES";
const char string_25[] PROGMEM = "PHASER CNTRL";
const char string_26[] PROGMEM = "SHIELD CNTRL";
const char string_27[] PROGMEM = "PROBE SENSOR";
const char string_28[] PROGMEM = "LIB COMPUTER";

const char string_29[] PROGMEM = " NUM OF ENEMY";
const char string_30[] PROGMEM = "  NUM OF BASE";
const char string_31[] PROGMEM = "  BASE SUPPLY";
const char string_32[] PROGMEM = "   BLACK HOLE";
const char string_33[] PROGMEM = "ASTEROID BELT";
const char string_34[] PROGMEM = "      JAMMING";
const char string_35[] PROGMEM = "START MISSION";

const char string_36[] PROGMEM = "MANY";
const char string_37[] PROGMEM = "ONCE";
const char string_38[] PROGMEM = "NOT EXIST";
const char string_39[] PROGMEM = "EXIST";
const char string_40[] PROGMEM = "DON'T";
const char string_41[] PROGMEM = "DO";

const char string_42[] PROGMEM = "COURSE?";
const char string_43[] PROGMEM = "DISTANSE?";
const char string_44[] PROGMEM = "ENERGY?";
const char string_45[] PROGMEM = "PERCENTAGE?";
const char string_46[] PROGMEM = "NUMBER OF?";

const char string_47[] PROGMEM = "\n  IS DAMAGED!";
const char string_48[] PROGMEM = "\n  IS REPAIRED!";
const char string_49[] PROGMEM = "\n  IS OUT OF ORDER.";

const char string_50[] PROGMEM = "JAMMING...";
const char string_51[] PROGMEM = "TORPEDO IS EMPTY.";
const char string_52[] PROGMEM = "STRONG GRAVITY\n  FIELD OBSERVED.";
const char string_53[] PROGMEM = "JAMMING DETECTED.";

const char * const string[] PROGMEM =
{
  string_0,
  string_1,
  string_2,
  string_3,
  string_4,
  string_5,
  string_6,
  string_7,
  string_8,
  string_9,
  string_10,
  string_11,
  string_12,
  string_13,
  string_14,
  string_15,
  string_16,
  string_17,
  string_18,
  string_19,
  string_20,
  string_21,
  string_22,
  string_23,
  string_24,
  string_25,
  string_26,
  string_27,
  string_28,
  string_29,
  string_30,
  string_31,
  string_32,
  string_33,
  string_34,
  string_35,
  string_36,
  string_37,
  string_38,
  string_39,
  string_40,
  string_41,
  string_42,
  string_43,
  string_44,
  string_45,
  string_46,
  string_47,
  string_48,
  string_49,
  string_50,
  string_51,
  string_52,
  string_53
};
