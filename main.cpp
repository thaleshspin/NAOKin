#include "src/NAOKin.h"
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    NAOKin nao(string("127.0.0.1"));

    nao.WakeUp();
    nao.GoToPosture("StandInit");
    nao.DoTrajectory();
    //nao.timer.Wait(2000);
    nao.GoToPosture("Crouch");
    nao.Rest();
    
    return 0;
}