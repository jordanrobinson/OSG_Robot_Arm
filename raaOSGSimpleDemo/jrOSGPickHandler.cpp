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

				//if(g_KeyswitchManipulator.valid()) {
				//	viewer->setCameraManipulator( g_KeyswitchManipulator, false );
				//	g_KeyswitchManipulator.release();
				//} else {
				//	g_KeyswitchManipulator = dynamic_cast<osgGA::KeySwitchMatrixManipulator*>(viewer->getCameraManipulator());
				viewer->setCameraManipulator(nullptr, false);
				//}
					  }
					  return true;
			case 'a': {





				//selectedRotator->rotateLeft = true;

				//if(g_KeyswitchManipulator.valid()) {
				//	viewer->setCameraManipulator( g_KeyswitchManipulator, false );
				//	g_KeyswitchManipulator.release();
				//} else {
				//	g_KeyswitchManipulator = dynamic_cast<osgGA::KeySwitchMatrixManipulator*>(viewer->getCameraManipulator());
				//viewer->setCameraManipulator(nullptr, false);
				//}
					  }
					  return true;
			}
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
