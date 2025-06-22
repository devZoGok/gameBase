#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <string>
#include <vector>

#include "util.h"

namespace sf{
	class Music;
}

namespace gameBase{
	class SoundManager{
		public:
			static SoundManager* getSingleton();
			void update();
			void play(std::vector<std::string>, int, int, bool, bool);
		private:
			struct Track{
				std::string path = ""; 
				sf::Music *soundObj = nullptr;

				Track(std::string);
			};
			SoundManager(){}
			void clearPlaylist();
			
			int currentTrackId = 0, volume, trackDelay;
			bool loop, shuffle;
			s64 lastPlayTime = 0;
			std::vector<Track> currentPlaylistTracks;
			std::vector<std::string> originalPlaylist;
	};
}

#endif
