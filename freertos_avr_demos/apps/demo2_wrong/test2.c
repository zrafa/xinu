#include "FreeRTOS.h"
#include "task.h"


static void v_blink_led_azul(void* pvParameters);
static void v_blink_led_rojo(void* pvParameters);


int main(void)
{
    /* Crear tarea (task) */
    xTaskHandle blink_azul_handle;
    xTaskHandle blink_rojo_handle;
 
    xTaskCreate
    (
	v_blink_led_azul, "blink_a", configMINIMAL_STACK_SIZE, NULL, 1, NULL
    );

    xTaskCreate
    (
	v_blink_led_rojo, "blink_r", configMINIMAL_STACK_SIZE, NULL, 2, NULL
    );

    /* Iniciar scheduler */
    vTaskStartScheduler();

	return 0;
}   /* FIN de main() */



/* tareas */

#define LED_AZUL (0x08) /* 0b00001000 */
#define LED_ROJO (0x20) /* 0b00100000 */

static void v_blink_led_azul(void* pvParameters)
{

	/* PUERTO B - led en la placa */
	volatile unsigned char * puerto_b = (unsigned char *) 0x25;
	volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B */

	/* habilitamos el led azul */
	*ddr_b = *ddr_b | (LED_AZUL);
	*puerto_b = *puerto_b | (LED_AZUL);

	for ( ;; ) {
		*puerto_b = *puerto_b ^ (LED_AZUL);
		vTaskDelay(500);
    	}

	/* la tarea nunca debe abandonar el for */
	vTaskDelete(NULL);
}



void esperar() {

    volatile unsigned long i;

    /* delay manual */
    for (i=0; i<500000; i++);
}





static void v_blink_led_rojo(void* pvParameters)
{

	/* PUERTO B - led en la placa */
	volatile unsigned char * puerto_b = (unsigned char *) 0x25;
	volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B */

	/* habilitamos el led rojo */
	*ddr_b = *ddr_b | (LED_ROJO);
	*puerto_b = *puerto_b | (LED_ROJO);

	for ( ;; ) {
		*puerto_b = *puerto_b ^ (LED_ROJO);
		// vTaskDelay(300);
                esperar();
    	}

	/* la tarea nunca debe abandonar el for */
	vTaskDelete(NULL);
}

