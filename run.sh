#!/bin/bash

gcc src/main.cpp --std=c++11 -lstdc++ -ldl -lpthread -lm -lncurses -o bin/stillalive && bin/stillalive
