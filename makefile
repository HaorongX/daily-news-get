#-------------------------------------------------------------------------
# 				Makefile
# Makefile for dng/src
#
# This makefile generates outputs:
#
#		dng.out
#
#-------------------------------------------------------------------------

dng: ./src/dng.c 
	gcc ./src/*.c -o ./src/dng.out
