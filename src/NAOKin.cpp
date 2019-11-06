#include "NAOKin.h"
#include <assert.h>

using namespace std;
using namespace AL;
using boost::property_tree::ptree;

typedef pair<string, string> str_str_pair;

NAOKin::NAOKin(string nao_ip) : almotion(nao_ip), alposture(nao_ip)
{
	timer.Restart();

	//Creating a reference for the json file
	m_motion_filenames.push_back(pair<string, string>("standInit.json", "standInit"));
	m_motion_filenames.push_back(pair<string, string>("standZero.json", "standZero"));

	//Parsing the values to the reference
	BOOST_FOREACH (str_str_pair &file_key_pair, m_motion_filenames)
	{
		parseMotionFile(file_key_pair.first, file_key_pair.second); //File / Posture name
	}
}

void NAOKin::DoTrajectory()
{
	interpolate("standInit");
	timer.Wait(1000);
	interpolate("standZero");
	timer.Wait(1000);
}

void NAOKin::parseMotionFile(string filename, string key)
{
	ptree pt; //Creating a tree for the postures values

	try
	{
		boost::property_tree::read_json(filename, pt); //Read the posture file and associate it with the tree
	}
	catch (boost::exception &ex)
	{
		cout << "File " << filename << " could not be loaded." << endl;
	}

	InterpolationValues ip_values; //Local data for the posture

	BOOST_FOREACH (const ptree::value_type &element, pt.get_child("root")) //For in the tree looking for values
	{
		vector<float> angles_vector;
		vector<float> times_vector;

		BOOST_FOREACH (const ptree::value_type &ele, element.second.get_child("angles"))
		{
			angles_vector.push_back(ele.second.get<float>("")); //Getting angle values
		}
		BOOST_FOREACH (const ptree::value_type &ele, element.second.get_child("times"))
		{
			times_vector.push_back(ele.second.get<float>("")); //Gerring time values
		}

		ip_values.names.push_back(element.second.get<string>("name"));
		ip_values.angles.push_back(angles_vector);
		ip_values.times.push_back(times_vector);
	}
	m_interpolations[key] = ip_values; //Setting values to the key
}

void NAOKin::setAngles(int numJoints, double speed, ...)
{
    va_list args; //Lists of arguments optimized
    int list_length = 2 * numJoints; //Names and angles
    
	va_start(args, list_length);
    ALValue names, angles;

    for (int i = 0; i < numJoints; ++i)
    {
        names.arrayPush(va_arg(args, char *));
    }

    for (int i = numJoints; i < list_length; ++i)
    {
        angles.arrayPush(va_arg(args, double));
    }

    va_end(args);

    almotion.setAngles(names, angles, speed);
}


void NAOKin::interpolate(string key) //The key representes the posture to interpolate
{
	InterpolationValues iv = m_interpolations[key]; //Making a InterpolationValues object with a 
													//container of values for the key
	ALValue al_names,
		al_angles,
		al_times;

	unsigned size = iv.angles.size();
	for (unsigned i = 0; i < size; ++i)
	{
		al_names.arrayPush(iv.names[i]);
		al_angles.arrayPush(iv.angles[i]);
		al_times.arrayPush(iv.times[i]);
	}

	almotion.angleInterpolation(iv.names, al_angles, al_times, true);
}

void NAOKin::WakeUp()
{
	almotion.wakeUp();
}

void NAOKin::Rest()
{
	almotion.rest();
}

void NAOKin::GoToPosture(string posture)
{
	alposture.goToPosture(posture, 1.0f);
}