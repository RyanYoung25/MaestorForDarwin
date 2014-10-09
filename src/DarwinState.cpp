/**
 * The class that is responsible for handling the state of Darwin and 
 * all of the robot components that is has. This handles updating components with correct values 
 * and writing all of the messages to the components on the robot in real mode. Simulation
 * is still a very large work in progress. 
 *
 * Author: Ryan 
 * 
 */

#include "DarwinState.h"

DarwinState::DarwinState(Robot::CM730 *_cm730)
{
    std::unordered_map<std::string, motor> motors; //map of all the motors on the robot
    cm730 = _cm730;

    //Initialize all of the motors
    std::pair<std::string, motor> RSPpair ("RSP", motor("RSP", 1, 200, cm730));
    std::pair<std::string, motor> LSPpair ("LSP", motor("LSP", 2, 200, cm730));
    std::pair<std::string, motor> RSRpair ("RSR", motor("RSR", 3, 200, cm730));
    std::pair<std::string, motor> LSRpair ("LSR", motor("LSR", 4, 200, cm730));
    std::pair<std::string, motor> REPpair ("REP", motor("REP", 5, 200, cm730));
    std::pair<std::string, motor> LEPpair ("LEP", motor("LEP", 6, 200, cm730));
    std::pair<std::string, motor> RHYpair ("RHY", motor("RHY", 7, 200, cm730));
    std::pair<std::string, motor> LHYpair ("LHY", motor("LHY", 8, 200, cm730));
    std::pair<std::string, motor> RHRpair ("RHR", motor("RHR", 9, 200, cm730));
    std::pair<std::string, motor> LHRpair ("LHR", motor("LHR", 10, 200, cm730));
    std::pair<std::string, motor> RHPpair ("RHP", motor("RHP", 11, 200, cm730));
    std::pair<std::string, motor> LHPpair ("LHP", motor("LHP", 12, 200, cm730));
    std::pair<std::string, motor> RKPpair ("RKP", motor("RKP", 13, 200, cm730));
    std::pair<std::string, motor> LKPpair ("LKP", motor("LKP", 14, 200, cm730));
    std::pair<std::string, motor> RAPpair ("RAP", motor("RAP", 15, 200, cm730));
    std::pair<std::string, motor> LAPpair ("LAP", motor("LAP", 16, 200, cm730));
    std::pair<std::string, motor> RARpair ("RAR", motor("RAR", 17, 200, cm730));
    std::pair<std::string, motor> LARpair ("LAR", motor("LAR", 18, 200, cm730));
    std::pair<std::string, motor> NKYpair ("NKY", motor("NKY", 19, 200, cm730));
    std::pair<std::string, motor> NKRpair ("NKR", motor("NKR", 20, 200, cm730));

    motors.insert(RSPpair);
    motors.insert(LSPpair);
    motors.insert(RSRpair);
    motors.insert(LSRpair);
    motors.insert(REPpair);
    motors.insert(LEPpair);
    motors.insert(RHYpair);
    motors.insert(LHYpair);
    motors.insert(RHRpair);
    motors.insert(LHRpair);
    motors.insert(RHPpair);
    motors.insert(LHPpair);
    motors.insert(RKPpair);
    motors.insert(LKPpair);
    motors.insert(RAPpair);
    motors.insert(LAPpair);
    motors.insert(RARpair);
    motors.insert(LARpair);
    motors.insert(NKYpair);
    motors.insert(NKRpair);    
}

DarwinState::~DarwinState()
{

}

void DarwinState::updateRobot()
{
    int param[20 * 7]; //Maximum size if all motors were to write at once. 
    int index = 0;
    int jointNum = 0;
    for (std::unordered_map<std::string, motor>::iterator it = motors.begin(); it != motors.end(); ++it)
    {
        motor joint = it->second;
        if(joint.requiresMotion())
        {   
            std::vector<int> values = joint.getData();
            for(int i = 0; i < values.size(); i ++)
            {
                param[index] = values[i];
                index ++; 
            }
            jointNum ++;
        }
    }

    if(jointNum > 0)
    {
        cm730->SyncWrite(Robot::MX28::P_D_GAIN, Robot::MX28::PARAM_BYTES, jointNum, param);
    }


}

void DarwinState::setProperty(char* Joint, std::string Property, double value)
{   
    motor* joint;
    try
    {
        joint = &motors.at(Joint);
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Joint: " << Joint << " does not exist" << std::endl;
        return;
    }

    if(Property.compare("position") == 0)
    {
        joint->setGoal(value); //angle
    }
    else
    {
        std::cout << "Property: " << Property << " does not exist for the joint " << Joint << std::endl;
    }


}

double DarwinState::getProperty(std::string Joint, std::string Property)
{
    motor* joint;
    try
    {
        joint = &motors.at(Joint);
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Joint: " << Joint << " does not exist" << std::endl;
        return 0.0;
    }

    if(Property.compare("position") == 0)
    {
        return joint->getValue(); 
    }
    else
    {
        std::cout << "Property: " << Property << " does not exist for the joint " << Joint << std::endl;
    }
}

void DarwinState::command(std::string Command, char* Joint)
{
    motor* joint;
    try
    {
        joint = &motors.at(Joint);
    }
    catch(const std::out_of_range& oor)
    {
        std::cout << "Joint: " << Joint << " does not exist" << std::endl;
        return;
    }

    if(Command.compare("Enable") == 0)
    {
       joint->enable(); 
    }
    else if(Command.compare("Disable") == 0)
    {
        joint->disable(); 
    }
    else
    {
        std::cout << "Command: " << Command << " does not exist for the joint " << Joint << std::endl;
    }
}