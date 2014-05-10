#pragma once

#include <osg/PolygonMode>
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>

class raaOSGSimpleEventHandler: public osgGA::GUIEventHandler
{
public:
	raaOSGSimpleEventHandler(osgViewer::Viewer* pViewer);
	virtual ~raaOSGSimpleEventHandler(void);

	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);

protected:
	osg::PolygonMode::Mode m_mMode;

	osg::PolygonMode::Mode progressMode();

};

