# rp2040-encoder-library
Arduino quadrature encoder library based on RPI Pico PIO example.

[![License: LGPL v3](https://img.shields.io/badge/License-LGPL_v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)

This library allows to read and reset any quadrature encoder attached to a RP2040 mcu.



```arduino
PioEncoder encoder(<first pin>);

void setup(){
    encoder.begin();
}

void loop(){

    ...

    int counts = encoder.getCount();

    ...

    encoder.reset();

    ...
}
```


***Note: encoder pins must be consecutive (e.g. 2 and 3, 10 and 11 etc.)***


> Copyright © 2023 G. Bruno - gbr1.github.io