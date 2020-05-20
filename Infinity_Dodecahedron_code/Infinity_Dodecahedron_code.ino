#include <PixelStrip.h>
#include "segmentDefs.h"

#define PIN D8

const uint16_t stripLength = 210;
const uint8_t stripType = NEO_GRB + NEO_KHZ800;
PixelStrip strip = PixelStrip(stripLength, PIN, stripType); //12 NEO_GRB

//Define some colors we'll use frequently
RGB white = { 255, 255, 255, strip.Color(255, 255, 255) };
RGB UCLAGold = { 254, 187, 54, strip.Color(254, 187, 54) };
RGB UCLABlue = { 83, 104, 149, strip.Color(83, 104, 149) };
RGB off = { 0, 0, 0, 0 };
RGB red = { 255, 0, 0, strip.Color(255, 0, 0) };
RGB orange = { 255, 43, 0, strip.Color(255, 43, 0) };
RGB ltOrange = { 255, 143, 0, strip.Color(255, 143, 0) };
RGB yellow = { 255, 255, 0, strip.Color(255, 255, 0) };
RGB green = { 0, 128, 0, strip.Color(0, 128, 0) };
RGB blue = { 0, 0, 255, strip.Color(0, 0, 255) };
//RGB indigo = { 75, 0, 130, strip.Color( 75, 0, 130) };
//RGB violet = { 238, 130, 238, strip.Color(238, 130, 238) };
RGB purple = {123, 7, 197, strip.Color(123, 7, 197) };
//RGB pink = {225, 0, 127, strip.Color(225, 0, 127) };

//define pallet array, contains 32bit representations of all colors used in patterns
uint32_t pallet[9] = { off.color32, white.color32, UCLAGold.color32, UCLABlue.color32, blue.color32, yellow.color32, red.color32, green.color32, purple.color32 };
//                   {------0-----, ------1-----, ---------2-------, ---------3-------, -----4-----, -------5------, -----6-----, ------7------ -------8--------}

uint32_t christmasPallet[5] = { red.color32, blue.color32, green.color32, yellow.color32, purple.color32 };
//define rainbow array
//RGB rainbow[8]= { white, red, orange, yellow, green, blue, indigo, violet };
//              {---0--, -1-, --2---, --3---, --4--, --5-, --6---, --7--- }

uint32_t firePallet[3] = { red.color32, ltOrange.color32, white.color32 };

uint32_t tempRandPallet[5]; //pallet for random colors (length sets number of colors used by randomColors effect)
byte simpleRepeatPatternRand[10] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4};

byte wavepattern[]  = { 6, 1 };
byte wavepattern2[] = { 5, 4 };
byte wavepattern3[] = { 6, 7 };
byte wavepattern4[] = { 8, 7 };
byte christmasWavePattern[5] = { 0, 1, 2, 3, 4};

//for simple repeart drawing functions
byte simpleRepeatPattern[5] = {8, 6, 7, 4, 5}; //{ 4, 0, 5, 0, 6, 0, 7, 0};

byte normalBrightness = 150;

void setup() {
  strip.begin();
  strip.setBrightness(normalBrightness);

  strip.show();
  Serial.begin(9600);

  randomSeed(ESP.getCycleCount()); //generate a random seed
}


