#include "abstractAppState.h"
#include "util.h"
#include "mapping.h"
#include "luaManager.h"

namespace gameBase {
	using namespace std;

	typedef LuaManager::Index Index;

	AbstractAppState::AbstractAppState(int type, int firstMapping, int numMappings, string optionsFile){
			this->type = type;
			this->firstMapping = firstMapping;
			this->numMappings = numMappings;
			this->optionsFile = optionsFile;
	}

	void AbstractAppState::onAttached(){
		attached = true;

		LuaManager *luaManager = LuaManager::getSingleton();
		luaManager->buildScript(vector<string>{optionsFile});
		string table = "mappings";

		for(int i = firstMapping; i < firstMapping + numMappings; i++){
			Index idIndex = Index(to_string(i + 1), false);
			int bind = luaManager->getIntFromTable(table, vector<Index>{idIndex, Index("bind", true)});
			Mapping::BindType type = (Mapping::BindType)luaManager->getIntFromTable(table, vector<Index>{idIndex, Index("bindType", true)});
			bool action = luaManager->getBoolFromTable(table, vector<Index>{idIndex, Index("action", true)});
			int trigger = luaManager->getIntFromTable(table, vector<Index>{idIndex, Index("trigger", true)});

			Mapping *m = new Mapping;
			m->bind = bind;
			m->type = type;
			m->action = action;
			m->trigger = trigger;
			mappings.push_back(m);	
		}
	}

	void AbstractAppState::onDettached(){
		attached = false;

		mappings.clear();
	}

	void AbstractAppState::removeMapping(int bind){
		int id = -1;

		for(int i = 0; i < mappings.size(); i++)
			if(mappings[i]->bind == bind)
				id = i;

		if(id != -1)
			mappings.erase(mappings.begin() + id);
	}
}
