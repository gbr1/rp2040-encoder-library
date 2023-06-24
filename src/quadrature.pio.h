/*
 * Copyright (C) 2023 Giovanni di Dio Bruno
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// this file is based on pio example in Raspberry Pi Pico SDK

#include <sys/_stdint.h>

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif


#define quadrature_encoder_wrap_target 15
#define quadrature_encoder_wrap 28

static const uint16_t quadrature_encoder_program_instructions[] = {
    0x000f, //  0: jmp    15                         
    0x000e, //  1: jmp    14                         
    0x001a, //  2: jmp    26                         
    0x000f, //  3: jmp    15                         
    0x001a, //  4: jmp    26                         
    0x000f, //  5: jmp    15                         
    0x000f, //  6: jmp    15                         
    0x000e, //  7: jmp    14                         
    0x000e, //  8: jmp    14                         
    0x000f, //  9: jmp    15                         
    0x000f, // 10: jmp    15                         
    0x001a, // 11: jmp    26                         
    0x000f, // 12: jmp    15                         
    0x001a, // 13: jmp    26                         
    0x008f, // 14: jmp    y--, 15                    
            //     .wrap_target
    0xe020, // 15: set    x, 0                       
    0x8080, // 16: pull   noblock                    
    0xa027, // 17: mov    x, osr                     
    0xa0e6, // 18: mov    osr, isr                   
    0x0036, // 19: jmp    !x, 22                     
    0xa0c2, // 20: mov    isr, y                     
    0x8020, // 21: push   block                      
    0xa0c3, // 22: mov    isr, null                  
    0x40e2, // 23: in     osr, 2                     
    0x4002, // 24: in     pins, 2                    
    0xa0a6, // 25: mov    pc, isr                    
    0xa02a, // 26: mov    x, !y                      
    0x005c, // 27: jmp    x--, 28                    
    0xa049, // 28: mov    y, !x                      
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program quadrature_encoder_program = {
    .instructions = quadrature_encoder_program_instructions,
    .length = 29,
    .origin = 0,
};

static inline pio_sm_config quadrature_encoder_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + quadrature_encoder_wrap_target, offset + quadrature_encoder_wrap);
    return c;
}

#include "hardware/clocks.h"
#include "hardware/gpio.h"

static inline void quadrature_encoder_program_init(PIO pio, uint sm, uint offset, uint pin, int max_step_rate){
	pio_sm_set_consecutive_pindirs(pio, sm, pin, 2, false);
	gpio_pull_up(pin);
	gpio_pull_up(pin + 1);
	pio_sm_config c = quadrature_encoder_program_get_default_config(offset);
	sm_config_set_in_pins(&c, pin);
	sm_config_set_jmp_pin(&c, pin);
	sm_config_set_in_shift(&c, false, false, 32);
	sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_NONE);
	if (max_step_rate == 0) {
		sm_config_set_clkdiv(&c, 1.0);
	} else {
		float div = (float)clock_get_hz(clk_sys) / (14 * max_step_rate);
		sm_config_set_clkdiv(&c, div);
	}
	pio_sm_init(pio, sm, offset, &c);
	pio_sm_set_enabled(pio, sm, true);
}

static inline void quadrature_encoder_request_count(PIO pio, uint sm){
	pio->txf[sm] = 1;
}

static inline int32_t quadrature_encoder_fetch_count(PIO pio, uint sm){
	while (pio_sm_is_rx_fifo_empty(pio, sm))
		tight_loop_contents();
	return pio->rxf[sm];
}

static inline int32_t quadrature_encoder_get_count(PIO pio, uint sm){
	quadrature_encoder_request_count(pio, sm);
	return quadrature_encoder_fetch_count(pio, sm);
}

static inline void quadrature_encoder_reset(PIO pio, uint sm){
  pio_sm_exec_wait_blocking (pio, sm, pio_encode_mov (pio_x, pio_null));
  pio_sm_exec_wait_blocking (pio, sm, pio_encode_mov (pio_y, pio_null));
}


#endif
