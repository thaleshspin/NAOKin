#ifndef _NAO_H_
#define _NAO_H_

#include <iostream>
#include <string>
#include <qi/os.hpp>
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <stdarg.h>

#include "Timer.h"
#include "Motion.h"
using namespace std;

class NAO
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
  void ParseMotionFile(string filename, string key);
  void SetAngles(int numJoints, double speed, ...);
  void Interpolate(string key);

public:
  NAO(string nao_ip);
  Timer timer;

  void WakeUp();
  void Rest();
  void Stiff();
  void Unstiff();
  void GoToPosture(string);
  void Trajectory();
};

#endif