#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osgFX/Scribe>
#include <osg/MatrixTransform>
#include <osg/Switch>
#include "jrOSGSwitchSetup.h"

jrOSGSwitchSetup::jrOSGSwitchSetup(void) {
}


jrOSGSwitchSetup::~jrOSGSwitchSetup(void) {
}

void jrOSGSwitchSetup::addSwitch(osg::Group* group) {

	//osg::Group* parent = node->getParent(0);
	osg::Switch* osgSwitch = new osg::Switch;
	osgFX::Scribe* osgSwitchOn = new osgFX::Scribe;
	osg::Group* osgSwitchOff = new osg::Group;
	//osg::Group* osgSwitchOn = new osg::Group;

	//std::cout << node->className() << " Name: " << node->getName() << " Lib: " << node->libraryName() << " Parents: " << node->getNumParents() << std::endl;


	osgSwitch->addChild(osgSwitchOn);
	osgSwitch->addChild(osgSwitchOff);


	for (int i = 0; i < group->getNumChildren(); i++) {
		if (group->getChild(i)->asGeode()) {
			std::cout << " Name: " << group->getChild(i)->getName() << std::endl;
			osgSwitchOn->addChild(group->getChild(i));
			osgSwitchOff->addChild(group->getChild(i));
		}
	}

	group->addChild(osgSwitch);
	for (int i = 0; i < osgSwitchOn->getNumChildren(); i++) {
		group->removeChild(osgSwitchOn->getChild(i));
	}

	std::string scribeName("Highlight_");
	scribeName.append(group->getName());

	osgSwitchOn->setName(scribeName);
	osgSwitchOn->setWireframeColor(osg::Vec4(0,1,0,0.5));

	std::string switchName("Switch_");
	switchName.append(group->getName());
	osgSwitch->setName(switchName);

	osgSwitch->setSingleChildOn(0);

	//
	//std::string switchName("Switch_");
	//switchName.append(node->getName());
	//osgSwitch->setName(switchName);

	//parent->addChild(osgSwitch);
	//parent->removeChild(node);
	//osgSwitch->addChild(scribe);
	//osgSwitch->setName(switchName);

	//osgSwitchOff->addChild(node);
	//std::string switchOffName("Switch_Off_");
	//switchOffName.append(node->getName());
	//osgSwitchOff->setName(switchOffName);

	//osgSwitch->addChild(osgSwitchOff);
	//osgSwitch->setSingleChildOn(1);
}