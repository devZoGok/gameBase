#pragma once
#ifndef KEY_H
#define KEY_H

namespace gameBase{
	struct Mapping{
		enum BindType{KEYBOARD, MOUSE_KEY, MOUSE_AXIS, JOYSTICK_KEY, JOYSTICK_AXIS};
		enum AuxTriggers{MOUSE_AXIS_LEFT = 310, MOUSE_AXIS_RIGHT = 311, MOUSE_AXIS_UP = 312, MOUSE_AXIS_DOWN = 313};
	
		int bind;
		BindType type;
		int trigger;
		bool action, pressed = false;
	};
}

#endif
