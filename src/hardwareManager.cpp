#include "WPILib.h"
#include "hardwareManager.hpp"

FRC::hardwareManager::hardwareManager():

	driveManager(),
	lidarManager()

{

}

void FRC::hardwareManager::hardwareStatus()
{
	//Check NavX board
	curNavX = driveManager.getAngle();
	if(curNavX > preNavX + .1 || curNavX < preNavX - .1)
	{
		NavXStatus = true;
	}
	else
	{
		NavXStatus = false;
	}
	preNavX = curNavX;

	//Check Lidar Status
	curLidar = lidarManager.getLidDistance();
	if(curLidar < 0)
	{
		lidarStatus = false;
	}
	else
	{
		lidarStatus = true;
	}

	//Check Left Front Encoder
	curLFEnc = driveManager.EncoderFreq[0];
	if((curLFEnc > preLFEnc + 5 || curLFEnc < preLFEnc - 5) && driveManager.speeds[0] > .1)
	{
		LFEncStatus = true;
	}
	else
	{
		LFEncStatus = false;
	}
	preLFEnc = curLFEnc;

	//Check Left Front Encoder
	curLFEnc = driveManager.EncoderFreq[1];
	if((curLBEnc > preLBEnc + 5 || curLBEnc < preLBEnc - 5) && driveManager.speeds[1] > .1)
	{
		LBEncStatus = true;
	}
	else
	{
		LBEncStatus = false;
	}
	preLBEnc = curLBEnc;

	//Check Right Front Encoder
	curRFEnc = driveManager.EncoderFreq[2];
	if((curRFEnc > preRFEnc + 5 || curRFEnc < preRFEnc - 5) && driveManager.speeds[2] > .1)
	{
		RFEncStatus = true;
	}
	else
	{
		RFEncStatus = false;
	}
	preRFEnc = curRFEnc;

	//Check Right Back Encoder
	curLBEnc = driveManager.EncoderFreq[3];
	if((curRBEnc > preRBEnc + 5 || curRBEnc < preRBEnc - 5) && driveManager.speeds[3] > .1)
	{
		RBEncStatus = true;
	}
	else
	{
		RBEncStatus = false;
	}
	preRBEnc = curRBEnc;
}

//Display values on smartDashboard
void FRC::hardwareManager::displayValues()
{
	//Nav board and Lidar Statuses
	SmartDashboard::PutBoolean("NavX Status", NavXStatus);
	SmartDashboard::PutBoolean("Lidar Status", lidarStatus);

	//Encode Statuses
	SmartDashboard::PutBoolean("Left Front Encoder Status", LFEncStatus);
	SmartDashboard::PutBoolean("Left Back Encoder Status", LBEncStatus);
	SmartDashboard::PutBoolean("Right Front Encoder Status", RFEncStatus);
	SmartDashboard::PutBoolean("Right Back Encoder Status", RBEncStatus);
}
