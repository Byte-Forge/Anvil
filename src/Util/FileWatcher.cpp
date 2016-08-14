#include "FileWatcher.hpp"

using namespace anvil;

std::map<fs::path, std::function<void(const fs::path&)>> FileWatcher::s_callbacks;
std::map<fs::path, time_t> FileWatcher::s_lastModified;
std::unique_ptr<std::thread> FileWatcher::s_thread = nullptr;
bool FileWatcher::s_running = true;
std::mutex FileWatcher::s_mutex;

void FileWatcher::Initialize()
{
	s_thread = std::unique_ptr<std::thread>(new std::thread([]() 
	{
		auto ms = std::chrono::milliseconds(500);
		while (s_running)
		{
			do 
			{
				// iterate through each watcher and check for modification
				std::lock_guard<std::mutex> lock(s_mutex);
				for (auto& file : s_lastModified)
				{
					//file has been modified -> call callback
					if (fs::last_write_time(file.first) > file.second)
					{
						s_callbacks[file.first](file.first);
					}	
				}

				// lock will be released before this thread goes to sleep
			} while (false);

			// make this thread sleep for a while
			std::this_thread::sleep_for(ms);
		}
	}));
}

void FileWatcher::AddPath(const fs::path & path, const std::function<void(const fs::path&)>& callback)
{
	bool exists = fs::exists(path);
	if (exists)
	{
		s_callbacks[path] = callback;
		s_lastModified[path] = fs::last_write_time(path);
	}
}

void FileWatcher::Shutdown()
{
	s_running = false;
	if(s_thread->joinable())
		s_thread->join();
}

