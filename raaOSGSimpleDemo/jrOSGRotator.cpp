#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osgFX/Scribe>
#include <osg/MatrixTransform>
#include "jrOSGRotator.h"

jrOSGRotator::jrOSGRotator(void) {
}


jrOSGRotator::~jrOSGRotator(void) {
}

void jrOSGRotator::rotate(osg::Node* node, const std::string name, double angle) {

	osg::Group* parent = node->getParent(0);

	osg::MatrixTransform* transform = new osg::MatrixTransform;

	const osg::Vec3d axis(-1, 0, 0);
	transform->setMatrix(osg::Matrix::rotate(angle, axis));
	transform->setName(name);
	transform->addChild(node);
	parent->replaceChild(node, transform);
}

void jrOSGRotator::rotate(osg::Node* node, double angle) {

	osg::Group* parent = node->getParent(0);
	osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);

	const osg::Vec3d axis(-1, 0, 0);
	transform->setMatrix(osg::Matrix::rotate(angle, axis));

}
