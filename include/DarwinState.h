#ifndef _DARWIN_STATE_H_
#define _DARWIN_STATE_H_
/**
 * The class that is responsible for handling the state of Darwin and 
 * all of the robot components that is has. This handles updating components with correct values 
 * and writing all of the messages to the components on the robot in real mode. Simulation
 * is still a very large work in progress. 
 *
 * Author: Ryan 
 * 
 */

#include "CM730.h"
#include "MX28.h"
#include "LinuxCM730.h"
#include "motor.h"
#include <unordered_map>
#include <vector>
#include <string> 
#include <stdexcept>
#include <iostream>


class DarwinState
{
    public:
        DarwinState(Robot::CM730* _cm730);
        ~DarwinState();
        void updateRobot();
        void setProperty(char* Joint, std::string Property, double value);
        double getProperty(std::string Joint, std::string Property);
        void command(std::string Command, char* Joint);

    private:
        //
        std::unordered_map<std::string, motor> motors; //Vector of all the motors on the robot
        //std::vector<led> leds;
        //imu* imu;
        Robot::CM730* cm730;
};
#endif