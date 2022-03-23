#include "inc.c"
//#include "pitches.h"

/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

// include the library code:

/* Constant identifying the "thickcad" library. */
#define THINKCAD 1

#define THINKCADS 3

/* Constant identifying the "arduino" library. */
#define ARDU 2

/* Provide a default library if the user does not select one. */
#ifndef LIBRARY_TO_USE
#define LIBRARY_TO_USE THINKCAD
#endif

#if LIBRARY_TO_USE == THINKCADS
#include <LiquidCrystal_I2C.h>

#elif LIBRARY_TO_USE == THINKCAD
#include <LiquidCrystal.h>
#elif LIBRARY_TO_USE == ARDU
#include <NeoSWSerial.h>
#include <LiquidCrystal_I2C.h>
//#include "NMEAGPS.h"
#else
#error "Invalid choice for LIBRARY_TO_USE (select ARDU or THINKCAD)"
#endif

//Arduino
//#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal.h>  //using lcd direct
#include <EEPROM.h>

//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#if LIBRARY_TO_USE == THINKCAD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
#endif

//Thinkcad
#if LIBRARY_TO_USE == THINKCADS
#include <LiquidCrystal_I2C.h>
#elif LIBRARY_TO_USE == THINKCAD
#include <LiquidCrystal.h>
#elif LIBRARY_TO_USE == ARDU
#include <LiquidCrystal_I2C.h>
#else
#error "Invalid choice for LIBRARY_TO_USE (select ARDU or THINKCAD)"
#endif

#if LIBRARY_TO_USE == THINKCAD
//thinkcad
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#else
//Arduino
LiquidCrystal_I2C lcd(0x27, 16, 2);
#endif

//Arduino
#if LIBRARY_TO_USE == THINKCADS
int waithelp = 15;
int scrollhelp = 10;

#elif LIBRARY_TO_USE == THINKCAD
int waithelp = 15;
int scrollhelp = 10;
#else
int waithelp = 30;
int scrollhelp = 20;
NeoSWSerial bt(3, 2); //RX, TX
//#include <SoftwareSerial.h>

///SoftwareSerial monitor(4, 12); //RX, TX
#endif




bool dataBT = false;
unsigned long timerBT = 0;
bool dataMonitor = false;
float coolant = 0;
float bat = 0;
unsigned long timerMonitor = 0;
String buff = "";
String buffs = "";
unsigned long timerdisp = 0;
int delaymessage = 3000;
unsigned long timermessage = 0;
unsigned long timersave = 0;
unsigned long timeranim = 0;
int blinkspeed = 20;
int idle = 0;
int helpidx = 0;
int mods = 0;
int cols = 0;
int loopc = 0;
int loopv = 0;
int mode1 = 0;
int mode2 = 0;
int mode2inc = 1;
int delaymode1 = -1;
int delaymode2 = -1;
String msg = "";
int waitmode1 = 100;
int waitmode2 = 100;
int settingMenu = 0;
int compstat = 0;
int defogstat = 0;
int step = 1;
float delta = 2;
int screen = 0;
float lastdegreeC = 0;
float diffdeg = 0;
int lastScreen = 0;
int lastidle = 0;
unsigned long timerconfig = 0;
bool saveconfig = 0;
bool showmessage = false;
bool saveconf = false;
int delaydegree = 25;
int delayvoltage = 25;
int n;
int freezeStat = 0;
int lastfreezeStat = 0;
int lastvalue = 0;
char welcome[16];
int loopanim = 0;

bool confsave = false;

int lastdefogstat = 0;

float tempSet = 10;
int delayButton = 150;
float tempCurr = 0;
int fanSet = 0;
int lastfanSet = 0;

//icon from standard system font
#if LIBRARY_TO_USE == THINKCAD
int icondefog = 26;
int icondegree = 178;
int iconoff = 183;
int iconstb = 29;

int iconbegin = 162;
int iconfinish = 163;
int iconstart = 91;
//lcd.setCursor(1, 0);
int iconflowhead = 188;
//int iconflowfoothead = 184;
int iconflowfoothead = byte(7);
int iconflowfootdefog = 175;
int iconflowdefog = 174;
int iconflowfoot = 191;

//lcd.write(iconflowhfoot)
int iconend = 93;
int iconcircular = 186;
int iconfrontflow = 221;
int iconblink = 255;
int initpos = 0;
int initposmenu = 0;

#else
int iconstb = 243;
int icondegree = 223;
int iconoff = 235;
int icondefog = 222;
int initpos = 0;
int initposmenu = 0;

int iconbegin = 162;
int iconfinish = 163;
int iconstart = 91;
//lcd.setCursor(1, 0);
int iconflowhead = 188;
//int iconflowfoothead = 184;
int iconflowfoothead = byte(7);
int iconflowfootdefog = 175;
int iconflowdefog = 174;
int iconflowfoot = 191;

//lcd.write(iconflowhfoot)
int iconend = 93;
int iconcircular = 186;
int iconfrontflow = 221;
int iconblink = 255;
#endif



int updates = 0;



float voltage, degreeC, degreeF;

char shows[] = "                ";

const int btnUpTemp = 13;   //pin 7 temp up
const int btnDownTemp = 10; //pin 10 temp down

const int btnUpFan = 9;   //pin 9 fan up
const int btnDownFan = 8; //pin 8 fan down

const int btnComp = 7; //pin 7 fan down

const int btnDefogg = 6; //pin 6 fan down

const int tempPin = A0;
const int buttonPin = A1;
const int radiatorPin = A3;
int buttonIndex = 0;


int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


// Variables will change:
int ledState = HIGH; // the current state of the output pin

int lastButtonStateComp = LOW; // the previous reading from the input pin
// the current reading from the input pin
int lastButtonStateDefogger = LOW; // the previous reading from the input pin

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 0;    // the debounce time; increase if the output flickers

//Arduino
//const int RELAYCOMP = 11;
//const int RELAYDEFOG = 10;

//Arduino
#if LIBRARY_TO_USE == THINKCAD
//Thinkcad
const int RELAYCOMP = 13;
const int RELAYDEFOG = 5;//10;
#else
//Thinkcad
const int RELAYCOMP = 11;
const int RELAYDEFOG = 5;//10;
#endif

const int RELAYFAN0 = 10;
const int RELAYFAN1 = 9;
const int RELAYFAN2 = 8;
const int RELAYFAN3 = 7;
const int RELAYFAN4 = 6;
const int SPEAKER_PIN = 12;

/*
  const int buttonTones[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
  };
*/

int buttonPress = 0;
int startPlay = 0;

int btnStateUpTemp = 0;
int btnStateDownTemp = 0;

int lastbtnStateUpTemp = 0;
int lastbtnStateDownTemp = 0;

int btnStateUpFan = 0;
int buttonStateUpFan = 0;
int btnStateDownFan = 0;
int buttonStateDownFan = 0;

int btnStateComp = 0;
int buttonStateComp = 0;
int btnStateDefogg = 0;
int buttonStateDefogg = 0;

int btnStateMode1 = 0;
int buttonStateMode1 = 0;
int lastButtonStateMode1 = 0;

int btnStateMode2 = 0;
int buttonStateMode2 = 0;
int lastButtonStateMode2 = 0;

int btnStateSetting = 0;
int buttonStateSetting = 0;
int lastbuttonStateSetting = 0;

int buttonStateDownTemp = 0;
int lastButtonStateDownTemp = 0;
int buttonStateUpTemp = 0;
int lastButtonStateUpTemp = 0;

float adjTemp = 0;


byte up[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00000
};

byte down[] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
  B00000

};


byte ac[] = {B01000, B10100, B11100, B10100, B00011, B00100, B00100, B00011};

byte acon[] = { B00110,
                B11001,
                B00000,
                B11001,
                B00110,
                B00000,
                B11001,
                B00110
              };

/*
  byte acons[] = {   B00000,
  B00000,
  B10101,
  B01110,
  B11011,
  B01110,
  B10101,
  B00000
  };
*/


//byte aconold[] = {B00000, B00101, B01010, B00000, B00101, B01010, B00000, B01111};

//byte off[] = {B01110, B01010, B01110, B00000, B11011, B10010, B11011, B10010};

byte headfoot[] = {B11011, B00011, B00001, B10001, B01011, B00010, B01100, B00000};

