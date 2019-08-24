//============================================================================
// Name        : scara.cpp
// Author      : torobak
// Version     :
// Copyright   :
// Description : Forward Kinematic approach to control SCARA 2 arms.
//============================================================================

#include <iostream>
#include <stdio.h>
#include <math.h>

#define _USE_MATH_DEFINES

using namespace std;

float length_of_arm1 = 100;
float length_of_arm2 = 100;

float calc_arm1_angle(float x, float y)
{
  float arm_angle = 0;

  arm_angle = (180/M_PI) * atan((float)y/x) -
		  acos((x*x + y*y + (length_of_arm1*length_of_arm1) -
		  (length_of_arm2*length_of_arm2)) /
		  ((2*length_of_arm1)*sqrt(x*x + y*y)));

  return arm_angle;
}

float calc_arm1_arm2_angle(float x, float y)
{
  float arm_angle = 0;

  arm_angle = (180/M_PI) * (acos((x*x + y*y -
		(length_of_arm1*length_of_arm1) -
		(length_of_arm2*length_of_arm2)) /
		(2*length_of_arm1*length_of_arm2)));

  return arm_angle;
}

int main() {
	cout << "SCARA FK2 calculation" << endl;

	for(int x = -140 ; x < 140 ; x+=10)
	{
		for(int y = -140 ; y < 140 ; y+=10)
		{
			if(0 == x && 0 == y)
			{
				x = 1;
			}
			cout << x << "\t" << y << "\t";
			cout << "Angle arm1: "
			     << calc_arm1_angle(x, y) << "\t";
			cout << "Angle arm2: "
				 << calc_arm1_arm2_angle(x, y) << endl;
		}
	}

	return 0;
}
