//This code is placed under the MIT license
//Copyright (c) 2020 Albert Barber
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

//code intended to run on esp8266, Wemos D1 mini
//requires lastest version of adafruit neopixel library (use the library manager)
#include <PixelStrip.h>
#include "segmentDefs.h"
#include <EEPROM.h>
#include <Ticker.h>

//toggles for enabling buttons and EEPROM
#define BUTTONS_ENABLE  false
#define EEPROM_ENABLE   false

//total number of effects (change this if you add any!)
#define NUM_EFFECTS     28

//pin connections
#define PIXEL_PIN       D8
#define BUTTON_1        D6
#define BUTTON_2        D7
#define BUTTON_3        D5

//below vars are placeholders for possible bluetooth and mic board connections
#define MIC_IN          A0
#define RX_BT           D1
#define TX_BT           D2

//EEPROM Addresses for settings
//we want to store the brightness, current effect index, and the effect rotation toggle
//so they can be recalled after the mask has been turned off
#define BRIGHTNESS_ADDR 2 //brightness address
#define CUR_EFFECT_ADDR 0 //index of current effect address
#define EFFECT_ROT_ADDR 1 //effect rotaion bool address
#define EEPROM_COM_TIME 3000 //ms

//effects control vars
byte effectIndex = 0; //number of effect that's currently active (will be read from EEPROM later)
boolean effectRota = true; //effects rotation on / off flag
boolean effectsStop = false; //stop all effects flag
boolean direct = true; //use for setting direction of effects
boolean breakCurrentEffect = false; //flag for breaking out of effects that use multiple sub effects / loops

//macro for implementing break for effects with multiple sub effects
#define breakEffectCheck() ({ \
    if( (breakCurrentEffect) ){ \
      (breakCurrentEffect) = false; \
      break; \
    } \
  })

//brightness vars
byte brightnessIndex = 2; //initial brightness, index of brightnessLevels array
//brightness levels array, max is 255, but 100 should be bright enough for amost all cases
//!!WARNING brightness is directly tied to power consumption, the max current per led is 60ma, this is for white at 255 brightness
//if you actually run all the leds at max, the glasses will draw 4.75 amps, this is beyond the rating of the jst connectors
const byte brightnessLevels[] = { 50, 100, 150, 200 };
const byte numBrightnessLevels = SIZE( brightnessLevels );

//Strip definitions
const uint16_t stripLength = 210;
const uint8_t stripType = NEO_GRB + NEO_KHZ800;
PixelStrip strip = PixelStrip(stripLength, PIXEL_PIN, stripType);

//initilize ticker objects
Ticker EEPROMcommiter; //timer for commiting data to EEPRROM

//Define some colors we'll use frequently
const uint32_t white =    strip.Color(255, 255, 255);
const uint32_t UCLAGold = strip.Color(254, 187, 54);
const uint32_t UCLABlue = strip.Color(83, 104, 149);
const uint32_t off =      strip.Color( 0, 0, 0 );
const uint32_t red =      strip.Color(255, 0, 0);
const uint32_t orange =   strip.Color(255, 43, 0);
const uint32_t ltOrange = strip.Color(255, 143, 0);
const uint32_t yellow =   strip.Color(255, 255, 0);
const uint32_t ltYellow = strip.Color(255, 255, 100);
const uint32_t green =    strip.Color(0, 128, 0);
const uint32_t blue =     strip.Color(0, 0, 255);
const uint32_t indigo =   strip.Color( 75, 0, 130);
const uint32_t violet =   strip.Color(238, 130, 238);
const uint32_t purple =   strip.Color(123, 7, 197);
const uint32_t pink =     strip.Color(225, 0, 127);

//define pallet array, contains 32bit representations of all colors used in patterns
uint32_t pallet[9] = { off, white, UCLAGold, UCLABlue, blue, yellow, red, green, purple };
//                   { -0-, --1--, ---2----, ----3---, -4--, ---5--, -6-, --7--, --8-- }

uint32_t christmasPallet[5] = { red, blue, green, yellow, purple };

uint32_t firePallet[3] = { red, ltOrange, white };

