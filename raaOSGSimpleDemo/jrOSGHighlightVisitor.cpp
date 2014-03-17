#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osg/MatrixTransform>
#include <osgFX/Scribe>
#include "jrOSGHighlightVisitor.h"


jrOSGHighlightVisitor::jrOSGHighlightVisitor(void) : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {
}


jrOSGHighlightVisitor::~jrOSGHighlightVisitor(void) {
}

void jrOSGHighlightVisitor::apply(osg::Node &node) {
	if (node.getName().find("ForeArm.Flat") != std::string::npos) {
		std::cout << "highlighting: " << node.getName() << std::endl;
		osgFX::Scribe* scribe = new osgFX::Scribe();
		osg::Group* parent = node.getParent(0);
		
		scribe->setName("highlighted");
		scribe->setWireframeColor(osg::Vec4(0,1,0,0.5));
		scribe->addChild(&node);
		
		parent->replaceChild(&node, scribe);

		parent = node.getParent(0);
		
		osg::MatrixTransform* transform = new osg::MatrixTransform;
		
		const double angle = 0.1;
		const osg::Vec3d axis(0, 0, 1);
		transform->setMatrix(osg::Matrix::rotate(angle, axis));
		transform->setName("trans");
		transform->addChild(&node);
		parent->replaceChild(&node, transform);

	} 	
	else if (node.getName().find("highlighted") != std::string::npos) {
		std::cout << "removing highlight on: " << node.getName() << std::endl;
		osg::Group* parent = node.getParent(0);
		osgFX::Scribe* scribe = dynamic_cast<osgFX::Scribe*>(&node);
		parent->replaceChild(&node, scribe->getChild(0));
		return;
	}




	traverse(node);
}
