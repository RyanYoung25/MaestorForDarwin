#ifndef _MOTOR_H_
#define _MOTOR_H_

/**
 * The motor class for darwin motors. This stores all of the data for a 
 * specific motor including the name, ID number, current position, 
 * goal position, current angle, goal angle, velocity, Enabled status, 
 * and the P I and D gains 
 * 
 */
#include <vector> 
#include <string> 
#include "CM730.h"
#include "MX28.h"
#include "LinuxCM730.h"

class motor
{
public:
    motor(std::string _name, int _ID, int _freq, Robot::CM730* _cm730);
    ~motor();

    void setPGain(int gain);
    void setIGain(int gain);
    void setDGain(int gain);
    void setVelocity(double vel);
    void setGoal(double angle);
    void setGoal(int value);
    void setCurrPos(int pos);
    void enable();
    void disable();
    double getAngle();
    int getValue();
    void update();
    bool requiresMotion();
    bool EnableTorque();
    std::vector<int> getData();

private: 

    //Read and write when needed
    Robot::CM730* cm730;
    //Identification 
    std::string name;
    int ID;

    //PID gains
    int Pgain;
    int Igain;
    int Dgain;
    //position data
    int curpos;
    int goalpos;
    double curangle;
    //Interoplation data
    double velocity;
    int interpolationStep;
    int currTime;
    int goalTime;
    int freq;
    int yI;
    float m;
    //requiresMotion flag
    bool motion;
    //Enabled motor torque flag
    bool enabled;

    void interpolate();
    int angleToPos(double angle); //11.378; 4096 / 360
    double posToAngle(int pos);

};
#endif