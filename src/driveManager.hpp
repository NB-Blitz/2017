#ifndef SRC_DRIVEMANAGER_HPP_
#define SRC_DRIVEMANAGER_HPP_

#include "WPILib.h"
#include "inputManager.hpp"
#include "CanTalon.h"
#include "AHRS.h"

namespace FRC
{
	class driveManager
	{
		public:
			driveManager();

			//Object Declarations
			CANTalon leftBackM, leftFrontM, rightBackM, rightFrontM; //enc: 3024 counts / 1 rev
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
			double JoyX;
			double JoyY;
			double joyRotate;
			double JoyXRaw;
			double JoyYRaw;
			double JoyRotateRaw;
			double speeds[4];
			double delta;
			double rotation;
			double pi = 3.14159265359;
			double ang;
			int dir = 1;
			double maxMagnitude;
			double bias;

			//PIcorrection
			int EncoderFreq[4];
			double spdRef[4];
			double SPFeedBack[4];
			double error[4];
			double intOut[4];
			double propOut[4];
			double PIout[4];
			double PWMout[4];
			bool intReset = false;
			double preSpeed[4];
	};
}
#endif
