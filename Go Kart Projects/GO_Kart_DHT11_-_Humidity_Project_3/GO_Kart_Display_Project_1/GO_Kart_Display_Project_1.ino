#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

MCUFRIEND_kbv tft;

// ---------- COLORS ----------
#define BLACK      0x0000
#define DARKGREY   0x2104
#define GREY       0x8410
#define WHITE      0xFFFF
#define GREEN      0x07E0
#define LIME       0x7FE0
#define BLUE       0x001F
#define CYAN       0x07FF
#define RED        0xF800
#define ORANGE     0xFD20
#define YELLOW     0xFFE0

// ---------- PINS ----------
#define SPEED_PIN     2
#define LAP_PIN       3
#define GEAR_PIN      A1
#define BATTERY_PIN   A0

// ---------- UI STATE ----------
enum UIState { STATE_WELCOME, STATE_COUNTDOWN, STATE_RACE };
UIState uiState = STATE_WELCOME;

unsigned long welcomeStartMillis   = 0;
unsigned long countdownStartMillis = 0;
int           lastCountdownPhase   = -1;

const unsigned long WELCOME_DURATION   = 5000;  // 5 seconds welcome
const unsigned long COUNTDOWN_DURATION = 4000;  // 3..2..1..GO (~4s)

// ---------- SPEED ----------
volatile int  speedPulses    = 0;
int           speed          = 0;
int           oldSpeed       = -1;
unsigned long lastSpeedTime  = 0;

// ---------- LAPS / TIME ----------
int laps    = 0;
int oldLaps = -1;

unsigned long lapStartTime     = 0;
unsigned long lastLapTime      = 0;
unsigned long bestLapTime      = 0;
unsigned long sessionStartTime = 0;

unsigned long oldLapTimeSec      = 999999;
unsigned long oldBestLapTimeSec  = 999999;
unsigned long oldLastLapTimeSec  = 999999;
unsigned long oldSessionTimeSec  = 999999;

// ---------- GEAR ----------
int gear    = 1;
int oldGear = -1;

// ---------- BATTERY ----------
int battery    = 100;
int oldBattery = -1;

// ---------- LAYOUT ----------
// Shift light bar
const int SHIFT_X        = 10;
const int SHIFT_Y        = 8;
const int SHIFT_W        = 460;
const int SHIFT_H        = 18;
const int SHIFT_SEGMENTS = 16;

// Center gear / speed
const int CENTER_X = 240;
const int CENTER_Y = 150;

// Left lap panel
const int LINFO_X = 10;
const int LINFO_Y = 80;
const int LINFO_W = 120;
const int LINFO_H = 150;

// Right time panel
const int RINFO_X = 350;
const int RINFO_Y = 80;
const int RINFO_W = 120;
const int RINFO_H = 150;

// Bottom panels
const int SES_X = 10;
const int SES_Y = 260;
const int SES_W = 220;
const int SES_H = 50;

const int BAT_X = 250;
const int BAT_Y = 260;
const int BAT_W = 220;
const int BAT_H = 50;

// Dynamic value regions
// Speed
const int SPEED_BOX_X = CENTER_X - 80;
const int SPEED_BOX_Y = CENTER_Y + 45;
const int SPEED_BOX_W = 160;
const int SPEED_BOX_H = 60;

// Gear
const int GEAR_BOX_X = CENTER_X - 45;
const int GEAR_BOX_Y = CENTER_Y - 45;
const int GEAR_BOX_W = 90;
const int GEAR_BOX_H = 90;

// Left panel dynamic
const int LAP_NUM_X = LINFO_X + 10;
const int LAP_NUM_Y = LINFO_Y + 35;
const int LAP_NUM_W = LINFO_W - 20;
const int LAP_NUM_H = 30;

const int CUR_TIME_X = LINFO_X + 10;
const int CUR_TIME_Y = LINFO_Y + 110;
const int CUR_TIME_W = LINFO_W - 20;
const int CUR_TIME_H = 20;

// Right panel dynamic
const int BEST_TIME_X = RINFO_X + 10;
const int BEST_TIME_Y = RINFO_Y + 35;
const int BEST_TIME_W = RINFO_W - 20;
const int BEST_TIME_H = 20;

