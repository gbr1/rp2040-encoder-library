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

#ifndef __PIO_ENCODER_H__
#define __PIO_ENCODER_H__

#include "Arduino.h"
#include "quadrature.pio.h"

#define COUNT_1X 2
#define COUNT_2X 1
#define COUNT_4X 0


class PioEncoder{
    private:
        uint8_t pin;
        uint sm;
        PIO pio;
        int max_step_rate;
        int flip_it;
        int zero_offset;
        uint8_t count_mode;
    public:
        static uint offset;
        static bool not_first_instance;
        
        PioEncoder(const uint8_t pin, const bool flip = false, const int zero_offset = 0, const uint8_t count_mode = COUNT_4X,
                   PIO pio = pio0, const uint sm = -1, const int max_step_rate = 0);
        void begin();
        void reset(const int reset_value = 0);
        void flip(const bool x=true);
        int getCount();
        void setMode(const uint8_t mode = COUNT_4X);
};


#endif