#include "StdAfx.h"

#include <osgViewer/Viewer>
#include <osg/StateSet>
#include <osg/Matrixd>
#include <osgDB/WriteFile>

#include <osgManipulator/TabBoxDragger>
#include <osgManipulator/TabBoxTrackballDragger>
#include <osgManipulator/TabPlaneDragger>
#include <osgManipulator/TabPlaneTrackballDragger>
#include <osgManipulator/TrackballDragger>
#include <osgManipulator/Translate1DDragger>
#include <osgManipulator/Translate2DDragger>
#include <osgManipulator/TranslateAxisDragger>

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

osg::Node *bodyRotateNode = 0;
osg::Node *rootNode = 0;
osg::ref_ptr<jrOSGRotatorDataType> rotatorData = 0;

osg::Matrixd *savedProjectionMatrix = 0;

raaOSGSimpleEventHandler::raaOSGSimpleEventHandler(osgViewer::Viewer* pViewer) {
	m_mMode = osg::PolygonMode::FILL;
	if (!bodyRotateNode) {
		jrOSGNodeFinder finder("Body_Rotator");
		finder.traverse(*(pViewer->getScene()->getSceneData()));
		bodyRotateNode = finder.getNode();
		rotatorData = dynamic_cast<jrOSGRotatorDataType*> (bodyRotateNode->getUserData());
		rotatorData->ref();
		bodyRotateNode->ref();
	}
	if (!rootNode) {
		jrOSGNodeFinder rootFinder("Robot_Locator");
		rootFinder.traverse(*(pViewer->getScene()->getSceneData()));
		rootNode = rootFinder.getNode();
		rootNode->ref();
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
				rotatorData->hand3Config->rotateLeft = true;
					  }
					  return true;
			case 'B': {
				rotatorData->hand3Config->rotateRight = true;
					  }
					  return true;
			case 'u': {
				rotatorData->hand2Config->rotateLeft = true;
					  }
					  return true;
			case 'U': {
				rotatorData->hand2Config->rotateRight = true;
					  }
					  return true;
			case 'l': {
				rotatorData->hand1Config->rotateLeft = true;
					  }
					  return true;
			case 'L': {
				rotatorData->hand1Config->rotateRight = true;
					  }
					  return true;
			case 'o': {
				rotatorData->upperArmConfig->rotateLeft = true;
					  }
					  return true;
			case 'O': {
				rotatorData->upperArmConfig->rotateRight = true;
					  }
					  return true;
			case 'j': {
				rotatorData->lowerArmConfig->rotateLeft = true;
					  }
					  return true;
			case 'J': {
				rotatorData->lowerArmConfig->rotateRight = true;
					  }
					  return true;
			case 'k': {
				rotatorData->bodyConfig->rotateLeft = true;
					  }
					  return true;
			case 'K': {
				rotatorData->bodyConfig->rotateRight = true;
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
				rotatorData->animate(0, rotatorData->bodyConfig);
				rotatorData->animate(0, rotatorData->upperArmConfig);
				rotatorData->animate(0, rotatorData->lowerArmConfig);
					  }
					  return true;
			case '5': {
				rotatorData->animate(0.5, rotatorData->bodyConfig);
				rotatorData->animate(-0.6, rotatorData->upperArmConfig);
				rotatorData->animate(0.3, rotatorData->lowerArmConfig);
				rotatorData->animate(-0.7, rotatorData->hand1Config);
				rotatorData->animate(0.7, rotatorData->hand2Config);
				rotatorData->animate(-0.7, rotatorData->hand3Config);
					  }
					  return true;
			case '6': {
				for (int i = 0; i < 6; i++) {
					rotatorData->recordedAnimateCoords[i] = rotatorData->configs[i]->rotateAngle;
				}
					  }
					  return true;
			case '7': {
				for (int i = 0; i < 6; i++) {
					rotatorData->animate(rotatorData->recordedAnimateCoords[i], rotatorData->configs[i]);
				}
					  }
					  return true;
			case '8': {
				for (int i = 0; i < 6; i++) {
					rotatorData->animate(rotatorData->configs[i]->undoAnimateAngle, rotatorData->configs[i]);
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
					file << rotatorData->configs[i]->rotateAngle << ",";
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
					rotatorData->animate(newAngles[i], rotatorData->configs[i]);
				}
					  }
					  return true;
			case '/': {
				osgDB::writeNodeFile(*(rootNode), "jrRobot.osg");
					  }
					  return true;

			case '`': {
				//scene->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);

				//osg::MatrixTransform* selection = new osg::MatrixTransform;
				//selection->addChild(scene);

				osgManipulator::TabPlaneDragger* d = new osgManipulator::TabPlaneDragger();
				d->setupDefaultGeometry();

				rotatorData->bodyConfig->osgSwitch->addChild(d);

				float scale = 40;
				d->setMatrix(osg::Matrix::scale(scale, scale, scale) *
					osg::Matrix::translate(rootNode->getBound().center()));

				d->addTransformUpdating(dynamic_cast<osg::MatrixTransform*>(rotatorData->bodyConfig->rotator));
				// we want the dragger to handle it's own events automatically
				d->setHandleEvents(true);

				// if we don't set an activation key or mod mask then any mouse click on
				// the dragger will activate it, however if do define either of ActivationModKeyMask or
				// and ActivationKeyEvent then you'll have to press either than mod key or the specified key to
				// be able to activate the dragger when you mouse click on it.  Please note the follow allows
				// activation if either the ctrl key or the 'a' key is pressed and held down.
				d->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);
				d->setActivationKeyEvent('a');
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
				rotatorData->hand1Config->osgSwitch->setSingleChildOn(0);
				rotatorData->hand2Config->osgSwitch->setSingleChildOn(0);
				rotatorData->hand3Config->osgSwitch->setSingleChildOn(0);
				rotatorData->upperArmConfig->osgSwitch->setSingleChildOn(0);
				rotatorData->lowerArmConfig->osgSwitch->setSingleChildOn(0);
				rotatorData->bodyConfig->osgSwitch->setSingleChildOn(0);
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
