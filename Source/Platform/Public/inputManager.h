#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class GLFWwindow;

namespace gameBase{
	class StateManager;

	class InputManager{
		public:
			InputManager(StateManager*, GLFWwindow*);
			~InputManager();
			void update();
		private:
			StateManager *stateManager;
			GLFWwindow *window;
	};
}

#endif
