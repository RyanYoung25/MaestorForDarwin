/**
 * The motor class for darwin motors. This stores all of the data for a 
 * specific motor including the name, ID number, current position, 
 * goal position, current angle, goal angle, velocity, Enabled status, 
 * and the P I and D gains 
 *
 * Author: Ryan 
 * 
 */

#include "motor.h"

motor::motor(std::string _name, int _ID, int _freq, Robot::CM730* _cm730)
{
    //for reading and writing
    cm730 = _cm730;
    //identificaion 
    name = _name;
    ID = _ID;
    //PID gains
    Pgain = 0;
    Igain = 0;
    Dgain = 0;
    //position data
    curpos = 0;
    goalpos = 0;
    curangle = 0;
    //Interoplation data
    velocity = 0;
    interpolationStep = 0;
    currTime = 0;
    goalTime = 0;
    m=0;
    yI=0;
    freq = _freq;
    //requiresMotion flag
    motion = false;
    enabled = false;
}

motor::~motor()
{
    
}

void motor::setPGain(int gain)
{
    Pgain = gain;
}

void motor::setIGain(int gain)
{
    Igain = gain;
}

void motor::setDGain(int gain)
{
    Dgain = gain;
}

void motor::setVelocity(double vel)
{
    velocity = vel;
}

void motor::setGoal(double angle)
{
    motion = true;
    goalpos = angleToPos(angle);    
}

void motor::setGoal(int value)
{
    motion = true;
    yI = getValue();

    //Set up the correct interpolation parameters. Eventually will be a seperate function.
    
    int diff = abs(value - yI);
    double timeSec = diff * velocity;
    goalTime = timeSec * freq; 
    currTime = 0;
    m = (goalTime - currTime) / (value - yI) ;
    goalpos = value;
}

void motor::setCurrPos(int pos)
{
    curpos = pos;
}

void motor::enable()
{
    enabled = true;
    cm730->WriteWord(ID, Robot::MX28::P_TORQUE_ENABLE, 1, 0); //Enable the torque
}  

void motor::disable()
{
    enabled = false;
    cm730->WriteWord(ID, Robot::MX28::P_TORQUE_ENABLE, 0, 0); //Diable the torque
}

double motor::getAngle()
{
    return curangle;
}

int motor::getValue()
{
    cm730->ReadWord(ID, Robot::MX28::P_PRESENT_POSITION_L, &curpos, 0); 
    curangle = posToAngle(curpos);
    return curpos;
}

void motor::update()
{
    motor::interpolate();
}

bool motor::requiresMotion()
{
    return motion;
}

std::vector<int> motor::getData()
{
    std::vector<int> data;
    data.reserve(7);
    data.push_back(ID);
    data.push_back(Dgain);
    data.push_back(Igain);
    data.push_back(Pgain);
    data.push_back(0);
    data.push_back(Robot::CM730::GetLowByte(interpolationStep));
    data.push_back(Robot::CM730::GetHighByte(interpolationStep));
    return data;

}

void motor::interpolate()
{
    //Implement linear interpolation.
    if(currTime < goalTime)
    {
        interpolationStep = m*currTime + yI;
        currTime ++;
    }
    else
    {
        motion = false;
    }
}

int motor::angleToPos(double angle)
{
    double ratio = 11.378; // 4096 / 360 from degrees to tics
    return (int) angle * ratio;
}

double motor::posToAngle(int pos)
{
    double ratio = .08789;
    return ratio * pos;
}

