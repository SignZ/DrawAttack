#include "NameSelectState.hpp"


namespace DrawAttack {

NameSelectState::NameSelectState(StateStack& stack, Context& context)
: State(stack, context)
{
	m_rectangle.setSize(cpp3ds::Vector2f(400, 240));
	m_rectangle.setFillColor(cpp3ds::Color(0,0,0,150));

	m_keyboard.loadFromFile("kb/keyboard.xml");
	m_text.setString(_("What is your name?"));
	m_text.setPosition(std::round(160.f - m_text.getLocalBounds().width / 2.f), 2.f);
}

void NameSelectState::renderTopScreen(cpp3ds::Window& window)
{
	window.draw(m_rectangle);
}

void NameSelectState::renderBottomScreen(cpp3ds::Window& window)
{
	window.draw(m_keyboard);
	window.draw(m_text);
}

bool NameSelectState::update(float delta)
{
	if (m_keyboard.popString(getContext().name)) {
		getContext().client.sendPlayerConnected(getContext().name);
	}

	m_keyboard.update(delta);
	return true;
}

bool NameSelectState::processEvent(const cpp3ds::Event& event)
{
	m_keyboard.processEvents(event);
	return false;
}

} // namespace DrawAttack
