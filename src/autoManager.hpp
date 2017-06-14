/*
 * autoManager.hpp
 *
 *  Created on: Feb 20, 2017
 *      Author: tv4958
 */

#ifndef SRC_AUTOMANAGER_HPP_
#define SRC_AUTOMANAGER_HPP_

#include "WPILib.h"
#include "inputManager.hpp"
#include "driveManager.hpp"
#include "cameraManager.hpp"
#include "CanTalon.h"
#include "AHRS.h"

namespace FRC
{
	class autoManager
	{
		public:
			autoManager();

			//Object Declarations
			Joystick Auto;
			FRC::driveManager driveManager;

			//Function Declarations
			double getEncDistance();
			void driveDistance(double distance, double angle);
			void rotate(double target, double speed, int direction);
			void centerWithTape(double angle, int pixelThreshold, double distFromCenter, double targetAng);
	};
}
#endif /* SRC_AUTOMANAGER_HPP_ */
