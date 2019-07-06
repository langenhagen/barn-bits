/**
 * @file This app lets you make some input and prints out the corresponding OIS key codes.
 *
 * The app may serve as an aid to identify key codes within ogre3d applications.
 * This app relies on ogre and not only on ois. The executables can be found in the bin of the
 * OGRE_HOME folder.
 *
 * @author barn
 * @version 20121020
 */
#include <iomanip>
#include <iostream>

#include <OIS/OIS.h>
#include <OGRE/Ogre.h>

using namespace std;

Ogre::Root* initOgre( int argc, char** argv);
std::pair<OIS::InputManager*,OIS::Keyboard*> setupOIS( Ogre::RenderWindow* win);
void doTheKeyCodeThing( const OIS::Keyboard* key);

int main( int argc, char** argv)
{
	// setup OGRE
	Ogre::Root* ogre = initOgre( argc, argv);
	Ogre::RenderWindow* win = ogre->getAutoCreatedWindow();

	win->setFullscreen( false, 100, 100);

	// setup OIS
	std::pair<OIS::InputManager*,OIS::Keyboard*> p = setupOIS( win);
	OIS::InputManager* man = p.first;
	OIS::Keyboard* key = p.second;

	// window loop
	while(true)
	{
		Ogre::WindowEventUtilities::messagePump(); // more convenient bc not the "busy" mouse cursor all the time

		key->capture();
		doTheKeyCodeThing( key);
	}
}

/**
 * @brief Initializes OGRE.
 * @param argc The argument counter, maybe the according parameter of the main function.
 * @param argv The argument vector, maybe the according parameter of the main function.
 */
Ogre::Root* initOgre( int argc, char** argv)
{
	const char* window_title = "OIS Input Grabber";
	const char* plugin_file = "plugins_barn.cfg";
	const char* config_file = "ogre.cfg";
	const char* log_file = "Ogre.log";

	Ogre::Root* root = new Ogre::Root( plugin_file, config_file, log_file);

	if (!root->restoreConfig())
	{
		if (!root->showConfigDialog())
		{
			delete root;
			return 0;
		}
	}

	root->initialise( true, window_title);
	return root;
}

/*
 * @brief sets up the ois input system.
 * @param win The window on which to listen for input.
 * @param man Reference to the input manager that will be created.
 * @param key Reference to the keyboard that will be created.
 * @return Returns a pair of a an input manager and a keyboard.
 */
std::pair<OIS::InputManager*,OIS::Keyboard*> setupOIS( Ogre::RenderWindow* win)
{
	OIS::InputManager* man;
	OIS::Keyboard* key;

	size_t windowHnd = 0;
	std::stringstream windowHndStr;

	win->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;

	OIS::ParamList pl;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	man = OIS::InputManager::createInputSystem( pl);
	key = static_cast<OIS::Keyboard*>( man->createInputObject( OIS::OISKeyboard, false));

	return std::pair<OIS::InputManager*,OIS::Keyboard*>( man,key);
}

/*
 * The totally stupid keyboard thing.
 * Since OIS lacks a fundamental thing: getting the enum-numbers to the key codes.
 */
