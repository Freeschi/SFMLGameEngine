#ifndef H_COMMANDQUEUE
#define H_COMMANDQUEUE

class CommandQueue
{
public:
	void						push(const Command& command);
	Command						pop();
	bool						isEmpty() const;


private:
	std::queue<Command>			mQueue;
};

#endif
