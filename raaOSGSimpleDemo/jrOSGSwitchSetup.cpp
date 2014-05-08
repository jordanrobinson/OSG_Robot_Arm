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

void jrOSGSwitchSetup::addSwitch(osg::Node* node) {

	osg::Group* parent = node->getParent(0);
	osg::Switch* osgSwitch = new osg::Switch;
	osgFX::Scribe* scribe = new osgFX::Scribe;
	osg::Group* osgSwitchOff = new osg::Group;

	std::cout << node->className() << " Name: " << node->getName() << " Lib: " << node->libraryName() << " Parents: " << node->getNumParents() << std::endl;

	std::string scribeName("Highlight_");
	scribeName.append(node->getName());

	scribe->setName(scribeName);
	scribe->setWireframeColor(osg::Vec4(0,1,0,0.5));
	scribe->addChild(node);
	
	std::string switchName("Switch_");
	switchName.append(node->getName());

	parent->addChild(osgSwitch);
	parent->removeChild(node);
	osgSwitch->addChild(scribe);
	osgSwitch->setName(switchName);

	osgSwitchOff->addChild(node);
	std::string switchOffName("Switch_Off_");
	switchOffName.append(node->getName());
	osgSwitchOff->setName(switchOffName);

	osgSwitch->addChild(osgSwitchOff);
	osgSwitch->setSingleChildOn(1);
}