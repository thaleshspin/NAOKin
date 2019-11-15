#ifndef _NAO_H_
#define _NAO_H_

#include <iostream>
#include <string>
#include <qi/os.hpp>
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>

#include "src/Timer.h"

using namespace std;


class NAO
{
private:
  AL::ALMotionProxy almotion;
  AL::ALRobotPostureProxy alposture;

public:
  NAO(string nao_ip);
  Timer timer;

  void WakeUp();
  void Rest();
  void GoToPosture(string);
};

#endif