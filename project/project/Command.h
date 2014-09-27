#ifndef H_COMMAND
#define H_COMMAND

struct Command
{
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

#endif