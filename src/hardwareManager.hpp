/*
 * hardwareMaager.hpp
 *
 *  Created on: Mar 28, 2017
 *      Author: Theo
 */

#ifndef SRC_HARDWAREMANAGER_HPP_
#define SRC_HARDWAREMANAGER_HPP_

#include "driveManager.hpp"
#include "lidarManager.hpp"

namespace FRC
{
	class hardwareManager
	{
		public:
			hardwareManager();

			//object declarations
			FRC::driveManager driveManager;
			FRC::lidarManager lidarManager;

			//Functions
			void hardwareStatus();
			void displayValues();

			//status variables
			bool lidarStatus = true;
			bool NavXStatus = true;
			bool LFEncStatus = true;
			bool LBEncStatus = true;
			bool RFEncStatus = true;
			bool RBEncStatus = true;

		private:

			//previous state variables
			double preNavX = 0;
			double preLFEnc = 0;
			double preLBEnc = 0;
			double preRFEnc = 0;
			double preRBEnc = 0;

			//Current state variables
			double curLidar = 0;
			double curNavX = 0;
			double curLFEnc = 0;
			double curLBEnc = 0;
			double curRFEnc = 0;
			double curRBEnc = 0;
	};
}

#endif /* SRC_HARDWAREMANAGER_HPP_ */
