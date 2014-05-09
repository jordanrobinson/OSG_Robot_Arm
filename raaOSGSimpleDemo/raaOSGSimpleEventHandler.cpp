#include "StdAfx.h"

#include <osgViewer/Viewer>
#include <osg/StateSet>

#include <iostream>

#include "raaOSGPrintVisitor.h"
#include "jrOSGHighlightVisitor.h"
#include "jrOSGHighlighter.h"
#include "jrOSGRotator.h"
#include "jrOSGNodeFinder.h"

#include "raaOSGSimpleEventHandler.h"
#include "jrOSGSwitchSetup.h"
#include "jrOSGRotatorDataType.h"


bool highlighted;
double rotateAngle;
osg::Node *g_pRoot = 0;

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


				if (!g_pRoot) {
					jrOSGNodeFinder finder("Body_Rotator");
					finder.traverse(*(pViewer->getScene()->getSceneData()));
					g_pRoot = finder.getNode();
				}

				osg::ref_ptr<jrOSGRotatorDataType> rotatorData = dynamic_cast<jrOSGRotatorDataType*> (g_pRoot->getUserData());
				rotatorData->rotateLeft = true;


				//osg::Node* node = finder.getNode();

				//jrOSGHighlighter highlighter;


				//if (!highlighted && rotateAngle < 0.8) {

				//	highlighter.highlightGreen(node, "testHighlight");
				//	highlighted = true;
				//}
				//if (rotateAngle > 0.8 && !highlighted) {
				//	//if (highlighted) {
				//	//	highlighter.unhighlight(node);
				//	//}

				//	highlighter.highlightRed(node, "testHighlight");
				//	highlighted = true;
				//	rotateAngle = 0.8;

				//}

				//jrOSGRotator rotator;

				//jrOSGNodeFinder transFinder("testRotate");

				//transFinder.traverse(*(pViewer->getScene()->getSceneData()));
				//osg::Node* transform = transFinder.getNode();

				//std::cout << transform << std::endl;

				//if (transform == NULL) {
				//	rotateAngle = 0.05;
				//	rotator.rotate(node, "testRotate", rotateAngle);
				//}
				//else {
				//	rotateAngle += 0.05;
				//	rotator.rotate(node, rotateAngle);
				//}
				//std::cout << "angle currently: " << rotateAngle << std::endl;
					  }
					  return true;
			case 'i':
			case 'I': {
				raaOSGPrintVisitor printer;

				printer.traverse(*(pViewer->getScene()->getSceneData()));
					  }
					  return true;
			case 's':
			case 'S': {


				if (!g_pRoot) {
					jrOSGNodeFinder finder("Body_Rotator");
					finder.traverse(*(pViewer->getScene()->getSceneData()));
					g_pRoot = finder.getNode();
				}

				osg::ref_ptr<jrOSGRotatorDataType> rotatorData = dynamic_cast<jrOSGRotatorDataType*> (g_pRoot->getUserData());
				rotatorData->rotateRight = true;
					  }
					  return true;
			case 'd':
			case 'D': {

				jrOSGNodeFinder finder("Switch_Hand1_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

					  }
					  return true;
			case 'f':
			case 'F': {

				jrOSGNodeFinder finder("Switch_LowerArm_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

					  }
					  return true;
			case 'g':
			case 'G': {

				jrOSGNodeFinder finder("Switch_UpperArm_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

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
		else if (pViewer && ea.getEventType() == osgGA::GUIEventAdapter::KEYUP) {
			switch(ea.getKey()) {
			case 'd':
			case 'D': {

				jrOSGNodeFinder finder("Switch_Hand1_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(1);

					  }
					  return true;
			case 'f':
			case 'F': {

				jrOSGNodeFinder finder("Switch_LowerArm_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(1);

					  }
					  return true;
			case 'g':
			case 'G': {

				jrOSGNodeFinder finder("Switch_UpperArm_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(1);

					  }
					  return true;
			case 'a':
			case 'A': {
				//osg::Node* node;
				//jrOSGNodeFinder finder("testHighlight");
				//finder.traverse(*(pViewer->getScene()->getSceneData()));
				//node = finder.getNode();

				//jrOSGHighlighter highlighter;
				//highlighter.unhighlight(node);
				//highlighted = false;
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
