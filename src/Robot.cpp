#include "WPILib.h"
#include "inputManager.hpp"
#include "driveManager.hpp"
#include "manipulator.hpp"
#include "autoManager.hpp"
#include "lidarManager.hpp"
#include "hardwareManager.hpp"

class Robot: public SampleRobot
{
	//Object Declarations
	//Commit Testing
	FRC::inputManager inputMan;
	FRC::driveManager driveMan;
	FRC::manipulator manipulator;
	FRC::autoManager autoMan;
	FRC::lidarManager lidarMan;
	FRC::hardwareManager hardwareMan;
	Timer *step3Timer;
	//Relay spike;

public:
	Robot() : //Declare Object Ports
		inputMan(),
		driveMan(),
		manipulator(),
		autoMan(),
		lidarMan(),
		hardwareMan()
		//spike(0)
{
		step3Timer = new Timer();
}
	/*-----------------------------------------------------------------------------------------------
	 * AUTONOMOUS
	 *----------------------------------------------------------------------------------------------*/
	void Autonomous(){
		visionInit();

		int step = 1;

		// ----------- Step 1 Vars -----------
		double autoJoystick = -0.25;
		double targetDistance = 2.25;
		double encDistance = 0;

		// ----------- Step 2 Vars -----------
		bool angleStatus = false;
		double prevAngle = -1;
		double Angle = 0;
		double targetAngle = 360;
		int direction = 1;
		double thresholdAngle = 10.0;
		double rotateSpeed = 0.25;

		// ----------- Step 4 Vars -----------
		double pixelThreshold = 8;

		// ----------- Step 5 Vars -----------
		bool lidarStatus = false;
		double lidarDistance = 0;
		double startLimit = 1;
		double endLimit = 0.4;
		double controlLimit = 0;
		double lidarMin = 1000000;

		// ----------- Step 6 Vars -----------
		int gearTarget = 15;
		int gearCounter = 0;
		int gearCounter2nd = 0;

		// ----------- Step 7 Vars -----------
		int reverseCounter = 0;
		int reverseTarget = 30;

		// ----------- Step 8 Vars -----------
		double targetReturnAngle = 360.0;

		// ----------- Step 9 Vars -----------
		int finalDriveCounter = 0;
		int finalDriveCounterTarget = 350;

		driveMan.resetEnc();
		driveMan.ahrs.Reset();
		step3Timer->Reset();

		while (IsAutonomous() && IsEnabled())
		{
			SmartDashboard::PutNumber("AutoEnum", step);

			//LEDs
		//	spike.Set(Relay::kForward);

			//Get Sensor Values
			prevAngle = Angle;
			Angle = driveMan.getAngle();
			lidarDistance = lidarMan.getLidDistance();
			encDistance = autoMan.getEncDistance();

			//Angle Status
			if(Angle != prevAngle)
			{
				angleStatus = true;
			}
			else
			{
				angleStatus = false;
			}

			//Lidar Status
			if(lidarDistance > 0.0)
			{
				lidarStatus = true;
			}
			else
			{
				lidarStatus = false;
			}

			SmartDashboard::PutNumber("Lidar Distance", lidarMan.getLidDistance());
			SmartDashboard::PutBoolean("Lidar Status", lidarStatus);
			SmartDashboard::PutBoolean("NavBoard Status", angleStatus);
			//SmartDashboard::PutNumber("Left Front Enc Vel", driveMan.EncoderFreq[0]);

			if(autoMan.Auto.GetRawButton(2)){
				// ----------------------- MIDDLE SPRING AUTO --------------------------
				// ----------- STEP 1 -----------
				// Put up the manipulator partially
				if (step == 1)
				{
					if(gearCounter < gearTarget)
					{
						manipulator.GearOut(0.7);
						gearCounter = gearCounter + 1;
					}
					else
					{
						manipulator.GearOut(0.0);
						step = 2;
					}
				}

				// ----------- STEP 2 -----------
				// Drive into the spring and stop
				if(step == 2)
				{
					if(lidarDistance > 0.4)
					{
						driveMan.mecanumDrive(0, autoJoystick, 0, false);
					}
					else
					{
						// Stop moving
						driveMan.mecanumDrive(0, 0, 0, true);

						// Do we need to check again?
						if(lidarDistance <= 0.05)
						{
							step = 2;
						}
						else
						{
							step = 3;
							gearCounter2nd = 0;
						}
					}
				}

				// ----------- STEP 3 -----------
				// Place the gear, yo
				if(step == 3)
				{
					driveMan.mecanumDrive(0, 0, 0, false);

					if(gearCounter2nd < gearTarget)
					{
						manipulator.GearOut(0.7);
						gearCounter2nd = gearCounter2nd + 1;
					}
					else
					{
						manipulator.GearOut(0);
						step = 10;
					}
				}
			}

			else
			{
				// ----------------------- LEFT OR RIGHT SPRING AUTO --------------------------
				if(autoMan.Auto.GetRawButton(3)) //RIGHT SPRING
				{
					targetAngle = 300.0;
					direction = 1; //Rotate left
				}
				else if (autoMan.Auto.GetRawButton(1)) //LEFT SPRING
				{
					targetAngle = 60.0;
					direction = -1; //Rotate right
				}

				// ----------- STEP 1 -----------
				// Drive forward from start
				if(step == 1)
				{
					if(encDistance < targetDistance)
					{
						driveMan.mecanumDrive(0, autoJoystick, 0, true);
					}
					else if(encDistance >= targetDistance)
					{
						driveMan.mecanumDrive(0, 0, 0, false);
						step = 2;
					}
				}

				// ----------- STEP 2 -----------
				// Rotate to the correct angle
				if(step == 2)
				{
					if(Angle > targetAngle + thresholdAngle || Angle < targetAngle - thresholdAngle)
					{
						autoMan.rotate(targetAngle, rotateSpeed, direction);
					}
					else
					{
						driveMan.mecanumDrive(0, 0, 0, false);
						step = 3;
						gearCounter = 0;
					}
				}
				SmartDashboard::PutNumber("nav Angle", driveMan.getAngle());
				// ----------- STEP 3 -----------
				// Put manipulator up partially
				if (step == 3)
				{
					if(gearCounter < gearTarget)
					{
						manipulator.GearOut(0.7);
						gearCounter = gearCounter + 1;
					}
					else
					{
						manipulator.gear.Set(0);
						if (autoMan.Auto.GetRawButton(4)) //If 4 is on
						{
							step = 4; //Use the camera code
						}
						else //If 4 is off
						{
							step = 5; //Don't use the camera code
						}
					}
				}

				// ----------- STEP 4 -----------
				// Center robot with reflective tape
				double distFromCenter = SmartDashboard::GetNumber("CENTER", -1) - 240;

				if(step == 4)
				{
					step3Timer->Start();
					double time = step3Timer->Get();

					if ((distFromCenter > pixelThreshold || distFromCenter < -pixelThreshold) && time >= 8)
					{
						driveMan.mecanumDrive(0, 0, 0, false);
						step = 8;
					}
					else
					if (distFromCenter> pixelThreshold || distFromCenter < -pixelThreshold)
					{
						autoMan.centerWithTape(Angle, pixelThreshold, distFromCenter, targetAngle);
					}
					else
					{
						driveMan.mecanumDrive(0, 0, 0, false);
						step = 5;
					}
				}
				SmartDashboard::PutNumber("dist from Center", distFromCenter);
				SmartDashboard::PutNumber("Lidar Min", lidarMin);
				// ----------- STEP 5 -----------
				// Drive into the spring and stop
				if(step == 5)
				{
					if(lidarMin > lidarDistance && lidarDistance > 0){
						lidarMin = lidarDistance;
					}

					if(lidarDistance > endLimit)
					{
						driveMan.mecanumDrive(0, autoJoystick, 0, true);
					}
					else
					{
						// Stop moving
						driveMan.mecanumDrive(0, 0, 0, false);

						// Do we need to check again?
						if(lidarDistance <= 0.05)
						{
							step = 5;
						}
						else
						{
							step = 6;
							gearCounter2nd = 0;
						}
					}
				}

				// ----------- STEP 6 -----------
				// Place the gear, yo
				if(step == 6)
				{
					driveMan.mecanumDrive(0, 0, 0, false);

					if(gearCounter2nd < gearTarget)
					{
						manipulator.GearOut(0.7);
						gearCounter2nd = gearCounter2nd + 1;
					}
					else
					{
						manipulator.GearOut(0);
						step = 7;
					}
				}

				// ----------- STEP 7 -----------
				// Get out and position for teleop
				if(step == 7)
				{
					if(reverseCounter < reverseTarget)
					{
						driveMan.mecanumDrive(0, 0.3, 0, true);
						reverseCounter = reverseCounter + 1;
					}
					else
					{
						driveMan.mecanumDrive(0, 0, 0, false);
						step = 8;
					}
				}

				// ----------- STEP 8 -----------
				// Return to forward angle
				int directionReturn = -direction; // Left/Right

				if(step == 8)
				{
					if(Angle > targetReturnAngle + thresholdAngle || Angle < targetReturnAngle - thresholdAngle)
					{
						autoMan.rotate(targetReturnAngle, rotateSpeed, directionReturn);
					}
					else
					{
						driveMan.mecanumDrive(0, 0, 0, false);
						step = 9;
					}
				}

				// ----------- STEP 9 -----------
				// Drive forward past line
				if(step == 9)
				{
					finalDriveCounter = finalDriveCounter + 1;

					if(finalDriveCounter < finalDriveCounterTarget)
					{
						driveMan.mecanumDrive(0, autoJoystick, 0, true);
					}
					else
					{
						driveMan.mecanumDrive(0, 0, 0, false);
						step = 10;
					}
				}
			}

			// ----------- Wait -----------
			if(step == 10){
				driveMan.mecanumDrive(0, 0, 0, false);
			}

			Wait(0.015); //
		}
	}

