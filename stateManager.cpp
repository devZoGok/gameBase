#include "stateManager.h"

namespace gameBase {
	void StateManager::update(){
		for(int i = 0; i < appStates.size(); i++)
			appStates[i]->update();
	}

	void StateManager::attachState(AbstractAppState *a){
		appStates.push_back(a);
		a->onAttached();
	}

	void StateManager::dettachState(AbstractAppState *a){
		int id=-1;

		for(int i = 0; i < appStates.size() && id == -1; i++)
			if(appStates[i] == a)
				id = i;

		if(id != -1){
			a->onDettached();
			appStates.erase(appStates.begin() + id);
		}
	}

	void StateManager::dettachStateByType(int type){
		int id = -1;

		for(int i = 0; i < appStates.size() && id == -1; i++)
			if(appStates[i]->getType() == type)
				id = i;

		if(id != -1){
			appStates[id]->onDettached();
			appStates.erase(appStates.begin() + id);
		}
	}

	AbstractAppState* StateManager::getStateByType(int type){
		AbstractAppState *a = nullptr;	

		for(int i = 0; i < appStates.size() && !a; i++)
			if(appStates[i]->getType() == type)
				a = appStates[i];

		return a;
	}
}
