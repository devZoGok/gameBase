#ifndef ABSTRACT_APP_STATE_H
#define ABSTRACT_APP_STATE_H

#include "mapping.h"
#include "solUtil.h"

#include <string>
#include <vector>

namespace sol{
	class state;
}

namespace gameBase {
	class AbstractAppState{
		public:
			AbstractAppState(int, int, int, std::string);
			virtual void update(){}
			virtual void onAttached();
			virtual void onDettached();
			inline int getType(){return type;}
			inline Mapping* getMapping(int id){return mappings[id];}
			inline std::vector<Mapping*>& getMappings(){return mappings;}
			inline int getNumMappings(){return mappings.size();}
			inline bool isAttached(){return attached;}
			void removeMapping(int);
			virtual void onAction(int, bool){}
			virtual void onAnalog(int, float){}
			virtual void onRawKeyPress(int){}
			virtual void onRawCharPress(unsigned int){}
			virtual void onRawMousePress(int){}
			virtual void onRawMouseWheelScroll(bool){}
			virtual void onRawJoystickMove(int, float){}
			virtual void onRawJoystickPress(int){}
		protected:
			AbstractAppState(){}
			~AbstractAppState(){}

			std::vector<Mapping*> mappings;
			std::string optionsFile;
			int type, firstMapping, numMappings;
			bool attached = false;
	};
}

#endif
