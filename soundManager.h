#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <string>
#include <vector>

namespace sf{
	class Music;
}

namespace gameBase{
	class SoundManager{
		public:
			static SoundManager* getSingleton();
			void update();
			void play(std::vector<std::string>, int, bool, bool);
		private:
			struct Track{
				std::string path = ""; 
				sf::Music *soundObj = nullptr;

				Track(std::string);
			};
			SoundManager(){}
			void clearPlaylist();
			
			int currentTrackId = 0;
			bool loop, shuffle;
			std::vector<Track> currentPlaylist;
	};
}

#endif
