/*
 * autoManager.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: tv4958
 */

#include "WPILib.h"
#include "autoManager.hpp"
#include "inputManager.hpp"
#include "driveManager.hpp"
#include "cmath"
#include "cstdbool"
#include "cstdlib"
//#include "CanTalon.h"
#include "AHRS.h"

FRC::autoManager::autoManager(): //Declare Object Ports

	Auto(3),
	driveManager()
{

}

//Get the average distance of the encoders
double FRC::autoManager::getEncDistance()
{
	double leftFront = -((driveManager.leftFrontM.GetEncPosition()/3024)* 2.0943951024);
	double leftBack = -((driveManager.leftBackM.GetEncPosition()/3024)* 2.0943951024);
	double rightFront = ((driveManager.rightFrontM.GetEncPosition()/3024)* 2.0943951024);
	double rightBack = ((driveManager.rightBackM.GetEncPosition()/3024)* 2.0943951024);

	double distance = (leftFront + leftBack + rightFront + rightBack)/4;

	return distance;
}

//Drive for a certain amount of distance
void FRC::autoManager::driveDistance(double distance, double angle)
{
	if(distance > getEncDistance())
	{
		driveManager.mecanumDrive(0, -.3, 0, false);
		//driveManager.straightDrive(angle, 0, .5);
	}
	else
	{
		driveManager.mecanumDrive(0, 0, 0, false);
		//driveManager.straightDrive(angle, 0, 0);
	}
}

//Rotate to specified target angle in specified direction at specified speed
void FRC::autoManager::rotate(double target, double speed, int direction)
{
	if(driveManager.getAngle() != target)
	{
		driveManager.mecanumDrive(0, 0, speed * direction, true);
	}
	else
	{
		driveManager.mecanumDrive(0, 0, 0, false);
	}
}

//Center the robot with the reflective tape
void FRC::autoManager::centerWithTape(double angle, int pixelThreshold, double distFromCenter, double targetAng)
{
	double speed = 0;

	if (distFromCenter > pixelThreshold)
	{
		speed = distFromCenter * .005;
		if (speed > .3) {
			speed = .3;
		}
		//driveManager.mecanumDrive(-.3, 0, 0, true);
		driveManager.straightDrive(targetAng, 0, -.25);
	}
	else if (distFromCenter < -pixelThreshold)
	{
		speed = distFromCenter * .005;
		if (speed < -.3) {
			speed = -.3;
		}
		//driveManager.mecanumDrive(.3, 0, 0, true);
		driveManager.straightDrive(targetAng, 0, .25);
	}
}
