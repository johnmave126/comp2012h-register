CC=gcc
CPP=g++
LINK=g++
LFLAGS=
LIBS=
AR=ar
RM=rm
CP=cp
INCPATH=-Iinclude -I.
CFLAGS=-O2 -Wextra -Wall -g -fexceptions -fstack-protector
CPPFLAGS=$(CFLAGS) -std=c++0X

TMP_PATH=build_tmp
BIN_PATH=build_bin

HEADERS = include/bootstrap.h \
		include/html_utility.h \
		include/deque.h \
		include/sortlist.h \
		include/register_common.h \
		include/term_utility.h 
SOURCES = src/html_utility.cpp \
		src/term_utility.cpp \
		src/register.cpp
OBJECTS = build_tmp/html_utility.o \
		build_tmp/term_utility.o \
		build_tmp/register.o 

all: Register

Register: $(OBJECTS) $(BIN_PATH)
	$(LINK) $(LFLAGS) -o $(BIN_PATH)/Register $(OBJECTS) $(LIBS)

build_tmp/html_utility.o: src/html_utility.cpp include/html_utility.h \
 include/deque.h include/bootstrap.h include/register_common.h $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/html_utility.o src/html_utility.cpp

build_tmp/term_utility.o: src/term_utility.cpp include/term_utility.h \
 include/register_common.h $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/term_utility.o src/term_utility.cpp

build_tmp/register.o: src/register.cpp include/term_utility.h include/register_common.h\
 include/sortlist.h $(TMP_PATH)
	$(CPP) -c $(CPPFLAGS) $(INCPATH) -o build_tmp/register.o src/register.cpp

$(TMP_PATH):
	mkdir -p $(TMP_PATH)

$(BIN_PATH):
	mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	rm -f $(TMP_PATH)/*.o $(BIN_PATH)/*