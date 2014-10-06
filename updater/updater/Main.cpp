// ====================================================================================================
// Includes
// ====================================================================================================
#include "Updater.h"

// ====================================================================================================
// Header
// ====================================================================================================
void quick_header_1(std::string n, int r)
{
	printf("[ ------------------------------------------------------------------- ]\n");
	printf("Updating to Version %s (r%i)\n", n.c_str(), r);
	printf("[ ------------------------------------------------------------------- ]\n");
}

// ====================================================================================================
// Main
// ====================================================================================================
int main(int argc, const char* argv[])
{
	/*
	 * Delete old updater
	 */
	if (file_exists("updater_old.exe"))
	{
		DeleteFile("updater_old.exe");
	}

	// Download UpdateInfo.ini
	printf("Searching for updates..\n");
	DownloadThreadInfo* pUpdateInfo = DownloadFile("http://hive-mind.eu/fastdl/data/freschi/UpdateInfo.ini", "UpdateInfo.ini");
	while (!pUpdateInfo->bFinished) { Sleep(50); }

	// Read UpdateInfo.ini
	// Read: Latest Version Number
	std::string _s_latest_rev = CIniFile::GetValue("VersionNumber", "Latest", "UpdateInfo.ini");
	int latest_rev;
	try {
		latest_rev = std::stoi(_s_latest_rev);
	} catch (...) {
		printf("Failed to parse UpdateInfo.ini\n");
		getchar();
		return 0;
	}
	std::string latest_rev_name = CIniFile::GetValue("VersionName", "Latest", "UpdateInfo.ini");
	printf("Latest Version: %s (Revision Number: %i)\n", latest_rev_name.c_str(), latest_rev);

	// Current Version
	int client_rev;
	std::string client_rev_s;
	try {
		client_rev_s = CIniFile::GetValue("VersionName", "Current", "Updater.ini");
		client_rev = std::stoi(CIniFile::GetValue("VersionNumber", "Current", "Updater.ini"));
	} catch (...) {
		// either update.ini is corrupt or doesnt exist
		client_rev_s = "[Unknown]";
		client_rev = 0;
	}
	printf("Installed Version: %s (Revision Number: %i)\n", client_rev_s.c_str(), client_rev);
	printf("\n\n");

	// Redownload everything?
	bool reinstall_all = false;
	if (client_rev >= latest_rev)
	{
		printf("Client is up-to-date!\n");
		printf("Press enter if you wish to reinstall everything...\n");

		std::getchar();
		reinstall_all = true;
	}

	// Check if update is required
	bool bUpdatedUpdater = false;
	if (client_rev < latest_rev || reinstall_all)
	{
		// Update Required
		if (!file_exists("Updater.ini")) CIniFile::Create("Updater.ini");
		ClearConsole();

		// Collect file revisions
		char buf[48];
		sprintf(buf, "Version_r%i", latest_rev);
		std::vector<CIniFile::Record> files = CIniFile::GetSection(std::string(buf), "UpdateInfo.ini");
		for (std::vector<CIniFile::Record>::iterator it = files.begin(); it != files.end(); ++it)
		{
			CIniFile::Record rec = *it;

			// Create directory
			if (rec.Value == "directory")
			{
				CreateDirectory(rec.Key.c_str(), NULL);
				continue;
			}

			// Check File Revision
			// required and latest
			ClearConsole();
			quick_header_1(latest_rev_name, latest_rev);
			printf("Checking File %s\n", rec.Key.c_str());

			int revision_required = GetFileRevision(rec.Value);
			int revision_present = GetFileRevision(CIniFile::GetValue(rec.Key, "FileRevisions", "Updater.ini"));

			// Needs update?
			if (revision_required > revision_present || reinstall_all || !file_exists(rec.Key))
			{
				char download_url[512];
				sprintf(download_url, "http://hive-mind.eu/fastdl/data/freschi/r%i/%s", revision_required, rec.Key.c_str());
				std::string saveas = rec.Key;

				// Utility so Updater can update itself
				if (saveas == "Updater.exe")
				{
					saveas = "updater_new.exe";
					bUpdatedUpdater = true;
				}
				
				// Download File
				DownloadThreadInfo* pUpdateInfo = DownloadFile(std::string(download_url), saveas);
				while (!pUpdateInfo->bFinished)
				{
					ClearConsole();
					quick_header_1(latest_rev_name, latest_rev);
					if (pUpdateInfo->size_total <= 1000)
					{
						printf("Downloading %s ...\n", rec.Key.c_str());
					}
					else {
						printf("Downloading %s (%s/%s)\n\n", rec.Key.c_str(), readable_fs(pUpdateInfo->size_downloaded).c_str(), readable_fs(pUpdateInfo->size_total).c_str());

						// Progress Bar
						printf(" [ ");

						int ab = 50; // anzahl der balken
						int pr_re = 100 / ab; // ein balken = pre_re %
						int pr = (int)pUpdateInfo->progress;
						for (int i = 0; i < ab; i++)
						{
							if (pr >= (i * pr_re))
							{
								printf("=");
							}
							else {
								printf(" ");
							}
						}

						printf(" ] %i %% ", pr);
					}

					// short pause
					Sleep(75);
				}

				// Save new File Revision
				CIniFile::SetValue(rec.Key, rec.Value, "FileRevisions", "Updater.ini");
			}
		}

		// Done! Change UpdateInfo.ini
		CIniFile::SetValue("VersionNumber", to_string(latest_rev), "Current", "Updater.ini");
		CIniFile::SetValue("VersionName", latest_rev_name, "Current", "Updater.ini");

		// Tell user
		ClearConsole();
		printf("Client is up-to-date!\n");
		printf("Press enter to quit..\n");
	}

	// Updater-Update
	if (bUpdatedUpdater)
	{
		MoveFile("Updater.exe", "updater_old.exe");
		MoveFile("updater_new.exe", "Updater.exe");
	}

	// Done
	std::getchar();
	return 0;
}