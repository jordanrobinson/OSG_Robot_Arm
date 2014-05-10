#pragma once

#include <osg/Node>
#include <osg/Vec3d>
#include "jrOSGNodeFinder.h"
#include "jrOSGRotatorConfig.h"

class jrOSGRotatorDataType : public osg::Referenced {
public:
	jrOSGRotatorConfig* bodyConfig;
	jrOSGRotatorConfig* upperArmConfig;
	jrOSGRotatorConfig* lowerArmConfig;
	jrOSGRotatorConfig* hand1Config;
	jrOSGRotatorConfig* hand2Config;
	jrOSGRotatorConfig* hand3Config;

	jrOSGRotatorConfig* configs [6];

	double recordedAnimateCoords [6];

	jrOSGRotatorDataType(osg::Node* node);
	virtual ~jrOSGRotatorDataType(void);
	void jrOSGRotatorDataType::updateRotation();
	void jrOSGRotatorDataType::highlight(jrOSGRotatorConfig* config);
	void jrOSGRotatorDataType::animate(jrOSGRotatorConfig* config);	
	void jrOSGRotatorDataType::animate(double newAngle, jrOSGRotatorConfig* config);

protected:
};
