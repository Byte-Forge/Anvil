#pragma once
#include <map>
#include <mutex>
#include <thread>
#include <memory>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem; 

namespace anvil
{
	class FileWatcher
	{
	public:
		static void Initialize();
		static void AddPath(const fs::path& path,const std::function<void(const fs::path&)> &callback);
		static void Shutdown();
	private:
		static std::map<fs::path,std::function<void(const fs::path&)>> s_callbacks;
		static std::map<fs::path,time_t> s_lastModified;
		static std::unique_ptr<std::thread> s_thread;
		static bool s_running;
		static std::mutex s_mutex;
	};
}