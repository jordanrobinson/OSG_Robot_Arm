#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osg/MatrixTransform>
#include "jrOSGRotatorDataType.h"
#include "jrOSGRotator.h"
#include "jrOSGHighlighter.h"
#include "jrOSGSwitchSetup.h"

jrOSGRotatorDataType::jrOSGRotatorDataType(osg::Node* node) {
	rotateAngle = 0;

	highlighted = false;
	rotateLeft = false;
	rotateRight = false;

	jrOSGSwitchSetup setup;
	
	bodyRotator = node;
	//setup.addSwitch(node);

	jrOSGNodeFinder upperArmFinder("UpperArm_Rotator");
	upperArmFinder.traverse(*(node));
	upperArmRotator = upperArmFinder.getNode();
	//setup.addSwitch(upperArmRotator);

	jrOSGNodeFinder lowerArmFinder("LowerArm_Rotator");
	lowerArmFinder.traverse(*(node));
	lowerArmRotator = lowerArmFinder.getNode();
	//setup.addSwitch(lowerArmRotator);

	jrOSGNodeFinder hand1Finder("Hand1_Rotator");
	hand1Finder.traverse(*(node));
	hand1Rotator = hand1Finder.getNode();
	setup.addSwitch(hand1Rotator);

	jrOSGNodeFinder hand2Finder("Hand2_Rotator");
	hand2Finder.traverse(*(node));
	hand2Rotator = hand2Finder.getNode();
	//setup.addSwitch(hand2Rotator);

	jrOSGNodeFinder hand3Finder("Hand3_Rotator");
	hand3Finder.traverse(*(node));
	hand3Rotator = hand3Finder.getNode();
	//setup.addSwitch(hand3Rotator);

	//std::cout << bodyRotator << std::endl;
}


jrOSGRotatorDataType::~jrOSGRotatorDataType(void) {
}

void jrOSGRotatorDataType::updateRotation() {
	//highlight();
	if (rotateLeft) {
		rotateAngle += 0.005;

		jrOSGRotator rotator;
		rotator.rotate(bodyRotator, rotateAngle);
		rotator.rotate(upperArmRotator, rotateAngle);
		rotator.rotate(lowerArmRotator, rotateAngle);
		rotator.rotate(hand1Rotator, rotateAngle);
		rotator.rotate(hand2Rotator, rotateAngle);
		rotator.rotate(hand3Rotator, rotateAngle);
	}

	if (rotateAngle > 0.8) {
		rotateRight = true;
		rotateLeft = false;
	}
	else if (rotateAngle < -0.8) {
		rotateRight = false;
		rotateLeft = true;
	}

	if (rotateRight) {
		rotateAngle -= 0.005;

		jrOSGRotator rotator;
		rotator.rotate(bodyRotator, rotateAngle);
		rotator.rotate(upperArmRotator, rotateAngle);
		rotator.rotate(lowerArmRotator, rotateAngle);
		rotator.rotate(hand1Rotator, rotateAngle);
		rotator.rotate(hand2Rotator, rotateAngle);
		rotator.rotate(hand3Rotator, rotateAngle);
	}

	rotateLeft = false;
	rotateRight = false;
}

void jrOSGRotatorDataType::highlight() {

	if (rotateLeft || rotateRight) {
		if (!highlighted) {
			jrOSGHighlighter highlighter;
			highlighter.highlightGreen(upperArmRotator);
			highlighted = true;
		}
	}
	else {
		//if (highlighted) {
		//	jrOSGHighlighter highlighter;
		//	highlighter.unhighlight(upperArmRotator->getParent(0));
		//	highlighted = false;
		//}
	}
}