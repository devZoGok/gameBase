#include "soundManager.h"

#include <SFML/Audio.hpp>

#include <algorithm>
#include <random>

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
		if(!currentPlaylistTracks.empty()){
			sf::SoundSource::Status status = currentPlaylistTracks[currentTrackId].soundObj->getStatus();

			if(status == sf::SoundSource::Status::Stopped){
				if(getTime() - lastPlayTime < trackDelay) return;

				bool lastTrack = (currentTrackId == currentPlaylistTracks.size() - 1);

				if(lastTrack && loop)
					currentTrackId = 0;
				else if(lastTrack && !loop)
					clearPlaylist();
				else if(!lastTrack)
					currentTrackId++;

				if(!currentPlaylistTracks.empty()){
					currentPlaylistTracks[currentTrackId].soundObj->play();
					currentPlaylistTracks[currentTrackId].soundObj->setVolume(volume);
					currentPlaylistTracks[currentTrackId].soundObj->setLooping(false);
				}
			}
			else if(status == sf::SoundSource::Status::Playing)
				lastPlayTime = getTime();
		}
	}

	void SoundManager::clearPlaylist(){
		for(Track &track : currentPlaylistTracks)
			delete track.soundObj;
		
		currentPlaylistTracks.clear();
		originalPlaylist.clear();
	}

	void SoundManager::play(vector<string> playlist, int volume, int trackDelay, bool loop, bool shuffle){
		bool samePlaylist = (playlist.size() == originalPlaylist.size());

		if(samePlaylist)
			for(int i = 0; i < originalPlaylist.size(); i++)
				if(originalPlaylist[i] != playlist[i]){
					samePlaylist = false;
					break;
				}

		if(samePlaylist) return;

		this->loop = loop;
		this->shuffle = shuffle;
		this->volume = volume;
		this->trackDelay = trackDelay;

		clearPlaylist();

		for(string path : playlist)
			currentPlaylistTracks.push_back(Track(path));

		if(shuffle){
			random_device rd;
    		mt19937 g(rd());
			std::shuffle(currentPlaylistTracks.begin(), currentPlaylistTracks.end(), g);
		}

		originalPlaylist = playlist;
		currentTrackId = 0;
		currentPlaylistTracks[currentTrackId].soundObj->play();
		currentPlaylistTracks[currentTrackId].soundObj->setVolume(volume);
		currentPlaylistTracks[currentTrackId].soundObj->setLooping(false);
	}
}
