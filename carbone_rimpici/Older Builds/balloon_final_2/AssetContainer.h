#ifndef ASSET_CONTAINER_H_
#define ASSET_CONTAINER_H_

#include <Trackable.h>
#include <string>

template <typename Key, typename Value>
class AssetContainer : public Trackable
{
public:
	AssetContainer();
	~AssetContainer();

	void addAsset(Key key, Value* pAsset);
	Value* getAsset(Key key) const;

	bool deleteAsset(Key key);

	void clearAssets();

private:
	std::map<Key, Value*> mAssetList;
};

template <typename Key, typename Value>
AssetContainer<Key, Value>::AssetContainer() {}

template <typename Key, typename Value>
AssetContainer<Key, Value>::~AssetContainer()
{
	clearAssets();
}

template <typename Key, typename Value>
void AssetContainer<Key, Value>::addAsset(Key key, Value* pAsset)
{
	if (!mAssetList.insert(std::make_pair(key, pAsset)).second)
	{
		std::string error = "Asset is already implemented in the container!";
		std::cout << error << std::endl;
		delete pAsset;
		throw std::exception(error.c_str());
	}
}

template <typename Key, typename Value>
Value* AssetContainer<Key, Value>::getAsset(Key key) const
{
	Value* foundAsset = nullptr;
	auto iter = mAssetList.find(key);

	if (iter != mAssetList.end())
	{
		foundAsset = iter->second;
	}
	else
	{
		std::string error = "Could not find asset from key";
		std::cout << error << std::endl;
		throw std::exception(error.c_str());
	}

	return foundAsset;
}

template <typename Key, typename Value>
bool AssetContainer<Key, Value>::deleteAsset(Key key)
{
	bool success = false;
	Value* foundAsset = nullptr;
	auto iter = mAssetList.find(key);

	if (iter != mAssetList.end())
	{
		foundAsset = iter->second;
		mAssetList.erase(iter);
		delete foundAsset;

		success = true;
	}

	return success;
}

template <typename Key, typename Value>
void AssetContainer<Key, Value>::clearAssets()
{
	auto iter = mAssetList.begin();
	for (; iter != mAssetList.end(); ++iter)
	{
		delete iter->second;
	}

	mAssetList.clear();
}

#endif