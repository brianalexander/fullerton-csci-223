#!/bin/bash

gcc -c main.c
gcc -c disphex.c
gcc -c dispoct.c

gcc -o a.out main.o disphex.o dispoct.o