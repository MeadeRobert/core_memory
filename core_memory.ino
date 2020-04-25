/*
1: read array (binary)
2: read array (characters)
3: read bit (protective read)
4: read bit (destructive read)
5: write array (6 ascii characters)
6: write bit (bit)
7: help
*/
#include "core_driver.cpp"

int input_selection;  //don't really need an initialized value
int x_coordinate;
int y_coordinate;
int bit_value;

void setup() {
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

  // init menu
  Serial.print("\n\n ----Command List---- \n\n");
  Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
  bit_value = 1;  //testing value
}

char output[64]; // declare output buffer
void loop() {
while (Serial.available()){
  
  input_selection = Serial.parseInt();
  Serial.flush();
  
  switch (input_selection){
    
    case 0:
      //serial.parseInt() reads a 0 when no commands are actively being sent,and this is cheaper than another while loop
    break;

    //READ ARRAY (all bits)
    case 1:
      Serial.println(F("You have selected READ ARRAY (all bits). The characters stored in the array are: "));
      /////////////////////////////
      //put memory access code here
      /////////////////////////////
      output[8] = '\0';
      for(int x=0; x<6; x++) {
        for(int y=0; y<8; y++) {
          if(read_preserve(x,y))output[y] = '1';
          else output[y] = '0';
        }
        Serial.println(output);
      }
      Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
    break;

    //READ ARRAY (Characters)
    case 2:
      Serial.println(F("You have selected READ ARRAY (Characters). The characters stored in the array are: "));

      // initialize output buffer and populate with array chars
      output[6] = '\0';
      for(int x=0; x<6; x++) {
        char c = 0;
        for(int y=0; y<8; y++) {
          c = c | (read_preserve(x,y) << (7-y));
        }
        output[x] = c;
      }
      Serial.println(output);
      Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
    break;

    //READ BIT (does not destroy stored value)
    case 3:
      Serial.println(F("You have selected READ BIT (protective read). Please enter the the byte row you wish to read (0:5)\n "));
      while(!Serial.available()){}                                                        //wait for input
      x_coordinate = Serial.parseInt();                                                   //grab the next integer input
                                  
      while (x_coordinate > 5 || x_coordinate < 0){                                       //make sure it has a valid index  
        Serial.println(F("That is not a valid row, please enter a number from 0 to 5"));    
        while(!Serial.available()){} //wait for input                                   
        x_coordinate = Serial.parseInt();
        Serial.flush();
      }
      
      Serial.print("you have selected row ");                                         
      Serial.print(x_coordinate);
      Serial.println(F("\n Please enter the index (0:7) of the bit you wish to read in the row"));  
     
      while(!Serial.available()){}                                                        //wait for input
      y_coordinate = Serial.parseInt();                                                   //grab the next integer input
      
      while (y_coordinate > 7 || y_coordinate < 0){                                       //make sure it has a valid index
        Serial.println(F("That is not a valid index, please enter a number from 0 to 7"));
        while(!Serial.available()){} //wait for input
        y_coordinate = Serial.parseInt();
        Serial.flush();
      }

      // read value; preserve core state
      bit_value = read_preserve(x_coordinate, y_coordinate);
            
      Serial.print("The value of ");
      Serial.print(x_coordinate);
      Serial.print(", ");
      Serial.print(y_coordinate);
      Serial.print(" is ");
      Serial.println(bit_value);
      Serial.println("This value has been preserved in memory");

      // print menu
      Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
    break;

    //READ BIT (destroys stored value)
    case 4:
      Serial.println(F("You have selected READ BIT (destructive read). Please enter the the byte row you wish to read (0:5)\n "));
      while(!Serial.available()){}                                                        //wait for input
      x_coordinate = Serial.parseInt();                                                   //grab the next integer input
                                  
      while (x_coordinate > 5 || x_coordinate < 0){                                       //make sure it has a valid index  
        Serial.println(F("That is not a valid row; please enter a number from 0 to 5"));    
        while(!Serial.available()){} //wait for input                                   
        x_coordinate = Serial.parseInt();
        Serial.flush();
      }
      
      Serial.print("you have selected row ");                                         
      Serial.print(y_coordinate);
      Serial.println(F("\n Please enter the index (0:7) of the bit you wish to read in the row"));
     
      while(!Serial.available()){}                                                        //wait for input
      y_coordinate = Serial.parseInt();                                                   //grab the next integer input
      
      while (y_coordinate > 7 || y_coordinate < 0){                                       //make sure it has a valid index
        Serial.println(F("That is not a valid index; please enter a number from 0 to 7"));
        while(!Serial.available()){} //wait for input
        y_coordinate = Serial.parseInt();
        Serial.flush();
      }

      // read value; neglect core state preservation
      bit_value = read_destroy(x_coordinate,y_coordinate);
            
      Serial.print("The value of row ");
      Serial.print(x_coordinate);
      Serial.print(", index ");
      Serial.print(y_coordinate);
      Serial.print(" is ");
      Serial.println(bit_value);
      Serial.println(F("This value has been destroyed in memory"));

      // print menu
      Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
    break;

    //WRITE ARRAY (6 ascii characters)
    case 5:
    Serial.println(F("You have selected WRITE ARRAY (writes 6 ASCII characters to memory. Please enter 6 characters."));

    while(!Serial.available()){}
    char buffer[7];
    Serial.readBytes(buffer, 6);
    buffer[6] = '\0';
    Serial.flush(); // delete extra input

    // write bytes to core array
    for(int x = 0; x < 6; x++) {
      for(int y = 0; y < 8; y++) {
        write_core(x,y,(buffer[x] >> (7-y)) & 1);
      }
    }

    // print menu
    Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
    break;

    //WRITE BIT (writes a single bit)
    case 6:
    Serial.println(F("You have selected WRITE BIT. Please enter the the byte row you wish to write to (0:5)\n "));
      while(!Serial.available()){}                                                        //wait for input
      x_coordinate = Serial.parseInt();                                                   //grab the next integer input
                                  
      while (x_coordinate > 5 || x_coordinate < 0){                                       //make sure it has a valid index  
        Serial.println(F("That is not a valid row; please enter a number from 0 to 5"));    
        while(!Serial.available()){} //wait for input                                   
        x_coordinate = Serial.parseInt();
        Serial.flush();
      }
      
      Serial.print("you have selected row ");                                         
      Serial.print(x_coordinate);
      Serial.println(F("\n Please enter the index (0:7) of the bit you wish to write to in the row"));  
     
      while(!Serial.available()){}                                                        //wait for input
      y_coordinate = Serial.parseInt();                                                   //grab the next integer input
      
      while (y_coordinate > 7 || y_coordinate < 0){                                       //make sure it has a valid index
        Serial.println(F("That is not a valid index; please enter a number from 0 to 7"));
        while(!Serial.available()){} //wait for input
        y_coordinate = Serial.parseInt();
        Serial.flush();
      }

      Serial.println(F("Please enter the value that you wish to write (1 or 0)"));
      while(!Serial.available()){}                                                        //wait for input
      bit_value = Serial.parseInt();                                                      //grab the next integer input
    
      while ((bit_value != 0) && (bit_value != 1)){                                       //make sure it has a valid index
        Serial.println(F("That is not a valid value; please enter either 0 or 1"));
        while(!Serial.available()){} //wait for input
        x_coordinate = Serial.parseInt();
        Serial.flush();
      }
     
      write_core(x_coordinate, y_coordinate, bit_value);
      
      Serial.print(bit_value);
      Serial.print(" has been written to row ");
      Serial.print(x_coordinate);
      Serial.print(", index ");
      Serial.println(y_coordinate);

    // print menu
    Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
    break;

    case 7:

    Serial.println(F("Writing Zeros to Array..."));
    // zero the array
    for(int x = 0; x < 6; x++) {
      for(int y = 0; y < 8; y++) {
        write_core(x,y,0);
      }
    }
    
     // print menu
    Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
    break;

    case 8:
    Serial.println(F("1: Read array (all bits). This does not take any inputs, and will dump all 48 bits of memory to the console"));
    Serial.println(F("2: Read array (characters). This dumps the content of memory as a 6 ASCII character string."));
    Serial.println(F("3: Read bit (protective read). This takes the location of the bit of interest as a row number and index, and outputs the value of the bit to the console. This does not destroy the value stored in the selected bit."));
    Serial.println(F("4: Read bit (destructive read). This takes the location of the bit of interest as a row number and index, and outputs the value of the bit to the console. This does WILL DESTROY the value stored in the selected bit."));
    Serial.println(F("5: Write array (6 ascii characters). This takes each character sequentially from the console, with each character on a newline."));
    Serial.println(F("6: Write bit (binary value). This takes the location of the bit of interest as a row number and index, and writes the given value to the selected bit"));
    Serial.println(F("7: Clear Array; writes zeros to all cores"));
    Serial.println(F("8: Help text."));

    // print menu
    Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: clear array (zeros) \n 8: help text \n"));
    break;

    default:
      Serial.println(F("That is not a valid input. Please enter a number from 0-8. \n For help, enter '8'"));
    break;
    }
  }
}
