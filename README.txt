DailyNewsGet App:
1.the structure:
DailyNewsGet
|
|--saves
|--installed
|----scripts
|------script_name
|------file_result(rules : Date[Year-Month-Day for example:2021-Jun-15]|website|TITLE)
|--logs
|--dng.out
|--dng.c
|--readme.txt
|--version.txt
2.usage age:
dng [opnion]
	wituout arguments:
		equal to "--help" with "-v"
	with arguments:
		-v print version
		--help give some suggestion
		install [arguments]
			install a script
			for example:
			1. dng install name1 "perl" "/home/test.pl"
			2. dng install name2 "python" "/home/test.py"
			3. dng install name3 "perl" "/home/test/test.pl 10"
			Note:
			If the script exists,its status will turn to 'open'
			(Equal to 'open')
			So if you want to update your script,a better way is to use the argument 'update'.	
		remove:
			uninstall a script
			for example:
			1. dng uninstall name1
			Note:
			If you just want to stop using the script.
			A better argument is 'close'
		update [arguments]
			update a script
			for exampe:
			1. dng update name1 "perl" "/home/test.pl"
		open [name]
			Turn a script status into 'open'
		close [name]
			Turn a script status into 'close'
		-list list all the scripts you have installed.
		-all use all the scripts to get the news
		-name1 -name2 .... use the script you desing to get the news.
