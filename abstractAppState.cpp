#include "abstractAppState.h"
#include "util.h"
#include "mapping.h"

using namespace std;

namespace gameBase {
	void AbstractAppState::onAttached(){
		attached = true;

		for(int i = 0; i < bindingsLines.size(); i++){
			int semicolon, numFoundCommas = 0;
			int commaIds[3];

			for(int j = 0; j < bindingsLines[i].length(); j++){
				if(bindingsLines[i].c_str()[j] == ':')
					semicolon = j;
				else if(bindingsLines[i].c_str()[j] == ','){
					commaIds[numFoundCommas] = j;
					numFoundCommas++;
				}
			}

			int bind = atoi(bindingsLines[i].substr(semicolon + 1, commaIds[0] - semicolon).c_str());
			Mapping::BindType type = (Mapping::BindType)atoi(bindingsLines[i].substr(commaIds[0] + 1, commaIds[1] - commaIds[0]).c_str());
			bool action = atoi(bindingsLines[i].substr(commaIds[1] + 1, commaIds[2] - commaIds[1]).c_str());
			int trigger = atoi(bindingsLines[i].substr(commaIds[2] + 1, string::npos).c_str());

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
