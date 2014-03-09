#pragma once

#include <osg/NodeVisitor>

class raaOSGPrintVisitor: public osg::NodeVisitor
{
public:
	raaOSGPrintVisitor(void);
	virtual ~raaOSGPrintVisitor(void);

	virtual void apply(osg::Node &node);
};

