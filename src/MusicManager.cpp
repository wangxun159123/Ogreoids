#include "stdafx.h"

#include "MusicManager.h"

namespace ogreoids {

	/**
	 * MusicManager constructor.
	 */
	MusicManager::MusicManager(){
		initialize();
		createMusic();
		createSounds();
	}

	/**
	 * MusicManager destructor.
	 */
	MusicManager::~MusicManager() {
		
		// Release all music channels.
		for (unsigned i = 0; i < music.size(); i++) {
			music[i]->release();
			errorCheck("Failed to release music files");
		}

	}

	MusicManager* MusicManager::getInstance(){
		static MusicManager musicManager;
		return &musicManager;
	}


// =====================================================================================
//
// #Initialization
//
// =====================================================================================

	/**
	 * Initialize FMOD sound system.
	 */
	void MusicManager::initialize() {

		// Create the main system object.
		result = FMOD::System_Create(&system);	
		errorCheck("Failed to create the sound system");

		// Initialize FMOD.
		result = system->init(100, FMOD_INIT_NORMAL, 0);	
		errorCheck("Failed to initialize FMOD");
		result = system->set3DSettings(0.05f, 1, 1);
		errorCheck("Failed to set 3D sound settings");

	}

	/**
	 * 
	 */
	void MusicManager::setListenerAttributes(Ogre::Vector3 pos, Ogre::Vector3 vel, Ogre::Vector3 dir, Ogre::Vector3 up){

		result = system->set3DListenerAttributes(0,
											&OgreToFmod(pos), &OgreToFmod(vel),
											&OgreToFmod(dir), &OgreToFmod(up));
		errorCheck("Failed to set 3D listener attributes");

	}

	/**
	 * Set 3D sound attibutes.
	 */
	FMOD::Channel* MusicManager::setAttributes(Ogre::Vector3 pos, Ogre::Vector3 vel, FMOD::Channel* channel) {
		result = channel->set3DAttributes(&OgreToFmod(pos), &OgreToFmod(vel));
		errorCheck("Failed to set sound 3D attributes for jetstream");
		return channel;
	}

	/**
	 * Initialize all music.
	 */
	void MusicManager::createMusic() {
		
	}

	/**
	 * Initialize all sound effects.
	 */
	void MusicManager::createSounds() {
		
		// Weapon system 1 shot.
		FMOD::Sound* ws1;
		result = system->createSound("media/sounds/sfx/arwingSingleLaserOneShot.mp3", FMOD_LOOP_OFF | FMOD_2D, 0, &ws1);
		errorCheck("Failed to create weapon system 1 firing sound effect");
		sounds.push_back(ws1);

		// Weapon system 2 shot.
		FMOD::Sound* ws2;
		result = system->createSound("media/sounds/sfx/arwingDoubleLaserOneShot.mp3", FMOD_LOOP_OFF | FMOD_2D, 0, &ws2);
		errorCheck("Failed to create weapon system 2 firing sound effect");
		sounds.push_back(ws2);

		// Weapon system 3 shot.
		FMOD::Sound* ws3;
		result = system->createSound("media/sounds/sfx/arwingHyperLaserOneShot.mp3", FMOD_LOOP_OFF | FMOD_2D, 0, &ws3);
		errorCheck("Failed to create weapon system 3 firing sound effect");
		sounds.push_back(ws3);

	}


// =====================================================================================
//
// #Update
//
// =====================================================================================

	/**
	 * Play a sound effect at the given index.
	 *
	 * @param index						index for which sound effect to play
	 *
	 */
	void MusicManager::playSound(unsigned index) {
		result = system->playSound(FMOD_CHANNEL_FREE, sounds[index], false, 0);
		errorCheck("Failed to play sound");
	}


// =====================================================================================
//
// #Update
//
// =====================================================================================

	void MusicManager::update(Ogre::Real deltaT) {
		result = system->update();
		errorCheck("Failed to update sound system");
	}
	

// =====================================================================================
//
// #Exceptation Handling
//
// =====================================================================================

	void MusicManager::errorCheck(const std::string& errMsg){

		if(result != FMOD_OK){

			std::stringstream ss;

			ss << errMsg << "FMOD error! " << result << ": " << FMOD_ErrorString(result);

			throw std::exception(ss.str().c_str());
		}

	}

}
