/*
 * autoManager.hpp
 *
 *  Created on: Feb 20, 2017
 *      Author: tv4958
 */

#ifndef SRC_AUTOMANAGER_HPP_
#define SRC_AUTOMANAGER_HPP_

#include "WPILib.h"
#include "driveManager.hpp"
#include "manipulator.hpp"
#include "lidarManager.hpp"
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
			FRC::driveManager driveMan;
			FRC::lidarManager lidarMan;
			FRC::manipulator manipulator;

			//Function Declarations
			double getEncDistance(bool clear);
			void driveDistance(double distance, double angle);
			void rotate(double target, double speed, int direction);
			void centerWithTape(double angle, int pixelThreshold, double distFromCenter, double targetAng);
			void centerAuto();
			void rightAuto();
			void leftAuto();

			double ENC_TARGET = 2.75;
			int PIXEL_THRESHOLD = 3;
			int REVERSE_TARGET = 30;
			double ANGLE_THRESHOLD = 10;
			double FINAL_TARGET = 350;

			int autoStep = 1;
			double encDistance = 0;
			double timer = 0;
			double distFromCenter = 0;
			int reverseCounter = 0;
			double finalDriveCounter = 0;
	};
}
#endif /* SRC_AUTOMANAGER_HPP_ */
