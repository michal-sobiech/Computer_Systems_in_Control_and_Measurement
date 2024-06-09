#!/bin/bash

set -e

API_DIR=$(realpath './stm_api')
API_WRAPPER_DIR='./VL53L0X_rasp'

cd $API_WRAPPER_DIR
API_DIR=$API_DIR CROSS_COMPILE=arm-linux-gnueabihf- make clean examples