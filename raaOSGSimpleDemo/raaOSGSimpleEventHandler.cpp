#include "StdAfx.h"

#include <osgViewer/Viewer>
#include <osg/StateSet>

#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "raaOSGPrintVisitor.h"
#include "jrOSGHighlightVisitor.h"
#include "jrOSGHighlighter.h"
#include "jrOSGRotator.h"
#include "jrOSGNodeFinder.h"

#include "raaOSGSimpleEventHandler.h"
#include "jrOSGSwitchSetup.h"
#include "jrOSGRotatorDataType.h"

double rotateAngle;
osg::Node *g_pRoot = 0;
osg::ref_ptr<jrOSGRotatorDataType> g_pRotatorData = 0;

raaOSGSimpleEventHandler::raaOSGSimpleEventHandler(osgViewer::Viewer* pViewer) {
	m_mMode = osg::PolygonMode::FILL;
	if (!g_pRoot) {
		jrOSGNodeFinder finder("Body_Rotator");
		finder.traverse(*(pViewer->getScene()->getSceneData()));
		g_pRoot = finder.getNode();
		g_pRotatorData = dynamic_cast<jrOSGRotatorDataType*> (g_pRoot->getUserData());
	}
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
				g_pRotatorData->bodyConfig->rotateLeft = true;
					  }
					  return true;
			case 's':
			case 'S': {
				g_pRotatorData->bodyConfig->rotateRight = true;
					  }
					  return true;
			case 'q':
			case 'Q': {
				g_pRotatorData->upperArmConfig->rotateLeft = true;
					  }
					  return true;
			case 'w':
			case 'W': {
				g_pRotatorData->upperArmConfig->rotateRight = true;
					  }
					  return true;
			case 'g':
			case 'G': {

				jrOSGNodeFinder finder("Switch_Hand2_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(2);

					  }
					  return true;
			case 'h':
			case 'H': {

				jrOSGNodeFinder finder("Switch_Hand3_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(2);

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
			case '4': {
				g_pRotatorData->animate(0, g_pRotatorData->bodyConfig);
				g_pRotatorData->animate(0, g_pRotatorData->upperArmConfig);
				g_pRotatorData->animate(0, g_pRotatorData->lowerArmConfig);
					  }
					  return true;
			case '5': {
				g_pRotatorData->animate(0.5, g_pRotatorData->bodyConfig);
				g_pRotatorData->animate(-0.6, g_pRotatorData->upperArmConfig);
				g_pRotatorData->animate(0.5, g_pRotatorData->lowerArmConfig);
					  }
					  return true;
			case '6': {

				for (int i = 0; i < 6; i++) {
					g_pRotatorData->recordedAnimateCoords[i] = g_pRotatorData->configs[i]->rotateAngle;
				}
					  }
					  return true;
			case '7': {
				for (int i = 0; i < 6; i++) {
					g_pRotatorData->animate(g_pRotatorData->recordedAnimateCoords[i], g_pRotatorData->configs[i]);
				}
					  }
					  return true;
			case '8': {
				for (int i = 0; i < 6; i++) {
					g_pRotatorData->animate(g_pRotatorData->configs[i]->undoAnimateAngle, g_pRotatorData->configs[i]);
				}
					  }
					  return true;
			case '9': {
				std::ofstream file;
				//time_t t = time(0);
				//std::stringstream ss;
				//ss << t;
				//std::string filename = ss.str();
				std::string filename = "test";
				filename.append(".txt");
				file.open(filename);
				std::cout << filename << std::endl;

				for (int i = 0; i < 6; i++) {
					file << g_pRotatorData->configs[i]->rotateAngle << ",";
				}

				file << "";
				file.close();
					  }
					  return true;
			case '0': {
				std::ofstream file;
				std::string filename = "test";
				filename.append(".txt");
				file.open(filename);
				std::cout << filename << std::endl;

				

				for (int i = 0; i < 6; i++) {
					file << g_pRotatorData->configs[i]->rotateAngle << ",";
				}

				file << "";
				file.close();
					  }
					  return true;
			}
		}
		else if (pViewer && ea.getEventType() == osgGA::GUIEventAdapter::KEYUP) {
			switch(ea.getKey()) {
			case 'a':
			case 'A': 
			case 's':
			case 'S': {
				jrOSGNodeFinder finder("Switch_Body_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

					  }
					  return true;
			case 'q':
			case 'Q': 
			case 'w':
			case 'W': {
				jrOSGNodeFinder finder("Switch_UpperArm_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

					  }
					  return true;
			case 'd':
			case 'D': {

				jrOSGNodeFinder finder("Switch_LowerArm_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

					  }
					  return true;
			case 'f':
			case 'F': {

				jrOSGNodeFinder finder("Switch_Hand1_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

					  }
					  return true;
			case 'g':
			case 'G': {

				jrOSGNodeFinder finder("Switch_Hand2_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

					  }
					  return true;
			case 'h':
			case 'H': {

				jrOSGNodeFinder finder("Switch_Hand3_Rotator");
				finder.traverse(*(pViewer->getScene()->getSceneData()));
				osg::Node* node = finder.getNode();

				osg::Switch* osgSwitch = dynamic_cast<osg::Switch*>(node);

				osgSwitch->setSingleChildOn(0);

					  }
					  return true;
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
