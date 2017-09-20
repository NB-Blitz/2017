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
#include "AHRS.h"

FRC::autoManager::autoManager(): //Declare Object Ports
	Auto(3),
	driveMan(),
	lidarMan(),
	manipulator()
{

}

//Use Center Autonomous Function
void FRC::autoManager::centerAuto()
{
	if(autoStep == 1)
	{
		if(manipulator.pot.GetValue() < 2000){
			manipulator.GearOut(1);
		}
		else
		{
			manipulator.gear.Set(0);
			autoStep = 2;
		}
	}
	if(autoStep == 2)
	{
		if(lidarMan.lidarDistance > 0.4)
		{
			driveMan.mecanumDrive(0, .4, 0);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 3;
		}
	}
	if(autoStep == 3)
	{
		manipulator.GearOut(1);
	}
}

//Use Right Autonomous Function
void FRC::autoManager::rightAuto()
{
	distFromCenter = SmartDashboard::GetNumber("CENTER", 240) - 240;

	if(autoStep == 1)
	{
		if(encDistance < ENC_TARGET)
		{
			driveMan.mecanumDrive(0, .4, 0);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 2;
		}
	}
	if(autoStep == 2)
	{
		if(driveMan.Angle < 300)
		{
			driveMan.mecanumDrive(0, 0, .3);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
		}
	}
	if(autoStep == 3)
	{
		timer = timer + .05;
		if(timer >= 1)
		{
			if ((distFromCenter > PIXEL_THRESHOLD || distFromCenter < -PIXEL_THRESHOLD) && timer >= 8)
			{
				driveMan.mecanumDrive(0, 0, 0);
				autoStep = 8;
			}
			if (distFromCenter > PIXEL_THRESHOLD || distFromCenter < -PIXEL_THRESHOLD)
			{
				centerWithTape(driveMan.Angle, PIXEL_THRESHOLD, distFromCenter, 300);
			}
			else
			{
				driveMan.mecanumDrive(0, 0, 0);
				autoStep = 4;
			}
		}
	}
	if(autoStep == 4)
	{
		if(manipulator.pot.GetValue() < 2000)
		{
			manipulator.GearOut(1);
		}
		else
		{
			manipulator.gear.Set(0);
			autoStep = 5;
		}
	}
	if(autoStep == 5)
	{
		if(lidarMan.lidarDistance > 0.4)
		{
			driveMan.mecanumDrive(0, .4, 0);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 6;
		}
	}
	if(autoStep == 6)
	{
		if(manipulator.pot.GetValue() < 3500)
		{
			manipulator.GearOut(1);
		}
		else
		{
			manipulator.gear.Set(0);
			autoStep = 7;
		}
	}
	if(autoStep == 7)
	{
		if(reverseCounter < REVERSE_TARGET)
		{
			driveMan.mecanumDrive(0, 0.3, 0);
			reverseCounter = reverseCounter + 1;
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 8;
		}
	}
	if(autoStep == 8){
		if(driveMan.Angle < 360)
		{
			driveMan.mecanumDrive(0, 0, -.3);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
		}
	}
	if(autoStep == 9)
	{
		finalDriveCounter = finalDriveCounter + 1;

		if(finalDriveCounter < FINAL_TARGET)
		{
			driveMan.mecanumDrive(0, .4, 0);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 10;
		}
	}
	if(autoStep == 10){
		driveMan.mecanumDrive(0, 0, 0);
	}
}

//Use Left Autonomous Function
void FRC::autoManager::leftAuto()
{
	distFromCenter = SmartDashboard::GetNumber("CENTER", 240) - 240;

	if(autoStep == 1)
	{
		if(encDistance < ENC_TARGET)
		{
			driveMan.mecanumDrive(0, .4, 0);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 2;
		}
	}
	if(autoStep == 2)
	{
		if(driveMan.Angle < 60)
		{
			driveMan.mecanumDrive(0, 0, -.3);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
		}
	}
	if(autoStep == 3)
	{
		timer = timer + .05;
		if(timer >= 1)
		{
			if ((distFromCenter > PIXEL_THRESHOLD || distFromCenter < -PIXEL_THRESHOLD) && timer >= 8)
			{
				driveMan.mecanumDrive(0, 0, 0);
				autoStep = 8;
			}
			if (distFromCenter > PIXEL_THRESHOLD || distFromCenter < -PIXEL_THRESHOLD)
			{
				centerWithTape(driveMan.Angle, PIXEL_THRESHOLD, distFromCenter, 300);
			}
			else
			{
				driveMan.mecanumDrive(0, 0, 0);
				autoStep = 4;
			}
		}
	}
	if(autoStep == 4){
		if(manipulator.pot.GetValue() < 2000)
		{
			manipulator.GearOut(1);
		}
		else
		{
			manipulator.gear.Set(0);
			autoStep = 5;
		}
	}
	if(autoStep == 5)
	{
		if(lidarMan.lidarDistance > 0.4)
		{
			driveMan.mecanumDrive(0, .4, 0);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 6;
		}
	}
	if(autoStep == 6)
	{
		if(manipulator.pot.GetValue() < 3500)
		{
			manipulator.GearOut(1);
		}
		else
		{
			manipulator.gear.Set(0);
			autoStep = 7;
		}
	}
	if(autoStep == 7)
	{
		if(reverseCounter < REVERSE_TARGET)
		{
			driveMan.mecanumDrive(0, 0.3, 0);
			reverseCounter = reverseCounter + 1;
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 8;
		}
	}
	if(autoStep == 8)
	{
		if(driveMan.Angle < 360)
		{
			driveMan.mecanumDrive(0, 0, .3);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
		}
	}
	if(autoStep == 9)
	{
		finalDriveCounter = finalDriveCounter + 1;

		if(finalDriveCounter < FINAL_TARGET)
		{
			driveMan.mecanumDrive(0, .4, 0);
		}
		else
		{
			driveMan.mecanumDrive(0, 0, 0);
			autoStep = 10;
		}
	}
	if(autoStep == 10)
	{
		driveMan.mecanumDrive(0, 0, 0);
	}

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
		driveMan.resetEnc();
	}
	else
	{
		leftFront = ((driveMan.leftFrontM.GetEncPosition()/3024)* 2.0943951024);
		leftBack = ((driveMan.leftBackM.GetEncPosition()/3024)* 2.0943951024);
		rightFront = -((driveMan.rightFrontM.GetEncPosition()/3024)* 2.0943951024);
		rightBack = -((driveMan.rightBackM.GetEncPosition()/3024)* 2.0943951024);
	}


	double distance = (leftFront + leftBack + rightFront + rightBack)/4;

	return distance;
}

//Drive for a certain amount of distance
void FRC::autoManager::driveDistance(double distance, double angle)
{
	if(distance > getEncDistance(false))
	{
		driveMan.mecanumDrive(0, -.3, 0);
	}
	else
	{
		driveMan.mecanumDrive(0, 0, 0);
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
		driveMan.straightDrive(0, -.5);
	}
	else if (distFromCenter < -pixelThreshold)
	{
		speed = distFromCenter * .005;
		if (speed < -.3) {
			speed = -.3;
		}
		driveMan.straightDrive(0, .5);
	}
}
