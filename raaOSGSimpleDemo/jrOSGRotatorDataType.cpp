#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osg/MatrixTransform>
#include <osg/Switch>
#include <osg/Vec3d>
#include "jrOSGRotatorDataType.h"
#include "jrOSGRotator.h"
#include "jrOSGHighlighter.h"
#include "jrOSGSwitchSetup.h"
#include "jrOSGRotatorConfig.h"

jrOSGRotatorDataType::jrOSGRotatorDataType(osg::Node* node) {

	bodyConfig = new jrOSGRotatorConfig();
	upperArmConfig = new jrOSGRotatorConfig();
	lowerArmConfig = new jrOSGRotatorConfig();
	hand1Config = new jrOSGRotatorConfig();
	hand2Config = new jrOSGRotatorConfig();
	hand3Config = new jrOSGRotatorConfig();


	bodyConfig->axis = osg::Vec3d(0, 0, 1);
	bodyConfig->rotateSpeed = 0.02;
	hand2Config->axis = osg::Vec3d(0, 0, 1);
	hand3Config->axis = osg::Vec3d(0, 1, 0);
	hand3Config->maxAngle = 1.7;
	hand3Config->minAngle = -1.7;

	configs[0] = bodyConfig;
	configs[1] = upperArmConfig;
	configs[2] = lowerArmConfig;
	configs[3] = hand1Config;
	configs[4] = hand2Config;
	configs[5] = hand3Config;

	for (int i = 0; i < 6; i++) {
		recordedAnimateCoords[i] = 0.0;
	}

	jrOSGSwitchSetup setup;

	bodyConfig->rotator = node;

	osg::Group* bodyRotatorGroup = dynamic_cast<osg::Group*>(bodyConfig->rotator);
	bodyConfig->osgSwitch = setup.addSwitch(bodyRotatorGroup);

	jrOSGNodeFinder upperArmFinder("UpperArm_Rotator");
	upperArmFinder.traverse(*(node));
	upperArmConfig->rotator = upperArmFinder.getNode();
	osg::Group* upperArmRotatorGroup = dynamic_cast<osg::Group*>(upperArmConfig->rotator);
	upperArmConfig->osgSwitch = setup.addSwitch(upperArmRotatorGroup);

	jrOSGNodeFinder lowerArmFinder("LowerArm_Rotator");
	lowerArmFinder.traverse(*(node));
	lowerArmConfig->rotator = lowerArmFinder.getNode();
	osg::Group* lowerArmRotatorGroup = dynamic_cast<osg::Group*>(lowerArmConfig->rotator);
	lowerArmConfig->osgSwitch = setup.addSwitch(lowerArmRotatorGroup);

	jrOSGNodeFinder hand1Finder("Hand1_Rotator");
	hand1Finder.traverse(*(node));
	hand1Config->rotator = hand1Finder.getNode();
	osg::Group* hand1RotatorGroup = dynamic_cast<osg::Group*>(hand1Config->rotator);
	hand1Config->osgSwitch = setup.addSwitch(hand1RotatorGroup);

	jrOSGNodeFinder hand2Finder("Hand2_Rotator");
	hand2Finder.traverse(*(node));
	hand2Config->rotator = hand2Finder.getNode();
	osg::Group* hand2RotatorGroup = dynamic_cast<osg::Group*>(hand2Config->rotator);
	hand2Config->osgSwitch = setup.addSwitch(hand2RotatorGroup);

	jrOSGNodeFinder hand3Finder("Hand3_Rotator");
	hand3Finder.traverse(*(node));
	hand3Config->rotator = hand3Finder.getNode();
	osg::Group* hand3RotatorGroup = dynamic_cast<osg::Group*>(hand3Config->rotator);
	hand3Config->osgSwitch = setup.addSwitch(hand3RotatorGroup);

}


jrOSGRotatorDataType::~jrOSGRotatorDataType(void) {
}

void jrOSGRotatorDataType::updateRotation() {

	jrOSGRotator rotator;

	for (int i = 0; i < 6; i++) {
		if (configs[i]->animating) {
			animate(configs[i]->newAngle, configs[i]);
		}
		highlight(configs[i]);

		if (configs[i]->rotateLeft || configs[i]->rotateRight) {
			if (configs[i]->rotateLeft) {
				configs[i]->rotateAngle += configs[i]->rotateSpeed;
				rotator.rotate(configs[i]->rotator, configs[i]->rotateAngle, configs[i]->axis);
			}
			if (configs[i]->rotateAngle > 0.705) {
				configs[i]->rotateRight = true;
				configs[i]->rotateLeft = false;
			}
			if (configs[i]->rotateAngle < -0.705) {
				configs[i]->rotateRight = false;
				configs[i]->rotateLeft = true;
			}
			if (configs[i]->rotateRight) {
				configs[i]->rotateAngle -= configs[i]->rotateSpeed;
				rotator.rotate(configs[i]->rotator, configs[i]->rotateAngle, configs[i]->axis);
			}
			configs[i]->rotateLeft = false;
			configs[i]->rotateRight = false;
		}
	}
}

void jrOSGRotatorDataType::highlight(jrOSGRotatorConfig* config) {

	if (config->rotateLeft || config->rotateRight) {
		if (config->rotateAngle > config->maxAngle || config->rotateAngle < config->minAngle) {
			config->osgSwitch->setSingleChildOn(2);
			std::cout << " rotateAngle: " << config->rotateAngle << " max: " << config->maxAngle << std::endl;
		}
		else {

			config->osgSwitch->setSingleChildOn(1);
		}
	}
}

void jrOSGRotatorDataType::animate(double newAngle, jrOSGRotatorConfig* config) {

	if (config->newAngle == newAngle) {
		animate(config);
	}
	else {
		config->undoAnimateAngle = config->rotateAngle;
		config->newAngle = newAngle;
		animate(config);
	}
}

void jrOSGRotatorDataType::animate(jrOSGRotatorConfig* config) {
	if (config->rotateAngle - config->newAngle > 0.01 || config->rotateAngle - config->newAngle < -0.01) {
		config->animating = true;
		if (config->newAngle > config->rotateAngle) {
			config->rotateLeft = true;
		}
		else if (config->newAngle < config->rotateAngle) {
			config->rotateRight = true;
		}
	}
	else {
		config->animating = false;
		config->osgSwitch->setSingleChildOn(0);
	}
}