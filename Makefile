#Makefile for DNG Project

PROJECT_NAME = dng
SRCPATH = src/$(PROJECT_NAME)_program
INCLUDE_ACHIEVE = include_achieve
SHELL_INSTALL_PATH = /usr/local/bin
INSTALL_PATH = /usr/local

default: dev

dev:

	#Clean up old install directory
	sudo rm -r -f $(INSTALL_PATH)/$(PROJECT_NAME)
	
	#Clean up old C Program
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME)_help/$(PROJECT_NAME)_help.out
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME)_list/$(PROJECT_NAME)_list.out
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME)_change/$(PROJECT_NAME)_change.out
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME)_execute/$(PROJECT_NAME)_execute.out
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME)_install/$(PROJECT_NAME)_install.out
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME)_remove/$(PROJECT_NAME)_remove.out
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME)_installed_scripts_status/$(PROJECT_NAME)_installed_scripts_status.out
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME)_setoutput/$(PROJECT_NAME)_setoutput.out
	sudo rm -f  $(SRCPATH)/$(PROJECT_NAME).out

	#Compile C Program
	gcc $(SRCPATH)/$(PROJECT_NAME)_help/$(PROJECT_NAME)_help.c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME)_help/$(PROJECT_NAME)_help.out
	gcc $(SRCPATH)/$(PROJECT_NAME)_list/$(PROJECT_NAME)_list.c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME)_list/$(PROJECT_NAME)_list.out
	gcc $(SRCPATH)/$(PROJECT_NAME)_change/$(PROJECT_NAME)_change.c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME)_change/$(PROJECT_NAME)_change.out
	gcc $(SRCPATH)/$(PROJECT_NAME)_execute/$(PROJECT_NAME)_execute.c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME)_execute/$(PROJECT_NAME)_execute.out
	gcc $(SRCPATH)/$(PROJECT_NAME)_install/$(PROJECT_NAME)_install.c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME)_install/$(PROJECT_NAME)_install.out
	gcc $(SRCPATH)/$(PROJECT_NAME)_remove/$(PROJECT_NAME)_remove.c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME)_remove/$(PROJECT_NAME)_remove.out
	gcc $(SRCPATH)/$(PROJECT_NAME)_installed_scripts_status/$(PROJECT_NAME)_installed_scripts_status.c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME)_installed_scripts_status/$(PROJECT_NAME)_installed_scripts_status.out
	gcc $(SRCPATH)/$(PROJECT_NAME)_setoutput/$(PROJECT_NAME)_setoutput.c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME)_setoutput/$(PROJECT_NAME)_setoutput.out
	gcc $(SRCPATH)/$(PROJECT_NAME).c $(SRCPATH)/$(INCLUDE_ACHIEVE)/*.c -o $(SRCPATH)/$(PROJECT_NAME).out
	
	#Clean up old install shell file
	sudo rm -f $(INSTALL_PATH)/$(PROJECT_NAME).sh
	
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
	sudo mv $(INSTALL_PATH)/$(PROJECT_NAME)_program $(INSTALL_PATH)/$(PROJECT_NAME)
	
	#Delect unceressary c code file
	sudo rm -R $(INSTALL_PATH)/$(PROJECT_NAME)/*.c
	sudo rm -R $(INSTALL_PATH)/$(PROJECT_NAME)/*/*.c
	
	#Change file competence
	sudo chmod 777 $(INSTALL_PATH)/$(PROJECT_NAME)
	sudo chmod 777 $(INSTALL_PATH)/$(PROJECT_NAME)/*
	sudo chmod 777 $(INSTALL_PATH)/$(PROJECT_NAME)/*.out
	sudo chmod 777 $(INSTALL_PATH)/$(PROJECT_NAME)/*/*.out
	sudo chmod 777 $(SHELL_INSTALL_PATH)/$(PROJECT_NAME).sh
	sudo chmod +x $(SHELL_INSTALL_PATH)/$(PROJECT_NAME).sh

	#Rename
	sudo mv $(SHELL_INSTALL_PATH)/$(PROJECT_NAME).sh $(SHELL_INSTALL_PATH)/$(PROJECT_NAME)
clean:

	#Clean up install directory
	sudo rm -r -f $(INSTALL_PATH)/$(PROJECT_NAME)
	#Clean up shell file
	rm -f  $(PROJECT_NAME).sh
	rm -f  $(PROJECT_NAME).sh
	#Clean up program
	rm -f  $(SRCPATH)/$(PROJECT_NAME)_help/$(PROJECT_NAME)_help.out
	rm -f  $(SRCPATH)/$(PROJECT_NAME)_list/$(PROJECT_NAME)_list.out
	rm -f  $(SRCPATH)/$(PROJECT_NAME)_change/$(PROJECT_NAME)_change.out
	rm -f  $(SRCPATH)/$(PROJECT_NAME)_execute/$(PROJECT_NAME)_execute.out
	rm -f  $(SRCPATH)/$(PROJECT_NAME)_install/$(PROJECT_NAME)_install.out
	rm -f  $(SRCPATH)/$(PROJECT_NAME)_remove/$(PROJECT_NAME)_remove.out
	rm -f  $(SRCPATH)/$(PROJECT_NAME)_installed_scripts_status/$(PROJECT_NAME)_installed_scripts_status.out
	rm -f  $(SRCPATH)/$(PROJECT_NAME)_setoutput/$(PROJECT_NAME)_setoutput.out
	rm -f  $(SRCPATH)/$(PROJECT_NAME).out