void doTheKeyCodeThing( const OIS::Keyboard* key)
{
	const char* separator = "\t";

	if( key->isKeyDown( (OIS::KeyCode)0x00))
	{
		cout << hex << "0x" << 0x00 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x01))
	{
		cout << hex << "0x" << 0x01 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x02))
	{
		cout << hex << "0x" << 0x02 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x03))
	{
		cout << hex << "0x" << 0x03 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x04))
	{
		cout << hex << "0x" << 0x04 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x05))
	{
		cout << hex << "0x" << 0x05 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x06))
	{
		cout << hex << "0x" << 0x06 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x07))
	{
		cout << hex << "0x" << 0x07 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x08))
	{
		cout << hex << "0x" << 0x08 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x09))
	{
		cout << hex << "0x" << 0x09 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x0A))
	{
		cout << hex << "0x" << 0x0A << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x0B))
	{
		cout << hex << "0x" << 0x0B << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x0C))
	{
		cout << hex << "0x" << 0x0C << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x0D))
	{
		cout << hex << "0x" << 0x0D << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x0E))
	{
		cout << hex << "0x" << 0x0E << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x0F))
	{
		cout << hex << "0x" << 0x0F << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x10))
	{
		cout << hex << "0x" << 0x10 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x11))
	{
		cout << hex << "0x" << 0x11 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x12))
	{
		cout << hex << "0x" << 0x12 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x13))
	{
		cout << hex << "0x" << 0x13 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x14))
	{
		cout << hex << "0x" << 0x14 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x15))
	{
		cout << hex << "0x" << 0x15 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x16))
	{
		cout << hex << "0x" << 0x16 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x17))
	{
		cout << hex << "0x" << 0x17 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x18))
	{
		cout << hex << "0x" << 0x18 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x19))
	{
		cout << hex << "0x" << 0x19 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x1A))
	{
		cout << hex << "0x" << 0x1A << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x1B))
	{
		cout << hex << "0x" << 0x1B << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x1C))
	{
		cout << hex << "0x" << 0x1C << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x1D))
	{
		cout << hex << "0x" << 0x1D << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x1E))
	{
		cout << hex << "0x" << 0x1E << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x1F))
	{
		cout << hex << "0x" << 0x1F << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x20))
	{
		cout << hex << "0x" << 0x20 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x21))
	{
		cout << hex << "0x" << 0x21 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x22))
	{
		cout << hex << "0x" << 0x22 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x23))
	{
		cout << hex << "0x" << 0x23 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x24))
	{
		cout << hex << "0x" << 0x24 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x25))
	{
		cout << hex << "0x" << 0x25 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x26))
	{
		cout << hex << "0x" << 0x26 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x27))
	{
		cout << hex << "0x" << 0x27 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x28))
	{
		cout << hex << "0x" << 0x28 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x29))
	{
		cout << hex << "0x" << 0x29 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x2A))
	{
		cout << hex << "0x" << 0x2A << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x2B))
	{
		cout << hex << "0x" << 0x2B << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x2C))
	{
		cout << hex << "0x" << 0x2C << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x2D))
	{
		cout << hex << "0x" << 0x2D << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x2E))
	{
		cout << hex << "0x" << 0x2E << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x2F))
	{
		cout << hex << "0x" << 0x2F << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x30))
	{
		cout << hex << "0x" << 0x30 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x31))
	{
		cout << hex << "0x" << 0x31 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x32))
	{
		cout << hex << "0x" << 0x32 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x33))
	{
		cout << hex << "0x" << 0x33 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x34))
	{
		cout << hex << "0x" << 0x34 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x35))
	{
		cout << hex << "0x" << 0x35 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x36))
	{
		cout << hex << "0x" << 0x36 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x37))
	{
		cout << hex << "0x" << 0x37 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x38))
	{
		cout << hex << "0x" << 0x38 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x39))
	{
		cout << hex << "0x" << 0x39 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x3A))
	{
		cout << hex << "0x" << 0x3A << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x3B))
	{
		cout << hex << "0x" << 0x3B << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x3C))
	{
		cout << hex << "0x" << 0x3C << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x3D))
	{
		cout << hex << "0x" << 0x3D << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x3E))
	{
		cout << hex << "0x" << 0x3E << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x3F))
	{
		cout << hex << "0x" << 0x3F << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x40))
	{
		cout << hex << "0x" << 0x40 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x41))
	{
		cout << hex << "0x" << 0x41 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x42))
	{
		cout << hex << "0x" << 0x42 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x43))
	{
		cout << hex << "0x" << 0x43 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x44))
	{
		cout << hex << "0x" << 0x44 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x45))
	{
		cout << hex << "0x" << 0x45 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x46))
	{
		cout << hex << "0x" << 0x46 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x47))
	{
		cout << hex << "0x" << 0x47 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x48))
	{
		cout << hex << "0x" << 0x48 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x49))
	{
		cout << hex << "0x" << 0x49 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x4A))
	{
		cout << hex << "0x" << 0x4A << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x4B))
	{
		cout << hex << "0x" << 0x4B << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x4C))
	{
		cout << hex << "0x" << 0x4C << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x4D))
	{
		cout << hex << "0x" << 0x4D << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x4E))
	{
		cout << hex << "0x" << 0x4E << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x4F))
	{
		cout << hex << "0x" << 0x4F << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x50))
	{
		cout << hex << "0x" << 0x50 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x51))
	{
		cout << hex << "0x" << 0x51 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x52))
	{
		cout << hex << "0x" << 0x52 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x53))
	{
		cout << hex << "0x" << 0x53 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x56))
	{
		cout << hex << "0x" << 0x56 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x57))
	{
		cout << hex << "0x" << 0x57 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x58))
	{
		cout << hex << "0x" << 0x58 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x64))
	{
		cout << hex << "0x" << 0x64 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x65))
	{
		cout << hex << "0x" << 0x65 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x66))
	{
		cout << hex << "0x" << 0x66 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x70))
	{
		cout << hex << "0x" << 0x70 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x73))
	{
		cout << hex << "0x" << 0x73 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x79))
	{
		cout << hex << "0x" << 0x79 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x7B))
	{
		cout << hex << "0x" << 0x7B << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x7D))
	{
		cout << hex << "0x" << 0x7D << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x7E))
	{
		cout << hex << "0x" << 0x7E << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x8D))
	{
		cout << hex << "0x" << 0x8D << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x90))
	{
		cout << hex << "0x" << 0x90 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x91))
	{
		cout << hex << "0x" << 0x91 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x92))
	{
		cout << hex << "0x" << 0x92 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x93))
	{
		cout << hex << "0x" << 0x93 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x94))
	{
		cout << hex << "0x" << 0x94 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x95))
	{
		cout << hex << "0x" << 0x95 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x96))
	{
		cout << hex << "0x" << 0x96 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x97))
	{
		cout << hex << "0x" << 0x97 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x99))
	{
		cout << hex << "0x" << 0x99 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x9C))
	{
		cout << hex << "0x" << 0x9C << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0x9D))
	{
		cout << hex << "0x" << 0x9D << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xA0))
	{
		cout << hex << "0x" << 0xA0 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xA1))
	{
		cout << hex << "0x" << 0xA1 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xA2))
	{
		cout << hex << "0x" << 0xA2 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xA4))
	{
		cout << hex << "0x" << 0xA4 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xAE))
	{
		cout << hex << "0x" << 0xAE << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xB0))
	{
		cout << hex << "0x" << 0xB0 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xB2))
	{
		cout << hex << "0x" << 0xB2 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xB3))
	{
		cout << hex << "0x" << 0xB3 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xB5))
	{
		cout << hex << "0x" << 0xB5 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xB7))
	{
		cout << hex << "0x" << 0xB7 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xB8))
	{
		cout << hex << "0x" << 0xB8 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xC5))
	{
		cout << hex << "0x" << 0xC5 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xC7))
	{
		cout << hex << "0x" << 0xC7 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xC8))
	{
		cout << hex << "0x" << 0xC8 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xC9))
	{
		cout << hex << "0x" << 0xC9 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xCB))
	{
		cout << hex << "0x" << 0xCB << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xCD))
	{
		cout << hex << "0x" << 0xCD << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xCF))
	{
		cout << hex << "0x" << 0xCF << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xD0))
	{
		cout << hex << "0x" << 0xD0 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xD1))
	{
		cout << hex << "0x" << 0xD1 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xD2))
	{
		cout << hex << "0x" << 0xD2 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xD3))
	{
		cout << hex << "0x" << 0xD3 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xDB))
	{
		cout << hex << "0x" << 0xDB << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xDC))
	{
		cout << hex << "0x" << 0xDC << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xDD))
	{
		cout << hex << "0x" << 0xDD << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xDE))
	{
		cout << hex << "0x" << 0xDE << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xDF))
	{
		cout << hex << "0x" << 0xDF << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xE3))
	{
		cout << hex << "0x" << 0xE3 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xE5))
	{
		cout << hex << "0x" << 0xE5 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xE6))
	{
		cout << hex << "0x" << 0xE6 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xE7))
	{
		cout << hex << "0x" << 0xE7 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xE8))
	{
		cout << hex << "0x" << 0xE8 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xE9))
	{
		cout << hex << "0x" << 0xE9 << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xEA))
	{
		cout << hex << "0x" << 0xEA << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xEB))
	{
		cout << hex << "0x" << 0xEB << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xEC))
	{
		cout << hex << "0x" << 0xEC << separator;
	}
	if( key->isKeyDown( (OIS::KeyCode)0xED))
	{
		cout << hex << "0x" << 0xED << separator;
	}
}
