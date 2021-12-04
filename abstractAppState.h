#ifndef ABSTRACT_APP_STATE_H
#define ABSTRACT_APP_STATE_H

#include "mapping.h"

#include <string>
#include <vector>

namespace gameBase {
	class AbstractAppState{
		public:
			virtual void update();
			virtual void onAttached();
			virtual void onDettached();
			inline int getType(){return type;}
			inline Mapping* getMapping(int id){return mappings[id];}
			inline std::vector<Mapping*>& getMappings(){return mappings;}
			inline int getNumMappings(){return mappings.size();}
			inline bool isAttached(){return attached;}
			void removeMapping(Mapping::Bind);
			virtual void onAction(Mapping::Bind,bool){}
			virtual void onAnalog(Mapping::Bind,float){}
			virtual void onRawKeyButton(short){}
			virtual void onRawMouseButton(short){}
			virtual void onRawJoystickAxis(short,float){}
			virtual void onRawJoystickButton(short){}
		protected:
			AbstractAppState(){}
			~AbstractAppState(){}
			std::vector<Mapping*> mappings;
			std::vector<std::string> bindingsLines;
			int type;
			bool attached = false;
	};
}

#endif
