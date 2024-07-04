#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"



static void v_blink_led_azul(void* pvParameters);


int main(void)
{
    /* Crear tarea (task) */
    xTaskHandle blink_azul_handle;
 
    xTaskCreate
    (
	v_blink_led_azul, "blink_a", configMINIMAL_STACK_SIZE, NULL, 1, blink_azul_handle
    );

    /* Iniciar scheduler */
    vTaskStartScheduler();

	return 0;
}   /* FIN de main() */



/* tareas */

#define LED_AZUL (0x08) /* 0b00001000 */

static void v_blink_led_azul(void* pvParameters)
{

	gpio_output(13);

	for ( ;; ) {
		gpio_pin(13, ON);
		vTaskDelay(500);
		gpio_pin(13, OFF);
		vTaskDelay(500);
    	}

	/* la tarea nunca debe abandonar el for */
	vTaskDelete(NULL);
}



