#pragma once

#include <osg\Group>

class jrOSGSwitchSetup {
public:
	jrOSGSwitchSetup(void);
	virtual ~jrOSGSwitchSetup(void);

	virtual void addSwitch(osg::Group* group);
};