const int LAST_TIME_X = RINFO_X + 10;
const int LAST_TIME_Y = RINFO_Y + 110;
const int LAST_TIME_W = RINFO_W - 20;
const int LAST_TIME_H = 20;

// Session time dynamic
const int SES_TIME_X = SES_X + 90;
const int SES_TIME_Y = SES_Y + 15;
const int SES_TIME_W = SES_W - 100;
const int SES_TIME_H = 20;

// Battery bar dynamic
const int BAT_BAR_X = BAT_X + 10;
const int BAT_BAR_Y = BAT_Y + 30;
const int BAT_BAR_W = BAT_W - 20;
const int BAT_BAR_H = 12;

// Countdown overlay
const int CD_X = 80;
const int CD_Y = 70;
const int CD_W = 320;
const int CD_H = 180;

// ---------- INTERRUPT ----------
void speedISR() {
  speedPulses++;
}

// ---------- TIME FORMAT ----------
void drawTimeMMSS(int16_t x, int16_t y, unsigned long ms, uint16_t color, uint8_t size) {
  char buf[6]; // "MM:SS"
  unsigned long sec = ms / 1000;
  uint8_t m = sec / 60;
  uint8_t s = sec % 60;

  sprintf(buf, "%02u:%02u", m, s);
  tft.setFont();  // default font for digits
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setCursor(x, y);
  tft.print(buf);
}

// --- BOOT SEQUENCE ---
void runBootSequence() {
  tft.fillScreen(BLACK);

  // F2 Logo / System Text
  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextColor(CYAN);
  tft.setCursor(120, 100);
  tft.print("SYSTEM INITIALIZING");

  // Loading Bar
  tft.drawRect(90, 140, 300, 20, WHITE);
  for (int i = 0; i < 296; i += 4) {
    tft.fillRect(92, 142, i, 16, GREEN);
    delay(15);
  }

  tft.setFont();  // back to default
}

// =====================================================
// ---------------- STATIC HUD DRAWING -----------------
// =====================================================

void drawShiftBarFrame() {
  tft.drawRoundRect(SHIFT_X, SHIFT_Y, SHIFT_W, SHIFT_H, 6, CYAN);
}

void drawCenterRing() {
  tft.drawCircle(CENTER_X, CENTER_Y, 78, DARKGREY);
  tft.drawCircle(CENTER_X, CENTER_Y, 80, CYAN);
  tft.drawCircle(CENTER_X, CENTER_Y, 55, GREY);
}

void drawLeftPanel() {
  tft.fillRoundRect(LINFO_X, LINFO_Y, LINFO_W, LINFO_H, 8, DARKGREY);
  tft.drawRoundRect(LINFO_X, LINFO_Y, LINFO_W, LINFO_H, 8, CYAN);

  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.setCursor(LINFO_X + 15, LINFO_Y + 20);
  tft.print("LAP");

  tft.setCursor(LINFO_X + 15, LINFO_Y + 95);
  tft.print("CUR");

  tft.setFont();
}

void drawRightPanel() {
  tft.fillRoundRect(RINFO_X, RINFO_Y, RINFO_W, RINFO_H, 8, DARKGREY);
  tft.drawRoundRect(RINFO_X, RINFO_Y, RINFO_W, RINFO_H, 8, CYAN);

  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.setCursor(RINFO_X + 15, RINFO_Y + 20);
  tft.print("BEST");

  tft.setCursor(RINFO_X + 15, RINFO_Y + 95);
  tft.print("LAST");

  tft.setFont();
}

void drawBottomPanels() {
  // Session
  tft.fillRoundRect(SES_X, SES_Y, SES_W, SES_H, 8, DARKGREY);
  tft.drawRoundRect(SES_X, SES_Y, SES_W, SES_H, 8, CYAN);

  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.setCursor(SES_X + 10, SES_Y + 25);
  tft.print("SESSION");
  tft.setFont();

  // Battery
  tft.fillRoundRect(BAT_X, BAT_Y, BAT_W, BAT_H, 8, DARKGREY);
  tft.drawRoundRect(BAT_X, BAT_Y, BAT_W, BAT_H, 8, CYAN);

  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.setCursor(BAT_X + 10, BAT_Y + 25);
  tft.print("BAT");
  tft.setFont();

  // Battery bar frame
  tft.drawRect(BAT_BAR_X, BAT_BAR_Y, BAT_BAR_W, BAT_BAR_H, WHITE);
}

