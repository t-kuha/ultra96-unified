/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "xgpiops.h"
#include "sleep.h"

#define MIO_LED0 20
#define MIO_LED1 19
#define MIO_LED2 18
#define MIO_LED3 17


int main()
{
    init_platform();

    print("..... LED Blink .....\n\r");

    XGpioPs gpio;
    XGpioPs_Config *gpio_config;

    gpio_config = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);

    int Status = XGpioPs_CfgInitialize(&gpio, gpio_config, gpio_config->BaseAddr);
    if (Status != XST_SUCCESS) {
    	return XST_FAILURE;
    }

    XGpioPs_SetDirectionPin(&gpio, MIO_LED0, 1);
    XGpioPs_SetDirectionPin(&gpio, MIO_LED1, 1);
    XGpioPs_SetDirectionPin(&gpio, MIO_LED2, 1);
    XGpioPs_SetDirectionPin(&gpio, MIO_LED3, 1);
    XGpioPs_SetOutputEnablePin(&gpio, MIO_LED0, 1);
    XGpioPs_SetOutputEnablePin(&gpio, MIO_LED1, 1);
    XGpioPs_SetOutputEnablePin(&gpio, MIO_LED2, 1);
    XGpioPs_SetOutputEnablePin(&gpio, MIO_LED3, 1);

    volatile int cnt = 0;
    while(1){
      XGpioPs_WritePin(&gpio, MIO_LED0, ( (cnt >> 0) & 0x01));
      XGpioPs_WritePin(&gpio, MIO_LED1, ( (cnt >> 1) & 0x01));
      XGpioPs_WritePin(&gpio, MIO_LED2, ( (cnt >> 2) & 0x01));
      XGpioPs_WritePin(&gpio, MIO_LED3, ( (cnt >> 3) & 0x01));
      usleep(200000);

      cnt++;
    }

    cleanup_platform();
    return 0;
}
