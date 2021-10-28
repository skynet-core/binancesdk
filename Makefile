ifeq ($(OS),Windows_NT)
	CC = msvc
	CPPSTD = 20
	LIBCXX = runtime
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CC = gcc
		CXX = g++
		CPPSTD = gnu20
		LIBCXX = libstd++11
    endif
    ifeq ($(UNAME_S),Darwin)
        CC = clang
		CXX = clang++
		CPPSTD = gnu20
		LIBCXX = libc++
    endif
endif


.PHONY: settings
settings:
	conan profile update settings.compiler=$(CC) default
	conan profile update settings.compiler.cppstd=$(CPPSTD) default
	conan profile update settings.compiler.libcxx=$(LIBCXX) default