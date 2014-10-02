// ====================================================================================================
// Game
// ====================================================================================================
#ifndef H_CONFIG
#define H_CONFIG

class Config
{
public:
	Config();

	int EntityLimit() {
		return m_iEntityLimit;
	};
	ACCESSOR_FUNC(FPSLimit, int, m_iFPSLimit);

private:
	int m_iEntityLimit;
	int m_iFPSLimit;
};

extern Config* g_pConfig;

#endif