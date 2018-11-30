#ifndef ASSET_CONTAINER_H_
#define ASSET_CONTAINER_H_

#include <Trackable.h>
#include <string>

template <typename T>
class AssetContainer : public Trackable
{
public:
	AssetContainer();
	~AssetContainer();

	bool addAsset(std::string key, T* pAsset);
	T* getAsset(std::string key) const;

	bool deleteAsset(std::string key);

	void clearAssets();

private:
	std::map<std::string, T*> mAssetList;
};

template <typename T>
AssetContainer<T>::AssetContainer() {}

template <typename T>
AssetContainer<T>::~AssetContainer()
{
	clearAssets();
}

template <typename T>
bool AssetContainer<T>::addAsset(std::string key, T* pAsset)
{
	bool success = true;

	if (!mAssetList.insert(std::make_pair(key, pAsset)).second)
	{
		std::cout << "Asset is already implemented in the container!" << std::endl;
		delete pAsset;
		success = false;
	}

	return success;
}

template <typename T>
T* AssetContainer<T>::getAsset(std::string key) const
{
	T* foundAsset = nullptr;
	auto iter = mAssetList.find(key);

	if (iter != mAssetList.end())
	{
		foundAsset = iter->second;
	}
	else
	{
		std::cout << "Buffer: \'" << key << "\' not found." << std::endl;
	}

	return foundAsset;
}

template <typename T>
bool AssetContainer<T>::deleteAsset(std::string key)
{
	bool success = false;
	T* foundAsset = nullptr;
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

template <typename T>
void AssetContainer<T>::clearAssets()
{
	auto iter = mAssetList.begin();
	for (; iter != mAssetList.end(); ++iter)
	{
		delete iter->second;
	}

	mAssetList.clear();
}

#endif