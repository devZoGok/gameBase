#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <vector>

#include "abstractAppState.h"

namespace gameBase {
	class StateManager{
		public:
			StateManager(){}
			~StateManager(){}
			void update();
			void attachState(AbstractAppState *a);
			void dettachState(AbstractAppState*);
			void dettachStateByType(int);
			inline void dettachStateById(int id){appStates.erase(appStates.begin() + id);}
			inline AbstractAppState* getStateById(int i){return appStates[i];}
			AbstractAppState* getStateByType(int);
			inline std::vector<AbstractAppState*> getAppStates(){return appStates;}
			inline int getNumAppStates(){return appStates.size();}
		private:
			std::vector<AbstractAppState*> appStates;
	};
}

#endif
