// Use one 74HC595 to control a CC/CA seven-segment display
//https://www.electronicwings.com/users/SMRITISINGH/codes/dice_using_7_segment_display_and_attiny85/1.0.0/Dice%20With%207%20segment%20display%20and%20Attiny85
//https://www.electronicwings.com/users/SMRITISINGH/projects/1309/dice-using-7-segment-display-and-attiny85
//https://www.youtube.com/watch?v=yi_e0TZ0uKw
//https://www.tinkercad.com/things/jz9WaizxM4N-dice-with-7segment-display-and-attiny85/editel
//https://iotprojectsideas.com/mini-weather-station-using-dht22-attiny85/

#define Tiny                  //must be running at 16 Mhz
#define use_DHT               // if not set use dhtnew
   
//7-seg display
//remove remarks if u r using CC 7-seg. display
//#define segDISPLAY CATHODE
const int ledPin   = 0;       // Common pin

//74HC595 bit shifter
const int clockPin = 2;       // pin 11 of 74HC595 (SHCP)
const int latchPin = 3;       // pin 12 of 74HC595 (STCP)
const int dataPin  = 4;       // pin 14 of 74HC595 (DS)

#ifdef  Tiny
  const int tempPin  = 1;
#else
  const int tempPin  = 5;
#endif

//DHT
#ifdef use_DHT
  #include  <DHT.h>
  #define   DHTTYPE    DHT22     // DHT 22 (AM2302)
  DHT dht   (tempPin, DHTTYPE);  // Define Temp Sensor
#endif

#ifdef use_dhtnew
  #include <dhtnew.h>
  DHTNEW mySensor(tempPin);
  DHTNEW.setType(22)
#endif

// digit pattern for a 7-segment display
const byte digit[] =
//https://en.wikipedia.org/wiki/Seven-segment_display_character_representations
//https://components101.com/displays/7-segment-display-pinout-working-datasheet
{//Dgfedcba
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111,  // 9
  B10000000,  // DP
  B01100011,  // upper 0
  B00100100,  // percent
  B00000000,  // OFF
  B01000000,  // -
  B01001001   // =
};

const byte snake[] =
{//Dgfedcba
  B00100000,  // f
  B00000001,  // a
  B00000010,  // b
  B01000000,  // g
  B00010000,  // e
  B00001000,  // d
  B00000100,  // c
  B01000000,  // g
  B00100000,  // f
  B00000000   // OFF
};

  float   meting;
  String  mychars;
  int     val,len,i,j,k;
  byte    dig;
  byte    OFF=13;
  int     wacht=750;
  int     errcode;
  bool    fun,whole;

void setup() {

  #ifndef  Tiny
   Serial.begin(115200);
   while (!Serial);
  #endif
  
  pinMode(dataPin,  OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(tempPin,  INPUT);
  pinMode(ledPin,   OUTPUT);

  #ifdef segDISPLAY
     digitalWrite(ledPin, LOW);
  #else 
     digitalWrite(ledPin, HIGH);
  #endif

  #ifndef  Tiny
    Serial.println(F("DHTbegin"));
  #else
    fun=true;
       for (int n=0;n<10;n++){             // showoff
       LEDwrite(n); delay(100);
    }
    fun=false;
  #endif

  #ifdef use_DHT
    dht.begin();
  #else
    mySensor.setDisableIRQ(false);
  #endif
  delay (1000);

}

void loop() {

    #ifdef use_DHT
      meting  =   dht.readTemperature();
    #else
      errcode =   mySensor.read();
      meting  =   mySensor.getTemperature(); // read temperature
    #endif
    
    DisplayValue  (meting,0);             // temp
    delay         (wacht);
    LEDwrite      (OFF);                 // display nothing
    delay         (wacht*5);

    #ifdef use_DHT
      meting =    dht.readHumidity();
    #else
      errcode =   mySensor.read();
      meting =    mySensor.getHumidity(); // Read humidity
    #endif
    
    DisplayValue  (meting,1);             // humidity
    delay         (wacht);
    LEDwrite      (OFF);                 // display nothing
    delay         (wacht*3);
}
    

void LEDwrite(int data) { 
  // turn off the output of 74HC595
  digitalWrite(latchPin, LOW);

  // update data to output from 74HC595
#ifdef segDISPLAY
  // It's a CA LED invert num
  if (fun){
    shiftOut(dataPin, clockPin, MSBFIRST, snake[data]);
  } else {
    shiftOut(dataPin, clockPin, MSBFIRST, digit[data]);
  }
#else
  // It's a CC LED 
  if (fun){
    shiftOut(dataPin, clockPin, MSBFIRST, ~snake[data]);
  } else {
    shiftOut(dataPin, clockPin, MSBFIRST, ~digit[data]);
  }
#endif

  // turn on the output of 74HC595
  digitalWrite(latchPin, HIGH);
}



void DisplayValue(float waarde,bool hum){ // display a value like 25.4 on 1 7 seg display including dot 2,5.,4,o
  mychars = String(waarde);
  len     = mychars.length();
  if (mychars.endsWith(".00")){//99.00 if no decimals
    whole=true;
    k = 0;
    len = len-3;
    mychars=mychars.substring(0,len);  
  }  else {k=-2;whole=false;}
  i=0;
  for (j=0;j<len+k;j++){ //17.5 2.3
       val  = mychars.substring(i,i+1).toInt();
       dig  = digit[val];
       if (mychars.substring(i+1,i+2)=="." && whole==false){    
          bitSet(dig,7);
          i++;
       }
       i++;
       ShiftIt(dig);      // display value
  } 
    if (hum){
       dig  = digit[12];    
    }else{
       dig  = digit[11];   
    } 
    ShiftIt(dig);         // display degree or percent
}

void ShiftIt(byte digi){
   LEDwrite      (OFF);                 // display nothing
   delay         (250);

   #ifndef  Tiny
    Serial.println  (meting);
    Serial.println  (digi,BIN);
   #else
    digitalWrite    (latchPin, LOW);
    #ifdef segDISPLAY
      shiftOut      (dataPin, clockPin, MSBFIRST, digi);
    #else
      shiftOut      (dataPin, clockPin, MSBFIRST, ~digi);
    #endif
     digitalWrite   (latchPin, HIGH);  
     delay(wacht);
   #endif

   #ifndef  Tiny
      Serial.println();
  #endif

  }
