#pragma once

#include <osg/NodeVisitor>
#include <osg/ref_ptr>

#include "jrOSGRotatorDataType.h"

class jrOSGRotateCallback: public osg::NodeCallback {
public:

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
	
	jrOSGRotateCallback(void);
	virtual ~jrOSGRotateCallback(void);
};
