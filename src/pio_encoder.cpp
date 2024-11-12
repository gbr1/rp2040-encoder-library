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

#include "pio_encoder.h"

uint PioEncoder::offset;
bool PioEncoder::not_first_instance;

PioEncoder::PioEncoder(const uint8_t pin, const bool flip, const int zero_offset, const uint8_t count_mode, PIO pio, const uint sm, const int max_step_rate){
    static uint offset;
    this->pin = pin;
    this->pio = pio;
    this->sm = sm;
    this->max_step_rate = max_step_rate;
    this->flip(flip);
    this->zero_offset = zero_offset;
    this->count_mode = count_mode;
}

void PioEncoder::begin(){
    pinMode(pin, INPUT);
    pinMode(pin+1, INPUT);

    if (!not_first_instance){
        offset = pio_add_program(pio, &quadrature_encoder_program);
    }
    not_first_instance=true;
    if (sm==-1){
        sm = pio_claim_unused_sm(pio, true);
    }
    sm=sm;
    quadrature_encoder_program_init(pio,sm,offset,pin,max_step_rate);
}

void PioEncoder::reset(const int reset_value){
    quadrature_encoder_reset(pio, sm);
    zero_offset=reset_value;
}

void PioEncoder::flip(const bool x){
    if (x){
        flip_it=-1;
    }
    else{
        flip_it=1;
    }
}

void PioEncoder::setMode(const uint8_t mode){
    count_mode = mode;
}

int PioEncoder::getCount(){
    return flip_it*(quadrature_encoder_get_count(pio, sm)>>count_mode)+zero_offset;
}

