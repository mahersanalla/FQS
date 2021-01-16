#!/bin/bash
make clean
rmmod QOSInfo
make
insmod ~/QOSProject/QOSKernelModule/QOSInfo.ko


