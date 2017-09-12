#include "WPILib.h"
#include "driveManager.hpp"
#include "inputManager.hpp"
#include "autoManager.hpp"
#include "CanTalon.h"
#include "AHRS.h"

FRC::driveManager::driveManager(): //Declare Object Ports

leftFrontM(1),	//array Pos 0
leftBackM(3),	//array Pos 1
rightFrontM(2),	//array Pos 2
rightBackM(4),	//array Pos 3
ahrs {SPI::Port::kMXP}

{

}

void FRC::driveManager::fieldControl(double x, double y, double rotate)
{
	double r = sqrt(pow(x, 2) + pow(y, 2));

	if(inputManager.joyStick.GetDirectionDegrees() < 0)
	{
		delta = 360 + inputManager.joyStick.GetDirectionDegrees();
	}
	else
	{
		delta = inputManager.joyStick.GetDirectionDegrees();
	}

	delta -= Angle;

	x = r * cos(delta * (pi/180));
	y= r * sin(delta * (pi/180));

	mecanumDrive(-y, -x, rotate);
}

void FRC::driveManager::straightDrive(double x, double y)
{
	delta = PreAngle - Angle;
	PreAngle = Angle;

	if(fabs(delta) > 180 && delta > 0)
	{
		delta = -(360 - fabs(delta));
	}
	else if(fabs(delta) > 180 && delta < 0)
	{
		delta = 360 - delta;
	}

	rotation = delta * 0.02;

	if(fabs(y) > fabs(x))
	{
		mecanumDrive(y, 0, -rotation);
	}
	else
	{
		mecanumDrive(0, x, -rotation);
	}
}

void FRC::driveManager::mecanumDrive(double x, double y, double rotate)
{
	//mecanum equation
	BSpeed[0] = x + y - rotate;
	BSpeed[1] = -(-x + y + rotate);
	BSpeed[2] = -x + y - rotate;
	BSpeed[3] = -(x + y + rotate);

	for (int i = 1; i < 4; i++)
	{
		double temp = std::fabs(BSpeed[i]);
		if (maxMagnitude < temp)
		{
			maxMagnitude = temp;
		}
	}
	if (maxMagnitude > 1.0)
	{
		for (int i = 0; i < 4; i++)
		{
			BSpeed[i] = BSpeed[i] / maxMagnitude;
		}
	}

	FSpeed[0] = PICorrection(BSpeed[0], EncVal[0]);
	FSpeed[1] = PICorrection(BSpeed[1], EncVal[1]);
	FSpeed[2] = PICorrection(BSpeed[2], EncVal[2]);
	FSpeed[3] = PICorrection(BSpeed[3], EncVal[3]);

	//Output to motor
	leftFrontM.Set(FSpeed[0]);
	leftBackM.Set(FSpeed[1]);
	rightFrontM.Set(FSpeed[2]);
	rightBackM.Set(FSpeed[3]);
}

double FRC::driveManager::PICorrection(double preValue, double Enc)
{
	if(useEnc)
	{
		targetSpeed = preValue * (RATE_FREQUENCY/MAX_HZ);
		currentSpeed = Enc/RATE_FREQUENCY;
		error = targetSpeed - currentSpeed;
		propOut = error * PROPORTIONAL_GAIN;
		PIOut = targetSpeed + propOut;
		return PIOut;
	}
	else
	{
		return preValue;
	}
}

void FRC::driveManager::resetEnc(){
	leftFrontM.SetEncPosition(0);
	leftBackM.SetEncPosition(0);
	rightFrontM.SetEncPosition(0);
	rightBackM.SetEncPosition(0);
}

void FRC::driveManager::getData()
{
	useEnc = autoManager.Auto.GetRawButton(5);
	Angle = ahrs.GetFusedHeading();
	EncVal[0] = leftFrontM.GetEncVel();
	EncVal[1] = leftBackM.GetEncVel();
	EncVal[2] = rightFrontM.GetEncVel();
	EncVal[3] = rightBackM.GetEncVel();
}
