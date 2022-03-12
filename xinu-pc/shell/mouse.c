/* source: https://forum.osdev.org/viewtopic.php?t=10247 */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <vga.h>
#include <mouse.h>

/*
#define inportb(p)      inb(p)
#define outportb(p,v)   outb(p,v)
*/

#define inportb(p)      inb(p)


//Mouse.inc by SANiK
//License: Use as you wish, except to cause damage
// byte mouse_cycle=0;     //unsigned char
// unsigned char mouse_byte[3];    //signed char
int mouse_x=0;         //signed char
int mouse_y=0;         //signed char

extern void print_text_on_vga(unsigned int x, unsigned int y, char *text);
extern void borrar(int x1, int y1, int x2, int y2);

process mouse_p (
                did32   dev             /* ID of tty device from which  */
        )                               /*   to accept commands         */
{
	int old_x=0;
	int old_y=0;;
	unsigned char c;
	char * h = "Xinu x86 GUI experiments: VGA display, mouse and kbd";
	print_text_on_vga(10, 500, h);
	char texto[10];
	int buf[3];
	
	open(MOUSE, NULL, 0);
	while(1) {
		read(MOUSE, buf, 3);
		mouse_x = buf[1];
		mouse_y = buf[2];

		if (buf[0] && 0x01)
		 	sprintf(texto, "mouse x: %d  y: %d    left : 1       ", mouse_x, mouse_y);
		else
		 	sprintf(texto, "mouse x: %d  y: %d    left : 0       ", mouse_x, mouse_y);
		pixel(old_x, old_y, 0x00ffff00);
		pixel(mouse_x, mouse_y, 0x00ff0000);
		print_text_on_vga(10, 10, texto);
		old_x = mouse_x; old_y = mouse_y;
		c = 0;
		sleepms(10);
 		inportb(0x60);
        //Enable the auxiliary mouse device
        mouse_wait(1);
        outportb(MOUSE_CTRL_STATUS_PORT, 0xA8);
 
        //Enable the mouse
        mouse_write(0xF4);
        mouse_read();  //Acknowledge


	}
	close(MOUSE);

}

