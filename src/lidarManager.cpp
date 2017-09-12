/*
 * Lidar_Manager_V2.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: Sam
 */
#include "WPILib.h"
#include "lidarManager.hpp"

FRC::lidarManager::lidarManager(): //Declare Object Ports

Lidar() {}

//Grabs Distance values form Lidar then converts from centimeters to meters
double FRC::lidarManager::getLidDistance()
{
	double distCent = 0;

	Lydar->WriteBulk(LIDAR_ADDR, 2);
	Lydar->WriteBulk(&LIDAR_ADDR[2], 1);
	if((int)busyRead & 0x01)
	{
		distCent = -100;
	}
	else
	{
		Lydar->WriteBulk(&LIDAR_ADDR[3], 1);
		Lydar->ReadOnly(2, readData);
		distCent = ((readData[0] * 265) + readData[1]);
	}


	return (distCent / 100); //Converts centimeters into meters

	/* OLD LIDAR CODE
	Lydar->WriteBulk(LIDAR_ADDR, 2);
	Lydar->WriteBulk(&LIDAR_ADDR[2], 1);
	do
	{
		Lydar->ReadOnly(1, busyRead);
		Wait(0.001);
	}
	while ((int)busyRead & 0x01);
	Lydar->WriteBulk(&LIDAR_ADDR[3], 1);
	Lydar->ReadOnly(2, readData);
	double distCent = ((readData[0] * 265) + readData[1]);

	return (distCent / 100); //Converts centimeters into meters
	*/

}

void FRC::lidarManager::getData()
{
	lidarDistance = getLidDistance();
}

//Returns Limit for Speed Input to Motor
double FRC::lidarManager::ProportionalSlowAntiDavid(double startLimit, double endLimit)
{
	double range = startLimit - endLimit;
	double output;
	double distance = getLidDistance();
	double processVariable = distance - endLimit;
	if (distance <= startLimit && distance >= endLimit)
	{
		output = (processVariable / range);
	}
	else if(processVariable > startLimit)
	{
		output = 1;
	}
	else
	{
		output = 0;
	}

	return output;
}
