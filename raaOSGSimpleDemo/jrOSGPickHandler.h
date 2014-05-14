#pragma once

#include <osgGA\GUIEventHandler>
#include <osgViewer\Viewer>

#include "jrOSGRotatorConfig.h"
#include "jrOSGRotatorDataType.h"

class jrOSGPickHandler : public osgGA::GUIEventHandler {
public:

	jrOSGPickHandler(osgViewer::Viewer* view);
	virtual ~jrOSGPickHandler(void);

	bool jrOSGPickHandler::handle(const osgGA::GUIEventAdapter &ea,	osgGA::GUIActionAdapter &aa,
		osg::Object *, osg::NodeVisitor *);

	//bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

	//virtual void pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea);

	//void setLabel(const std::string& name)
	//{
	//	if (_updateText.get()) _updateText->setText(name);
	//}

protected:

	osgViewer::Viewer* viewer;
	jrOSGRotatorConfig* selectedRotator;
	osg::ref_ptr<jrOSGRotatorDataType> g_pRotatorData;

	//osg::ref_ptr<osgText::Text>  _updateText;
};