###############################################################
#
# Purpose: Makefile for "Maestor for darwin"
# Author.: Ryan
#
###############################################################

CC = g++
CFLAGS = -Wall -std=c++0x -pthread -g 
LDFLAGS = 
TARGET_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include

${TARGET_DIR}/DarwinState.o : ${SRC_DIR}/DarwinState.cpp ${INCLUDE_DIR}/DarwinState.h
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/DarwinState.cpp

${TARGET_DIR}/motor.o : ${SRC_DIR}/motor.cpp ${INCLUDE_DIR}/motor.h
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/motor.cpp

${TARGET_DIR}/CM730.o : ${SRC_DIR}/CM730.cpp ${INCLUDE_DIR}/CM730.h
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/CM730.cpp

${TARGET_DIR}/MX28.o : ${SRC_DIR}/MX28.cpp ${INCLUDE_DIR}/MX28.h
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/MX28.cpp

${TARGET_DIR}/LinuxCM730.o : ${SRC_DIR}/LinuxCM730.cpp ${INCLUDE_DIR}/LinuxCM730.h
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/LinuxCM730.cpp

${TARGET_DIR}/main.o : ${SRC_DIR}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/main.cpp

all : ${TARGET_DIR}/main.o ${TARGET_DIR}/DarwinState.o ${TARGET_DIR}/motor.o ${TARGET_DIR}/CM730.o ${TARGET_DIR}/MX28.o ${TARGET_DIR}/LinuxCM730.o
	${CC} ${CFLAGS} main.o DarwinState.o motor.o CM730.o MX28.o LinuxCM730.o ${LDFLAGS} -o maestorForDarwin	