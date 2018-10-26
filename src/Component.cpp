#include "Component.h"
namespace GUI {

void Component::update(sf::Time deltaTime) {
	return;
}

bool Component::isSelected() const {
	return mIsSelected;
}

void Component::select() {
	if (isSelectable())
		mIsSelected = true;
}

void Component::deselect() {
	if (isSelectable())
		mIsSelected = false;
}

bool Component::isActivated() const {
	return mIsActive;
}

void Component::activate() {
	mIsActive = true;
}

void Component::deactivate() {
	mIsActive = false;
}

}
