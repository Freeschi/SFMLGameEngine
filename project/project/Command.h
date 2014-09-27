// ====================================================================================================
// Command
// ====================================================================================================
#ifndef H_COMMAND
#define H_COMMAND

struct Command
{
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

#endif