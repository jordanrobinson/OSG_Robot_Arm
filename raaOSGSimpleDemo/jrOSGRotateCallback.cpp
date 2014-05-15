#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osgFX/Scribe>
#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osg/Node>
#include "jrOSGRotateCallback.h"

jrOSGRotateCallback::jrOSGRotateCallback(void) {}

jrOSGRotateCallback::~jrOSGRotateCallback(void) {
	unref();
}

void jrOSGRotateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv) {
	osg::ref_ptr<jrOSGRotatorDataType> rotatorData = dynamic_cast<jrOSGRotatorDataType*> (node->getUserData());

	if (rotatorData) {
		rotatorData->updateRotation();
	}
	traverse(node, nv);
}
