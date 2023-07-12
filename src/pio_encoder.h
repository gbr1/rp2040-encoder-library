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


class PioEncoder{
    private:
        uint8_t pin;
        uint sm;
        PIO pio;
        int max_step_rate;
        int flip_it;
    public:
        static uint offset;
        static bool not_first_instance;
        
        PioEncoder(uint8_t _pin, PIO _pio = pio0, uint _sm = -1, int max_step_rate = 0, bool wflip=false);
        void begin();
        void reset();
        void flip(const bool x=true);
        int getCount();
};


#endif