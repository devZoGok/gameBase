#include "abstractAppState.h"
#include "util.h"
#include "mapping.h"

using namespace std;

namespace gameBase {
	void AbstractAppState::onAttached(){
		attached = true;

		for(int i = 0; i < bindingsLines.size(); i++){
			int semicolon;

			for(int j = 0; j < bindingsLines[i].length(); j++)	
				if(bindingsLines[i].c_str()[j] == ':')
					semicolon = j;

			Mapping::BindType type = (Mapping::BindType)atoi(bindingsLines[i].substr(semicolon + 1, 1).c_str());
			bool action = atoi(bindingsLines[i].substr(semicolon + 3, 1).c_str());
			int trigger = atoi(bindingsLines[i].substr(semicolon + 5, string::npos).c_str());

			Mapping *m = new Mapping;
			m->bind = 3 + i;
			m->type = type;
			m->action = action;
			m->trigger = trigger;
			mappings.push_back(m);	
		}
	}

	void AbstractAppState::onDettached(){
		attached = false;

		while(!mappings.empty())
				mappings.pop_back();
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
