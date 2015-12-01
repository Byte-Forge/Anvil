#include "Platform.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#endif
#include "StringHelper.hpp"
using namespace hpse;


std::vector<const std::string> IO::ListFiles(const std::string & dir, const std::string & ext)
{
	std::vector<const std::string> files;
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
	#endif
	return files;
}
