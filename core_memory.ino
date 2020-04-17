#include "core_driver.cpp"


// testing results
/*
 *  + + x x x x x x
 *  
 */

bool values[8][8] = 
  {
  {0, 1, 0, 0, 1, 0, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
  };

void setup()
{
  // setup serial connection
  Serial.begin(9600);
  
  // config pins
  pinMode(DS, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(MR, OUTPUT);
  pinMode(LATCH_RESET, OUTPUT);
  pinMode(SENSE_LATCH, INPUT);
  
  // set default pin states
  digitalWrite(DS, LOW);
  digitalWrite(OE, HIGH);
  digitalWrite(ST_CP, LOW);
  digitalWrite(SH_CP, LOW);
  digitalWrite(MR, HIGH);
}



//unsigned long int a = 1;
bool a = 1;

int x = 0;
int y = 3;

void loop()
{ 
// DO NOT RUN THIS WITH CORES ATTACHED
// FIRE WILL RESULT
//  write_data_8(0x01);
//  write_data_8(0x00);
//  write_data_8(0x01);
//  write_data_8(0x00);
//  digitalWrite(OE, LOW);
//  digitalWrite(ST_CP, LOW);
//  digitalWrite(ST_CP, HIGH);
//  delay(1000);
//  digitalWrite(ST_CP, LOW);

//// MAY RUN THIS WITH CORES ATTACHED

  Serial.println("writes");

  for(x = 5; x < 6; x++) {
    for(y = 0; y < 8; y++) {
      write_core(x,y,(y % 2));
      Serial.println((y % 2));
      delay(200);
    }
  }
  delay(2000);
  Serial.println("reads");

  for(x = 5; x < 6; x++) {
    for(y = 0; y < 8; y++) {
      Serial.println(read_preserve(x,y));
      delay(200);
    }
  }

  Serial.println("restart");
 
}

