#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osg/MatrixTransform>
#include <osgFX/Scribe>
#include "jrOSGNodeFinder.h"

jrOSGNodeFinder::jrOSGNodeFinder(const std::string& name) : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
	nodeName = name;
}

jrOSGNodeFinder::~jrOSGNodeFinder(void) {
}

void jrOSGNodeFinder::apply(osg::Node &node) {
	if (node.getName() == nodeName) {
		targetNode = &node;
	}
	traverse(node);
}

osg::Node* jrOSGNodeFinder::getNode() {
	return targetNode;
}