uint32_t tempRandPallet2[3];
uint32_t tempRandPallet[5]; //pallet for random colors (length sets number of colors used by randomColors effect)
byte simpleRepeatPatternRand[10] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4};

byte wavepattern[]  = { 6, 1 };
byte wavepattern2[] = { 5, 4 };
byte wavepattern3[] = { 6, 7 };
byte wavepattern4[] = { 8, 7 };
byte christmasWavePattern[5] = { 0, 1, 2, 3, 4};

//for simple repeart drawing functions
byte simpleRepeatPattern[5] = {8, 6, 7, 4, 5}; //{ 4, 0, 5, 0, 6, 0, 7, 0};

//callback routine for committing EEPROM data
//EEPRROM has limited writes, so we want to commit all the writes after a delay
//this allows the data to change while the user is pressing buttons, and we'll only commit
//the final values once they are done
void ICACHE_RAM_ATTR commitEEPROM() {
  EEPROM.commit();
}

//triggered by button 1, stops the current pattern, and switches to the next one, wrapping if needed
//also stores effect index in eeprom
//if button 2 is also being held, turn effects on / off
void ICACHE_RAM_ATTR nextEffect() {
  strip.pixelStripStopPattern = true; //stop the current pattern
  breakCurrentEffect = true; //set flag to break out of current case statement
  //if we are rotating to the next effect, reset all the segment directions
  //and store the next effect index in eeprom
  if (effectRota) {
    resetSegDirections();
    EEPROM.write(CUR_EFFECT_ADDR, (effectIndex + 1) % NUM_EFFECTS);
    //stop any other commit timers and start a new one
    EEPROMcommiter.detach();
    EEPROMcommiter.once_ms(EEPROM_COM_TIME, commitEEPROM);
  }
  //if button 2 is being held, stop/start the effect cycle
  //otherwise increase the index to start the next effect
  if ( digitalRead(BUTTON_2) == LOW) {
    effectsStop = !effectsStop;
  }
}

//triggered by button 2, turns effect rotation on / off
//also stores the state in eeprom
//(if rotation is off, the current effect will be repeated continuously)
//if button 1 is also being held, turn effects on / off
void ICACHE_RAM_ATTR effectRotaToggle() {
  if ( digitalRead(BUTTON_1) == LOW) {
    strip.pixelStripStopPattern = true;
    effectsStop = !effectsStop;
  } else {
    effectRota = !effectRota;
    EEPROM.write(EFFECT_ROT_ADDR, effectRota);
    //stop any other commit timers and start a new one
    EEPROMcommiter.detach();
    EEPROMcommiter.once_ms(EEPROM_COM_TIME, commitEEPROM);
  }
}

//triggered by button 3, sets the strip brightness to the next
//also stores the brighness index in eeprom
//brightness level in the brightnessLevels array (wrapping to the start if needed)
void ICACHE_RAM_ATTR brightnessAdjust() {
  brightnessIndex = (brightnessIndex + 1) % numBrightnessLevels;
  strip.setBrightness( brightnessLevels[ brightnessIndex ] );
  EEPROM.write(BRIGHTNESS_ADDR, brightnessIndex);
  //stop any other commit timers and start a new one
  EEPROMcommiter.detach();
  EEPROMcommiter.once_ms(EEPROM_COM_TIME, commitEEPROM);
}

//increments the effect index (wrapping if needed)
void incrementEffectIndex() {
  resetSegDirections();
  strip.runRainbowOffsetCycle(false);
  strip.setRainbowOffset(0);
  effectIndex = (effectIndex + 1) % NUM_EFFECTS;
}

void setup() {
  //initalize the led strip, and set the starting brightness
  strip.begin();

  if (BUTTONS_ENABLE) {
    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(BUTTON_3, INPUT_PULLUP);
    //because of the way my library currently works, effects occupy the processor until they end
    //so to break out of an effect, or change sytem values, we need to use interrupts
    attachInterrupt(digitalPinToInterrupt(BUTTON_1), nextEffect, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_2), effectRotaToggle, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_3), brightnessAdjust, FALLING);
  }

  if (EEPROM_ENABLE && BUTTONS_ENABLE) {
    // EEPROM Initialization
    EEPROM.begin(512);

    //read EEPROM values for current effect, brightness, and effect rotation
    effectRota = EEPROM.read(EFFECT_ROT_ADDR);
    brightnessIndex = EEPROM.read(BRIGHTNESS_ADDR);
    effectIndex = EEPROM.read(CUR_EFFECT_ADDR);
  }

  strip.setBrightness( brightnessLevels[brightnessIndex] );
  strip.show();
  //Serial.begin(115200);

  randomSeed(ESP.getCycleCount()); //generate a random seed
  //fill in our random pallet
  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  strip.genRandPallet( tempRandPallet2, SIZE(tempRandPallet2) );
}

