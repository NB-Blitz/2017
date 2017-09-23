#ifndef SRC_MANIPULATOR_HPP_
#define SRC_MANIPULATOR_HPP_

#include "WPILib.h"
#include "inputManager.hpp"
#include "CANTalon.h"

namespace FRC
{
	class manipulator
	{
		public:
			manipulator();

			//Object Declarations
			FRC::inputManager inputManager;
			CANTalon gear;
			Talon climbMotor;
			AnalogInput pot;
			PowerDistributionPanel PDP;

			//Function Declarations
			void GearReset(double speed);
			void GearOut(double speed);
			void climb();
	};
}
#endif
