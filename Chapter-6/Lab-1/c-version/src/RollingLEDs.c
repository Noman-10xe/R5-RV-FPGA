#include <header.h>

// delays for num milliseconds
void delay(int num) {
  volatile int i, j;
  
  for (i = 0; i < num; i++){
  	for ( j = 0; j < DELAY; j++){
  	}
}
}

int main ( void )
{
  int En_Value=0xFFFF, switches_value;
  short unsigned int value;
  
  WRITE_GPIO(GPIO_INOUT, En_Value);
  
  value = 0xF;
  WRITE_GPIO(GPIO_led, value);

  while (1) {
  
    switches_value = READ_GPIO(GPIO_sw) >> 16;
    
    if (switches_value & 0x2){
    	unsigned int lsb = value & 0x1;
    	value = (value >> 1) | (lsb << 15); // Shift direction to right and wrap the lsb around
    	
    	if ( switches_value & 0x1){
    		delay(200);
    		WRITE_GPIO(GPIO_led, value);		
    	}
    	
    	else {
    		delay(1000);
    		WRITE_GPIO(GPIO_led, value);		
    	}	
    }
    
    else {
    unsigned int msb = value & 0x8000;	// extract msb
    value = (value << 1) | ( msb >> 15);
    
    if ( switches_value & 0x1){
    		delay(200);
    		WRITE_GPIO(GPIO_led, value);		
    	}
    	
    	else {
    		delay(1000);
    		WRITE_GPIO(GPIO_led, value);
    	
    		}
	  }
	}

  return(0);
}
