#ifndef DRAWATTACK_STATE_HPP
#define DRAWATTACK_STATE_HPP

#include "StateIdentifiers.hpp"
#include "../Network/Client.hpp"
#include <cpp3ds/System/Time.hpp>
#include <cpp3ds/Window/Event.hpp>
#include <memory>


namespace cpp3ds
{
	class Window;
	class TcpSocket;
}

namespace DrawAttack {

class StateStack;
class Player;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct TransitionData
	{
		std::string message;
		States::ID  nextStateID;
	};

	struct Context
	{
		Context(Client& client, cpp3ds::String& name, cpp3ds::String& data, TransitionData& transition);
		Client& client;
		cpp3ds::String& name;
		cpp3ds::String& data;
		TransitionData& transition;
	};

	State(StateStack& stack, Context& context);
	virtual ~State();

	virtual void renderTopScreen(cpp3ds::Window& window) = 0;
	virtual void renderBottomScreen(cpp3ds::Window& window) = 0;
	virtual bool update(float delta) = 0;
	virtual bool processEvent(const cpp3ds::Event& event) = 0;

protected:
	void requestStackPush(States::ID stateID);
	void requestStackPop(States::ID stateID = States::None);
	void requestStackClear();

	Context getContext() const;

private:
	StateStack*  m_stack;
	Context      m_context;
};

} // namespace DrawAtack

#endif // DRAWATTACK_STATE_HPP
