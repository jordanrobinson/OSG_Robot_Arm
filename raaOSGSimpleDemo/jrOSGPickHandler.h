#pragma once

#include <osgGA\GUIEventHandler>
#include <osgGA\NodeTrackerManipulator>
#include <osgViewer\Viewer>

#include "jrOSGRotatorConfig.h"
#include "jrOSGRotatorDataType.h"

class jrOSGPickHandler : public osgGA::GUIEventHandler {
public:

	jrOSGPickHandler(osgViewer::Viewer* view);
	virtual ~jrOSGPickHandler(void);

	bool jrOSGPickHandler::handle(const osgGA::GUIEventAdapter &ea,	osgGA::GUIActionAdapter &aa,
		osg::Object *, osg::NodeVisitor *);

protected:

	osgViewer::Viewer* viewer;
	jrOSGRotatorConfig* selectedRotator;
	osg::ref_ptr<jrOSGRotatorDataType> g_pRotatorData;
	double lastXPosition;
	double lastYPosition;
	osgGA::NodeTrackerManipulator* trackerManipulator;
};