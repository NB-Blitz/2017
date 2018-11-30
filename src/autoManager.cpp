/*
 * autoManager.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: tv4958
 */

#include "WPILib.h"
#include "autoManager.hpp"

FRC::autoManager::autoManager(): //Declare Object Ports

	Auto(3),
	driveManager()
{

}


//Use Center Autonomous Function
void FRC::autoManager::centerAuto()
{

}

//Use Right Autonomous Function
void FRC::autoManager::rightAuto()
{

}

//Use Left Autonomous Function
void FRC::autoManager::leftAuto()
{

}

//Get the average distance of the encoders
double FRC::autoManager::getEncDistance(bool clear)
{
	double leftFront = 0;
	double leftBack = 0;
	double rightFront = 0;
	double rightBack = 0;

	if (clear == true)
	{
		driveManager.resetEnc();
	}
	else
	{
		leftFront = ((driveManager.leftFrontM.GetSelectedSensorPosition()/3024)* 2.0943951024);
		leftBack = ((driveManager.leftBackM.GetSelectedSensorPosition()/3024)* 2.0943951024);
		rightFront = -((driveManager.rightFrontM.GetSelectedSensorPosition()/3024)* 2.0943951024);
		rightBack = -((driveManager.rightBackM.GetSelectedSensorPosition()/3024)* 2.0943951024);
	}


	double distance = (leftFront + leftBack + rightFront + rightBack)/4;

	return distance;
}

//Drive for a certain amount of distance
void FRC::autoManager::driveDistance(double distance, double angle)
{
	if(distance > getEncDistance(false))
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
		//driveManager.mecanumDrive(-.35, 0, 0, true);
		driveManager.straightDrive(targetAng, 0, -.5);
	}
	else if (distFromCenter < -pixelThreshold)
	{
		speed = distFromCenter * .005;
		if (speed < -.3) {
			speed = -.3;
		}
		//driveManager.mecanumDrive(.35, 0, 0, true);
		driveManager.straightDrive(targetAng, 0, .5);
	}
}
