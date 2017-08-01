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
			double getEncDistance(bool clear);
			void driveDistance(double distance, double angle);
			void rotate(double target, double speed, int direction);
			void centerWithTape(double angle, int pixelThreshold, double distFromCenter, double targetAng);
			void centerAuto();
			void rightAuto();
			void leftAuto();

			//Auto Variable Declarations
			int step = 1;

					// ----------- Step 1 Vars -----------
					double autoJoystick = -0.4;
					double targetDistance = 2.75;
					double encDistance = 0;

					// ----------- Step 2 Vars -----------
					bool angleStatus = false;
					double prevAngle = -1;
					double Angle = 0;
					double targetAngle = 300; //Default: 360
					int direction = 1;
					double thresholdAngle2 = 3.0;
					double rotateSpeed = 0.3;

					// ----------- Step 3 Vars -----------
					double pixelThreshold = 3;

					// ----------- Step 5 Vars -----------
					bool lidarStatus = false;
					double lidarDistance = 0;
					double startLimit = 1;
					double endLimit = 0.4;
					double controlLimit = 0;
					double lidarMin = 1000000;

					// ----------- Step 6 Vars -----------
					int gearTarget = 20;
					int gearCounter = 0;
					int gearCounter2nd = 0;

					// ----------- Step 7 Vars -----------
					int reverseCounter = 0;
					int reverseTarget = 30;

					// ----------- Step 8 Vars -----------
					double targetReturnAngle = 360.0;
					double thresholdAngle8 = 10;

					// ----------- Step 9 Vars -----------
					int finalDriveCounter = 0;
					int finalDriveCounterTarget = 350;

	};
}
#endif /* SRC_AUTOMANAGER_HPP_ */