byte fanicon[8] = {B00000, B01010, B10101, B01110, B10101, B01010, B00000, B11111};

byte tempicon[] = {B00100, B01010, B01010, B01110, B01110, B11111, B11111, B01110};

byte defogger[] = {B00000, B00000, B01110, B10001, B10001, B11111, B00000, B00000};





#if LIBRARY_TO_USE == THINKCAD
//thinkcad use
void setup()
{

  Serial.begin(115200);

  pinMode(RELAYCOMP, OUTPUT);

  pinMode(RELAYDEFOG, OUTPUT);

  pinMode(RELAYFAN1, OUTPUT);
  pinMode(RELAYFAN2, OUTPUT);
  pinMode(RELAYFAN3, OUTPUT);
  pinMode(RELAYFAN4, OUTPUT);
  pinMode(RELAYFAN0, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.createChar(0, up);
  lcd.createChar(1, down);
  lcd.createChar(2, tempicon);
  lcd.createChar(3, fanicon);
  lcd.createChar(4, ac);
  lcd.createChar(5, defogger);
  lcd.createChar(6, acon);
  lcd.createChar(7, off);

  /*
    for (int i=0;i<255;i++){
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(char(i));
    }
  */

  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  getSaved();
  screen = 1;
  timerBT = millis();
}
#else
//arduino use
void setup()
{

  Serial.begin(9600);
#if LIBRARY_TO_USE == ARDU
  bt.begin(9600);
  //monitor.begin(9600);
  //Serial.begin(9600);
#endif

#if LIBRARY_TO_USE == ARDU
  lcd.begin();
#else
  lcd.begin(16, 2);
#endif
  lcd.backlight();
  lcd.home();
  lcd.clear();


  digitalWrite(RELAYDEFOG, 1);
  digitalWrite(RELAYFAN0, 1);
  digitalWrite(RELAYCOMP, 1);
  digitalWrite(RELAYFAN1, !LOW);
  digitalWrite(RELAYFAN2, !LOW);
  digitalWrite(RELAYFAN3, !LOW);
  digitalWrite(RELAYFAN4, !LOW);

  pinMode(RELAYCOMP, OUTPUT);

  pinMode(RELAYDEFOG, OUTPUT);

  pinMode(RELAYFAN1, OUTPUT);
  pinMode(RELAYFAN0, OUTPUT);
  pinMode(RELAYFAN2, OUTPUT);
  pinMode(RELAYFAN3, OUTPUT);
  pinMode(RELAYFAN4, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.createChar(0, up);
  lcd.createChar(1, down);
  lcd.createChar(2, tempicon);
  lcd.createChar(3, fanicon);
  lcd.createChar(4, ac);
  lcd.createChar(5, defogger);
  lcd.createChar(6, acon);
  lcd.createChar(7, headfoot);

  setIconFan(0);

  getSaved();

  sendToBT("init", String(0, 0));


  setIconMode2();
  lastScreen = -1;
  screen = 0;
}
#endif

void sendToBT(String com, String values) {
#if LIBRARY_TO_USE == ARDU
  //Serial.print("BT Status");
  //Serial.println(bt.available());
  //if (bt.available()){

  bt.print(com);
  bt.print(values);
  bt.print("#");
  // }
#endif
}


void sendToMonitor(String com, String values) {
#if LIBRARY_TO_USE == ARDU
  //Serial.print("BT Status");
  //Serial.println(bt.available());
  //if (bt.available()){

  Serial.print(com);
  Serial.print(values);
  Serial.print("#");
  // }
#endif
}



void playSound() {

  if ( startPlay == 1) {
    //lcd.noBacklight();
    //Serial.println("sound on");
    //tone(SPEAKER_PIN, 2000);
    startPlay = 0;
  } else {
    //lcd.backlight();
    //Serial.println("sound off");
    //noTone(SPEAKER_PIN);

  }

}

/*
  char tfan[]= "FAN";
  char ttemp[] = "TEMP";
  char ttempset[] = "TEMPSET";
*/

void sendDataMonitor() {
#if LIBRARY_TO_USE == ARDU
  if (!dataMonitor  && ( coolant != 0 || bat != 0 )) {
    //Serial.println("Send data BT");
    dataMonitor = true;
    sendToMonitor("FAN:", String(fanSet));
    //sendToBT(tfan, String(fanSet));
    sendToMonitor("TEMP:", String(tempCurr, 1));
    //sendToBT(ttemp, String(tempCurr, 1));
    sendToMonitor("TEMPSET:", String(tempSet, 1));
    //sendToBT(ttempset, String(tempSet, 1));
    sendToMonitor("FREEZE:", String(freezeStat));
    sendToMonitor("DEFOG:", String(defogstat));
    sendToMonitor("MODE1:", String(mode1));
    sendToMonitor("MODE2:", String(mode2));
    sendToMonitor("COOLANT:", String(coolant, 1));
    sendToMonitor("COMPSTAT:", String(compstat));
    sendToMonitor("BAT:", String(bat, 1));

    //sendToMonitor("LAT:", String(lati, 5));
    //sendToMonitor("LNG:", String(lngt, 5));
    //sendToMonitor("DATE:", dates);
    //sendToMonitor("TIME:", times);
    //sendToMonitor("SPD:", String(spd));
    //sendToMonitor("ODO:", String(odo));
    //sendToMonitor("SAT:", String(sat));
    //sendToMonitor("GPRS:", String(gprs));
    dataMonitor = false;

  }
#endif
}

void sendDataBT() {
#if LIBRARY_TO_USE == ARDU
  if (!dataBT) {
    //Serial.println("Send data BT");
    dataBT = true;
    sendToBT("FAN:", String(fanSet));
    //sendToBT(tfan, String(fanSet));
    sendToBT("TEMP:", String(tempCurr, 1));
    //sendToBT(ttemp, String(tempCurr, 1));
    sendToBT("TEMPSET:", String(tempSet, 1));
    //sendToBT(ttempset, String(tempSet, 1));
    sendToBT("FREEZE:", String(freezeStat));
    sendToBT("DEFOG:", String(defogstat));
    sendToBT("MODE1:", String(mode1));
    sendToBT("MODE2:", String(mode2));
    sendToBT("COOLANT:", String(coolant, 1));
    sendToBT("COMPSTAT:", String(compstat));
    sendToBT("BAT:", String(bat, 1));
    dataBT = false;

  }
#endif
}


String getStringPartByNr(String data, char separator, int index) {
  int stringData = 0;        //variable to count data part nr
  String dataPart = "";      //variable to hole the return text

  for (int i = 0; i < data.length() - 1; i++) { //Walk through the text one letter at a time
    if (data[i] == separator) {
      //Count the number of times separator character appears in the text
      stringData++;
    } else if (stringData == index) {
      //get the text when separator is the rignt one
      dataPart.concat(data[i]);
    } else if (stringData > index) {
      //return text and stop if the next separator appears - to save CPU-time
      return dataPart;
      break;
    }
  }
  //return text if this is the last part
  return dataPart;
}
void splashScreen()
{
}

void displayDegree(int col, int row)
{
  //lcd.setCursor(col, row);
  //lcd.write(byte(3));
  lcd.write(icondegree);
}

void displayIconTemp()
{
  lcd.setCursor(0 + initpos, 1);
  lcd.write(byte(4));
}

void getDegree()
{
  if (loopc >= delaydegree)
  {
    loopc = 0;
    Vo = analogRead(tempPin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
    Tc = T - 273.15;
    Tf = (Tc * 9.0) / 5.0 + 32.0;
    degreeC = Tc;
    //Serial.print("Kelvin = ");
    //Serial.println(T);
    //Serial.print("Last Degree = ");

    //Serial.println(lastdegreeC);
  }
}


void getVoltage()
{


  int Vo;
  float R1 = 10000;
  float logR2, R2, T, Tc, Tf;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


  loopv++;

  if (loopv >= delayvoltage) {
    loopv = 0;

    float offset = 0;
    int volt = analogRead(A2);// read the input
    double voltage = map(volt, 0, 1023, 0, 2500) + offset; // map 0-1023 to 0-2500 and add correction offset

    voltage /= 100; // divide by 100 to get the decimal values
    voltage += 0;
    bat = voltage;
    //Serial.print("Voltage: ");
    //Serial.print(voltage);//print the voltge
    //Serial.println("V");

    Vo = analogRead(A3);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
    Tc = T - 273.15;
    Tf = (Tc * 9.0) / 5.0 + 32.0;
    coolant = Tc; //42.3;

    //Serial.print("Kelvin = ");
    //Serial.println((float)Vo);







  }
}


void setIconMode2() {

  int lvl = 0;

  lvl = mode2;

  /*
    if (mode2 == 0)
      icons = iconflowdefog;
    else if (mode2 == 1)
      icons  = iconflowfootdefog;
    else if (mode2 == 2 )
      icons = iconflowfoot;
    else if ( mode2 == 3 )
      icons = iconflowfoothead;
    else if ( mode2 == 4 )
      icons = iconflowhead;
  */


  if (lvl == 0) {
    // iconflowdefog;
    byte icon[] =  {
      B11101,
      B10101,
      B11101,
      B00001,
      B00001,
      B00010,
      B00100,
      B01000

    };

    lcd.createChar(iconflowfoothead, icon);
  } else  if (lvl == 1) {
    // iconflowfootdefog;
    byte icon[] =  {
      B11101,
      B10101,
      B11101,
      B00001,
      B10001,
      B01010,
      B00100,
      B01000

    };

    lcd.createChar(iconflowfoothead, icon);
  } else  if (lvl == 2) {
    //iconflowfoot;
    byte icon[] =  {
      B00001,
      B00001,
      B00001,
      B10001,
      B01001,
      B00010,
      B01100,
      B00000

    };

    lcd.createChar(iconflowfoothead, icon);
  } else  if (lvl == 3) {
    //iconflowfoothead;
    byte icon[] =  {
      B01101,
      B00001,
      B00001,
      B10001,
      B01001,
      B00010,
      B01100,
      B00000

    };

    lcd.createChar(iconflowfoothead, icon);
  } else  if (lvl == 4) {
    //iconflowhead;
    byte icon[] =  {
      B01101,
      B00001,
      B00001,
      B00001,
      B00001,
      B00010,
      B01100,
      B00000

    };

    lcd.createChar(iconflowfoothead, icon);
  }
}




void setIconFan(int lvl) {

  if (lvl > 0) {
    if (lvl == 4) {
      //4
      byte fanoff1[] =  {
        B10100,
        B10100,
        B11100,
        B00100,
        B00101,
        B00011,
        B01011,
        B11011

      };

      byte fanoff2[] = {
        B00001,
        B00011,
        B01011,
        B11011,
        B11011,
        B11011,
        B11011,
        B11011

      };
      lcd.createChar(3, fanoff1);
      lcd.createChar(1, fanoff2);
    } if (lvl == 3) {
      //3
      byte fanoff1[] =  {
        B11100,
        B00100,
        B11100,
        B00100,
        B11101,
        B00011,
        B01011,
        B11011

      };

      byte fanoff2[] = {
        B00000,
        B00000,
        B01000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11011
      };
      lcd.createChar(3, fanoff1);
      lcd.createChar(1, fanoff2);
    } if (lvl == 2) {
      //2
      byte fanoff1[] =  {
        B11100,
        B00100,
        B11100,
        B10000,
        B11101,
        B00011,
        B01011,
        B11011
      };

      byte fanoff2[] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11011
      };
      lcd.createChar(3, fanoff1);
      lcd.createChar(1, fanoff2);
    } else if (lvl == 1) {
      //1
      byte fanoff1[] =  {
        B11000,
        B01000,
        B01000,
        B01000,
        B11100,
        B00000,
        B01000,
        B11011
      };

      byte fanoff2[] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11011
      };
      lcd.createChar(3, fanoff1);
      lcd.createChar(1, fanoff2);
    }


  } else {

    byte fanoff1[] =  {
      B10100,
      B01000,
      B10100,
      B00000,
      B00000,
      B00000,
      B00000,
      B11011
    };

    byte fanoff2[] = {
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B00000,
      B11011
    };
    lcd.createChar(3, fanoff1);
    lcd.createChar(1, fanoff2);
  }
}


void displayFanIndicator(int lvl)
{
  lcd.setCursor(14 + initpos, 0);
  //showIconFan(lvl);
  lcd.write(byte(3));
  //lcd.write(194);
  // lcd.setCursor(14,0);
  // lcd.write(188);
  //displayNumber(15,1,lvl);
  lcd.setCursor(15 + initpos, 0);
  //if (lvl > 0)
  //  lcd.print(lvl);
  //else
  lcd.write(byte(1));
}

/*
  void displayTempSet()
  {
  float v = tempSet;

  tempSet = ((float)((int)(tempSet * 10))) / 10;

  //V is now equal to 12.3
  lcd.setCursor(0, 0);
  lcd.write(byte(2));
  //lcd.setCursor(1, 0);
  lcd.write( tempSet);
  //lcd.setCursor(2,0);
  lcd.print(tempSet, 1);

  ///if (tempSet > 10 && tempSet < 99)
  //{
  //lcd.setCursor(6, 0);
  //lcd.print(" ");
  //}

  //if (tempSet < 10 && tempSet > 0)
  //{
  //lcd.setCursor(5, 0);
  //lcd.print(" ");
  //}

  displayDegree(7, 0);
  lcd.print("  ");
  }
*/

void displayTempSet()
{
  float v = tempSet;

  tempSet = ((float)((int)(tempSet * 10))) / 10;

  //V is now equal to 12.3
  lcd.setCursor(0 + initpos, 0);
  lcd.write(byte(2));
  //lcd.setCursor(1, 0);
  //lcd.write( tempSet);
  //lcd.setCursor(2,0);
  lcd.print(tempSet, 1);
  displayDegree(7, 0);
  if (tempSet < 10)
  {
    lcd.print("  ");
    //lcd.setCursor(6, 0);
    //lcd.print(" ");
  } else

    if (tempSet > 10 && tempSet < 99)
    {
      lcd.print(" ");
      //lcd.setCursor(5, 0);
      //lcd.print(" ");
    }
}

void displayMode1()
{


  //V is now equal to 12.3
  lcd.setCursor(7 + initpos, 0);
  lcd.write(iconstart);
  //lcd.setCursor(1, 0);
  if (mode1 == 0)
    lcd.write(iconcircular);
  else
    lcd.write(iconfrontflow);


  lcd.write(iconend);
}

void displayMode2()
{
  //V is now equal to 12.3
  lcd.setCursor(10 + initpos, 0);
  lcd.write(iconstart); //162

  int icons = 0;

  if (mode2 == 0)
    icons = iconflowdefog;
  else if (mode2 == 1)
    icons  = iconflowfootdefog;
  else if (mode2 == 2 )
    icons = iconflowfoot;
  else if ( mode2 == 3 )
    icons = iconflowfoothead;
  else if ( mode2 == 4 )
    icons = iconflowhead;
  //lcd.setCursor(1, 0);
  //lcd.write(icons);//188
  //
  lcd.write(iconflowfoothead);
  //lcd.write(iconflowhfoot)



  lcd.write(iconend);//163
}

void displayTempCurrent()
{

  lcd.setCursor(4 + initpos, 1);
  //if (n==2){
  //  lcd.print(" ");
  //}else{

  if (degreeC != lastdegreeC)
  {
    lcd.write(iconbegin);

    diffdeg = degreeC - lastdegreeC;

    //if (degreeC > lastdegreeC)
    lcd.write(byte(0));
    //else if (degreeC < lastdegreeC)
    //  lcd.write(byte(1));
    //else
    //  lcd.print(" ");
    //}
    lcd.setCursor(6 + initpos, 1);

    lcd.print(tempCurr, 1);
    displayDegree(11, 1);
    lcd.write(iconfinish);
    lcd.print("  ");
  }


  lastdegreeC = degreeC;
}

void getVoltages()
{
  int volt = analogRead(A2);// read the input
  //Serial.print("Voltage=");
  //Serial.println(volt * 0.004882814);
  bat = volt * 0.004882814;
  // return (volt * 0.004882814);
}

void animateAC() {

  byte anim1[] = {
    B00111,
    B11000,
    B00000,
    B11000,
    B00111,
    B00000,
    B11000,
    B00111
  };

  byte anim2[] = {
    B00011,
    B11100,
    B00000,
    B11100,
    B00011,
    B00000,
    B11100,
    B00011
  };

  byte anim3[] = {
    B10001,
    B01110,
    B00000,
    B01110,
    B10001,
    B00000,
    B01110,
    B10001
  };

  byte anim4[] = {
    B11000,
    B00111,
    B00000,
    B00111,
    B11000,
    B00000,
    B00111,
    B11000
  };

  byte anim5[] = {
    B11100,
    B00011,
    B00000,
    B00011,
    B11100,
    B00000,
    B00011,
    B11100
  };

  byte anim6[] = {
    B01110,
    B10001,
    B00000,
    B10001,
    B01110,
    B00000,
    B10001,
    B01110
  };


  // uint8_t icons[8] = {0};



  if (loopanim == 0) {
    lcd.createChar(6, anim1);
    /*
      for (int i = 0; i <= 8; i++) {
      icons[i] = anim1[i];
      lcd.createChar(6, icons);
      }
    */

  } else if (loopanim == 1) {
    lcd.createChar(6, anim2);
    /*
      for (int i = 0; i <= 8; i++) {
      icons[i] = anim2[i];
      lcd.createChar(6, icons);
      }
    */
  } else     if (loopanim == 2) {
    lcd.createChar(6, anim3);
    /*
      for (int i = 0; i <= 8; i++) {
      icons[i] = anim3[i];
      lcd.createChar(6, icons);
      }
    */

  } else if (loopanim == 3) {
    lcd.createChar(6, anim4);
    /*
      for (int i = 0; i <= 8; i++) {
      icons[i] = anim4[i];
      lcd.createChar(6, icons);
      }
    */
  } else if (loopanim == 4) {
    lcd.createChar(6, anim5);
    /*
      for (int i = 0; i <= 8; i++) {
      icons[i] = anim5[i];
      lcd.createChar(6, icons);
      }
    */
  } else if (loopanim == 5) {
    lcd.createChar(6, anim6);
    /*
      for (int i = 0; i <= 8; i++) {
      icons[i] = anim6[i];
      lcd.createChar(6, icons);
      }
    */
  }

}

void displayCompStat()
{
  lcd.setCursor(0 + initpos, 1);
  //lcd.write(4);
  lcd.print("");
  int bytes;
  int col = 0;
  lcd.setCursor(0 + initpos, 1);
  for (int x = 0; x < 2; x++)
  {
    col++;

    if (compstat == 1 && fanSet > 0)
    {
      if (freezeStat == 1)
      {
        if (col == 1)
          lcd.write(4);
        //lcd.print(" on ");
        //lcd.write(26);
        //lcd.print("A/C");
        lcd.write(6);
        triggerComp();
      }
      else
      {
        if (col == 1)
          lcd.write(4);
        //lcd.print("A/C");
        lcd.write(iconstb);
        //lcd.print(" ]");
        triggerComp();
      }
    }
    else
    {
      freezeStat = 0;
      //lcd.write(byte(6));
      if (col == 1)
      {
        if (compstat == 1)
        {
          if (col == 1)
            lcd.write(4);
          // lcd.print("A/C");
          lcd.write(127);
        }
        else
        {
          //lcd.write(iconoff);
          lcd.print("   ");
        }
        triggerComp();
        //lcd.print(" off");
      }
      else
      {
        lcd.print(" ");
      }
      triggerComp();
    }
  }

}

void displayDefogger()
{
  lcd.setCursor(14 + initpos, 1);
  if (defogstat == 1)
  {
    lcd.write(5);
    lcd.setCursor(15 + initpos, 1);
    lcd.write(icondefog);
  }
  else
  {
    //lcd.setCursor(15,1);
    //lcd.setCursor(15,1);
    //lcd.write(183);
    lcd.print("  ");
  }

}

int lastbtnStateDownFan = 0;
int lastbtnStateUpFan = 0;

void checkThreshold()
{

  if (tempSet + delta < tempCurr)
  {
    freezeStat = 1;
  }
  else if (tempSet >= tempCurr)
  {
    freezeStat = 0;
  }
}

void triggerComp()
{
  if (lastfreezeStat != freezeStat)
  {
    digitalWrite(RELAYCOMP, !freezeStat);
    lastfreezeStat = freezeStat;
    //if (freezeStat == 1)
    //  Serial.println("Compressor Active");
    //else
    //  Serial.println("Compressor Inactive");
  }
}

void triggerMode1()
{
  if (delaymode1 == 0 )
  {
    //digitalWrite(RELAYCOMP, !freezeStat);

    //Serial.println("Change Mode1");
    delaymode1 = -1;
  } else if (delaymode1 > 0) {
    delaymode1--;

  }
}

void triggerMode2()
{
  if (delaymode2 == 0 )
  {
    //digitalWrite(RELAYCOMP, !freezeStat);

    //Serial.println("Change Mode2");
    delaymode2 = -1;
  } else if (delaymode2 > 0) {
    delaymode2--;

  }
}

void triggerDefogger()
{
  if (lastdefogstat != defogstat)
  {
    digitalWrite(RELAYDEFOG, !defogstat);
    lastdefogstat = defogstat;
    // if (defogstat == 1)
    //Serial.println("Defogger Active");
    // else
    //Serial.println("Defogger Inactive");
  }
}

void triggerFan()
{
  if (lastfanSet != fanSet)
  {
    setIconFan(fanSet);
    digitalWrite(RELAYFAN1, !LOW);
    digitalWrite(RELAYFAN2, !LOW);
    digitalWrite(RELAYFAN3, !LOW);
    digitalWrite(RELAYFAN4, !LOW);
    digitalWrite(RELAYFAN0, 1);
    lastfanSet = fanSet;

    if (fanSet == 1)
      digitalWrite(RELAYFAN1, !HIGH);
    else if (fanSet == 2)
      digitalWrite(RELAYFAN2, !HIGH);
    else if (fanSet == 3)
      digitalWrite(RELAYFAN3, !HIGH);
    else if (fanSet == 4)
      digitalWrite(RELAYFAN4, !HIGH);

    if (fanSet > 0)
    {
      digitalWrite(RELAYFAN0, 0);
      //Serial.print("Fan Set to ");
      //Serial.println(fanSet);
    }
    //else
    // {
    //   Serial.print("Fan inactive ");
    //}
  }
}

void getStateComp()
{
  int reading = buttonStateComp;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonStateComp)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != btnStateComp)
    {
      btnStateComp = reading;

      // only toggle the LED if the new button state is HIGH
      if (btnStateComp == HIGH)
      {
        startPlay = 1;
        compstat = !compstat;


        if (compstat == 1 ) {
          if ( fanSet == 0 ) {
            fanSet = 1;
            triggerFan();
          }
        }
        //  compstat = 0;
        //else
        //  compstat = 1;
      }
    }
  }

  lastButtonStateComp = reading;
}

