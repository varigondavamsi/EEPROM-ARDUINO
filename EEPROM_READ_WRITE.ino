/*
vamsi krishna varigonda
code to read and write in EEPROM
EEPROM is an non volatile memory
*/
#include <EEPROM.h>

String input_data;
void setup()
{
  Serial.begin(9600);
   Serial.println("Enter the value to be read by 'read<space>location'");
  Serial.println("Enter the value to be written by 'write<space>location<space>value'");
}

void loop()
{
  if (Serial.available()>0)//checks for serial monitor
  {
    input_data = Serial.readStringUntil('\n'); //reads string
    String dataRead = input_data;
    String dataWrite = input_data;
    String serial_Read = "read";
    String serial_Write = "write";
    dataRead.remove(4);
    dataWrite.remove(5);
    
    if (dataRead.equals(serial_Read)) //to check if it's read/write
    {
       String read_add = input_data.substring(5);//reads from 5th point
       int real_add = read_add.toInt();
       int memRead = EEPROM.read(real_add); //reads from eeprom
       Serial.print("Address: ");
       Serial.print(read_add);
       Serial.print(" has value: ");
       Serial.println(memRead, DEC);
    }       
      else if (dataWrite.equals(serial_Write)) //to check if it's read/write
      {       
      	String write_add = input_data.substring(6);            	      
      	int burn_add = write_add.indexOf(' ');//the value to search for - char or String
      	String s1 = write_add.substring(0, burn_add);      
      	int write_real_add = s1.toInt();       
      	String s2 = write_add.substring(burn_add + 1); 
        int write_real_data = s2.toInt();
        byte add1 = write_real_data & 0XFF;
        byte num2 = (write_real_data >> 8) & 0XFF; //cuts off bits that are higher than the low 8 bits
        EEPROM.write(write_real_add, add1);        
        EEPROM.write(write_real_add + 1, num2);        
        Serial.println("Data has been wriiten ");              
     }
  }
}
