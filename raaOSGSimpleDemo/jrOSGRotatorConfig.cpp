#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osg/Switch>
#include "jrOSGRotatorConfig.h"

jrOSGRotatorConfig::jrOSGRotatorConfig() {
	rotateLeft = false;
	rotateRight = false;
	rotateAngle = 0;
	rotateSpeed = 0.01;
	minAngle = -0.7;
	maxAngle = 0.7;
	newAngle = 0;
	undoAnimateAngle = 0;
	axis = osg::Vec3d(1, 0, 0);
	animating = false;
	osgSwitch = 0;
	rotator = 0;
}


jrOSGRotatorConfig::~jrOSGRotatorConfig(void) {
	rotator->unref();
}
