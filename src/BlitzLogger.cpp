/*
 * BlitzLogger.cpp
 *
 *  Created on: Aug 5, 2017
 *      Author: Sam
 */
#include <BlitzLogger.hpp>
#include <iostream>
#include <chrono>
#include <ctime>

FRC::BlitzLogger::BlitzLogger()
{

}

void FRC::BlitzLogger::init(int logLevel)
{
	std::string dateTime;
	dateTime = "/home/lvuser/BlitzLogger/Steamworks/";
	dateTime.append(getTimeStamp());
	dateTime.append(".txt");
	logfile.open(dateTime);
}

std::string FRC::BlitzLogger::getTimeStamp()
{
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(p);
	std::string timeStamp = ctime(&t);
	return timeStamp;
}

void FRC::BlitzLogger::log(std::string currentStage, std::string level, std::string message)
{
	std::string timeStamp = FRC::BlitzLogger::getTimeStamp();
	logfile << "[" << &timeStamp << "]"; //writes timestamp to file
	logfile << " "; //Separating time stamp and message type
	logfile << "[" << &currentStage << "]"; //writes timestamp to file
	logfile << " "; //Separating time stamp and message type
	logfile << "[" << &level << "]"; //writes timestamp to file
	logfile << " "; //Separating message type and message
	logfile << message; //Writes message to file
	logfile << "\n"; //Sets writing location to next line for next log message
}

void FRC::BlitzLogger::error(std::string currentStage, std::string message)
{
	if(logLevel >= Error)
	{
		log(currentStage, "Error", message);
	}
}

void FRC::BlitzLogger::warning(std::string currentStage, std::string message)
{
	if(logLevel >= Warning)
	{

	}
}

void FRC::BlitzLogger::info(std::string currentStage, std::string message)
{
	if(logLevel >= Info)
	{

	}
}

void FRC::BlitzLogger::debug(std::string currentStage, std::string message)
{
	if(logLevel >= Debug)
	{

	}
}

void FRC::BlitzLogger::trace(std::string currentStage, std::string message)
{
	if(logLevel >= Trace)
	{

	}
}