void getStateDefogger()
{
  int reading = buttonStateDefogg;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonStateDefogger)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != btnStateDefogg)
    {
      btnStateDefogg = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonStateDefogg == HIGH)
      {
        defogstat = !defogstat;
        triggerDefogger();
      }
    }
  }

  lastButtonStateDefogger = reading;
}

void getStateUpFan()
{
  int reading = buttonStateUpFan;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastbtnStateUpFan)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != btnStateUpFan)
    {

      btnStateUpFan = reading;

      // only toggle the LED if the new button state is HIGH
      if (btnStateUpFan == HIGH)
      {
        startPlay = 1;
        fanSet += 1;
        if (fanSet > 4)
          fanSet = 4;

        triggerFan();
      }
    }
  }

  lastbtnStateUpFan = reading;
}

void getStateDownFan()
{
  int reading = buttonStateDownFan;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastbtnStateDownFan)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != btnStateDownFan)
    {
      btnStateDownFan = reading;

      // only toggle the LED if the new button state is HIGH
      if (btnStateDownFan == HIGH)
      {
        startPlay = 1;
        fanSet -= 1;
        lastbtnStateDownFan = reading;
      }
      if (fanSet < 0) {
        fanSet = 0;
      }

      if (fanSet <= 0) {
        compstat = 0;
      }

      triggerFan();
    }
  }
  lastbtnStateDownFan = reading;
}

