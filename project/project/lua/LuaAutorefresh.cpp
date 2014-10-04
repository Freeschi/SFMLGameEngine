// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"
#include "FileWatcher/FileWatcher.h"

// ====================================================================================================
// Init Auto Refresh
// ====================================================================================================
namespace LuaFunctions
{
	namespace Autorefresh
	{
		FW::FileWatcher* fileWatcher = NULL;

		class UpdateListener : public FW::FileWatchListener
		{
		public:
			UpdateListener()
			{
				m_cLastRefresh.restart();
			}

			void handleFileAction(FW::WatchID watchid, const std::string& dir, const std::string& filename, FW::Action action)
			{
				char fullpath_c[712];
				sprintf(fullpath_c, "%s%s", dir.c_str(), filename.c_str());
				std::string fullpath(fullpath_c);
				UTIL::ParseFilePath(fullpath);

				if (action == FW::Actions::Modified)
				{
					if (lua->IsOnFileList(const_cast<char*>(fullpath.c_str())) && m_cLastRefresh.getElapsedTime().asMilliseconds() > sf::milliseconds(50).asMilliseconds())
					{
						printf("[Lua] Reloaded %s\n", fullpath.c_str());
						lua->IncludeFile(const_cast<char*>(fullpath.c_str()));
						m_sLastFile = fullpath;
						m_cLastRefresh.restart();
					}
				}
			}

		private:
			std::string m_sLastFile;
			sf::Clock m_cLastRefresh;
		};

		void Init()
		{
			fileWatcher = new FW::FileWatcher();
			UpdateListener* listener = new UpdateListener();
			FW::WatchID watchid = fileWatcher->addWatch("lua/", listener);
			Update();
		}
		void Update()
		{
			if (fileWatcher != NULL)
				fileWatcher->update();
			else
				printf("[Lua] LuaFunctions::Autorefresh::Update called too early!\n");
		}
	}
}