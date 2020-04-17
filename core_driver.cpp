#include "core_driver.h"

// Shift Register Data Control
// -----------------------------------------

inline void write_data_1(bool data)
{
  if(data)
    {
      #ifdef DEBUG_DRIVER 
      Serial.print(1); 
      #endif
      digitalWrite(DS, HIGH);
      delayMicroseconds(5);
    }
    #ifdef DEBUG_DRIVER 
    else 
    {
      Serial.print(0); 
      digitalWrite(DS, LOW);
      delayMicroseconds(5);
    }
    #endif
 
    digitalWrite(SH_CP, HIGH);
    delayMicroseconds(5);
    digitalWrite(SH_CP, LOW);
    delayMicroseconds(5);



    if(data)
    {
      digitalWrite(DS, LOW);
      delayMicroseconds(5);
    }
}

inline void write_data_8(unsigned char data)
{
  for(int i = 0; i < sizeof(unsigned char)*8; i++)
  {
    // write first bit and shift right
    write_data_1(data & 1);
    data >>= 1;
  }
  #ifdef DEBUG_DRIVER
  Serial.println(); 
  #endif
}


inline void write_data_32(unsigned long int data)
{
  for(int i = 0; i < sizeof(unsigned long int)*8; i++)
  {
    // write first bit and shift right
    write_data_1(data & 1);
    data >>= 1;
  }
  #ifdef DEBUG_DRIVER
  Serial.println(); 
  #endif
}

// Output and Sense Control
// ---------------------------------------------

inline void pulse()
{
  // turn on output
  digitalWrite(OE, LOW);
  digitalWrite(ST_CP, LOW);
  digitalWrite(ST_CP, HIGH);
  delayMicroseconds(PULSE_LENGTH);
  // turn off output
  digitalWrite(OE, HIGH);
  delayMicroseconds(PULSE_SPACE); 
}

inline void pulse_reset()
{
  // reset sense latch
  digitalWrite(LATCH_RESET, HIGH);
  delayMicroseconds(100);
  digitalWrite(LATCH_RESET, LOW);
  
  // turn on output
  digitalWrite(OE, LOW);
  digitalWrite(ST_CP, LOW);
  digitalWrite(ST_CP, HIGH); 
  
  delayMicroseconds(PULSE_LENGTH);
  
  // turn off output and clear shift registers
  digitalWrite(OE, HIGH);
  write_data_32(0);
  digitalWrite(ST_CP, LOW);
  digitalWrite(ST_CP, HIGH);
  delayMicroseconds(PULSE_SPACE);
}

inline bool pulse_sense()
{
  // reset sense latch
  digitalWrite(LATCH_RESET, HIGH);
  delayMicroseconds(100);
  digitalWrite(LATCH_RESET, LOW);
  
  // turn on output
  digitalWrite(OE, LOW);
  digitalWrite(ST_CP, LOW);
  digitalWrite(ST_CP, HIGH);
  
  delayMicroseconds(PULSE_LENGTH);

  // turn off output
  digitalWrite(OE, HIGH);

  delayMicroseconds(PULSE_SPACE);

  return digitalRead(SENSE_LATCH); 
}

inline bool pulse_sense_reset()
{
  // reset latch
  digitalWrite(LATCH_RESET, HIGH);
  delayMicroseconds(100);
  digitalWrite(LATCH_RESET, LOW);
  
   // turn on output
  digitalWrite(OE, LOW);
  digitalWrite(ST_CP, LOW);
  digitalWrite(ST_CP, HIGH);
  
  delayMicroseconds(PULSE_LENGTH);
  
  // turn off output and clear shift registers
  digitalWrite(OE, HIGH);
  write_data_32(0);
  digitalWrite(ST_CP, LOW);
  digitalWrite(ST_CP, HIGH);

  delayMicroseconds(PULSE_SPACE);

  return digitalRead(SENSE_LATCH); 
}

// Core Array Bit Access Control (Reads/Writes, destructive and preservative)
// ------------------------------------------------------------

inline void write_core(char x, char y, bool value)
{
  // write binary 1's to core
  if(value == 1)
  {
    write_data_8(0);
    write_data_8(1 << x);
    write_data_8(0);
    write_data_8(1 << y);
  }
  // write binary 0's to core
  else
  {
    write_data_8(1 << x);
    write_data_8(0);
    write_data_8(1 << y);
    write_data_8(0);
  }
  pulse_reset();
}

inline void write_core_array(bool values[8][8])
{
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
      write_core(x, y, values[x][y]);
    }
  }
}

inline bool read_preserve(char x, char y)
{
  // tries to write a zero => pulse means it was a 1
  write_data_8(1 << x);
  write_data_8(0);
  write_data_8(1 << y);
  write_data_8(0);
  bool state = pulse_sense_reset();

  // restore the state
  write_core(x, y, state);
  return state;
}

inline bool read_destroy(char x, char y)
{
  // read and leave state destroyed
  // tries to write a zero => pulse means it was a 1
  write_data_8(1 << x);
  write_data_8(0);
  write_data_8(1 << y);
  write_data_8(0);
  return pulse_sense_reset();
}

inline bool** read_all_preserve()
{
  // declare empty 8x8 array of booleans
  bool** values = (bool**) calloc(64, sizeof(bool));
  for(int i = 0; i < 8; i++) values[i] = (bool*) malloc(8*sizeof(bool));

  // read array of cores and restore the states
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
      values[x][y] = read_preserve(x, y); 
    }
  }
  return values;
}

inline bool** read_all_destroy()
{
  // declare empty 8x8 array of booleans
  bool** values = (bool**) calloc(64, sizeof(bool));
  for(int i = 0; i < 8; i++) values[i] = (bool*) malloc(8*sizeof(bool));

  // read array of cores and leave the states destroyed
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
      values[x][y] = read_destroy(x, y); 
    }
  }
  return values;
}

