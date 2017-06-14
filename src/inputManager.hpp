#ifndef SRC_INPUTMANAGER_HPP_
#define SRC_INPUTMANAGER_HPP_

#include "WPILib.h"
#include "cmath"

namespace FRC
{
	class inputManager
	{
		public:
			inputManager();

			//Object Declarations
			Joystick JoyStick, xBox;

			//Function Declarations
			double joystickRadians();
	};
}
#endif
