#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

int main()
{
    init_platform();

    print("..... Blinking PL LEDs .....\n\r");

    int ret = 0;
    XGpio inst;
    ret = XGpio_Initialize(&inst, XPAR_GPIO_0_DEVICE_ID);
    if(ret != 0){
    	print("[ERROR] XGpio_Initialize()\n\r");
    	return -1;
    }

    // Set direction (output)
    XGpio_SetDataDirection(&inst, 1, 0);

    // Blinking
    int val = 0;
    while(1){
        XGpio_DiscreteWrite(&inst, 1, (val & 0x3));
        val++;
        sleep(1);
    }

    cleanup_platform();
    return 0;
}
