/*
1: read array (binary)
2: read array (characters)
3: read bit (protective read)
4: read bit (destructive read)
5: write array (6 ascii characters)
6: write bit (bit)
7: help


*/

int input_selection;  //don't really need an initialized value
int x_coordinate;
int y_coordinate;
int bit_value;

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n ----Command List---- \n\n");
  Serial.print(F(" 1: read array (all bits) \n 2: read array (characters) \n 3: read bit (protective read) \n 4: read bit (destructive read) \n 5: write array (6 ascii characters) \n 6: write bit (binary value) \n 7: help text \n"));
  bit_value = 1;  //testing value
}

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
    break;

    //READ ARRAY (Characters)
    case 2:
      Serial.println(F("You have selected READ ARRAY (Characters). The characters stored in the array are: "));
      /////////////////////////////
      //put memory access code here
      /////////////////////////////
    break;

    //READ BIT (does not destroy stored value)
    case 3:
      Serial.println(F("You have selected READ BIT (protective read). Please enter the the byte row you wish to read (0:5)\n "));
      while(!Serial.available()){}                                                        //wait for input
      y_coordinate = Serial.parseInt();                                                   //grab the next integer input
                                  
      while (y_coordinate > 5 || y_coordinate < 0){                                       //make sure it has a valid index  
        Serial.println(F("That is not a valid row, please enter a number from 0 to 5"));    
        while(!Serial.available()){} //wait for input                                   
        y_coordinate = Serial.parseInt();
        Serial.flush();
      }
      
      Serial.print("you have selected row ");                                         
      Serial.print(y_coordinate);
      Serial.print(F("\n Please enter the index (0:7) of the bit you wish to read in row"));  
     
      while(!Serial.available()){}                                                        //wait for input
      x_coordinate = Serial.parseInt();                                                   //grab the next integer input
      
      while (x_coordinate > 7 || x_coordinate < 0){                                       //make sure it has a valid index
        Serial.println(F("That is not a valid index, please enter a number from 0 to 7"));
        while(!Serial.available()){} //wait for input
        x_coordinate = Serial.parseInt();
        Serial.flush();
      }

      /////////////////////////////
      //put memory access code here
      /////////////////////////////
            
      Serial.print("The value of ");
      Serial.print(x_coordinate);
      Serial.print(", ");
      Serial.print(y_coordinate);
      Serial.print(" is ");
      Serial.println(bit_value);
      Serial.println("This value has been preserved in memory");

    break;

    //READ BIT (destroys stored value)
    case 4:
      Serial.println(F("You have selected READ BIT (destructive read). Please enter the the byte row you wish to read (0:5)\n "));
      while(!Serial.available()){}                                                        //wait for input
      y_coordinate = Serial.parseInt();                                                   //grab the next integer input
                                  
      while (y_coordinate > 5 || y_coordinate < 0){                                       //make sure it has a valid index  
        Serial.println(F("That is not a valid row, please enter a number from 0 to 5"));    
        while(!Serial.available()){} //wait for input                                   
        y_coordinate = Serial.parseInt();
        Serial.flush();
      }
      
      Serial.print("you have selected row ");                                         
      Serial.print(y_coordinate);
      Serial.print(F("\n Please enter the index (0:7) of the bit you wish to read in row"));  
     
      while(!Serial.available()){}                                                        //wait for input
      x_coordinate = Serial.parseInt();                                                   //grab the next integer input
      
      while (x_coordinate > 7 || x_coordinate < 0){                                       //make sure it has a valid index
        Serial.println(F("That is not a valid index, please enter a number from 0 to 7"));
        while(!Serial.available()){} //wait for input
        x_coordinate = Serial.parseInt();
        Serial.flush();
      }

      /////////////////////////////
      //put memory access code here
      /////////////////////////////
            
      Serial.print("The value of row ");
      Serial.print(x_coordinate);
      Serial.print(", index ");
      Serial.print(y_coordinate);
      Serial.print(" is ");
      Serial.println(bit_value);
      Serial.println(F(". This value has been destroyed in memory"));
    break;

    //WRITE ARRAY (6 ascii characters)
    case 5:
    Serial.println(F("You have selected WRITE ARRAY (writes 6 ASCII characters to memory. Please enter each single character on a new line in the desired order..."));

    /////////////////////////////
    //put memory access code here
    /////////////////////////////
    
    break;

    //WRITE BIT (writes a single bit)
    case 6:
    Serial.println(F("You have selected WRITE BIT. Please enter the the byte row you wish to write to (0:5)\n "));
      while(!Serial.available()){}                                                        //wait for input
      y_coordinate = Serial.parseInt();                                                   //grab the next integer input
                                  
      while (y_coordinate > 5 || y_coordinate < 0){                                       //make sure it has a valid index  
        Serial.println(F("That is not a valid row, please enter a number from 0 to 5"));    
        while(!Serial.available()){} //wait for input                                   
        y_coordinate = Serial.parseInt();
        Serial.flush();
      }
      
      Serial.print("you have selected row ");                                         
      Serial.print(y_coordinate);
      Serial.print(F("\n Please enter the index (0:7) of the bit you wish to write to in the row"));  
     
      while(!Serial.available()){}                                                        //wait for input
      x_coordinate = Serial.parseInt();                                                   //grab the next integer input
      
      while (x_coordinate > 7 || x_coordinate < 0){                                       //make sure it has a valid index
        Serial.println(F("That is not a valid index, please enter a number from 0 to 7"));
        while(!Serial.available()){} //wait for input
        x_coordinate = Serial.parseInt();
        Serial.flush();
      }

      Serial.println(F("Please enter the value that you wish to write (1 or 0)"));
      while(!Serial.available()){}                                                        //wait for input
      bit_value = Serial.parseInt();                                                      //grab the next integer input
    
      while ((bit_value != 0) && (bit_value != 1)){                                       //make sure it has a valid index
        Serial.println(F("That is not a valid index, please enter a number from 0 to 7"));
        while(!Serial.available()){} //wait for input
        x_coordinate = Serial.parseInt();
        Serial.flush();
      }
     
      /////////////////////////////
      //put memory access code here
      /////////////////////////////
      
      Serial.print(bit_value);
      Serial.print(" has been written to row ");
      Serial.print(x_coordinate);
      Serial.print(", index ");
      Serial.println(y_coordinate);
      
    break;

    case 7:
    Serial.println(F("1: Read array (all bits). This does not take any inputs, and will dump all 48 bits of memory to the console"));
    Serial.println(F("2: Read array (characters). This dumps the content of memory as a 6 ASCII character string."));
    Serial.println(F("3: Read bit (protective read). This takes the location of the bit of interest as a row number and index, and outputs the value of the bit to the console. This does not destroy the value stored in the selected bit."));
    Serial.println(F("4: Read bit (destructive read). This takes the location of the bit of interest as a row number and index, and outputs the value of the bit to the console. This does WILL DESTROY the value stored in the selected bit."));
    Serial.println(F("5: Write array (6 ascii characters). This takes each character sequentially from the console, with each character on a newline."));
    Serial.println(F("6: Write bit (binary value). This takes the location of the bit of interest as a row number and index, and writes the given value to the selected bit"));
    Serial.println(F("7: Help text."));
    break;

    default:
      if (input_selection > 6)
      Serial.println(F("That is not a valid input.\n For help, enter '9'"));
    break;
    }
  }
}
