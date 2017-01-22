#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usart.h"
#include "main.h"

int main(void)
{
	int ret;
	int i;
	char message[11] = {0};
	message[0] = 'H';
	message[1] = 'e';
	message[2] = 'l';
	message[3] = 'l';
	message[4] = 'o';
	message[5] = ' ';
	message[6] = 'W';
	message[7] = 'o';
	message[8] = 'l';
	message[9] = 'r';
	message[10] = 'd';

	ret = usart_init_usart_1();

	rcc_periph_clock_enable(RCC_GPIOC);

	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

	while(1){

		gpio_toggle(GPIOC, GPIO13); /* LED on/off */

		usart_send_string(message, 11);

		for (i = 0; i < 400000; i++){ /* Wait a bit. */
			__asm__("nop");
		}

	}
	return 0;
}
