#!/bin/sh
make -s clean && make -s liboe && make -s install >/dev/null && make -s dynamic && make -s install && make -s clean
