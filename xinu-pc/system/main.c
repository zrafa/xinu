/*  main.c  - main */

#include <xinu.h>


extern paint_screen();
extern print_text_on_vga(unsigned int x, unsigned int y, const char * t);

process	main(void)
{


	paint_screen();
	print_text_on_vga(10, 300, "Xinu PC with VGA support");

	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}
