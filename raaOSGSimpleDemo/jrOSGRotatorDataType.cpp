#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include "jrOSGRotatorDataType.h"

jrOSGRotatorDataType::jrOSGRotatorDataType(osg::Node* node) {
	rotateAngle = 0;
	isRotating = true;

	jrOSGNodeFinder finder("Body_Rotator");
	finder.traverse(*(node));
	bodyRotator = finder.getNode();
}


jrOSGRotatorDataType::~jrOSGRotatorDataType(void) {
}

void jrOSGRotatorDataType::updateRotation() {
	if (isRotating) {
		rotateAngle + 0.1;
		std::cout << "angle currently: " << rotateAngle << std::endl;
		//bodyRotator->setCurrentHPR(osg::Vec3(rotateAngle, 0, 0));
	}
}