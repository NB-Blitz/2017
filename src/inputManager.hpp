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
			Joystick joyStick, xBox;

			//Function Declarations
			void getData();

			double joyX;
			double joyY;
			double joyZ;
	};
}
#endif