void getStateMode2()
{
  int reading = buttonStateMode2;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonStateMode2)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != btnStateMode2)
    {
      btnStateMode2 = reading;

      // only toggle the LED if the new button state is HIGH
      if (btnStateMode2 == HIGH)
      {
        mode2 += mode2inc;
        //Serial.print("Mode 2 = ");
        //Serial.println(mode2);

        if ( mode2 > 4) {
          mode2 = 3;
          mode2inc = -1;
        } else if (mode2 < 0 ) {
          mode2 = 1;
          mode2inc = 1;
        }
        setIconMode2();

        timersave = millis();
        saveconfig = true;
        //putEEPROM();

        lastButtonStateMode2 = reading;
        delaymode2 = waitmode2;
      }

    }
  }
  lastButtonStateMode2 = reading;
}


void getStateMode1()
{
  int reading = buttonStateMode1;

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonStateMode1)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != btnStateMode1)
    {
      //Serial.println("Mode1");
      btnStateMode1 = reading;

      // only toggle the LED if the new button state is HIGH
      if (btnStateMode1 == HIGH)
      {
        mode1++;

        if ( mode1 > 1)
          mode1 = 0;

        timersave = millis();
        saveconfig = true;
        //putEEPROM();

        lastButtonStateMode1 = reading;
      }

      delaymode1 = waitmode1;
    }
  }
  lastButtonStateMode1 = reading;
}

