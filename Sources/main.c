#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */



void MCUInit(unsigned char fbus);
void AT45_init(void);
void AT45_Test(void);



void main(void) {
  /* put your own code here */
    MCUInit(32);
    AT45_init();
    AT45_Test();

  


	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
