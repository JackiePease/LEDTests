class spiral{
public:
  void setup(int aStartLED, int aLength);
  void advance();
protected:
  int iStartLED;
  int iLength;
  int iState;
  int iPixelsFedIn;
  int iRandom;
  int iLoopCount;
  int iAnimationCount;
};