void showHelp(char help[])
{

  if (idle % scrollhelp != 0)
  {
  }
  else
  {

    int size = strlen(help);
    int helps = helpidx + (15 + helpidx);
    int h = helpidx;
    lcd.setCursor(0 + initpos, 0);
    //Serial.print("Length help = ");
    // Serial.println(help);

    for (int j = 0; j < 15; j++)
    {
      if (size > h)
      {
        //lcd.setCursor(j,0);
        shows[j] = help[h];
        //lcd.write(help[h]);
      }
      else
      {
        shows[j] = char(32);
        //lcd.write(" ");
      }
      h++;
    }
    lcd.print(shows);
    //delay(50);
    helpidx++;
    if (helpidx > size)
    {
      helpidx = 0;
      idle = 0;
    }
  }
}

void showMessage() {
  lcd.setCursor(0 + initpos, 0);
  lcd.print(msg);
  lcd.setCursor(1 + initpos, 1);
  lcd.print("                    ");
}

void clearscreen() {
  lcd.setCursor(0 + initpos, 0);
  lcd.print("                ");
  lcd.setCursor(0 + initpos, 1);
  lcd.print("                ");
}

void showSettingScreen()
{

  btnStateDownTemp = buttonStateDownTemp; //digitalRead(btnDownTemp);
  btnStateUpTemp = buttonStateUpTemp;     //digitalRead(btnUpTemp);
  btnStateDownFan = buttonStateDownFan;
  btnStateUpFan = buttonStateUpFan;

  if (lastScreen != screen)
  {
    helpidx = 0;
    lcd.clear();
    lcd.setCursor(0 + initposmenu, 0);
    n = 0;
    idle = 0;
  }

  n++;

  //if (n > 100 ){
  //if ( millis() - lastidle )
  idle++;
  //}

  if (settingMenu > 3) {
    if (  millis() - timermessage < delaymessage && showmessage) {
      showMessage();
    } else {
      showmessage = false;
      screen = -1;
      //screen = 1;
      //lcd.clear();
      //settingMenu = 0;
    }
  }


  //-------------------------------- Display To Screen  ----------------------------------
  if (settingMenu == 0)
  {
    //Delta Setting
    char help[] = "Use Button Temp [Up] and [Down] to change setting value";

    lcd.setCursor(0 + initposmenu, 0);
    if (idle < waithelp)
      lcd.print("Setting : Delta ");
    else
      showHelp(help);
    lcd.setCursor(0 + initposmenu, 1);
    lcd.print("Delta :");
    lcd.setCursor(7 + initposmenu, 1);
    lcd.print(delta, 1);
    lcd.print("          ");
  }
  else if (settingMenu == 1)
  {
    //Adjust Setting
    char help[] = "Use Button Temp [Up] and [Down] to change setting value";
    lcd.setCursor(0 + initposmenu, 0);

    if (idle < waithelp)
      lcd.print("Setting : Adjust Temp");
    else
      showHelp(help);

    float adjT = degreeC + adjTemp;
    lcd.setCursor(0 + initposmenu, 1);
    lcd.print("Temp  :");
    lcd.setCursor(7 + initposmenu, 1);
    lcd.print(adjT, 1);
    lcd.print("          ");
  }
  else if (settingMenu == 2)
  {
    char help[] = "Use Button Temp [Up] and [Down] to change letter, Button Fan [Up] and [Down] for move cursor";
    lcd.setCursor(0 + initposmenu, 0);
    if (idle < waithelp)
      lcd.print("Setting:Greeting");
    else
      showHelp(help);

    // Welcome Message
    //lcd.blink();
    //lcd.setCursor(cols, 1);
    lcd.setCursor(0 + initposmenu, 1);
    //char welc[16];
    for (int i = 0; i < 16; i++)
    {
      //lcd.setCursor(i, 1);
      int byt = (int)welcome[i];

      if (i == cols)
      {
        //lcd.setCursor(i, 1);
        if (mods == 0)
        {
          //lcd.noBlink();
          //delay(1000);
          // lcd.blink();
          //Serial.println("blink");
          lcd.write(welcome[cols]);
        }
        else
        {
          //lcd.write(welcome[cols]);
          //lcd.noBlink();
          //delay(1000);
          //lcd.blink();
          //Serial.println("no blink");
          lcd.write(iconblink);
        }
      }
      else
      {
        if (byt < 32 || byt > 155)
        {
          //welc[i] = char(32);
          lcd.write(byte(32));
        }
        else
        {
          lcd.write(welcome[i]);
          //welc[i] = welcome[i];
        }
      }
    }

    //lcd.print(welcome);

    //lcd.blink();
    //delay(50);

    if (n >= blinkspeed)
    {
      n = 0;
      if (mods == 0)
        mods = 1;
      else
        mods = 0;

      //lcd.blink();
      //lcd.setCursor(cols - 1, 1);
      //delay(50);
      //lcd.noBlink();
      /*
        if (mods == 0)
        {
        lcd.noBlink();
        //delay(1000);
        lcd.blink();
        //Serial.println("blink");
        lcd.write(welcome[cols]);
        }
        else
        {
        //lcd.write(welcome[cols]);
        lcd.noBlink();
        //delay(1000);
        lcd.blink();
        //Serial.println("no blink");
        lcd.write(byte(0));
        }
      */
    }
  } else if (settingMenu == 3)
  {
    //Adjust Setting
    char help[] = "Use Button Temp [Up] and [Down] to change [Yes] or [No]";
    lcd.setCursor(0 + initposmenu, 0);

    if (idle < waithelp)
      lcd.print("Confirmation :  ");
    else
      showHelp(help);


    //
    // Serial.print("Menu Conf");
    lcd.setCursor(0 + initposmenu, 1);
    lcd.print(" Save ? : ");
    lcd.print((confsave ? "[Yes]" : "[No]"));
    lcd.print("                     ");
  }
  //-------------------------- End of Display Screen ----------------------------//

  //--------------------------- Button Handling ----------------------------------//

  if (buttonStateSetting != lastbuttonStateSetting)
  {
    if (buttonStateSetting == HIGH)
    {
      n = 0;
      screen = 3;
      settingMenu++;
      helpidx = 0;
      idle = 0;

      if (settingMenu > 3)
      {
        if (confsave) {
          confsave = false;
          //saveconfig = true;
          putEEPROM();
          showmessage = true;
          msg = " Setting Saved  ";
          timermessage = millis();


          //Serial.println("Save Setting custom object from EEPROM: ");
          //  tempSet = EEPROM.read(0);
          //Serial.print("Data tempSet= ");
          //Serial.println(tempSet);

          //  delta = EEPROM.read(3);
          //Serial.print("Delta= ");
          // Serial.println(delta);

          //  adjTemp = EEPROM.read(5);
          //Serial.print("adj= ");
          //Serial.println(adjTemp);

          //Serial.print("welc = ");
          //Serial.println(welcome);

          getEEPROM();

          //Serial.println("After Save Setting custom object from EEPROM: ");
          //  tempSet = EEPROM.read(0);
          //Serial.print("Data tempSet= ");
          //Serial.println(tempSet);

          //  delta = EEPROM.read(3);
          //Serial.print("Delta= ");
          //Serial.println(delta);

          //  adjTemp = EEPROM.read(5);
          //Serial.print("adj= ");
          //Serial.println(adjTemp);

          //Serial.print("welc = ");
          //Serial.println(welcome);
        } else {
          if (!showmessage) {
            //lcd.clear();

            initpos = 16;
            showSlide();
            screen = -1;
            settingMenu = 0;
          }
        }
      }

      if (settingMenu != 0)
        delay(400);
    }
    lastbuttonStateSetting = buttonStateSetting;
  }

  //if (btnStateDownTemp != lastbtnStateDownTemp || settingMenu == 2)
  //{

  if (btnStateDownTemp == HIGH)
  {

    //lastDebounceTime = millis();

    if ((millis() - lastDebounceTime) > delayButton)
    {
      startPlay = 1;

      // decrease temp
      if (settingMenu == 0)
      {
        delta -= 0.5;
        // Serial.print("Set Delta :");
        //Serial.println(delta);
        //EEPROM.update(3, delta);
      }
      else if (settingMenu == 2)
      {
        int byt = (int)welcome[cols];
        byt--;
        if (byt < 32 || byt > 155)
          byt = 32;

        if (byt < 32)
          byt = 32;
        welcome[cols] = char(byt);
      } else if (settingMenu == 3) {
        confsave = !confsave;
        //Serial.print("Set Delta :");
        //Serial.println(delta);
        //EEPROM.update(3, delta);
      }
      else
      {
        adjTemp -= 0.1;
        //EEPROM.update(5, adjTemp);
        //Serial.print("Set Adjust :");
        //Serial.println(adjTemp);
      }
      //delay(20);
      lastDebounceTime = millis();
    }
  }
  //}

  //if (btnStateUpTemp != lastbtnStateUpTemp || settingMenu == 2)
  //{
  if (btnStateUpTemp == HIGH)
  {

    if ((millis() - lastDebounceTime) > delayButton)
    {
      //Serial.println("TempUp");
      startPlay = 1;
      if (settingMenu == 0)
      {
        delta += 0.5;
        //Serial.print("Set Delta :");
        //Serial.println(delta);
        //EEPROM.update(3, delta);
      }
      else if (settingMenu == 2)
      {
        int byt = (int)welcome[cols];
        byt++;
        if (byt < 32 || byt > 155)
          byt = 32;

        if (byt > 155)
          byt = 155;

        welcome[cols] = char(byt);
      } else if (settingMenu == 3)
      {
        confsave = !confsave;

        //Serial.print("Set Conf Save :");
        //Serial.println(confsave);
        //EEPROM.update(3, delta);
      }
      else
      {
        adjTemp += 0.1;
        //EEPROM.update(5, adjTemp);
        //Serial.print("Set Adjust :");
        //Serial.println(adjTemp);
      }
      //delay(50);
      lastDebounceTime = millis();
    }
  }
  lastbtnStateUpTemp = btnStateUpTemp;
  //}

  if (btnStateDownFan != lastbtnStateDownFan || settingMenu == 2)
  {
    if (btnStateDownFan == HIGH)
    {

      if ((millis() - lastDebounceTime) > delayButton)
      {
        // decrease temp
        if (settingMenu == 2)
        {
          cols--;

          if (cols < 0)
            cols = 0;
          n = 10;
          mods = 0;
          //delta -= 0.5;
          //Serial.print("Set Delta :");
          //Serial.println(delta);
          //EEPROM.update(3, delta);
        }
        //delay(200);
        lastDebounceTime = millis();
      }
    }
    lastbtnStateDownFan = btnStateDownFan;
  }

  if (btnStateUpFan != lastbtnStateUpFan || settingMenu == 2)
  {
    if (btnStateUpFan == HIGH)
    {

      if ((millis() - lastDebounceTime) > delayButton)
      {
        if (settingMenu == 2)
        {
          cols++;

          if (cols > 14)
            cols = 14;
          n = 10;
          mods = 0;
          //delta += 0.5;
          // Serial.print("Set Delta :");
          //  Serial.println(delta);
          //EEPROM.update(3, delta);
        }
        //delay(200);
        lastDebounceTime = millis();
      }
    }
    lastbtnStateUpFan = btnStateUpFan;
  }

  //delay(200);
  lastidle = millis();
}


