// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "thirdparty/IniFile/IniFile.h"

Config* g_pConfig = NULL;

// ====================================================================================================
// Config
// ====================================================================================================
Config::Config()
{
	m_iFPSLimit = 60;
	m_iEntityLimit = 256;

	// FPS Limit
	if (CIniFile::RecordExists("FPSLimit", "Game", "config.ini"))
	{
		try
		{
			m_iFPSLimit = std::stoi(CIniFile::GetValue("FPSLimit", "Game", "config.ini"));
		}
		catch (...)
		{
			printf("Failed to read config.ini:Game:FPSLimit\n");
		}
	}

	// Entity Limit
	if (CIniFile::RecordExists("EntityLimit", "Game", "config.ini"))
	{
		try
		{
			m_iFPSLimit = std::stoi(CIniFile::GetValue("FPSLimit", "Game", "config.ini"));
		}
		catch (...)
		{
			printf("Failed to read config.ini:Game:EntityLimit\n");
		}
	}

	// Inform
	printf("Config::FPSLimit = %i\nConfig::EntityLimit = %i\n\n", m_iFPSLimit, m_iEntityLimit);
}