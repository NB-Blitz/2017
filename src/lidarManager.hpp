/*
 * Lidar_Manager_V2.hpp
 *
 *  Created on: Feb 20, 2017
 *      Author: Sam
 */

#ifndef SRC_LIDARMANAGER_HPP_
#define SRC_LIDARMANAGER_HPP_

#include "WPILib.h"
#include "CANTalon.h"
#include "math.h"
#include "inputManager.hpp"
#include "driveManager.hpp"

namespace FRC
{
	class lidarManager
	{
		public:
			lidarManager();

			//Object Declarations
			FRC::lidarManager *Lidar;
			I2C *Lydar = new I2C(I2C::kOnboard, 0x62);
			uint8_t LIDAR_ADDR[4] {0x00, 0x04, 0x01, 0x8f};
			uint8_t busyRead[1];
			uint8_t readData[2];

			//Function Declarations
			double getLidDistance();
			double ProportionalSlowAntiDavid(double startLimit, double endLimit);
	};
}
#endif /* SRC_LIDARMANAGER_HPP_ */