void drawSpeedLabel() {
  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.setCursor(CENTER_X - 30, SPEED_BOX_Y - 10);
  tft.print("SPEED");

  tft.setTextColor(WHITE);
  tft.setCursor(CENTER_X + 30, SPEED_BOX_Y + 45);
  tft.print("km/h");
  tft.setFont();
}

void drawLogoTag() {
  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.setCursor(SHIFT_X + 4, SHIFT_Y + SHIFT_H + 14);
  tft.print("RC F2 DASH");
  tft.setFont();
}

// Car silhouette
void drawCarSilhouette() {
  int yBase = CENTER_Y + 5;
  tft.drawLine(CENTER_X - 40, yBase,     CENTER_X + 40, yBase,     GREY);
  tft.drawLine(CENTER_X - 30, yBase - 8, CENTER_X + 30, yBase - 8, GREY);
  tft.drawLine(CENTER_X - 40, yBase,     CENTER_X - 30, yBase - 8, GREY);
  tft.drawLine(CENTER_X + 40, yBase,     CENTER_X + 30, yBase - 8, GREY);
  tft.fillCircle(CENTER_X - 25, yBase + 6, 4, GREY);
  tft.fillCircle(CENTER_X + 25, yBase + 6, 4, GREY);
}

void drawRaceHUD_static() {
  tft.fillScreen(BLACK);
  drawShiftBarFrame();
  drawCenterRing();
  drawCarSilhouette();
  drawLeftPanel();
  drawRightPanel();
  drawBottomPanels();
  drawSpeedLabel();
  drawLogoTag();
}

// =====================================================
// --------------- WELCOME + COUNTDOWN -----------------
// =====================================================

void showWelcomeScreen() {
  tft.fillScreen(BLACK);

  tft.fillRect(0, 0,   480, 80, DARKGREY);
  tft.fillRect(0, 240, 480, 80, DARKGREY);
  tft.drawLine(0, 80,   480, 80,  CYAN);
  tft.drawLine(0, 240,  480, 240, CYAN);

  tft.setFont(&FreeSansBold24pt7b);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.setCursor(40, 145);
  tft.print("WELCOME TO F2");

  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextColor(CYAN);
  tft.setCursor(140, 190);
  tft.print("LET'S WE START");

  tft.setFont();
}

void updateCountdownOverlay() {
  unsigned long e = millis() - countdownStartMillis;

  if (e >= COUNTDOWN_DURATION) {
    uiState = STATE_RACE;

    laps = 0;
    speed = 0;
    lastLapTime  = 0;
    bestLapTime  = 0;
    sessionStartTime = millis();
    lapStartTime     = sessionStartTime;

    oldSpeed = -1;
    oldGear  = -1;
    oldLaps  = -1;
    oldBattery = -1;
    oldLapTimeSec     = 999999;
    oldBestLapTimeSec = 999999;
    oldLastLapTimeSec = 999999;
    oldSessionTimeSec = 999999;

    drawRaceHUD_static();
    return;
  }

  int phase;
  if (e < 3000) {
    phase = e / 1000;   // 0,1,2 -> "3","2","1"
  } else {
    phase = 3;          // "GO"
  }

  if (phase == lastCountdownPhase) return;
  lastCountdownPhase = phase;

  // Overlay box
  tft.fillRoundRect(CD_X, CD_Y, CD_W, CD_H, 16, BLACK);
  tft.drawRoundRect(CD_X, CD_Y, CD_W, CD_H, 16, CYAN);

  const char* txt;
  uint16_t color;

  if (phase == 0) { txt = "3";  color = YELLOW; }
  else if (phase == 1) { txt = "2"; color = ORANGE; }
  else if (phase == 2) { txt = "1"; color = RED; }
  else { txt = "GO"; color = GREEN; }

  tft.setFont(&FreeSansBold24pt7b);
  tft.setTextColor(color);
  tft.setTextSize(2);

  int16_t x = (phase == 3) ? (CENTER_X - 80) : (CENTER_X - 30);
  int16_t y = CENTER_Y + 25;
  tft.setCursor(x, y);
  tft.print(txt);

  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.setCursor(CD_X + 90, CD_Y + CD_H - 25);
  tft.print("RACE START");
  tft.setFont();
}