//todo: write pattern cycling function to shift through a set of given patterns
//use function to do lightning pattern
//change random light set to allow fading bssed on fire function?
void loop() {
  boolean direct = true;
  
  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  strip.twinkle(tempRandPallet[0], tempRandPallet[1], 2, 15, 25, 10000);
  
  strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
  strip.randomColorSet(off.color32, true, tempRandPallet, SIZE(tempRandPallet), 60, 5, 12000);

//  for (int i = 0; i < 3; i++) {
//    strip.genRandPallet( tempRandPallet, SIZE(tempRandPallet) );
//    strip.doRepeatSimplePattern(simpleRepeatPatternRand, SIZE(simpleRepeatPatternRand), tempRandPallet, SIZE(tempRandPallet), 20, 25, 20, false);
//  }
  strip.stripOff();
  strip.colorSpinSimple( horizSegments, 3, 0, 0, 3, -1, 3, 0, 1, 170, 60 );

  strip.stripOff();
  strip.colorSpinSimple( hexSegments, 3, 0, 0, 7, -1, 7, 0, 1, 170, 60 );

  //strip.segGradientCycleRand(horizSegments, 3, 7, 150, direct, 2, 80);

  //strip.shooterSeg(horizSegments, pallet, 3, 0, 8, 4, 1, 2, 4, false, false, 60, 150);

  strip.stripOff();
  strip.colorSpinSimple( horizSegments, 1, 0, 0, 31, 1, 0, 0, 2, 170, 60 ); //rainbow half

  strip.shooterSeg( hexSegments, pallet, 3, 0, 8, 1, 1, 2, 4, false, false, 60, 150);

  strip.sparkSeg( ringSegments, 20, 1, 1, white.color32, 1, 0, 5, true, 150, 60 ); //radial rainbow Bg, white sparks

  strip.fireworksRand( 3, -1, 0, 2, 1, 60, 60);

  strip.stripOff();
  strip.fillStrip(orange.color32, false);
  strip.doFireV2Seg( vertLineSegments, firePallet, SIZE(firePallet), 45, 120, 400, 40);

  strip.shooterSeg( vertLineSegments, pallet, 3, 0, 8, 2, 1, 2, 4, false, false, 60, 150);
  strip.shooterSeg( vertLineSegments, pallet, 3, 0, 8, 2, 1, 2, 4, true, false, 60, 150);

  strip.colorSpinSimple( vertLineSegments, 1, 0, 0, 7, 1, 0, 0, 2, 170, 60 ); //rainbow half

  strip.solidRainbowCycle(35, 2);

  strip.segGradientCycleRand(ringSegments, 4, 7, 150, direct, 1, 80);

  strip.rainbowWave( ringSegments, 100, true, 8, 10);

  //strip.randomWaves( ringSegments, 3, 2, 2, 50, direct, 7, 10);

  for (int i = 0; i < 3; i++) {
    direct = !direct;
    strip.singleWave( ringSegments, RC(), 0, 1, ringSegments.numSegs - 1, direct, 3, 10);
  }

  //white leds, rainbow background, no trails, not scanner, zero eyeszie
  strip.patternSweepRand( 8, white.color32, -1, 0, 0, true, 0, 1, 60, 320 );

  for (int i = 0; i < 4; i++) {
    strip.gradientCycleRand( 4, 7, 24 * 7, direct, 90);
    direct = !direct;
  }

  strip.simpleStreamerRand( 3, 0, 3, 3, 0, false, 24 * 4, 70);

  //  for (int i = 0; i < 4; i++) {
  //    strip.rainbow(35);
  //  }

  //strip.theaterChaseRainbow(off.color32, 70, 4, 2);

  //  strip.stripOff();
  //  for (int j = 0; j < 4; j++) {
  //    if ((j % 2) == 0 ) {
  //      strip.colorWipeRainbow(40, stripLength, true, false, false, true);
  //      strip.colorWipe(off.color32, stripLength, 40, true, false, true);
  //    } else {
  //      strip.colorWipeRainbow(40, stripLength, false, false, false, true);
  //      strip.colorWipe(off.color32, stripLength, 40, false, false, true);
  //    }
  //  }

  strip.twinkle(pallet[wavepattern[0]], pallet[wavepattern[1]], 2, 15, 25, 10000);
  strip.twinkle(pallet[wavepattern2[1]], pallet[wavepattern2[0]], 2, 15, 25, 10000);
  strip.twinkle(pallet[wavepattern3[1]], pallet[wavepattern3[0]], 2, 15, 25, 10000);
  strip.twinkle(pallet[wavepattern4[0]], pallet[wavepattern4[1]], 2, 15, 25, 10000);
  //strip.twinkleSet(0, christmasPallet, SIZE(christmasPallet), 2, 60, 15, 12000);

  //random colors, blank BG, 6 length trails, no scanner, color mode 1
//  for (int i = 0; i < 3; i++) {
//    strip.patternSweepRand( 6, -1, 0, 1, 5, false, 0, 1, 60, 24 * 8 );
//  }

  for (int i = 0; i < 2; i++) {
    //white leds, rainbow background, no trails, not scanner, zero eyeszie
    strip.patternSweepRainbowRand( 4, 0, 1, 6, true, 0, 50, 24 * 8);
  }

  for (int j = 0; j < 256; j++) {
    strip.randomColors(off.color32, true, strip.Wheel(j & 255), 70, 8, 110);
  }

  strip.randomColors(-1, false, white.color32, 70, 5, 15000);

  //strip.stripOff();
  //strip.setBrightness(90);
  // strip.rainbowSingleWave( starSegments, 1, 10, 2, 20, 15);
  //strip.setBrightness(normalBrightness);

  strip.doRepeatSimplePattern(simpleRepeatPattern, SIZE(simpleRepeatPattern), pallet, SIZE(pallet), 20, 25, 20, false);

  //  for (int i = 0; i < 3; i++) {
  //    strip.patternSweepRepeatRand(3, 0, 0, 2, 3, false, false, 0, 0, 1, 65, 200 );
  //  }


  //strip.randomColorSet(off.color32, true, christmasPallet, SIZE(christmasPallet), 100, 3, 15000);
  //
  //  strip.fire(yellow.color32, true, red.color32, 20, 20, 40, 50, 10000);
  //  strip.fire(red.color32, true, blue.color32, 20, 20, 40, 50, 10000);
  //  strip.fire(green.color32, true, blue.color32, 20, 20, 40, 50, 10000);

}

//a quick shortening of the random color function, just to reduce the pattern function calls more readable
uint32_t RC() {
  return strip.randColor();
}
