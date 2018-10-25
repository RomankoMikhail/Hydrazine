#ifndef GAMESTACK_H_
#define GAMESTACK_H_

#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class GameStack : public sf::Drawable {
public:
	class State : public sf::Drawable {
	private:
		GameStack * mStack;
		virtual void draw(sf::RenderTarget & target, sf::RenderStates state) const override;
		virtual void init();
	public:
		virtual void update(const sf::Time delta);
		virtual const bool isDrawBreak() const;
		virtual const bool isUpdateBreak() const;


		State(GameStack * stack);
		virtual ~State() = default;
	};

	struct Action {
		std::shared_ptr<State> obj;
		enum {
			PUSH,
			POP
		} action;
	};
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates state) const override;

	std::deque<std::shared_ptr<State>> mStack;
	std::vector<Action> mActions;
public:

	void pop();
	void push(std::shared_ptr<State> state);

	virtual void update(const sf::Time delta);

	GameStack() = default;
	virtual ~GameStack() = default;
};

#endif /* GAMESTACK_H_ */
