// ====================================================================================================
// State Stack
// ====================================================================================================
#ifndef H_STATE_STACK
#define H_STATE_STACK

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit StateStack();
	template <typename T>
	void RegisterState(States::ID stateID);
	void Update(sf::Time dt);
	void Draw();
	void HandleEvent(const sf::Event& event);
	void PushState(States::ID stateID);
	void PopState();
	void ClearStates();
	bool IsEmpty() const;

private:
	State::Ptr CreateState(States::ID stateID);
	void ApplyPendingChanges();

private:
	struct PendingChange
	{
		PendingChange(Action a) { action = a; }
		PendingChange(Action a, States::ID s) { action = a; stateID = s; }
		Action action;
		States::ID stateID;
	};

private:
	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	std::map<States::ID, std::function<State::Ptr() >> mFactories;
};

template <typename T>
void StateStack::RegisterState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this));
	};
}


#endif