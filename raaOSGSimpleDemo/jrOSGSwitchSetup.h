#pragma once

#include <osg\Group>

class jrOSGSwitchSetup: osg::Referenced {
public:
	jrOSGSwitchSetup(void);
	virtual ~jrOSGSwitchSetup(void);

	virtual osg::Switch* addSwitch(osg::Group* group);
};
