#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osgFX/Scribe>
#include "jrOSGHighlighter.h"

jrOSGHighlighter::jrOSGHighlighter(void) {
}


jrOSGHighlighter::~jrOSGHighlighter(void) {
}

void jrOSGHighlighter::highlight(osg::Node* node, const std::string name) {
	std::cout << "highlighting: " << node->getName() << std::endl;
	osgFX::Scribe* scribe = new osgFX::Scribe();
	osg::Group* parent = node->getParent(0);

	scribe->setName(name);
	scribe->setWireframeColor(osg::Vec4(0,1,0,0.5));
	scribe->addChild(node);

	parent->replaceChild(node, scribe);

}

void jrOSGHighlighter::unhighlight(osg::Node* node) {

	std::cout << "removing highlight on: " << node->getName() << std::endl;
	osg::Group* parent = node->getParent(0);
	osgFX::Scribe* scribe = dynamic_cast<osgFX::Scribe*>(node);
	parent->replaceChild(node, scribe->getChild(0));
	return;
}