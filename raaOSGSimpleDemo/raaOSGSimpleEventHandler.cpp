#include "StdAfx.h"

#include <osgViewer/Viewer>
#include <osg/StateSet>
#include <osgDB/WriteFile>

#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "raaOSGPrintVisitor.h"
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
			case 'b': {
				g_pRotatorData->hand3Config->rotateLeft = true;
					  }
					  return true;
			case 'B': {
				g_pRotatorData->hand3Config->rotateRight = true;
					  }
					  return true;
			case 'u': {
				g_pRotatorData->hand2Config->rotateLeft = true;
					  }
					  return true;
			case 'U': {
				g_pRotatorData->hand2Config->rotateRight = true;
					  }
					  return true;
			case 'l': {
				g_pRotatorData->hand1Config->rotateLeft = true;
					  }
					  return true;
			case 'L': {
				g_pRotatorData->hand1Config->rotateRight = true;
					  }
					  return true;
			case 'o': {
				g_pRotatorData->upperArmConfig->rotateLeft = true;
					  }
					  return true;
			case 'O': {
				g_pRotatorData->upperArmConfig->rotateRight = true;
					  }
					  return true;
			case 'j': {
				g_pRotatorData->lowerArmConfig->rotateLeft = true;
					  }
					  return true;
			case 'J': {
				g_pRotatorData->lowerArmConfig->rotateRight = true;
					  }
					  return true;
			case 'k': {
				g_pRotatorData->bodyConfig->rotateLeft = true;
					  }
					  return true;
			case 'K': {
				g_pRotatorData->bodyConfig->rotateRight = true;
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
				g_pRotatorData->animate(0.3, g_pRotatorData->lowerArmConfig);
				g_pRotatorData->animate(-0.7, g_pRotatorData->hand1Config);
				g_pRotatorData->animate(0.7, g_pRotatorData->hand2Config);
				g_pRotatorData->animate(-0.7, g_pRotatorData->hand3Config);
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
				// if we need many we can turn on the timestamp based file saving, but it makes choosing difficult
				std::ofstream file;
				// time_t t = time(0);
				// std::stringstream ss;
				// ss << t;
				// std::string filename = ss.str();
				std::string filename = "savedpos";
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
				std::string line;
				std::ifstream file("savedpos.txt");

				double newAngles[6];

				if (file.is_open()) {
					while (getline(file, line)) {
						std::string input = line;
						std::istringstream ss(input);
						std::string token;

						int i = 0;
						while (std::getline(ss, token, ',')) {
							newAngles[i] = atof(token.c_str());
							i++;
						}
					}
					file.close();
				}
				for (int i = 0; i < 6; i++) {
					g_pRotatorData->animate(newAngles[i], g_pRotatorData->configs[i]);
				}
					  }
					  return true;
			case '/': {
				osgDB::writeNodeFile(*(g_pRoot->getParent(0)), "mech.osgb");
					  }
					  return true;
			}
		} else if (pViewer && ea.getEventType() == osgGA::GUIEventAdapter::KEYUP) {
			switch(ea.getKey()) {
			case 'b':
			case 'B':
			case 'u':
			case 'U':
			case 'l':
			case 'L':
			case 'o':
			case 'O':
			case 'j':
			case 'J':
			case 'k':
			case 'K':
			case '#':
			case '~': {
				g_pRotatorData->hand1Config->osgSwitch->setSingleChildOn(0);
				g_pRotatorData->hand2Config->osgSwitch->setSingleChildOn(0);
				g_pRotatorData->hand3Config->osgSwitch->setSingleChildOn(0);
				g_pRotatorData->upperArmConfig->osgSwitch->setSingleChildOn(0);
				g_pRotatorData->lowerArmConfig->osgSwitch->setSingleChildOn(0);
				g_pRotatorData->bodyConfig->osgSwitch->setSingleChildOn(0);
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
