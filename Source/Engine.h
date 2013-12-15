#ifndef ENGINE_H
#define ENGINE_H

#include "Ogre.h"

class Engine
{
public:
	Engine(HWND hWnd);
	~Engine(void);

	Ogre::Root*			root;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* renderWindow;
	Ogre::Camera*		camera;

	Ogre::Root*			getRoot(void);
};

#endif //ENGINE_H