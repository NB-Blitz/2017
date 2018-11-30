#ifndef SRC_MANIPULATOR_HPP_
#define SRC_MANIPULATOR_HPP_

#include "WPIlib.h"
#include "DigitalInput.h"
#include "inputManager.hpp"
#include <ctre/Phoenix.h>

namespace FRC
{
	class manipulator
	{
		public:
			manipulator();

			//Object Declarations
			FRC::inputManager inputManager;
			WPI_TalonSRX gear, climbMotor;
			DigitalInput GearSwitch;
			AnalogInput pot;
			PowerDistributionPanel PDP;

			//Function Declarations
			void GearReset(double speed);
			void GearOut(double speed);
			void climb();
	};
}
#endif