void animateIcon(int offset) {
  uint8_t icons[8] = {0};


  if ( diffdeg < 0 ) {
    if (loopanim % 2 == 0) {
      for (int i = 0; i <= 8; i++) {
        icons[i] = down[i];
        lcd.createChar(offset, icons);

      }
    } else {
      for (int i = 0; i <= 8; i++) {
        icons[i] = 0;
        lcd.createChar(offset, icons);

      }
    }
  } else {
    if (loopanim % 2 == 0) {
      for (int i = 7; i >= (0); i--) {
        icons[i] = up[i];
        lcd.createChar(offset, icons);

      }
    } else {
      for (int i = 7; i >= 0; i--) {
        icons[i] = 0;
        lcd.createChar(offset, icons);

      }
    }

  }
}

void showMainScreen()
{
  if (millis() - timeranim > 500 ) {
    loopanim++;

    if (loopanim > 5)
      loopanim = 0;

    timeranim = millis();
    animateIcon(0);
    animateAC();
    //animateIcon(down, 1, 0);

  }

  settingMenu = 0;
  if (lastScreen != screen)
  {
    if (screen >= 0) {
      lcd.clear();
      lcd.setCursor(0 + initpos, 0);
    }
    lastdegreeC = 0;
    loopc = delaydegree;
    loopv = delayvoltage;
  }
  // voltage = getVoltage(tempPin);
  // degreeC = (voltage - 0.5 ) * (100.0);
  // degreeF = degreeC * (9.0 / 5.0 ) + 32;

  btnStateDownTemp = buttonStateDownTemp; //digitalRead(btnDownTemp);
  btnStateUpTemp = buttonStateUpTemp;     //digitalRead(btnUpTemp);

  getStateComp();
  getStateDefogger();
  getStateUpFan();
  getStateDownFan();
  getDegree();
  getVoltage();
  getStateMode1();
  getStateMode2();

  // if (buttonStateSetting != lastbuttonStateSetting) {
  if (buttonStateSetting == HIGH)
  {
    //initposmenu = 16;
    n = 0;
    screen = 3;
    showSlide();
    settingMenu = 0;
    //tempSet -= 0.5;
    //customVar.tempSet = tempSet;
    //EEPROM.put(0, customVar);
    //Serial.print("Menu Setting Selected ");
    delay(100);
  }
  lastbuttonStateSetting = buttonStateSetting;
  //}

  // if (btnStateDownTemp != lastbtnStateDownTemp) {
  if (btnStateDownTemp == HIGH)
  {
    if ((millis() - lastDebounceTime) > delayButton)
    {
      startPlay = 1;
      // decrease temp
      tempSet -= 0.5;
      //customVar.tempSet = tempSet;
      timersave = millis();
      saveconfig = true;
      //putEEPROM();
      //EEPROM.put(0, customVar);
      lastDebounceTime = millis();
    }
  }
  lastbtnStateDownTemp = btnStateDownTemp;
  //}

  //if (btnStateUpTemp != lastbtnStateUpTemp)
  //{
  if (btnStateUpTemp == HIGH)
  {

    if ((millis() - lastDebounceTime) > delayButton)
    {
      startPlay = 1;

      // decrease temp
      tempSet += 0.5;
      timersave = millis();
      saveconfig = true;
      //putEEPROM();
      //delay(100);
      lastDebounceTime = millis();
    }
  }
  lastbtnStateUpTemp = btnStateUpTemp;
  //}

  /*
    if (btnStateUpTemp != lastbtnStateUpTemp) {
    if (btnStateUpTemp == HIGH){
    // decrease temp
    tempSet += 0.5;
    EEPROM.update(0, tempSet);
    int temps = EEPROM.read(0);
    Serial.print("Data tempSet= ");
    Serial.println(temps);
    delay(20);
    }
    lastbtnStateUpTemp = btnStateUpTemp;
    }
  */

  tempCurr = degreeC + adjTemp;

  checkThreshold();
  displayTempSet();
  displayMode1();
  displayMode2();
  displayFanIndicator(fanSet);
  displayTempCurrent();
  displayCompStat();
  displayDefogger();
  triggerMode1();
  triggerMode2();

  step++;
  step = step % 2;

  if (step == 1)
    n++;

  if (n > 2)
    n = 0;

  //delay(100);

  //tempCurr = degreeC;
}

