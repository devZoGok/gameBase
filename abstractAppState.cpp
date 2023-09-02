#include "abstractAppState.h"
#include "util.h"
#include "solUtil.h"
#include "mapping.h"

namespace gameBase {
	using namespace std;

	AbstractAppState::AbstractAppState(int type, int firstMapping, int numMappings, string optionsFile){
			this->type = type;
			this->firstMapping = firstMapping;
			this->numMappings = numMappings;
			this->optionsFile = optionsFile;
	}

	void AbstractAppState::onAttached(){
		attached = true;

		SOL_LUA_STATE.script_file(optionsFile);
		string table = "mappings";

		for(int i = firstMapping; i < firstMapping + numMappings; i++){
			Mapping *m = new Mapping;
			m->bind = SOL_LUA_STATE[table][i + 1]["bind"];
			m->type = (Mapping::BindType)SOL_LUA_STATE[table][i + 1]["bindType"];
			m->action = SOL_LUA_STATE[table][i + 1]["action"];
			m->trigger = SOL_LUA_STATE[table][i + 1]["trigger"];
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
