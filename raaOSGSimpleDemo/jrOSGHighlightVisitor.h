#pragma once

#include <osg/NodeVisitor>

class jrOSGHighlightVisitor: public osg::NodeVisitor {
public:
	jrOSGHighlightVisitor(void);
	virtual ~jrOSGHighlightVisitor(void);

	virtual void apply(osg::Node &node);
};
