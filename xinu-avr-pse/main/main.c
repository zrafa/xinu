#include <xinu.h>
#include "serial.h"


int main(void)
{
	int n = 0;

	serial_init();
	while(1) {
		sleepms(1000);
		n++;
		serial_put_str("hola \n\r");
		serial_put_int(n, 4);
		serial_put_str("\n\r");

	}
}


