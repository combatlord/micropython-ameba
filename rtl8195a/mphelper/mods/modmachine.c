/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Chester Tseng
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*****************************************************************************
 *                              Header includes
 * ***************************************************************************/
// micropython headers

// local object headers
#if 0
#include "machine/objpin.h"
#include "machine/obji2c.h"
#include "machine/objuart.h"
#include "machine/objspi.h"
#include "machine/objpwm.h"

#endif
#include "machine/objsdio_host.h"
#include "machine/objdac.h"
#include "machine/objflash.h"
#include "machine/objloguart.h"
#include "machine/objwdt.h"
#include "machine/objrtc.h"
#include "machine/objadc.h"
#include "machine/objcrypto.h"


// mbed lib headers
#include "sys_api.h"

/*****************************************************************************
 *                              External variables
 * ***************************************************************************/

void modmachine_init(void) {
    crypto_init0();
    rtc_init0();
    loguart_init0();
    adc_init0();
}

STATIC mp_obj_t machine_reset(void) {
    sys_reset();
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(machine_reset_obj, machine_reset);

STATIC const mp_map_elem_t machine_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__),      MP_OBJ_NEW_QSTR(MP_QSTR_umachine) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_reboot),        MP_OBJ_FROM_PTR(&machine_reset_obj) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_LOGUART),       MP_OBJ_FROM_PTR(&log_uart_type) },
#if MP_RTL8195A
    { MP_OBJ_NEW_QSTR(MP_QSTR_SDIO_HOST),     MP_OBJ_FROM_PTR(&sdio_host_type) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_DAC),           MP_OBJ_FROM_PTR(&dac_type) },
#endif
    { MP_OBJ_NEW_QSTR(MP_QSTR_FLASH),         MP_OBJ_FROM_PTR(&flash_type) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_WDT),           MP_OBJ_FROM_PTR(&wdt_type) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_RTC),           MP_OBJ_FROM_PTR(&rtc_type) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_CRYPTO),        MP_OBJ_FROM_PTR(&crypto_type) },
#if MP_RTL8195A || MP_RTL8711AM
    { MP_OBJ_NEW_QSTR(MP_QSTR_ADC),           MP_OBJ_FROM_PTR(&adc_type) },
#endif

#if 0
    { MP_OBJ_NEW_QSTR(MP_QSTR_I2C),           MP_OBJ_FROM_PTR(&i2c_type) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_Pin),           (mp_obj_t)&pin_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_UART),          (mp_obj_t)&uart_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_SPI),           (mp_obj_t)&spi_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_PWM),           (mp_obj_t)&pwm_type },
#endif
};
STATIC MP_DEFINE_CONST_DICT(machine_module_globals, machine_module_globals_table);

const mp_obj_module_t mp_module_umachine = {
    .base    = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&machine_module_globals,
};