#ifndef PUBLIC_ERROR_H
#define PUBLIC_ERROR_H
#define PrintErrorMessage(error_code) fprintf(stdout, "DNG 错误信息:%s\n", error_code);
#define CV_PACKAGE_NOT_FOUND "无法找到所指定的拓展程序"
#define CV_LACK_ARGUMENTS "输入缺失必要的参数"
#define CV_OPEN_DIR_FAILRUE "文件夹打开失败"
#define CV_COMMAND_NOT_FOUND "无法找到对应的指令 请使用 'dng help' 获取指令帮助信息"
#define CV_READ_NOTE_FAILURE "无法读取Note配置文件"
#define CV_PACKAGE_HELP_FAILURE "拓展未安装或拓展帮助文件缺失"
#define CV_INSTALL_DIRECTORY_ACCESS_FAILURE "无法访问拓展文件夹"
#define CV_SUCCESS NULL
#define ERROR_OPEN_FILE 1002
#define ERROR_NO_FILE 200
#define ERROR_OPEN_DIRECTORY 2202
#define ERROR_ALLOC_MEMORY 22221
#define ERROR_CREATE_FILE 222
#define S_SUCCESS 0
#define STATUS_CONTINUE S_SUCCESS
#endif
