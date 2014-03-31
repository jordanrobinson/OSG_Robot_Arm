#include "StdAfx.h"

#include <osgViewer/Viewer>
#include <osg/StateSet>

#include "raaOSGPrintVisitor.h"
#include "jrOSGHighlightVisitor.h"
#include "jrOSGHighlighter.h"
#include "jrOSGRotator.h"
#include "jrOSGNodeFinder.h"

#include "raaOSGSimpleEventHandler.h"

bool highlighted;
double rotateAngle;

raaOSGSimpleEventHandler::raaOSGSimpleEventHandler() {
	m_mMode = osg::PolygonMode::FILL;
}

raaOSGSimpleEventHandler::~raaOSGSimpleEventHandler(void) {
}

bool raaOSGSimpleEventHandler::handle(const osgGA::GUIEventAdapter &ea,	osgGA::GUIActionAdapter &aa,
	osg::Object *, osg::NodeVisitor *) {
		osgViewer::Viewer *pViewer = dynamic_cast<osgViewer::Viewer*>(aa.asView());

		if(pViewer && ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN) {
			switch(ea.getKey()) {
			case 'a':
			case 'A': {
				//jrOSGHighlightVisitor highlighter;
				//highlighter.traverse(*(pViewer->getScene()->getSceneData()));


				jrOSGNodeFinder finder("UpperArm_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				if (!highlighted) {
					jrOSGHighlighter highlighter;
					highlighter.highlight(node, "testHighlight");
					highlighted = true;
				}

				jrOSGRotator rotator;

				jrOSGNodeFinder transFinder("testRotate");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* transform = finder.getNode();

				if (transform == NULL) {
					rotateAngle = 0.1;
					rotator.rotate(node, "testRotate", rotateAngle);
				}
				else {
					rotateAngle += 0.1;
					rotator.rotate(transform, rotateAngle);
				}

					  }
					  return true;
			case 'i':
			case 'I': {
				raaOSGPrintVisitor printer;

				printer.traverse(*(pViewer->getScene()->getSceneData()));
					  }
					  return true;
			case 'p':
			case 'P':
				pViewer->getSceneData()->getOrCreateStateSet()->setAttributeAndModes(
					new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, progressMode()),
					osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
				return true;
			}
		}
		else if (pViewer && ea.getEventType() == osgGA::GUIEventAdapter::KEYUP && highlighted) {
			switch(ea.getKey()) {
			case 'a':
			case 'A': {
				osg::Node* node;
				jrOSGNodeFinder finder("testHighlight");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				node = finder.getNode();

				jrOSGHighlighter highlighter;
				highlighter.unhighlight(node);
				highlighted = false;
					  }
			}
		}
		return false;
}

osg::PolygonMode::Mode raaOSGSimpleEventHandler::progressMode() {
	switch(m_mMode) {
	case osg::PolygonMode::POINT:
		return m_mMode = osg::PolygonMode::LINE;
	case osg::PolygonMode::LINE:
		return m_mMode = osg::PolygonMode::FILL;
	default:
		return m_mMode = osg::PolygonMode::POINT;
	}
}
