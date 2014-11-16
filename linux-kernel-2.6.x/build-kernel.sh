#!/bin/bash

export PATH=/opt/arm-2010q1/bin:$PATH
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- KALLSYMS_EXTRA_PASS=1 uImage
make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- KALLSYMS_EXTRA_PASS=1 modules
