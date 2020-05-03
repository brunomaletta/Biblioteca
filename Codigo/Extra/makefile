CXX = g++
ifeq ($(d), 1)
DEBUG = -DDEBUG
endif
CXXFLAGS = -fsanitize=address -O1 -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare $(DEBUG)
