#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osgFX/Scribe>
#include "jrOSGHighlightVisitor.h"


jrOSGHighlightVisitor::jrOSGHighlightVisitor(void) : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
}


jrOSGHighlightVisitor::~jrOSGHighlightVisitor(void) {
}

void jrOSGHighlightVisitor::apply(osg::Node &node) {
	if (node.getName().find("Base") != std::string::npos) {
		osgFX::Scribe* scribe = new osgFX::Scribe();
		scribe->setWireframeColor(osg::Vec4(0,1,0,0.5));
		scribe->addChild(&node);

		osg::Group* parent = node.getParent(0);
		parent->replaceChild(&node, scribe);

	}

	traverse(node);
}
