#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osgFX/Scribe>
#include "jrOSGHighlighter.h"

jrOSGHighlighter::jrOSGHighlighter(void) {
}


jrOSGHighlighter::~jrOSGHighlighter(void) {
}

void jrOSGHighlighter::highlight(osg::Node* node, const osg::Vec4 &colour) {
	std::cout << "highlighting: " << node->getName() << std::endl;
	osgFX::Scribe* scribe = new osgFX::Scribe();
	osg::Group* parent = node->getParent(0);

	std::string scribeName("Highlight_");
	scribeName.append(node->getName());

	scribe->setName(scribeName);
	scribe->setWireframeColor(colour);
	scribe->addChild(node);

	parent->replaceChild(node, scribe);
}

void jrOSGHighlighter::highlightRed(osg::Node* node) {
	highlight(node, osg::Vec4(0.7,0,0,0));
}

void jrOSGHighlighter::highlightGreen(osg::Node* node) {
	highlight(node, osg::Vec4(0,0.7,0,0));
}

void jrOSGHighlighter::unhighlight(osg::Node* node) {
	if (node) {
		std::cout << "removing highlight on: " << node->getName() << std::endl;
		osg::Group* parent = node->getParent(0);
		osgFX::Scribe* scribe = dynamic_cast<osgFX::Scribe*>(node);
		if (scribe && scribe->getChild(0)) {
			parent->replaceChild(node, scribe->getChild(0));
		}

	}
}