/* kbdread.c  -  kbdread */

#include <xinu.h>
#include <mouse.h>

/*------------------------------------------------------------------------
 * kbdread  -  Read the status of the keyboard driver
 *------------------------------------------------------------------------
 */
devcall	kbdread (
	  struct dentry	*devptr,	/* Entry in device switch table	*/
	  char          *buffer,        /* Address of buffer            */
          uint32        count           /* Length of buffer             */
	)
{
	memcpy(buffer, &mouse, sizeof(mouse));

	//mouse.buttons = 0;
	//mouse.x = 0;
	//mouse.y = 0;
	return OK;
}
