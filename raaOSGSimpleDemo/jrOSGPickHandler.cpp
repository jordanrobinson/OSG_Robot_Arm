#include "StdAfx.h"

#include <Windows.h>
#include <iostream>
#include <sstream>

#include "jrOSGPickHandler.h"
#include "jrOSGRotatorConfig.h"
#include "jrOSGRotatorDataType.h"

jrOSGPickHandler::jrOSGPickHandler(osgViewer::Viewer* view) {
	viewer = view;
	selectedRotator = 0;
	jrOSGNodeFinder finder("Body_Rotator");
	finder.traverse(*(viewer->getScene()->getSceneData()));
	g_pRotatorData = dynamic_cast<jrOSGRotatorDataType*> (finder.getNode()->getUserData());
	lastXPosition = 0;
	lastYPosition = 0;
}

jrOSGPickHandler::~jrOSGPickHandler(void) {
	unref();
}

bool jrOSGPickHandler::handle(const osgGA::GUIEventAdapter &ea,	osgGA::GUIActionAdapter &aa,
	osg::Object *, osg::NodeVisitor *) {
		if(viewer && selectedRotator && ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN) {
			switch(ea.getKey()) {
			case '#': {
				selectedRotator->rotateRight = true;
					  }
					  return true;
			case '~': {
				selectedRotator->rotateLeft = true;
					  }
					  return true;
			}
		}
		else if (viewer && selectedRotator && ea.getModKeyMask() == 4) { // should be MOD_KEY_CTRL but that gives the wrong code, 12 instead of 4

			if (ea.getYnormalized() > lastYPosition) {
				selectedRotator->rotateLeft = true;
			}
			else if (ea.getYnormalized() < lastYPosition) {
				selectedRotator->rotateRight = true;
			}
			lastXPosition = ea.getXnormalized();
			lastYPosition = ea.getYnormalized();
		}
		else if (ea.getModKeyMask() == 0 && selectedRotator && viewer) {
			selectedRotator->osgSwitch->setSingleChildOn(0);
		}

		switch(ea.getEventType()) {
		case(osgGA::GUIEventAdapter::PUSH):	{
			osgUtil::LineSegmentIntersector::Intersections intersections;

			std::string gdlist="";
			float x = ea.getX();
			float y = ea.getY();
			std::ostringstream os;
			if (viewer->computeIntersections(x, y, intersections)) {
				for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
					hitr != intersections.end(); ++hitr) {
						if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty())) {
							// the geodes are identified by name.
							os << "Object \"" << hitr->nodePath.back()->getName() << "\"" << std::endl;
							if (hitr->nodePath.back()->getName().find("Hand3") != std::string::npos) {
								selectedRotator = g_pRotatorData->hand3Config;
								return true;
							} else if (hitr->nodePath.back()->getName().find("Hand2") != std::string::npos) {
								selectedRotator = g_pRotatorData->hand2Config;
								return true;
							} else if (hitr->nodePath.back()->getName().find("Hand1") != std::string::npos) {
								selectedRotator = g_pRotatorData->hand1Config;
								return true;
							} else if (hitr->nodePath.back()->getName().find("ForeArm") != std::string::npos) {
								selectedRotator = g_pRotatorData->lowerArmConfig;
								return true;
							} else if (hitr->nodePath.back()->getName().find("BaseArm") != std::string::npos) {
								selectedRotator = g_pRotatorData->upperArmConfig;
								return true;
							} else if (hitr->nodePath.back()->getName().find("Base") != std::string::npos) {
								selectedRotator = g_pRotatorData->bodyConfig;
								return true;
							}
						} else if (hitr->drawable.valid()) {
							os << "Object \"" << hitr->drawable->className() << "\"" << std::endl;
						}
				}
			}
			std::cout << os.str() << std::endl;
			return true;
											}
		default:
			return false;
		}

}
