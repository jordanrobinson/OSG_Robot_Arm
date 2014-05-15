#include "StdAfx.h"
#include <windows.h>
#include <iostream>
#include <osgFX/Scribe>
#include <osg/Switch>
#include <osg/MatrixTransform>
#include "jrOSGSwitchSetup.h"

jrOSGSwitchSetup::jrOSGSwitchSetup(void) {
}


jrOSGSwitchSetup::~jrOSGSwitchSetup(void) {
}

osg::Switch* jrOSGSwitchSetup::addSwitch(osg::Group* group) {
	osg::Switch* osgSwitch = new osg::Switch;
	osgFX::Scribe* osgSwitchOn = new osgFX::Scribe;
	osgFX::Scribe* osgSwitchError = new osgFX::Scribe;
	osg::Group* osgSwitchOff = new osg::Group;

	osgSwitch->addChild(osgSwitchOff);
	osgSwitch->addChild(osgSwitchOn);
	osgSwitch->addChild(osgSwitchError);

	for (unsigned int i = 0; i < group->getNumChildren(); i++) {
		if (group->getChild(i)->asGeode()) {
			osgSwitchOn->addChild(group->getChild(i));
			osgSwitchOff->addChild(group->getChild(i));
			osgSwitchError->addChild(group->getChild(i));
		}
	}

	group->addChild(osgSwitch);
	for (unsigned int i = 0; i < osgSwitchOn->getNumChildren(); i++) {
		group->removeChild(osgSwitchOn->getChild(i));
	}

	std::string scribeName("Highlight_");
	scribeName.append(group->getName());

	osgSwitchOn->setName(scribeName);
	osgSwitchOn->setWireframeColor(osg::Vec4(0, 0.8, 0, 0.5));

	std::string errorName("Error_Highlight_");
	errorName.append(group->getName());

	osgSwitchError->setName(scribeName);
	osgSwitchError->setWireframeColor(osg::Vec4(0.8, 0, 0, 0.5));

	std::string switchName("Switch_");
	switchName.append(group->getName());
	osgSwitch->setName(switchName);

	std::string switchOffName("Switch_Off_");
	switchOffName.append(group->getName());
	osgSwitchOff->setName(switchOffName);

	osgSwitch->setSingleChildOn(0);
	return osgSwitch;
}
