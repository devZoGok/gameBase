#include "inputManager.h"
#include "stateManager.h"
#include "util.h"

#include <glfw3.h>
#include <cmath>
#include <iostream>

namespace gameBase{
	double *posX, *posY, strX, strY;
	int width, height;
	StateManager *manager = nullptr;
	
	void foo(GLFWwindow *window, double newPosX, double newPosY){
		strX = (*posX - newPosX) / width, strY = (newPosY - *posY) / height;
	}

	void charFoo(GLFWwindow *window, unsigned int codepoint){
			if(manager)
				for(AbstractAppState *a : manager->getAppStates())
					a->onRawCharPress(codepoint);
	}

	InputManager::InputManager(StateManager *sm, GLFWwindow *window){
		manager = sm;
		this->stateManager = sm;
		this->window = window;
		posX = new double, posY = new double;
	}

	InputManager::~InputManager(){}

	void InputManager::update(){
 		glfwGetWindowSize(window, &width, &height);

		glfwGetCursorPos(window, posX, posY);
		int joystick;
		int numAxis = 3, numButtons = 6;
		const u8 *buttons;
		const float *axis;

		if(glfwJoystickPresent(GLFW_JOYSTICK_1)){
			joystick = GLFW_JOYSTICK_1;
			axis = glfwGetJoystickAxes(joystick, &numAxis);
			buttons = glfwGetJoystickButtons(joystick, &numButtons);
		}

		for(int j = 0; j < stateManager->getAppStates().size(); j++){
			glfwSetCharCallback(window, charFoo);
			AbstractAppState *currentState = stateManager->getAppStates()[j];

			for(int i = 0; i < currentState->getNumMappings(); i++){
				Mapping *m = currentState->getMapping(i);

				if(m->action){
					bool pressed;

					switch(m->type){
						case Mapping::KEYBOARD:
							pressed = glfwGetKey(window, m->trigger);
							break;
						case Mapping::MOUSE_KEY:
							pressed = glfwGetMouseButton(window, m->trigger);
							break;
						case Mapping::JOYSTICK_KEY:
							if(glfwJoystickPresent(GLFW_JOYSTICK_1))
								pressed = buttons[m->trigger];

							break;
					}

					if((pressed && !m->pressed) || (!pressed&&m->pressed)){
						m->pressed = pressed;	
						currentState->onAction(m->bind, pressed);
					}
				}
				else{
					switch(m->type){
						case Mapping::MOUSE_AXIS:
							{
								float str;

								switch(m->trigger){
									case Mapping::MOUSE_AXIS_LEFT:
									case Mapping::MOUSE_AXIS_RIGHT:
										str = strX;
										break;
									case Mapping::MOUSE_AXIS_UP:
									case Mapping::MOUSE_AXIS_DOWN:
										str = strY;
										break;
								}

								currentState->onAnalog(m->bind, str);
								break;
							}
						case Mapping::JOYSTICK_AXIS:
							{
								int axisId = (m->trigger - (m->trigger % 2 > 0)) / 2;
								float str = (fabs(axis[axisId]) >= .1 ? axis[axisId] : 0);

								if(fabs(str) > 0)
									currentState->onAnalog(m->bind, str);

								break;
							}
					}
				}
			}

			for(int i = 32; i < 300; i++)
				if(glfwGetKey(window, i))
					currentState->onRawKeyPress(i);

			for(int i = 0; i < 3; i++)
				if(glfwGetMouseButton(window, i))
					currentState->onRawMousePress(i);

			glfwSetCursorPosCallback(window, foo);

			if(glfwJoystickPresent(GLFW_JOYSTICK_1)){
				for(int i = 0; i < numAxis; i++)
					if(abs(axis[i]) == 1)
						currentState->onRawJoystickMove(i, axis[i]);

				for(int i = 0; i < numButtons; i++)
					if(buttons[i])
						currentState->onRawJoystickPress(i);
			}
		}
	}
}
