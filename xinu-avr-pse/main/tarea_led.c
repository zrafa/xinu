/*
 * tarea 1: esta tarea parpadea un led a 1hz.
 */

#include <xinu.h>
#include "gpio.h"

void led()
{
	gpio_output(13);

	while(1) {
		gpio_pin(13, ON);
		sleepms(500);
		gpio_pin(13, OFF);
		sleepms(500);
	}
}
