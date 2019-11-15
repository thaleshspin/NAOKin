#include "NAO.h"

using namespace std;
using namespace AL;


NAO::NAO(string nao_ip) : almotion(nao_ip), alposture(nao_ip)
{
	timer.Restart();
}

void NAO::WakeUp()
{
	almotion.wakeUp();
}

void NAO::Rest()
{
	almotion.rest();
}

void NAO::GoToPosture(string posture)
{
	alposture.goToPosture(posture, 1.0f);
}