#pragma once

#include <osg\Node>

class jrOSGSwitchSetup {
public:
	jrOSGSwitchSetup(void);
	virtual ~jrOSGSwitchSetup(void);

	virtual void addSwitch(osg::Node* node);
};
