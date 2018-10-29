#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <map>
#include <memory>
#include <string>
#include <iterator>
#include <cassert>
#include <thread>
#include <mutex>

/// Specifies resource manager for storing game assets
template<class Resource, typename Id>
class ResourceManager {
	std::map<Id, std::unique_ptr<Resource>> mResources;
	std::mutex mMutex;
public:
	/// Creates new resource with specified id
	Resource & create(const Id & identifier);
	/// Destroys resource with specified id
	void destroy(const Id & identifier);
	/// Gets access to resource by id
	Resource& get(const Id &identifier);
	/// Gets constant access to resource by id
	const Resource& get(const Id &identifier) const;
};

template<class Resource, typename Id>
Resource & ResourceManager<Resource, Id>::create(const Id & identifier) {
	mMutex.lock();
	std::unique_ptr<Resource> newElement(new Resource());

	auto inserted = mResources.insert(
			std::make_pair(identifier, std::move(newElement)));
	if (inserted.second == false)
		throw std::runtime_error("Can't create element in ResouceManager");

	mMutex.unlock();
	return *inserted.first->second;
}

template<class Resource, typename Id>
void ResourceManager<Resource, Id>::destroy(const Id & identifier) {
	mMutex.lock();

	auto found = mResources.find(identifier);
	if (found == mResources.end())
		throw std::runtime_error("Can't destroy element in ResourceManager");

	mResources.erase(found);
	mMutex.unlock();
}

template<class Resource, typename Id>
Resource& ResourceManager<Resource, Id>::get(const Id &identifier) {
	mMutex.lock();

	auto found = mResources.find(identifier);
	if (found == mResources.end())
		throw std::runtime_error("Can't get element in ResourceManager");

	mMutex.unlock();
	return *found->second;
}

template<class Resource, typename Id>
const Resource& ResourceManager<Resource, Id>::get(const Id &identifier) const {

	auto found = mResources.find(identifier);
	if (found == mResources.end())
		throw std::runtime_error("Can't get constant  element in ResourceManager");

	return *found->second;
}

#endif /* RESOURCEMANAGER_HPP_ */

