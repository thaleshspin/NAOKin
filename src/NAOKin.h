#ifndef _NAOKIN_H_
#define _NAOKIN_H_

#include <iostream>
#include <string>
#include <qi/os.hpp>
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>

#include "src/external/Kofinas/NAOKinematics.h"
#include "src/external/Kofinas/KMat.hpp"
#include "src/Timer.h"

#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <stdarg.h>

using namespace std;
using boost::property_tree::ptree;

class NAOKin
{
private:
  AL::ALMotionProxy almotion;
  AL::ALRobotPostureProxy alposture;

  struct InterpolationValues
  {
    vector<string> names;
    vector<vector<float> > angles;
    vector<vector<float> > times;
  };

  map<string, InterpolationValues> m_interpolations;

  vector<pair<string, string> > m_motion_filenames;

  void parseMotionFile(string filename, string key);

  void setAngles(int numJoints, double speed, ...);

  void interpolate(string key);

public:
  NAOKin(string nao_ip);
  Timer timer;

  void WakeUp();
  void Rest();
  void GoToPosture(string);
  void DoTrajectory();
};

#endif