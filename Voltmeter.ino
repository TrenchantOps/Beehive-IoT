float input_voltage = 0.0;

float temp=0.0;

float r1=100000.0;    //r1 value

float r2=10000.0;      //r2 value



void setup() 
{ 
//Initialize serial monitor at 9600 baudrate 
Serial.begin(9600); 
} 

void loop() 
{ 
//Reading analog input from A0 pin 
int digitalValue = (analogRead(0)); 
//Converting digital value to voltage 
//int voltage = ((digitalValue*5)/1023); 
temp = (digitalValue * 3.3) / 1024.0;   
input_voltage = temp / (r2/(r1+r2));        
if (input_voltage < 0.1)   
{     
 input_voltage=0.0;    
}     
//Printing digital value in serial monitor 
Serial.print("Digital Value: "); 
Serial.print(digitalValue); 
//Printing measured input voltage in serial monitor 
Serial.print(", input_voltage: "); 
Serial.println(input_voltage); 
}
