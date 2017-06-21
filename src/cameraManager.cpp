/*
 * cameraManager.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: Robotics
 */

#include "WPILib.h"
#include "cameraManager.hpp"

//Receive CENTER (of the 2 tapes, in pixels) from Network Table and convert to inches away from center of screen
double FRC::cameraManager::getDistFromCenter()
{
	return SmartDashboard::GetNumber("CENTER", -1) - 240;
}

/* Change this file too */