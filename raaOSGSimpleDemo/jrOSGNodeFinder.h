#pragma once

#include <osg/NodeVisitor>

class jrOSGNodeFinder: public osg::NodeVisitor {
public:
	jrOSGNodeFinder(const std::string& name);
	virtual ~jrOSGNodeFinder(void);
	
	virtual void apply(osg::Node &node);

	osg::Node* getNode();

protected:
	std::string nodeName;
	osg::Node* targetNode;
};