//!! If you want to change the main loop code, please read all the comments below and in the loop !!
//To remove an effect, simply change its case # to anything greater than the total number of effects (999 for ex)
//if you want to know about certain effects, please see comments in the library for said effect
//if you want to know how segments work, please see comments in segmentSet.h

//The main loop of the program, works as follows:
//if effectsStop is true, effects are "off", so we won't try to start the next effect
//otherwise we jump to the effect matching the effectIndex value using a switch statment
//we also "clean up" a bit by reseting direct to true and the breakCurrentEffect flag to false
//if we don't find an effect with the effectIndex, we increment the effectIndex until we do
//while an effect is running, button inputs can either lock the effect or skip to the next effect
//if we lock the effect (set effectRota to false), we do not increment effectIndex when the effect ends, essentially restarting the effect (with new colors if they're randomly choosen)
//if the effect is skipped, we set strip.pixelStripStopPattern and breakCurrentEffect to true
//strip.pixelStripStopPattern will stop the current effect, and breakCurrentEffect will break out of the current switch statement if needed (the switch case has more than one effect)
//once the effect ends (either naturally or from a button press), we incremented effectIndex (as long as effectRota is set true)
//and jump to the top of the main loop

void loop() {

  if (!effectsStop) { //if effectsStop is true, we won't display any effect
    direct = !direct;
    breakCurrentEffect = false;
    resetBrightness();
    //switch statment contains all effects
    //I'm not going to comment each one, as they're hard to describe
    //if an case has a loop, it generally means the effect will by run multiple times in diff directions
    //these will contain breakEffectCheck(); which will breakout of the case if the effect is skipped by button input
    //segmentName.flipSegDirectionEvery(1, true) means that the direction of the names segments will be reversed
    //this is used to change the direction of colorSpin effects

    switch (effectIndex) { //select the next effect based on the effectIndex
      case 0:
        strip.rainbowWave( ringSegments, 150, true, 3, 15);
        break;
      case 1:
        strip.fixedLengthRainbowCycle(21, true, 150, 80);
        break;
      case 2:
        strip.genRandPallet( tempRandPallet2, SIZE(tempRandPallet2) );
        strip.twinkleSet(0, tempRandPallet2, SIZE(tempRandPallet2), 2, 15, 65, 15000);
        break;
      case 3:
        strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
        strip.patternSweepSetRand( 14, tempRandPallet,  SIZE(tempRandPallet), 0, 1, 3, true, 0, 1, 60, 200);
        break;
      case 4:
        strip.patternSweepRainbowRand( 14, 0, 1, 3, true, 0, 60, 24 * 8);
        break;
      case 5:
        strip.setRainbowOffsetCycle(5, false);
        strip.runRainbowOffsetCycle(true);
        strip.randomColors( -4, false, white, 70, 5, 15000);
        break;
      case 6:
        for (int i = 0; i < 2; i++) {
          breakEffectCheck();
          strip.patternSweepRepeatRand(3, 0, 0, 2, 7, false, direct, 0, 0, 1, 5, 200 );
          direct = !direct;
        }
        break;
      case 7:
        strip.fillStrip(orange, false);
        strip.doFireV2Seg( vertLineSegments, firePallet, SIZE(firePallet), 45, 120, true, 400, 50);
        break;
      case 8:
        for (int i = 0; i < 2; i++) {
          breakEffectCheck();
          strip.segGradientCycleRand( ringSegments, 4, 7, 150, direct, 1, 60);
          direct = !direct;
        }
        break;
      case 9:
        strip.simpleStreamerRand( 3, 0, 3, 3, 0, true, 150, 70);
        break;
      case 10:
        for (int i = 0; i < 2; i++) {
          breakEffectCheck();
          vertLineSegments.flipSegDirectionEvery(1, true);
          strip.colorSpinSimple( vertLineSegments, 3, 0, 0, 7, -1, 5, 0, 1, 200, 60 );
        }
        break;
      case 11:
        strip.colorSpinSimple( hexSegments, 3, 0, 0, 7, -1, 7, 0, 1, 170, 60 );
        break;
      case 12:
        strip.genRandPallet( tempRandPallet2, SIZE(tempRandPallet2) );
        tempRandPallet2[1] = 0;
        strip.shiftingSea( tempRandPallet2, SIZE(tempRandPallet2), 60, 0, 1, 1000, 10 );
        break;
      case 13:
        strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
        strip.randomColorSet(0, true, tempRandPallet, SIZE(tempRandPallet), 70, 5, 12000);
        break;
      case 14:
        strip.setRainbowOffsetCycle(40, false);
        strip.runRainbowOffsetCycle(true);
        strip.sparkSeg( ringSegments, 20, 1, 1, white, 1, 0, 5, false, true, 300, 60 ); //radial rainbow Bg, white sparks
        break;
      case 15:
        strip.colorSpinSimple( vertLineSegments, 1, 0, 0, 14, 1, 0, 0, 2, 250, 50 ); //rainbow half
        break;
      case 16:
        strip.setRainbowOffsetCycle(60, false);
        strip.runRainbowOffsetCycle(true);
        //white leds, rainbow background, no trails, not scanner, zero eyeszie
        strip.patternSweepRand( 15, white, -1, 0, 0, true, 0, 1, 60, 320 );
        break;
      case 17:
        for (int j = 0; j < 256; j++) {
          strip.randomColors(0, true, strip.Wheel(j & 255), 70, 8, 110);
        }
        break;
      default:
        break;
    }
    //if effectRota is true we'll advance to the effect index
    if (effectRota) {
      incrementEffectIndex();
    }
    strip.stripOff(); //clear the strip for the next effect
  }

  //unused effects
  //  for (int i = 0; i < 4; i++) {
  //    strip.gradientCycleRand( 4, 14, 24 * 7, direct, 90);
  //    direct = !direct;
  //  }

  //strip.sonarWavesRand( ringSegments, 6, 0, 14, 23, false, false, true, true, 120, 60);

  //strip.colorSpinRainbow( horizSegments, true, 200, 60);

  //strip.colorSpinRainbow( hexSegments, true, 200, 100);

  //strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  //strip.twinkle(tempRandPallet[0], tempRandPallet[1], 2, 15, 75, 10000);

  //strip.solidRainbowCycle(35, 2);

  //strip.colorSpinSimple( horizSegments, 3, 0, 0, 3, -1, 3, 0, 1, 170, 60 );

  //strip.segGradientCycleRand(horizSegments, 3, 7, 150, direct, 2, 80);

  //strip.shooterSeg(horizSegments, pallet, 3, 0, 8, 4, 1, 2, 4, false, false, 60, 150);

  //strip.colorSpinSimple( horizSegments, 1, 0, 0, 31, 1, 0, 0, 2, 170, 60 ); //rainbow half

  //trip.shooterSeg( hexSegments, pallet, 3, 0, true, 8, 1, 1, 2, 4, false, false, 60, 150);

  //strip.fireworksRand( 4, -1, 0, 2, 1, 60, 60);

  //strip.randomColors(-1, false, white.color32, 70, 5, 15000);

  // strip.doRepeatSimplePattern(simpleRepeatPattern, SIZE(simpleRepeatPattern), pallet, SIZE(pallet), 20, 25, 20, false);

}

//a quick shortening of the random color function, just to reduce the pattern function calls more readable
uint32_t RC() {
  return strip.randColor();
}

//sets the current brightness to index value in brightness array
//does not actually change brightness index, so it can be reset later
void setTempBrightness(int index) {
  if (index < numBrightnessLevels && index > 0) {
    strip.setBrightness(brightnessLevels[index]);
  }
}

//resets brightness to current brightnessIndex
void resetBrightness() {
  strip.setBrightness(brightnessLevels[brightnessIndex]);
}