// =====================================================
// ---------------------- SETUP ------------------------
// =====================================================

void setup() {
  pinMode(SPEED_PIN, INPUT_PULLUP);
  pinMode(LAP_PIN,   INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(SPEED_PIN), speedISR, FALLING);

  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9486;
  tft.begin(ID);
  tft.setRotation(1);

  runBootSequence();

  uiState = STATE_WELCOME;
  showWelcomeScreen();
  welcomeStartMillis = millis();
}

// =====================================================
// ----------------------- LOOP ------------------------
// =====================================================

void loop() {
  readSpeed();
  if (uiState == STATE_RACE) {
    readLap();
  }
  readGear();
  readBattery();

  if (uiState == STATE_WELCOME) {
    if (millis() - welcomeStartMillis >= WELCOME_DURATION) {
      uiState = STATE_COUNTDOWN;
      drawRaceHUD_static();
      countdownStartMillis = millis();
      lastCountdownPhase   = -1;
    }
  } else if (uiState == STATE_COUNTDOWN) {
    updateCountdownOverlay();
  } else if (uiState == STATE_RACE) {
    updateRaceHUD();
  }
}

// =====================================================
// ---------------- SENSOR READINGS --------------------
// =====================================================

void readSpeed() {
  if (millis() - lastSpeedTime >= 1000) {
    noInterrupts();
    int pulses = speedPulses;
    speedPulses = 0;
    interrupts();

    // Adjust factor for your wheel to get real km/h
    speed = pulses * 2;

    lastSpeedTime = millis();
  }
}

void readLap() {
  static int lastState = HIGH;
  int state = digitalRead(LAP_PIN);

  if (lastState == HIGH && state == LOW) {
    unsigned long now = millis();

    if (laps > 0) {
      lastLapTime = now - lapStartTime;
      if (bestLapTime == 0 || lastLapTime < bestLapTime) {
        bestLapTime = lastLapTime;
      }
    }

    laps++;
    lapStartTime = now;
  }

  lastState = state;
}

void readGear() {
  int val = analogRead(GEAR_PIN);

  if      (val < 150) gear = 1;
  else if (val < 300) gear = 2;
  else if (val < 450) gear = 3;
  else if (val < 600) gear = 4;
  else if (val < 750) gear = 5;
  else                gear = 6;
}

void readBattery() {
  float raw = analogRead(BATTERY_PIN);
  float voltage = raw * (5.0 / 1023.0);
  voltage *= 5.0; // divider

  int mV = voltage * 1000;
  battery = map(mV, 11000, 12600, 0, 100);
  battery = constrain(battery, 0, 100);
}

// =====================================================
// -------------------- HUD UPDATE ---------------------
// =====================================================

void updateShiftBar() {
  const int MAX_SPEED = 300;
  int segW = (SHIFT_W - (SHIFT_SEGMENTS + 1)) / SHIFT_SEGMENTS;

  int s = speed;
  if (s < 0) s = 0;
  if (s > MAX_SPEED) s = MAX_SPEED;

  int lights = map(s, 0, MAX_SPEED, 0, SHIFT_SEGMENTS);

  for (int i = 0; i < SHIFT_SEGMENTS; i++) {
    int x = SHIFT_X + 1 + i * (segW + 1);
    int y = SHIFT_Y + 2;
    uint16_t colOff = BLACK;
    uint16_t colOn;

    if (i < 5)       colOn = GREEN;
    else if (i < 10) colOn = YELLOW;
    else if (i < 13) colOn = ORANGE;
    else             colOn = RED;

    if (i < lights) {
      tft.fillRect(x, y, segW, SHIFT_H - 4, colOn);
    } else {
      tft.fillRect(x, y, segW, SHIFT_H - 4, colOff);
    }
  }
}

