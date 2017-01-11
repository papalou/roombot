#!/bin/sh

printf "Extract toolchain from archive\n"

tar xvf archive/gcc-arm-none-eabi.tar.bz2 -C toolchain

printf "Extract libopencm3 from archive\n"

tar xvf archive/libopencm3.tar -C libopencm3

exit 0
