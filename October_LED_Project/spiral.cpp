#include "spiral.h"
#include "FastLED.h"

extern CHSV ledsTarget[];
extern bool glowUpEclairs[];

extern uint8_t OREO_LENGTH;
extern uint8_t HARIBO_LENGTH;
extern uint8_t WISPA_LENGTH;
extern uint8_t ECLAIR_LENGTH;

extern uint8_t NOTHING_HUE;
extern uint8_t HARIBO_HUE;
extern uint8_t OREO_HUE;
extern uint8_t WISPA_HUE;
extern uint8_t ECLAIR_HUE;

extern uint8_t NOTHING_SATURATION;
extern uint8_t HARIBO_SATURATION;
extern uint8_t OREO_SATURATION;
extern uint8_t WISPA_SATURATION;
extern uint8_t ECLAIR_SATURATION;

extern uint8_t NOTHING_VALUE;
extern uint8_t HARIBO_VALUE;
extern uint8_t OREO_VALUE;
extern uint8_t WISPA_VALUE;
extern uint8_t ECLAIR_VALUE;

#define FEEDING_IN_NOTHING 0
#define FEEDING_IN_HARIBO 1
#define FEEDING_IN_OREO 2
#define CRAZY_WISPA_ANIMATION 3

void spiral::setup(int aStartLED, int aLength){
  iStartLED = aStartLED;
  iLength = aLength;
  // Start off feeding nothing in
  iState = FEEDING_IN_NOTHING;
  iPixelsFedIn = 0;
  iLoopCount = 0;
  iRandom = random(3, 8); // Only move when number of loops is a multiple of this -> speed of animation in spiral
                          // Change after eclairs

}

void spiral::advance() {


  if (iState == CRAZY_WISPA_ANIMATION){
        if (iPixelsFedIn <= WISPA_LENGTH){

          float fGlowUp = float(iPixelsFedIn) / float(WISPA_LENGTH); 

          for(int i = iStartLED + iLength - 10; i < iStartLED + iLength; i++) {
            ledsTarget[i] = CHSV(WISPA_HUE, WISPA_SATURATION, fGlowUp * WISPA_VALUE);
          }

          for(int i = iStartLED; i < iStartLED + iLength - 10; i++ ) {
            int chance = random(100);       
            if ((float(chance) * fGlowUp) > 25){
              glowUpEclairs[i] = true;                  
            }             
          }
        }

        if (iPixelsFedIn > WISPA_LENGTH && iPixelsFedIn < ECLAIR_LENGTH + WISPA_LENGTH) {
          float fFade = float(ECLAIR_LENGTH + WISPA_LENGTH - iPixelsFedIn) / float(ECLAIR_LENGTH);           
          for(int i = iStartLED + iLength - 10; i < iStartLED + iLength; i++) {
            if (fFade > 0.12){
              ledsTarget[i] = CHSV(WISPA_HUE, WISPA_SATURATION, (fFade) * WISPA_VALUE);
            } else {
              ledsTarget[i] = CHSV(0, 0, 0);
            }
          }

          for(int i = iStartLED; i < iStartLED + iLength - 10; i++ ) {
            int chance = random(100);
            if ((float(chance) * fFade) > 25){
              ledsTarget[i] = CHSV(ECLAIR_HUE, ECLAIR_SATURATION, ECLAIR_VALUE);
            } else {
                    ledsTarget[i] = CHSV(NOTHING_HUE, 0, 0);                    
            }
          }
        }
  }   
  
  iLoopCount++;
  if (iLoopCount%iRandom == 0){

    for(int i = iStartLED + iLength - 2; i >= iStartLED; i--) {
        ledsTarget[i + 1] = ledsTarget[i];
    }
 
    switch (iState) {
      case FEEDING_IN_NOTHING:
        {
            ledsTarget[iStartLED] = CHSV(NOTHING_HUE, NOTHING_SATURATION, NOTHING_VALUE);
            // We weren't feeding anything in
            // Randomly decide if we should feed something in
            int chance = random(100);
            if ((chance > 75 && chance <= 85)) {
              // Start feeding in HARIBO
              iState = FEEDING_IN_HARIBO;
            } else if (chance > 85 && chance <= 98) {
              // Start feeding in OREO
              iState = FEEDING_IN_OREO;
            } else if (chance > 98) {
              iState = CRAZY_WISPA_ANIMATION;
            }
            // else stay feeding nothing in
        }      
        break;
      case FEEDING_IN_HARIBO:
        {    
            ledsTarget[iStartLED] = CHSV(HARIBO_HUE, HARIBO_SATURATION, HARIBO_VALUE/(iPixelsFedIn + 1));
            iPixelsFedIn++;
            if (iPixelsFedIn == HARIBO_LENGTH) {
              // We've finished feeding it in
              iPixelsFedIn = 0;
              iState = FEEDING_IN_NOTHING;
            }
        }
        break;
      case FEEDING_IN_OREO:
        {
            ledsTarget[iStartLED] = CHSV(OREO_HUE, OREO_SATURATION, OREO_VALUE/(iPixelsFedIn + 1));
            iPixelsFedIn++;
            if (iPixelsFedIn == OREO_LENGTH) {
              // We've finished feeding it in
              iPixelsFedIn = 0;
              iState = FEEDING_IN_NOTHING;
            }
        }
        break;    
      case CRAZY_WISPA_ANIMATION:
        {
            // Just update now, as related to timing for OREO and HARIBO
            iPixelsFedIn++;
            ledsTarget[iStartLED] - CHSV(0, 0, 0);
            if (iPixelsFedIn == WISPA_LENGTH + ECLAIR_LENGTH) {
              for(int i = iStartLED; i < iStartLED + iLength; i++) {
                ledsTarget[i] = CHSV(0, 0, 0);
              }
              iPixelsFedIn = 0;
              iState = FEEDING_IN_NOTHING;
              iRandom = random(3, 8); // change speed of animation in spiral
            }
        }
    }
  }
}
