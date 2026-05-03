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
			void attachAppState(AbstractAppState *a);
			void dettachAppState(AbstractAppState*);
			void dettachAppStateByType(int);
			inline void dettachAppStateById(int id){appStates.erase(appStates.begin() + id);}
			inline AbstractAppState* getAppStateById(int i){return appStates[i];}
			AbstractAppState* getAppStateByType(int);
			inline std::vector<AbstractAppState*> getAppStates(){return appStates;}
			inline int getNumAppStates(){return appStates.size();}
		private:
			std::vector<AbstractAppState*> appStates;
	};
}

#endif
