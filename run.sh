#!/bin/bash

gcc src/main.cpp --std=c++11 -ldl -lpthread -lm -lncurses -o bin/stillalive && bin/stillalive
