#!/bin/sh

if [ -e toolchain ]; then
	printf "rm existing toolchain folder\n"
	rm -rf toolchain
fi

printf "Extract toolchain from archive\n"
tar xvf archive/gcc-arm-none-eabi.tar.bz2 -C .

mv gcc-arm-none-eabi-5_4-2016q3 toolchain


if [ -e libopencm3 ]; then
	printf "rm existing opencm3 folder\n"
	rm -rf libopencm3
fi

printf "Extract libopencm3 from archive\n"
tar xvf archive/libopencm3.tar -C .

exit 0
