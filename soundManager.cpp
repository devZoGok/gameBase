#include "soundManager.h"

#include <SFML/Audio.hpp>

namespace gameBase{
	using namespace std;

	SoundManager::Track::Track(string p) : path(p){
		soundObj = new sf::Music(p);
		soundObj->openFromFile(p.c_str());
	}

	static SoundManager* soundManager = nullptr;

	SoundManager* SoundManager::getSingleton(){
		if(soundManager == nullptr)
			soundManager = new SoundManager();

		return soundManager;
	}

	void SoundManager::update(){
		if(currentPlaylist[currentTrackId].soundObj->getStatus() == sf::SoundSource::Status::Stopped){
			bool lastTrack = (currentTrackId == currentPlaylist.size() - 1);

			if(lastTrack && loop)
				currentTrackId = 0;
			else if(lastTrack && !loop)
				clearPlaylist();
			else if(!lastTrack)
				currentTrackId++;

			if(!currentPlaylist.empty()){
				currentPlaylist[currentTrackId].soundObj->play();
				currentPlaylist[currentTrackId].soundObj->setLooping(false);
			}
		}
	}

	void SoundManager::clearPlaylist(){
		for(Track &track : currentPlaylist)
			delete track.soundObj;
		
		currentPlaylist.clear();
	}

	void SoundManager::play(vector<string> playlist, int volume, bool loop, bool shuffle){
		this->loop = loop;
		this->shuffle = shuffle;

		clearPlaylist();

		for(string path : playlist)
			currentPlaylist.push_back(Track(path));

		currentTrackId = 0;
		currentPlaylist[currentTrackId].soundObj->play();
		currentPlaylist[currentTrackId].soundObj->setLooping(false);
	}
}
