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

// these are encoders attached to Hare motor control board
PioEncoder encA(2);
PioEncoder encB(6);
PioEncoder encC(8);
PioEncoder encD(22);


void setup() {
  encA.begin();
  encB.begin();
  encC.begin();
  encC.flip();
  encD.begin();
  encD.flip();
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  Serial.print(encA.getCount());
  Serial.print("\t\t");
  
  Serial.print(encB.getCount());
  Serial.print("\t\t");
  
  Serial.print(encC.getCount());
  Serial.print("\t\t");

  Serial.print(encD.getCount());
  Serial.print("\n");

  delay(10);
}