	/*-----------------------------------------------------------------------------------------------
	 * TELE-OP
	 *----------------------------------------------------------------------------------------------*/
	void OperatorControl()
	{
		visionInit();

		bool isPressed = false;
		bool isPrePressed = false;
		double CurrAngle = 0;
		bool toggleOn = false;

		driveMan.mecanumDrive(0, 0, 0, false);
		driveMan.resetEnc();

		while (IsOperatorControl() && IsEnabled())
		{
			//LEDs
			//spike.Set(Relay::kForward);

			//Encoder Toggle
			toggleOn = autoMan.Auto.GetRawButton(5);
			isPressed = inputMan.JoyStick.GetRawButton(1);

			if(isPressed != isPrePressed && !isPrePressed)
			{
				CurrAngle = driveMan.getAngle();
				isPrePressed = true;
			}
			else if(isPressed != isPrePressed && !isPressed)
			{
				isPrePressed = false;
			}

			driveMan.ramp();

			if(inputMan.JoyStick.GetRawButton(8))
			{
				driveMan.ahrs.Reset();
			}
			else if(inputMan.JoyStick.GetRawButton(1))
			{
				driveMan.straightDrive(CurrAngle, driveMan.JoyX, driveMan.JoyY);
			}
			else if(inputMan.JoyStick.GetRawButton(2))
			{
				driveMan.FieldControl(driveMan.JoyX,driveMan.JoyY,driveMan.joyRotate);
			}
			else if(inputMan.JoyStick.GetRawButton(3))
			{
				driveMan.straightDrive(CurrAngle, 0, .3);
			}
			else if(inputMan.JoyStick.GetRawButton(4))
			{
				driveMan.straightDrive(CurrAngle, 0, -.3);
			}
			else if(inputMan.JoyStick.GetRawButton(7))
			{
				autoMan.driveDistance(2, CurrAngle);
			}
			else if(inputMan.JoyStick.GetRawButton(11))
			{
				driveMan.resetEnc();
			}
			else
			{
				CurrAngle = driveMan.getAngle();
				driveMan.mecanumDrive(driveMan.JoyY, driveMan.JoyX, driveMan.joyRotate, autoMan.Auto.GetRawButton(5));
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

			//Ball ejector
			if(inputMan.xBox.GetRawAxis(3) > .1)
			{
				manipulator.ballEject();
			}
			else
			{
				manipulator.ball.Set(0);
			}

			//Direction control
			if(inputMan.JoyStick.GetRawAxis(3) > 0)
			{
				driveMan.dir = -1;
			}
			else
			{
				driveMan.dir = 1;
			}

			//Start the climbing function
			manipulator.climb();

			//Check Hardware Status
			hardwareMan.hardwareStatus();

			//display statuses to smart dashboard
			hardwareMan.displayValues();
			Wait(0.005);
		}
	}

	/*-----------------------------------------------------------------------------------------------
	 * TEST
	 *----------------------------------------------------------------------------------------------*/
	void Test() {
		hardwareMan.LFEncStatus = false;
		hardwareMan.LBEncStatus = false;
		hardwareMan.RFEncStatus = false;
		hardwareMan.RBEncStatus = false;

		driveMan.resetEnc();

		while (IsTest() && IsEnabled())
		{
			visionInit();

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

			//Encoders
			/*
			SmartDashboard::PutNumber("Left Front Enc Pos", driveMan.leftFrontM.GetEncPosition());
			SmartDashboard::PutNumber("Left Back Enc Pos", driveMan.leftBackM.GetEncPosition());
			SmartDashboard::PutNumber("Right Front Enc Pos", driveMan.rightFrontM.GetEncPosition());
			SmartDashboard::PutNumber("Right Back Enc Pos", driveMan.rightBackM.GetEncPosition());

			SmartDashboard::PutNumber("Left Front Enc Vel", driveMan.EncoderFreq[0]);
			SmartDashboard::PutNumber("Left Back Enc Vel", driveMan.EncoderFreq[1]);
			SmartDashboard::PutNumber("Right Front Enc Vel", driveMan.EncoderFreq[2]);
			SmartDashboard::PutNumber("Right Back Enc Vel", driveMan.EncoderFreq[3]);

			SmartDashboard::PutNumber("Avg Encoder Dis (ft)", autoMan.getEncDistance());

			//Sensors
			SmartDashboard::PutNumber("Angle", driveMan.getAngle());
			SmartDashboard::PutNumber("Lidar Distance", lidarMan.getLidDistance());
			//SmartDashboard::PutNumber("Control Limit", lidarMan.ProportionalSlowAntiDavid(1, .4));

			//Manipulators
			SmartDashboard::PutNumber("Manipulator Pot", manipulator.pot.GetValue());
			SmartDashboard::PutNumber("Climber Motor 1", manipulator.PDP.GetCurrent(0));
			SmartDashboard::PutNumber("Climber Motor 2", manipulator.PDP.GetCurrent(1));
			/**/
			Wait(0.005);
		}
	}

	static void visionInit()
	{
		//cs::AxisCamera axisCamera = CameraServer::GetInstance()->AddAxisCamera("10.51.48.11");
		//cs::UsbCamera usbCamera = CameraServer::GetInstance()->StartAutomaticCapture();
		//axisCamera.SetResolution(480, 360);
		//usbCamera.SetResolution(480, 270);
	}
};

START_ROBOT_CLASS(Robot)
