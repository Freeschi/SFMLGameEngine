// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "Lua.h"

// ====================================================================================================
// Exception Handler
// ====================================================================================================
void ExceptionOccured(char* kind, char* what)
{
	printf("-----------------------------------------------\n");
	printf("UNHANDLED EXCEPTION! (%s)\n", kind);
	printf("-----------------------------------------------\n");
	printf("%s\n", what);

	FRESCHI_FATAL_ERROR(what);
}

// ====================================================================================================
// Main
// ====================================================================================================
int main()
{
#ifdef _WIN32
	DeleteFile("updater_old.exe");
#endif

	try
	{
		g_pGame = new Game();
		g_pGame->Run();
	}
	catch (LuaException& e)
	{
		char msg[2048];
		sprintf(msg, "%s\ntrace: %s", e.what(), e.traceback());
		ExceptionOccured("LuaException", const_cast<char*>(msg));
	}
	catch (luabind::error& e)
	{
		ExceptionOccured("luabind::error", const_cast<char*>(e.what()));
	}
	catch (std::exception& e)
	{
		ExceptionOccured("std::exception", const_cast<char*>(e.what()));
	}
	catch (std::string what)
	{
		ExceptionOccured("std::string", const_cast<char*>(what.c_str()));
	}
	catch (char* what)
	{
		ExceptionOccured("char*", what);
	}
	catch (const char* what)
	{
		ExceptionOccured("const char*", const_cast<char*>(what));
	}
	catch (...)
	{
		ExceptionOccured("Unknown", "Unknown exception!");
	}

	// Cleanup
	delete g_pGame;
	delete g_pPlayer;
	delete g_pConfig;
	delete g_pWorld;

	return 0;
}



