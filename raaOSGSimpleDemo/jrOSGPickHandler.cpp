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

}

bool jrOSGPickHandler::handle(const osgGA::GUIEventAdapter &ea,	osgGA::GUIActionAdapter &aa,
	osg::Object *, osg::NodeVisitor *) {
		if(viewer && selectedRotator && ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN) {
			switch(ea.getKey())
			{
			case '#': 
				{
					selectedRotator->rotateRight = true;
					std::cout << selectedRotator->rotator->getName() << std::endl;
					//std::cout << "hit" << std::endl;
				}
				return true;
			case '~': 
				{
					selectedRotator->rotateLeft = true;
					std::cout << selectedRotator->rotator->getName() << std::endl;
					//std::cout << "hit" << std::endl;
				}
				return true;
			}
		}

		switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::PUSH):
			{
				osgUtil::LineSegmentIntersector::Intersections intersections;

				std::string gdlist="";
				float x = ea.getX();
				float y = ea.getY();
				std::ostringstream os;
				if (viewer->computeIntersections(x,y,intersections))
				{
					for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
						hitr != intersections.end(); ++hitr) {
							if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty())) {
								// the geodes are identified by name.
								os<<"Object \"" << hitr->nodePath.back()->getName() << "\""<<std::endl;
								if (hitr->nodePath.back()->getName().find("Hand3") != std::string::npos) {
									std::cout << "found!" << '\n';
									selectedRotator = g_pRotatorData->hand3Config;
								}
							}
							else if (hitr->drawable.valid()) {
								os<<"Object \""<<hitr->drawable->className()<<"\""<<std::endl;
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
