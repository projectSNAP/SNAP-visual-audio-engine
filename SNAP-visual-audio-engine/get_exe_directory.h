#include <string>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
std::string get_exe_directory() {
	char path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	std::string strPath(path);
	return strPath.substr(0, strPath.find_last_of("\\/")) + "\\";
}
#elif __linux__
std::string get_exe_directory() {
	std::string path = "";
	pid_t pid = getpid();
	char buf[20] = {0};
	sprintf(buf, "%d", pid);
	std::string _link = "/proc/";
	_link.append( buf );
	_link.append( "/exe");
	char proc[512];
	int ch = readlink(_link.c_str(), proc, 512);
	if (ch != -1) {
		proc[ch] = 0;
		path = proc;
		std::string::size_type t = path.find_last_of(SLASH);
		path = path.substr(0, t);
	}
	return path + "/";
}
#else
std::string get_exe_directory() {
	std::cerr << "WARNING: This program was written for windows and linux only, behavior is undefined on other operating systems!" << std::endl;
	return "";
}
#endif

