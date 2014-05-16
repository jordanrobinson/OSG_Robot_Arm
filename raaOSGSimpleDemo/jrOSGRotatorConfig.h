#pragma once

#include <osg/Switch>
#include <osg/Vec3d>

class jrOSGRotatorConfig: osg::Referenced
{
public:

	jrOSGRotatorConfig(void);
	virtual ~jrOSGRotatorConfig(void);

	bool rotateLeft;
	bool rotateRight;
	double rotateAngle;
	double rotateSpeed;
	double minAngle;
	double maxAngle;
	double newAngle;
	double undoAnimateAngle;
	bool animating;
	osg::Switch* osgSwitch;
	osg::Node* rotator;
	osg::Vec3d axis;
};

