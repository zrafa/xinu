#include <xinu.h>

#include "gpio.h"
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "nokia.h"

#define ABS(x) ((x) < 0 ? (-x) : (x))
float offset = 0; // este offset lo uso para aumentar la frecuencia de entrada 
// al buzzer. es algo que uso a oido nomas, no hace en si al codigo

//unsigned int tempo = 500;
extern unsigned int tempo;
//int melody[] = NOKIA_MELODY;
//int melody[] = {1, 2, 3, 3};


void sonido(unsigned long frec, unsigned long dur, int pin);
void cancion(int nargs, char *args[]);
void speaker(int nargs, char *args[]);



int main(void)
{
	tempo = 2500;

	/* speaker 1 */
	resume(create(speaker, 256, 20, "s1", 4, 10, 250, 13, 750));
	sleepms(5000);

	/* speaker 2 */
	resume(create(speaker, 256, 20, "s2", 4, 120, 250, 5, 1750));
	sleepms(5000);

	/* speaker 3 */
	resume(create(speaker, 256, 20, "s3", 4, 500, 250, 2, 250));

	/* un programa embebido nunca finaliza */
	for(;;);
}


void speaker(int nargs, char *args[])
{
	int frec = (int) args[0];
	int dur = (int) args[1];
	int pin = (int) args[2];
	int espera = (int) args[3];
	for(;;) {
		sonido(frec, dur, pin);
		sleepms(espera);
	};
}


/* dur en microsegundos */
void sonido(unsigned long frec, unsigned long dur, int pin)
{
	double t = 0;
	double us = 1000000.0 / frec / 2.0;

	gpio_output(pin);

    	while (t < (double) dur) {
		gpio_pin(pin, ON);
		_delay_us(us);
		gpio_pin(pin, OFF);
		_delay_us(us);
		t = t + us + us;
	}
}

void cancion(int nargs, char *args[])
{
	int pin = (int) args[0];
	int notes = sizeof(melody) / sizeof(melody[0]) / 2;
	int divider = 0;
	unsigned int duration = 0;
	unsigned int wholenote = (60000 * 4) / tempo;

	gpio_output(pin);
	for (int n = 0; n < notes * 2; n = n + 2) {
		divider = melody[n + 1];
		if (divider > 0) {
			duration = wholenote / divider;
		} else if (divider < 0) {
			duration = wholenote / ABS(divider);
			duration *= 1.5;
		}
		melody_note(melody[n], duration, pin);
		//delay_ms(duration * 0.1);
	}
}

