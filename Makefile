#Makefile for DNG Project

PROJECT_NAME = dng
SRCPATH = src/main
INCLUDE_ACHIEVE = library
SHELL_INSTALL_PATH = /usr/local/bin
INSTALL_PATH = /usr/local

default: dev

dev:

	#Clean up old install directory
	sudo rm -r -f $(INSTALL_PATH)/$(PROJECT_NAME)
	
	#Clean up old C Program
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME).out

	#Compile C Program
	gcc $(SRCPATH)/$(PROJECT_NAME).c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME).out -g
	
	#Clean up old install shell file
	sudo rm -f $(INSTALL_PATH)/$(PROJECT_NAME).sh
	#Clean up project shell file
	sudo rm -f $(PROJECT_NAME).sh
	#Create Install Shell File
	echo cd $(INSTALL_PATH) >> $(PROJECT_NAME).sh 
	echo -n $(INSTALL_PATH)/$(PROJECT_NAME)/$(PROJECT_NAME).out  >> $(PROJECT_NAME).sh
	echo -n  ' '  >> $(PROJECT_NAME).sh
	echo -n  $$  >> $(PROJECT_NAME).sh
	echo -n '*'  >> $(PROJECT_NAME).sh
	
	#Copy shell file to pre-path
	sudo cp  $(PROJECT_NAME).sh $(SHELL_INSTALL_PATH)/$(PROJECT_NAME).sh
	
	#Copy files to install file
	sudo cp -r ./$(SRCPATH)/ $(INSTALL_PATH)/
	
	#Rename
	sudo mv $(INSTALL_PATH)/main $(INSTALL_PATH)/$(PROJECT_NAME)
	
	#Delect unceressary c code file
	sudo rm -R $(INSTALL_PATH)/$(PROJECT_NAME)/*.c
	sudo rm -R $(INSTALL_PATH)/$(PROJECT_NAME)/*/*.c
	
	#Change file competence
	sudo chmod 777 $(INSTALL_PATH)/$(PROJECT_NAME)
	sudo chmod 777 $(INSTALL_PATH)/$(PROJECT_NAME)/*
	sudo chmod 777 $(INSTALL_PATH)/$(PROJECT_NAME)/*.out
	sudo chmod 777 $(SHELL_INSTALL_PATH)/$(PROJECT_NAME).sh
	sudo chmod +x $(SHELL_INSTALL_PATH)/$(PROJECT_NAME).sh

	#Rename
	sudo mv $(SHELL_INSTALL_PATH)/$(PROJECT_NAME).sh $(SHELL_INSTALL_PATH)/$(PROJECT_NAME)
