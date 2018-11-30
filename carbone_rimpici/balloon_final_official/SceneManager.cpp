/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "OptionsScene.h"
#include "EndScene.h"

SceneManager::SceneManager() :
	mIsInitialized(false)
{

}

SceneManager::~SceneManager()
{
	if (mIsInitialized)
	{
		auto iter = mSceneList.begin();
		for (; iter != mSceneList.end(); ++iter)
		{
			if (iter->second->mIsInitialized)
			{
				iter->second->save();
			}

			delete iter->second;
		}

		mSceneList.clear();

		mIsInitialized = false;
	}
}

bool SceneManager::initScenes()
{
	if (!mIsInitialized)
	{
		mSceneList.insert(std::make_pair(EnumScene::TITLE_SCENE, new TitleScene()));
		mSceneList.insert(std::make_pair(EnumScene::GAME_SCENE, new GameScene()));
		mSceneList.insert(std::make_pair(EnumScene::OPTIONS_SCENE, new OptionsScene()));
		mSceneList.insert(std::make_pair(EnumScene::END_SCENE, new EndScene()));

		mIsInitialized = true;
		
		try
		{
			setCurrentScene(EnumScene::TITLE_SCENE);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			mIsInitialized = false;
		}
	}

	return mIsInitialized;
}

void SceneManager::update(float deltaTime)
{
	mpCurrentScene->update(deltaTime);
}

void SceneManager::draw()
{
	mpCurrentScene->draw();
}

void SceneManager::save()
{
	mpCurrentScene->save();
}

void SceneManager::setCurrentScene(EnumScene scene)
{
	auto iter = mSceneList.begin();
	for (; iter != mSceneList.end(); ++iter)
	{
		if (iter->first == scene)
		{
			if (mpCurrentScene)
			{
				mpCurrentScene->end();
			}

			mpCurrentScene = iter->second;

			mpCurrentScene->start();
			return;
		}
	}

	throw std::exception("Unable to find scene with scene ID.");
}