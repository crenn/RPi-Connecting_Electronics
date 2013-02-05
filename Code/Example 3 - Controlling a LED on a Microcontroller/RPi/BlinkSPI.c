///////////////////////////////////////////////////////////////////////////////
//
//  This code was written by Trystan Jones (crenn6977@gmail.com)
//  http://www.crennsmind.com
//  (2013/02/05) - Initial version of Blink SPI
//
//  Note: The code relies on the BCM2835 C peripheral library which can be
//        found here:
//        http://www.open.com.au/mikem/bcm2835/
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <bcm2835.h>

#define CMD_BYTE 0x3F

#define LED_ON   0x40
#define LED_OFF  0x04

// Delay code from: http://cboard.cprogramming.com/c-programming/105688-time-h-delay.html
#include <time.h>
 
void Delay (unsigned int Sec) {
       clock_t ticks1 = clock(), ticks2 = ticks1;
       while ( ( ticks2/CLOCKS_PER_SEC - ticks1/CLOCKS_PER_SEC ) < Sec)
           ticks2 = clock();
}

int main (int argc, char *argv[]) {
  char buf[2] = {0x00};
  int i = 0;
  char state = LED_OFF;

  // Initialise the peripherals
  if (!bcm2835_init()) {
    printf("Uh oh! This program needs to be run as root to work.");
    return 1;
  }

  // Initialise and set up the SPI peripheral to use
  bcm2835_spi_begin();
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
  
  // Repeat 4 times
  for(i = 0; i < 4; i++) {
    // Prepare Message to be sent
    buf[0] = CMD_BYTE;
    if (state == LED_OFF) 
      buf[1] = LED_ON;
    else
      buf[1] = LED_OFF;
    state = buf[1];
  
    // Let the user know the program is about to send the message
    printf("About to send!\r\n");

    // Send that message!
    bcm2835_spi_transfern(buf, 2);
    
	// Wait a second
	Delay(1);
  }


  // Disable the SPI peripheral, which also sets the used pins to input
  bcm2835_spi_end();
  return 0;
}