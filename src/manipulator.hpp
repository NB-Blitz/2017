#ifndef SRC_MANIPULATOR_HPP_
#define SRC_MANIPULATOR_HPP_

#include "CANTalon.h"
#include "DigitalInput.h"
#include "Talon.h"
#include "inputManager.hpp"

namespace FRC
{
	class manipulator
	{
		public:
			manipulator();

			//Object Declarations
			FRC::inputManager inputManager;
			CANTalon gear;
			Talon ball, climbMotor;
			DigitalInput GearSwitch;
			AnalogInput pot;
			PowerDistributionPanel PDP;

			//Function Declarations
			void GearReset(double speed);
			void GearOut(double speed);
			void ballEject();
			void climb();
	};
}
#endif




