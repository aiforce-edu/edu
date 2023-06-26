#define pinSW1  D2
#define pinSW2  D3
#define pinLED1 D4
#define pinLED2 D7

const int NUM_SW  = 2;
const int NUM_LED = 2;

// index 0 : about sw1, index 1 : about sw2
int  arrSW[NUM_SW] = {pinSW1, pinSW2};
bool cState[NUM_SW] = {false,false};
bool lState[NUM_SW] = {false,false};

// index 0 : about red led, index 1 : about blue led
int  arrLED[NUM_LED] = {pinLED1, pinLED2};
bool valLED[NUM_LED] = {false,false};

void setup()
{
  pinMode(pinSW1, INPUT);
  pinMode(pinSW2, INPUT);
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
}

void loop() 
{
  for (int i=0 ; i < NUM_SW ; i++)
  {
    lState[i] = cState[i]; // Switch value update
    cState[i] = digitalRead(arrSW[i]); // read switch value
  }
  delay(10); // for debouncing

  for(int i=0 ; i < NUM_SW ; i++)
  {
    if(cState[i] && (cState[i] != lState[i])) // Switch pushed
    {
      valLED[i] = !valLED[i];
      digitalWrite(arrLED[i], valLED[i]);
    }
  }
}
