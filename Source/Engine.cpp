#include "StdAfx.h"
#include "Engine.h"


Engine::Engine(HWND hWnd) : root(nullptr)
{
	char szPath[MAX_PATH];

	char applicationName[] = "OgreInWin32.exe";

	GetModuleFileName(nullptr, szPath, MAX_PATH);

	Ogre::ConfigFile	ogreConfigFile;
	char				applicationPath[MAX_PATH];
	char				drive[_MAX_DRIVE];
	char				dir[_MAX_DIR];

	//
	// Initialiser le système, mais ne pas créer la fenêtre de rendu.
	//

	_splitpath(szPath, drive, dir, nullptr, nullptr);

	strcpy(applicationPath, drive);
	strcat(applicationPath, dir);

	root = new Ogre::Root("", "", Ogre::String(applicationPath + Ogre::String("gravity.log")));

	ogreConfigFile.load(Ogre::String(applicationPath + Ogre::String("ogre.cfg")), "\t:=", false);

	Ogre::String renderSystemName;
	renderSystemName = ogreConfigFile.getSetting("Render System");

	
#ifdef _DEBUG
	if (renderSystemName == "Direct3D9 Rendering Subsystem")
	{
		root->loadPlugin("RenderSystem_Direct3D9_d");
	}
	else
	if (renderSystemName == "OpenGL Rendering Subsystem")
	{
		root->loadPlugin("RenderSystem_GL_d");
	}
	else
	{
		root->loadPlugin("RenderSystem_Direct3D9_d");
	}

	root->loadPlugin("Plugin_ParticleFX_d");
#else
	if (renderSystemName == "Direct3D9 Rendering Subsystem")
	{
		root->loadPlugin("RenderSystem_Direct3D9");
	}
	else
	if (renderSystemName == "OpenGL Rendering Subsystem")
	{
		root->loadPlugin("RenderSystem_GL");
	}
	else
	{
		root->loadPlugin("RenderSystem_Direct3D9");
	}

	root->loadPlugin("Plugin_ParticleFX");
#endif

	Ogre::RenderSystemList rendersList = root->getAvailableRenderers();
	root->setRenderSystem(rendersList[0]);

	// chargement des Chemins de ressources à partir du fichier de configuration
	Ogre::ConfigFile cf;
	Ogre::String resourcePath = applicationPath + Ogre::String("resources.cfg");
	cf.load(resourcePath);

	// Passez par toutes les sections et paramètres du fichier de config
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName;
	Ogre::String typeName;
	Ogre::String archName;
	Ogre::ConfigFile::SettingsMultiMap* settings;
	Ogre::ConfigFile::SettingsMultiMap::iterator i;

	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		settings = seci.getNext();

		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			archName = applicationPath + archName;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	root->initialise(false);

	sceneManager = root->createSceneManager(Ogre::ST_GENERIC, "Win32Ogre");

	//
	// Créer la fenêtre de rendu
	//

	Ogre::NameValuePairList parms;
	parms["externalWindowHandle"] = Ogre::StringConverter::toString((long)hWnd);
	parms["vsync"] = "true";

	RECT   rect;
	GetClientRect(hWnd, &rect);

	Ogre::RenderTarget* renderWindow = nullptr;

	try
	{
		renderWindow = root->createRenderWindow("Ogre in Win32", rect.right - rect.left, rect.bottom - rect.top, false, &parms);
	}
	catch (...)
	{
		MessageBox(hWnd, "Cannot initialize\nCheck that graphic-card driver is up-to-date", "Initialize Render System", MB_OK | MB_ICONSTOP);
		exit(EXIT_SUCCESS);
	}

	// chargement des ressources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// Créer la caméra
	camera = sceneManager->createCamera("Camera");
	camera->setNearClipDistance(0.5);
	camera->setFarClipDistance(5000);
	camera->setCastShadows(false);
	camera->setUseRenderingDistance(true);
	camera->setPosition(Ogre::Vector3(200.0, 50.0, 100.0));

	Ogre::SceneNode* cameraNode = nullptr;
	cameraNode = sceneManager->getRootSceneNode()->createChildSceneNode("CameraNode");

	Ogre::Viewport* viewPort = nullptr;

	if (0 == renderWindow->getNumViewports())
	{
		viewPort = renderWindow->addViewport(camera);
		viewPort->setBackgroundColour(Ogre::ColourValue(0.8f, 1.0f, 0.8f));
	}

	// Modifier le rapport d'aspect de la caméra pour correspondre à la fenêtre
	camera->setAspectRatio(Ogre::Real(rect.right - rect.left) / Ogre::Real(rect.bottom - rect.top));

	// Créer les entités
	Ogre::Entity*		robotEntity = sceneManager->createEntity("Robot", "robot.mesh");
	
	Ogre::Light* light = sceneManager->createLight("MainLight");
	light->setPosition(200.0f, 50.0f, 100.0f);

	Ogre::SceneNode*	robotNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	robotNode->attachObject(robotEntity);

	Ogre::AxisAlignedBox	robotBox = robotEntity->getBoundingBox();
	Ogre::Vector3			robotCenter = robotBox.getCenter();

	camera->lookAt(robotCenter);

	root->renderOneFrame();
}


Engine::~Engine(void)
{
}


Ogre::Root* Engine::getRoot(void)
{
	return root;
}