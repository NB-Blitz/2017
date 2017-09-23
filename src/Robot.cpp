#include "WPILib.h"
#include "inputManager.hpp"
#include "autoManager.hpp"
#include "driveManager.hpp"
#include "manipulator.hpp"
#include "lidarManager.hpp"
#include "hardwareManager.hpp"

class Robot: public SampleRobot
{
	//Object Declarations
	FRC::inputManager inputMan;
	FRC::autoManager autoMan;
	FRC::driveManager driveMan;
	FRC::manipulator manipulator;
	FRC::lidarManager lidarMan;
	FRC::hardwareManager hardwareMan;

public:
	Robot() :
		//Declare Object Ports
		inputMan(),
		autoMan(),
		driveMan(),
		manipulator(),
		lidarMan(),
		hardwareMan()
		{

		}

	/*-----------------------------------------------------------------------------------------------*/
	/*-----------------------------------------AUTONOMOUS--------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------*/
	void Autonomous()
	{

		driveMan.resetEnc();
		driveMan.ahrs.Reset();

		while (IsAutonomous() && IsEnabled())
		{
			//Get Sensor Values
			lidarMan.getData();
			driveMan.getData();
			driveMan.useEnc = autoMan.Auto.GetRawButton(5);

			// Displays
			SmartDashboard::PutNumber("Lidar", lidarMan.lidarDistance);
			SmartDashboard::PutNumber("nav Angle", driveMan.Angle);

			if(autoMan.Auto.GetRawButton(1))
			{
				autoMan.leftAuto();
			}
			else if(autoMan.Auto.GetRawButton(2))
			{
				autoMan.centerAuto();
			}
			else if(autoMan.Auto.GetRawButton(3))
			{
				autoMan.rightAuto();
			}

			Wait(0.05); //
		}
	}

	/*-----------------------------------------------------------------------------------------------
	 * TELE-OP
	 *----------------------------------------------------------------------------------------------*/
	void OperatorControl()
	{

		driveMan.mecanumDrive(0, 0, 0);
		driveMan.resetEnc();

		while (IsOperatorControl() && IsEnabled())
		{
			//Drive type selection
			if(inputMan.joyStick.GetRawButton(1))
			{
				driveMan.straightDrive(inputMan.joyX, inputMan.joyY);
			}
			else if(inputMan.joyStick.GetRawButton(2))
			{
				driveMan.fieldControl(inputMan.joyX, inputMan.joyY, inputMan.joyZ);
			}
			else if(inputMan.joyStick.GetRawButton(3))
			{
				driveMan.straightDrive(0, .3);
			}
			else if(inputMan.joyStick.GetRawButton(4))
			{
				driveMan.straightDrive(0, -.3);
			}
			else if(inputMan.joyStick.GetRawButton(11))
			{
				driveMan.resetEnc();
			}
			else
			{
				driveMan.mecanumDrive(inputMan.joyX, inputMan.joyY, inputMan.joyZ * .7);
			}


			//Reset AHRS
			if(inputMan.joyStick.GetRawButton(8))
			{
				driveMan.ahrs.Reset();
			}


			//Gear manipulator
			if(inputMan.xBox.GetRawAxis(5) < -.1)
			{
				manipulator.GearOut(-inputMan.xBox.GetRawAxis(5));
			}
			else if(inputMan.xBox.GetRawAxis(5) > .1)
			{
				manipulator.GearReset(-inputMan.xBox.GetRawAxis(5));
			}
			else
			{
				manipulator.gear.Set(0);
			}

			//Start the climbing function
			manipulator.climb();

			//WPT
			Wait(0.015);
		}
	}

	/*-----------------------------------------------------------------------------------------------
	 * TEST
	 *----------------------------------------------------------------------------------------------*/
	void Test()
	{
		hardwareMan.LFEncStatus = false;
		hardwareMan.LBEncStatus = false;
		hardwareMan.RFEncStatus = false;
		hardwareMan.RBEncStatus = false;

		driveMan.resetEnc();

		while (IsTest() && IsEnabled())
		{

			//Button 1 - Left Fronts
			if (autoMan.Auto.GetRawButton(1))
			{
				driveMan.leftFrontM.Set(.3);

				if(driveMan.leftFrontM.GetEncVel() != 0)
				{
					hardwareMan.LFEncStatus = true;
				}
			}
			else
			{
				driveMan.leftFrontM.Set(0);
				hardwareMan.LFEncStatus = false;
			}

			//Button 2 - Left Back
			if (autoMan.Auto.GetRawButton(2))
			{
				driveMan.leftBackM.Set(.3);

				if(driveMan.leftBackM.GetEncVel() != 0)
				{
					hardwareMan.LBEncStatus = true;
				}
			}
			else
			{
				driveMan.leftBackM.Set(0);
				hardwareMan.LBEncStatus = false;
			}

			//Button 3 - Right Front
			if (autoMan.Auto.GetRawButton(3))
			{
				driveMan.rightFrontM.Set(.3);

				if(driveMan.rightFrontM.GetEncVel() != 0)
				{
					hardwareMan.RFEncStatus = true;
				}
			}
			else
			{
				driveMan.rightFrontM.Set(0);
				hardwareMan.RFEncStatus = false;
			}

			//Button 4 - Right Back
			if (autoMan.Auto.GetRawButton(4))
			{
				driveMan.rightBackM.Set(.3);

				if(driveMan.rightBackM.GetEncVel() != 0)
				{
					hardwareMan.RBEncStatus = true;
				}
			}
			else
			{
				driveMan.rightBackM.Set(0);
				hardwareMan.RBEncStatus = false;
			}

			//Button 5 - Manipulator
			if (autoMan.Auto.GetRawButton(5))
			{
				manipulator.GearOut(.3);
			}
			else
			{
				manipulator.GearOut(0);
			}
			hardwareMan.displayValues();

			Wait(0.005);
		}
	}
};

START_ROBOT_CLASS(Robot)