void showSplashScreen()
{
  if (lastScreen != screen)
  {
    lcd.setCursor(0, 0);
    lastScreen - screen;
    n = 0;
  }
  n++;

  if (n == 1)
  {
    lcd.print(welcome);

    for (int positionCounter = 0; positionCounter < 16; positionCounter++)
    {
      int buttonValue = analogRead(A1);

      getRangeButton(buttonValue);

      if (buttonPress == 1)
        break;
      //  // scroll one position left:
      lcd.scrollDisplayRight();
      //  // wait a bit:
      //  delay(150);
    }

    if (buttonPress == 0) {
      for (int positionCounter = 0; positionCounter < 16; positionCounter++)
      {
        int buttonValue = analogRead(A1);

        getRangeButton(buttonValue);
        if (buttonPress == 1)
          break;
        // scroll one position left:
        lcd.scrollDisplayLeft();
        // wait a bit:
        delay(80);
      }
    }

    //delay(1000);
    // to move it back to center:
    //for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    //  // scroll one position left:
    //  lcd.scrollDisplayLeft();
    //  // wait a bit:
    // delay(150);
    //}
    if (buttonPress == 0)
      delay(1000);
  }

  int buttonValue = analogRead(A1);
  getRangeButton(buttonValue);


  if (n > 1 || buttonPress == 1)
  {
    n = 0;
    //lcd.clear();
    screen = -1;
    initpos = 16;
  }
  //delay(200);
}



void showInitialMain()
{
  if (lastScreen != screen)
  {
    //   lcd.setCursor(0, 0);
    //   lastScreen - screen;
    n = 0;
  }
  n++;

  if (n == 1)
  {
    //lcd.print(welcome);

    /*
      for (int positionCounter = 0; positionCounter < 16; positionCounter++)
      {
       int buttonValue = analogRead(A1);

       getRangeButton(buttonValue);

       if (buttonPress == 1)
         break;
       //  // scroll one position left:
       lcd.scrollDisplayRight();
       //  // wait a bit:
       //  delay(150);
      }
    */

    //if (buttonPress == 0) {
    for (int positionCounter = 0; positionCounter < 16; positionCounter++)
    {
      // int buttonValue = analogRead(A1);

      //getRangeButton(buttonValue);
      //if (buttonPress == 1)
      //  break;
      // scroll one position left:
      lcd.scrollDisplayLeft();
      // wait a bit:
      delay(50);
    }
    //}

    //delay(1000);
    // to move it back to center:
    //for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    //  // scroll one position left:
    //  lcd.scrollDisplayLeft();
    //  // wait a bit:
    // delay(150);
    //}
    //if (buttonPress == 0)
    delay(500);
  }

  //int buttonValue = analogRead(A1);
  //getRangeButton(buttonValue);


  if (n > 1 )
  {
    n = 0;
    lcd.clear();
    screen = 1;
    initpos = 0;
  }
  //delay(200);
}


long string_to_long (String number)
{
  number = number + ' ';
  char buf[number.length()];
  //Serial.println(number);
  number.toCharArray(buf, number.length());
  long result = atol(buf);
  //Serial.println(result);
  return result;
}




void showSlide()
{
  if (lastScreen != screen)
  {
    //   lcd.setCursor(0, 0);
    //   lastScreen - screen;
    n = 0;
  }
  n++;

  if (n == 1)
  {
    //lcd.print(welcome);

    /*
      for (int positionCounter = 0; positionCounter < 16; positionCounter++)
      {
       int buttonValue = analogRead(A1);

       getRangeButton(buttonValue);

       if (buttonPress == 1)
         break;
       //  // scroll one position left:
       lcd.scrollDisplayRight();
       //  // wait a bit:
       //  delay(150);
      }
    */

    //if (buttonPress == 0) {
    for (int positionCounter = 0; positionCounter < 16; positionCounter++)
    {
      // int buttonValue = analogRead(A1);

      //getRangeButton(buttonValue);
      //if (buttonPress == 1)
      //  break;
      // scroll one position left:
      lcd.scrollDisplayLeft();
      // wait a bit:
      delay(20);
    }
    //}

    //delay(1000);
    // to move it back to center:
    //for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    //  // scroll one position left:
    //  lcd.scrollDisplayLeft();
    //  // wait a bit:
    // delay(150);
    //}
    //if (buttonPress == 0)
    //delay(500);
  }

  //int buttonValue = analogRead(A1);
  //getRangeButton(buttonValue);


  if (n > 1 )
  {
    n = 0;
    lcd.clear();
    screen = 2;
    initposmenu = 0;
  }
  //delay(200);
}

void getEEPROM()
{
  int pos = 0;
  int addr = 0;

  EEPROM.get(pos, tempSet);

  addr = sizeof(tempSet);
  pos += addr;
  EEPROM.get(pos, delta);

  addr = sizeof(delta);
  pos += addr;
  EEPROM.get(pos, adjTemp);

  addr = sizeof(adjTemp);
  pos += addr;

  char byt;
  int curpos = pos;

  for (int i = 0; i < 16; i++)
  {
    EEPROM.get(pos, byt);
    //Serial.write(byt);
    if (isnan(byt))
    {
      break;
    }
    else
    {
      welcome[i] = byt;
    }
    pos++;
  }

  //addr = sizeof(adjTemp);
  //pos += addr;



  if (pos == curpos)
  {
    char welc[] = "Initializing....";
    memcpy(welcome, welc, 16);
    pos += 16;
    EEPROM.get(pos, mode1);
    pos++;
    EEPROM.get(pos, mode2);
  } else {
    EEPROM.get(pos, mode1);
    pos++;

    EEPROM.get(pos, mode2);
    pos++;
  }
}

void putEEPROM()
{
#if LIBRARY_TO_USE == ARDU
  int pos = 0;
  int addr = 0;

  EEPROM.put(pos, tempSet);

  addr = sizeof(tempSet);
  pos += addr;
  EEPROM.put(pos, delta);

  addr = sizeof(delta);
  pos += addr;
  EEPROM.put(pos, adjTemp);

  addr = sizeof(adjTemp);
  pos += addr;

  char byt;
  int curpos = pos;

  for (int i = 0; i < 16; i++)
  {

    byt = welcome[i];

    EEPROM.put(pos, byt);
    pos++;
  }

  EEPROM.put(pos, mode1);
  pos++;

  EEPROM.put(pos, mode2);
  pos++;

  //Serial.print("Saving EEPROM");
#endif
}

void getSaved()
{

  int initsave = 0;

  //Serial.println("check data after restart: ");
  //Serial.println("Read custom object from EEPROM: ");

  getEEPROM();

  //Serial.print("Data tempSet= ");
  //Serial.println(tempSet);

  //Serial.print("Delta= ");
  //Serial.println(delta);

  //Serial.print("adj= ");
  //Serial.println(adjTemp);

  //Serial.print("welc = ");
  //Serial.println(welcome);

  //Serial.print("mode1= ");
  //Serial.println(mode1);

  //Serial.print("mode2 = ");
  //Serial.println(mode2);

  if (isnan(tempSet))
    tempSet = 20;

  if (delta < -30 || delta > 30 || isnan(delta)) {
    delta = 2;
    initsave = 1;
  }

  if (adjTemp < -30 || adjTemp > 30 || isnan(adjTemp)) {
    adjTemp = -0.1;
    initsave = 1;
  }

  //char welc[] = "welcome         ";
  //memcpy(welcome, welc, sizeof(welc[0]) * 16);
  if (isnan(welcome[0]))
  {
    char welc[] = "welcome         ";
    memcpy(welcome, welc, sizeof(welc[0]) * 16);
  }

  if (mode1 < 0 || mode1 > 1) {
    mode1 = 0;
    initsave = 1;
  }

  if (mode2 < 0 || mode2 > 4) {
    mode2 = 0;
    initsave = 1;
  }

  //if ( initsave == 1 )
  //  putEEPROM();
  /*
    Serial.println("After Read custom object from EEPROM: ");

    Serial.print("Data tempSet= ");
    Serial.println(tempSet);

    Serial.print("Delta= ");
    Serial.println(delta);

    Serial.print("adj= ");
    Serial.println(adjTemp);

    Serial.print("welc = ");
    Serial.println(welcome);


    Serial.print("mode1= ");
    Serial.println(mode1);

    Serial.print("mode2 = ");
    Serial.println(mode2);

  */
}