void updateRaceHUD() {
  unsigned long now = millis();

  // SPEED + SHIFT BAR
  if (speed != oldSpeed) {
    tft.fillRect(SPEED_BOX_X, SPEED_BOX_Y, SPEED_BOX_W, SPEED_BOX_H, BLACK);

    tft.setFont();
    tft.setTextColor(WHITE);
    tft.setTextSize(5);
    tft.setCursor(SPEED_BOX_X + 8, SPEED_BOX_Y + 10);
    tft.print(speed);

    updateShiftBar();
    oldSpeed = speed;
  }

  // GEAR
  if (gear != oldGear) {
    tft.fillRect(GEAR_BOX_X, GEAR_BOX_Y, GEAR_BOX_W, GEAR_BOX_H, BLACK);

    tft.setFont();
    tft.setTextColor(ORANGE);
    tft.setTextSize(7);
    tft.setCursor(CENTER_X - 23, CENTER_Y - 35);
    tft.print(gear);

    oldGear = gear;
  }

  // LAPS
  if (laps != oldLaps) {
    tft.fillRect(LAP_NUM_X, LAP_NUM_Y, LAP_NUM_W, LAP_NUM_H, BLACK);

    tft.setFont();
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(LAP_NUM_X + 5, LAP_NUM_Y);
    tft.print(laps);

    oldLaps = laps;
  }

  // CURRENT LAP TIME
  unsigned long curLapSec = (now - lapStartTime) / 1000;
  if (curLapSec != oldLapTimeSec) {
    oldLapTimeSec = curLapSec;
    tft.fillRect(CUR_TIME_X, CUR_TIME_Y, CUR_TIME_W, CUR_TIME_H, BLACK);
    drawTimeMMSS(CUR_TIME_X + 5, CUR_TIME_Y, now - lapStartTime, WHITE, 2);
  }

  // BEST LAP TIME
  unsigned long bestSec = (bestLapTime == 0) ? 0 : bestLapTime / 1000;
  if (bestSec != oldBestLapTimeSec) {
    oldBestLapTimeSec = bestSec;

    tft.fillRect(BEST_TIME_X, BEST_TIME_Y, BEST_TIME_W, BEST_TIME_H, BLACK);
    if (bestLapTime == 0) {
      tft.setFont();
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.setCursor(BEST_TIME_X + 5, BEST_TIME_Y);
      tft.print("--:--");
    } else {
      drawTimeMMSS(BEST_TIME_X + 5, BEST_TIME_Y, bestLapTime, WHITE, 2);
    }
  }

  // LAST LAP TIME
  unsigned long lastSec = (lastLapTime == 0) ? 0 : lastLapTime / 1000;
  if (lastSec != oldLastLapTimeSec) {
    oldLastLapTimeSec = lastSec;

    tft.fillRect(LAST_TIME_X, LAST_TIME_Y, LAST_TIME_W, LAST_TIME_H, BLACK);
    if (lastLapTime == 0) {
      tft.setFont();
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.setCursor(LAST_TIME_X + 5, LAST_TIME_Y);
      tft.print("--:--");
    } else {
      drawTimeMMSS(LAST_TIME_X + 5, LAST_TIME_Y, lastLapTime, WHITE, 2);
    }
  }

  // SESSION TIME
  unsigned long sessionSec = (now - sessionStartTime) / 1000;
  if (sessionSec != oldSessionTimeSec) {
    oldSessionTimeSec = sessionSec;
    tft.fillRect(SES_TIME_X, SES_TIME_Y, SES_TIME_W, SES_TIME_H, DARKGREY);
    drawTimeMMSS(SES_TIME_X + 5, SES_TIME_Y, now - sessionStartTime, WHITE, 2);
  }

  // BATTERY
  if (battery != oldBattery) {
    tft.fillRect(BAT_BAR_X + 1, BAT_BAR_Y + 1, BAT_BAR_W - 2, BAT_BAR_H - 2, BLACK);

    int w = map(battery, 0, 100, 0, BAT_BAR_W - 4);
    uint16_t col = GREEN;
    if (battery < 50) col = YELLOW;
    if (battery < 25) col = RED;
    tft.fillRect(BAT_BAR_X + 2, BAT_BAR_Y + 2, w, BAT_BAR_H - 4, col);

    tft.fillRect(BAT_X + BAT_W - 50, BAT_Y + 8, 45, 25, DARKGREY);
    tft.setFont();
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(BAT_X + BAT_W - 45, BAT_Y + 12);
    tft.print(battery);

    oldBattery = battery;
  }
}
