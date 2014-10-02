#ifndef H_LOADING_TASK
#define H_LOADING_TASK

class LoadingTask
{
public:
	LoadingTask();

	void Execute(LoadingState* pLoadingState);
	bool IsFinished();
	
	float GetPercentage();

private:
	void RunTask();

	LoadingState* m_pLoadingState;
	sf::Thread mThread;
	float m_flProgress;
	bool m_bFinished;
	sf::Clock m_cElapsedTime;
	sf::Mutex m_mMutex;
};

#endif