void getRangeButton(int value)
{

  if (value >= 900 && value < 1000)
  {
    buttonStateUpFan = 1;
    buttonPress = 1;
  }
  else
  {
    buttonStateUpFan = 0;
  }

  if (value >= 890 && value < 900)
  {
    buttonStateDownFan = 1;
    buttonPress = 1;
  }
  else
  {
    buttonStateDownFan = 0;
  }

  if (value >= 860 && value < 890)
  {
    buttonStateDefogg = 1;
    buttonPress = 1;
  }
  else
  {
    buttonStateDefogg = 0;
  }

  if (value >= 840 && value < 860)
  {
    buttonStateMode2 = 1;
    buttonPress = 1;
  }
  else
  {
    buttonStateMode2 = 0;
  }

  if (value >= 800 && value < 840)
  {
    buttonStateSetting = 1;
    buttonPress = 1;
  }
  else
  {
    buttonStateSetting = 0;
  }

  if (value >= 700 && value < 800)
  {
    buttonStateMode1 = 1;
    buttonPress = 1;
  }
  else
  {
    buttonStateMode1 = 0;
  }

  if (value >= 600 && value < 700)
  {
    buttonStateComp = 1;
    buttonPress = 1;
  }
  else
  {
    buttonStateComp = 0;
  }

  if (value > 100 && value < 600)
  {
    buttonStateDownTemp = 1;
    buttonPress = 1;
  }
  else
  {
    buttonStateDownTemp = 0;
  }

  if (value >= 0 && value < 100)
  {
    //buttonStateMode2 = 1;
    //buttonStateMode1 = 1;
    //buttonStateUpFan = 1;
    //buttonStateDefogg = 1;
    /// buttonStateDownTemp = 1;
    //buttonStateComp = 1;
    buttonStateUpTemp = 1;
    buttonPress = 1;
    //  buttonStateSetting = 1;
    //buttonStateComp = 1;
  }
  else
  {

    buttonStateUpTemp = 0;
  }

  //Serial.print("value range = ");
  // Serial.println(value);
  // lastvalue = value;

  if (value != lastvalue && value < 1002)
  {

    //Serial.print("value range = ");
    //Serial.println(value);
    lastvalue = value;
  }

}



void processCommands(String &cmd) {

  String coms = cmd;
  buffs = "";
  String com = getStringPartByNr(coms, ':', 0);
  String values = getStringPartByNr(coms, ':', 1 );
  String dummy = "";

  values.replace("#", "");

  if (com == "UPDATE") {
    updates = values.toInt();
  } else if (com == "FAN") {
    if (updates == 1) {
      fanSet = values.toInt();
      //case "FAN":
      //fanSet = values.toInt();
      triggerFan();
      lastfanSet = fanSet;

      if (fanSet <= 0) {
        compstat = 0;
      }

    }
  } else if (com == "TEMP") {
    //    tempcurr = values.toFloat();
  } else if (com == "TEMPSET") {
    if (updates == 1) {
      tempSet = values.toFloat();


    }
  }
  else if (com == "COMPSTAT") {
    if (updates == 1) {
      // compstat = values.toInt();
      if (values == "1") {
        compstat = 1;
        freezeStat = 1;
        if (fanSet == 0)
          fanSet = 1;

        triggerComp();
        triggerFan();

        lastfanSet = fanSet;
        lastfreezeStat = freezeStat;
      } else if (values == "0") {
        compstat = 0;
        freezeStat = 0;
        triggerComp();
      }

      lastfreezeStat = freezeStat;

    }

  } else if (com == "MODE1") {
    //case "MODE1":
    if (updates == 0) return;
    mode1 = values.toInt();
    delaymode1 = waitmode1;
    //  break;
  } else if (com == "MODE2") {
    //case "MODE2":
    if (updates==0) return ;
    mode2 = values.toInt();
    delaymode2 = waitmode2;
    setIconMode2();
    // triggerMode2();
    //  break;
  } else if (com == "DEFOGGER") {
    //case "DEFOGGER":
    if (updates==0) return ;
    defogstat = values.toInt();
    triggerDefogger();
    lastdefogstat = defogstat;
  }
}


void updateCommand(String &com, String &values){
  
  if ( com == "TEMPSET" ||
       com == "MODE1" ||
       com == "MODE2" ) {

    //timersave = millis();
    //saveconfig = true;

  }

  if ( com == "TEMPSET" ) {
    tempSet = values.toFloat();

  } else if (com == "FAN") {
    //case "FAN":
    fanSet = values.toInt();
    triggerFan();
    lastfanSet = fanSet;

    if (fanSet <= 0) {
      compstat = 0;
    }

    //  break;
  } else if (com == "MODE1") {
    //case "MODE1":
    mode1 = values.toInt();
    delaymode1 = waitmode1;
    //  break;
  } else if (com == "MODE2") {
    //case "MODE2":
    mode2 = values.toInt();
    delaymode2 = waitmode2;
    setIconMode2();
    // triggerMode2();
    //  break;
  } else if (com == "AC") {
    //case "AC":
    if (values == "1") {
      compstat = 1;
      freezeStat = 1;
      if (fanSet == 0)
        fanSet = 1;

      triggerComp();
      triggerFan();

      lastfanSet = fanSet;
      lastfreezeStat = freezeStat;
    } else if (values == "0") {
      compstat = 0;
      freezeStat = 0;
      triggerComp();
    }

    lastfreezeStat = freezeStat;
    //break;
  } else if (com == "DEFOGGER") {
    //case "DEFOGGER":
    defogstat = values.toInt();
    triggerDefogger();
    lastdefogstat = defogstat;
  }
  if ( com == "TEMPSET" ||
       com == "FAN" ||
       com == "MODE1" ||
       com == "DEFOGGER" ||
       com == "AC" ||
       com == "MODE1" ||
       com == "MODE2" ) {

    //sendDataBT();
    //dataBT = false;

  }
}

void processCommand(String &cmd) {
  String com = getStringPartByNr(cmd, ':', 0);
  String values = getStringPartByNr(cmd, ':', 1 );
  values.replace("#", "");

  //Serial.print(" Process Command =");
  //Serial.print(com);
  //Serial.print(" => ");
  //Serial.println(values);
   updateCommand(com,values);

}

void loop()
{
  playSound();

  int buttonValue = analogRead(A1);

  getRangeButton(buttonValue);

  if (screen != lastScreen)
  {
    lcd.clear();
  }

  //if (millis() - timerdisp > 500){
  timerdisp = millis();


  if (screen == 0)
  {
    //welcome screen
    showSplashScreen();
  }
  else if (screen == -1)
  {
    showMainScreen();
    showInitialMain();
  }
  else if (screen == 1)
  {
    //main screenre
    showMainScreen();
  }
  else if (screen == 2)
  {
    //setting screen
    showSettingScreen();
  } else if (screen == 3) {
    showSlide();
  }




  //}

  if (millis() - timersave > 10000 && saveconfig ) {
    putEEPROM();
    saveconfig = false;
  }

#if LIBRARY_TO_USE == ARDU
  while (bt.available()) {
    char character = bt.read();
    buff.concat(character);
    if (character == '#') { // if end of message received
      //Serial.print(buff); //display message and
      processCommand(buff);
      buff = ""; //clear buffer
      //Serial.println();
    }
  }




  while (Serial.available()) {
    //data = Serial.read();
    char data = Serial.read();

    buffs.concat(data);
    if (data == '#') { // if end of message received
      //initserial++;
      //if (initserial > 150) {
      //  initserial = 1;
      //  idleserial = 0;

      //}

      //Serial.print(buff); //display message and
      processCommands(buffs);
      buffs = ""; //clear buffer
      //Serial.println();
    }

  }


#endif

  if ( millis() - timerBT > 2000 ) {
    timerBT = millis();
    //Serial.print("Timer : ");
    //Serial.print(millis());
    //Serial.print(" , ");
    //Serial.println(timerBT);
    sendDataBT();
  }

  if ( millis() - timerMonitor > 1500 ) {
    timerMonitor = millis();
    //Serial.print("monitor : ");
    //Serial.print(millis());
    //Serial.print(" , ");
    //Serial.println(timerBT);
    sendDataMonitor();
  }

  lastScreen = screen;
  loopc++;
  //  displayOLED();
}
