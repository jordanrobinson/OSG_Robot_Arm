#pragma once

#include <osg/Node>
#include <osg/Vec3>
#include "jrOSGNodeFinder.h"

class jrOSGRotatorDataType : public osg::Referenced {
public:
	bool isRotating;
	jrOSGRotatorDataType(osg::Node* node);
	virtual ~jrOSGRotatorDataType(void);
	void jrOSGRotatorDataType::updateRotation();




protected:
	double rotateAngle;
	osg::Node* bodyRotator;
	osg::Node* upperArmRotator;
	osg::Node* lowerArmRotator;
	osg::Node* hand1Rotator;
	osg::Node* hand2Rotator;
	osg::Node* hand3Rotator;
};
