/*
 * driveManager.hpp
 *
 *  Created on: Jul 29, 2017
 *      Author: admin
 */

#ifndef SRC_DRIVEMANAGER_HPP_
#define SRC_DRIVEMANAGER_HPP_

#include "WPILib.h"
#include "CanTalon.h"
#include "inputManager.hpp"
#include "autoManager.hpp"
#include "AHRS.h"

namespace FRC
{
	class driveManager
	{
	public:
		driveManager();
		FRC::inputManager inputManager;
		FRC::autoManager autoManager;

		//Object Declarations
		CANTalon leftBackM, leftFrontM, rightBackM, rightFrontM;
		AHRS ahrs;

		//Functions
		void fieldControl(double x, double y, double rotate);
		void straightDrive(double x, double y)
		void mecanumDrive(double x, double y, double rotate);
		double PICorrection(double PreValue, double Enc);
		void resetEnc();
		void getData();

		//Variables
		double const RATE_FREQUENCY = 2000; //target Velocity
		double const PROPORTIONAL_GAIN = 1.0; //Proportional multiplier
		double const MAX_HZ = 2600.0; // max Hz

		double pi = 3.14159265359;

		double delta = 0;
		double PreAngle = 0;
		double rotation = 0;

		double BSpeed[4];	//Base Speeds
		double FSpeed[4];	//final Speeds
		double maxMagnitude = 0;

		double targetSpeed = 0;
		double currentSpeed = 0;
		double error = 0;
		double propOut = 0;
		double PIOut = 0;
		bool useEnc = true;

		double EncVal[4];
		double Angle = 0;
	};
}

#endif
