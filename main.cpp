#include "src/NAO.h"
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    NAO nao(string("127.0.0.1")); 
    nao.Stiff();
    nao.WakeUp(); //Wake up robot
    nao.GoToPosture("StandInit");    
    nao.Trajectory(); //Be carefull with the stiffness!!! The robot is doing the moviments so fast (improve this later!)
    nao.timer.Wait(2000);
    nao.GoToPosture("Crouch");
    nao.Rest();
    nao.Unstiff();
    
    return 0;
}