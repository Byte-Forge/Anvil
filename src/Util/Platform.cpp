#include "Platform.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif
#include "StringHelper.hpp"

using namespace hpse;


std::vector<std::string> IO::ListFiles(const std::string & dir, const std::string & ext)
{
	std::vector<std::string> files;
	#ifdef _WIN32
	char search_path[200];
	sprintf(search_path, "%s/*.*", dir.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
			{
				std::string name = fd.cFileName;
				std::string fileExt = StringHelper::split(name, '.').back();
				
				if(fileExt==ext||ext.size()==0)
					files.push_back(name);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	#else
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == NULL)
	{
		return files;
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		std::string name = dirp->d_name;
		std::string fileExt = StringHelper::split(name, '.').back();

		if (fileExt == ext || ext.size() == 0)
			files.push_back(name);
	}
	closedir(dp);
	#endif
	return files;
}

void hpse::ShowError(const std::string & msg)
{
	#ifdef _WIN32
	MessageBox(NULL, msg.c_str(), "Error", MB_OK | MB_ICONERROR);
	#endif
}
