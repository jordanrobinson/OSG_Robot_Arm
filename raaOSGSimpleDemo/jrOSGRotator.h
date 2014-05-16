#pragma once

#include <osg\Node>

class jrOSGRotator: public osg::Referenced {
public:
	jrOSGRotator(void);
	virtual ~jrOSGRotator(void);

	virtual void rotate(osg::Node* node, const std::string name, double angle);
	virtual void rotate(osg::Node* node, double angle, osg::Vec3d axis);
};
