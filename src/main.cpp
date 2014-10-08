/** 
 * Test case for MAESTOR for Darwin. This is designed just to make the Right Shoulder pitch move back and forth. 
 *
 * It creates a CS730 object then passes it on to the DarwinState the makes all of the motor objects and 
 * then tries to move the robot out. 
 */

#include "DarwinState.h"
#include "CM730.h"
#include "LinuxCM730.h"
#include <sys/time.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    
    Robot::LinuxCM730 linux_cm730("/dev/ttyUSB0");
    Robot::CM730 cm730(&linux_cm730);
    if(cm730.Connect() == false)
    {
        printf("Fail to connect CM-730!\n");
        return 0;
    }

    DarwinState state(&cm730);

    state.command("Enable", "RSP");
    state.setProperty("RSP", "position", 0.1);

    for(int i = 0; i < 200; i ++)
    {
        state.updateRobot();
        std::cout << "updated" << std::endl;
        usleep(50000);
    }

    std::cout << "Waiting..." << std::endl;
    usleep(5000000);

    state.setProperty("RSP", "position", 0.0);

    for(int i = 0; i < 200; i ++)
    {
        state.updateRobot();
        std::cout << "updating" << std::endl;
        usleep(50000);
    }

    return 0;
}