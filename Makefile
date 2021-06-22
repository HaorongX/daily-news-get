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
	@gcc src/*.c -o src/dng
	@sudo mkdir -p /usr/local/dng
	@sudo mkdir -p /usr/local/dng/installed
	@sudo mkdir -p /usr/local/dng/doc
	@sudo cp -r -f src/dng /usr/local/dng
	@sudo cp -r -f src/doc/*.* /usr/local/dng/doc
	@sudo cp -f dng.sh /usr/bin/dng
	@sudo chmod +x /usr/bin/dng

# This part design for the developers

dev:
	gcc src/*.c -o src/dng -D DEBUG
	sudo mkdir -p /usr/local/dng
	sudo mkdir -p /usr/local/dng/installed
	sudo mkdir -p /usr/local/dng/doc
	sudo cp -r -f src/dng /usr/local/dng
	sudo cp -r -f src/doc/*.* /usr/local/dng/doc
	sudo cp -f dng.sh /usr/bin/dng
	sudo chmod +x /usr/bin/dng


	
