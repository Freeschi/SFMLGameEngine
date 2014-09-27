#ifndef H_PLAYER
#define H_PLAYER

class Player
{
	public:
		void HandleEvent(const sf::Event& event,CommandQueue& commands);
		void HandleRealtimeInput(CommandQueue& commands);
};
#endif