#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SFML/Graphics.hpp>

namespace GUI {
class Component: public sf::Drawable, public sf::Transformable, sf::NonCopyable {
protected:
	bool mIsSelected = false;
	bool mIsActive = false;
public:
	virtual void update(sf::Time deltaTime);
	virtual bool isSelectable() const = 0;
	virtual bool isSelected() const;
	virtual void select();
	virtual void deselect();
	virtual bool isActivated() const;
	virtual void activate();
	virtual void deactivate();
	virtual void handle(sf::Event & event) = 0;

	Component() = default;
	virtual ~Component() = default;
};
}
#endif /* COMPONENT_H_ */
