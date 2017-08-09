/*
 * BlitzLogger.hpp
 *
 *  Created on: Aug 5, 2017
 *      Author: Sam
 */

#ifndef SRC_BLITZLOGGER_HPP_
#define SRC_BLITZLOGGER_HPP_

#include "WPILib.h"
#include <iostream>
#include <fstream>

namespace FRC
{
	class BlitzLogger
	{
	public :
		BlitzLogger();

		//Variables
		std::ofstream logfile;
		bool writeDebugMessage = false;

		//Non-logging functions
		void init(bool debugMode);
		void close();

		//Logging Functions
		void info(char currentStage[], char message[]);
		void debug(char currentStage[], char message[]);
		void warning(char currentStage[], char message[]);
		void error(char currentStage[], char message[]);
		void trace(char currentStage[], char message[]);

		enum stage
		{
			Auto = "Auto",
			TeleOp = "TeleOp"
		};
	};
}




#endif /* SRC_BLITZLOGGER_HPP_ */
