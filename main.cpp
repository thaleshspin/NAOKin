#include "src/NAO.h"
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    NAO nao(string("127.0.0.1")); 

    nao.WakeUp(); //Wake up robot
    nao.GoToPosture("StandInit");
    nao.timer.Wait(2000);
    nao.GoToPosture("Crouch");
    nao.Rest();
    
    return 0;
}