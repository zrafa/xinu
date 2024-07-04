#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"


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
	v_blink_led_rojo, "blink_r", configMINIMAL_STACK_SIZE, NULL, 1, NULL
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

	gpio_output(13);

	for ( ;; ) {
		gpio_pin(13, ON);
		vTaskDelay(700);
		gpio_pin(13, OFF);
		vTaskDelay(700);
    	}

	/* la tarea nunca debe abandonar el for */
	vTaskDelete(NULL);
}


static void v_blink_led_rojo(void* pvParameters)
{

	gpio_output(12);


	for ( ;; ) {
		gpio_pin(12, ON);
		vTaskDelay(200);
		gpio_pin(12, OFF);
		vTaskDelay(200);
    	}

	/* la tarea nunca debe abandonar el for */
	vTaskDelete(NULL);
}

