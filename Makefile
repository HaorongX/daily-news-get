#-------------------------------------------------------------------------
# 				Makefile
# Makefile for dng/src
#
# This makefile generates outputs:
#
#		dng.out
#
#-------------------------------------------------------------------------

#default

default : install

# This part is design for install dng
# Refer to translate-shell's makefile

install: 
	gcc src/*.c -o src/dng
	@mkdir -p /usr/bin/installed
	@mkdir -p /usr/bin/doc
	cp -r src/*.* /usr/bin/
	cp -r src/doc/*.* /usr/bin/doc


	
