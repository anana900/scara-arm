//============================================================================
// Name        : scara.cpp
// Author      :
// Version     :
// Copyright   :
// Description : Forward Kinematic approach to control SCARA 2 arms.
//============================================================================

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <utility>

#define _USE_MATH_DEFINES

using namespace std;

class ScaraArm {
	private:
	unsigned int length_of_arm1;
	unsigned int length_of_arm2;

	public:
	ScaraArm():length_of_arm1(5), length_of_arm2(5)
	{}

	int calc_arm1_angle(float x, float y);
	int calc_arm1_arm2_angle(float x, float y);
	pair<int,int> calculateScara(int x, int y);
};

int ScaraArm::calc_arm1_angle(float x, float y)
{
  float arm_angle = 0;

  arm_angle = (180/M_PI) * (atan((float)y/x) -
		  acos((x*x + y*y + (length_of_arm1*length_of_arm1) -
		  (length_of_arm2*length_of_arm2)) /
		  ((2*length_of_arm1)*sqrt(x*x + y*y))));

  return (int)arm_angle;
}

int ScaraArm::calc_arm1_arm2_angle(float x, float y)
{
  float arm_angle = 0;

  arm_angle = (180/M_PI) * (acos((x*x + y*y -
		(length_of_arm1*length_of_arm1) -
		(length_of_arm2*length_of_arm2)) /
		(2*length_of_arm1*length_of_arm2)));

  return (int)arm_angle;
}

pair<int,int> ScaraArm::calculateScara(int x, int y)
{
	return make_pair(calc_arm1_angle(x, y), calc_arm1_arm2_angle(x, y));
}

int main() {
	cout << "SCARA FK2 calculation" << endl;
	ScaraArm scaraRobot;
	pair<int, int> dupa (0, 0);

	for(int x = -7 ; x < 8 ; x+=1)
	{
		for(int y = -7 ; y < 8 ; y+=1)
		{
			if(0 == x && 0 == y)
			{
				dupa.second = 180;
				/*
				// Wystarczy obrócic 2-gie ramie o 180.
				// Ramie 1-wsze pozostaje bez zmian
				// Rozwiązanie matematycznie poprawne, niepraktyczne
				cout << x << "\t" << y << "\t";
				cout << "Move to position 0.0" << endl;
				continue;
				*/
			}
			else
			{
				dupa = scaraRobot.calculateScara(x, y);

				if(x < 0)
				{
					dupa.first += 180;
				}
			}

			cout << x << "\t" << y << "\t";
			cout << "Angle arm1: "
			     << dupa.first << "\t";
			cout << "Angle arm2: "
				 << dupa.second  << endl;
		}
	}
    cout << "KONIEC";
	return 0;
}
