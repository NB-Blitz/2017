#ifndef SRC_DRIVEMANAGER_HPP_
#define SRC_DRIVEMANAGER_HPP_

#include "WPILib.h"
#include "inputManager.hpp"
#include "cmath"
#include "cstdbool"
#include "cstdlib"
#include "AHRS.h"
#include <ctre/Phoenix.h>

namespace FRC
{
	class driveManager
	{
		public:
			driveManager();

			//Object Declarations
			WPI_TalonSRX leftBackM, leftFrontM, rightBackM, rightFrontM; //enc: 3024 counts / 1 rev
			AHRS ahrs;
			FRC::inputManager inputManager;

			//Function Declarations
			void PIcorrection(int id);
			void mecanumDrive(double x, double y, double rotate, bool bypass);
			void ramp();
			void straightDrive(double PreAngle, double x, double y);
			double getDistance();
			void resetEnc();
			void driveDistance(double distance);
			void rotate(double degrees);
			void FieldControl(double x, double y, double rotate);
			float getAngle();

			//Variable Declarations
			//JoySticks
			double JoyX  = 0;
			double JoyY = 0;
			double joyRotate = 0;
			double JoyXRaw = 0;
			double JoyYRaw = 0;
			double JoyRotateRaw = 0;
			double speeds[4] = {0, 0, 0, 0};
			double delta = 0;
			double rotation = 0;
			double pi = 3.14159265359;
			double ang = 0;
			int dir = 1;
			double maxMagnitude = 0;
			double bias = 0;

			//PIcorrection
			int EncoderFreq[4] = {0, 0, 0, 0};
			double spdRef[4] = {0, 0, 0, 0};
			double SPFeedBack[4] = {0, 0, 0, 0};
			double error[4] = {0, 0, 0, 0};
			double intOut[4] = {0, 0, 0, 0};
			double propOut[4] = {0, 0, 0, 0};
			double PIout[4] = {0, 0, 0, 0};
			double PWMout[4] = {0, 0, 0, 0};
			bool intReset = false;
			double preSpeed[4] = {0, 0, 0, 0};
	};
}
#endif
