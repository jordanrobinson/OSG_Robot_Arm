// raaOSGSimpleDemo.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/Group>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Material>

#include "raaOSGSimpleEventHandler.h"
#include "raaOSGPrintVisitor.h"
#include "jrOSGNodeFinder.h"
#include "jrOSGRotatorDataType.h"
#include "jrOSGRotateCallback.h"
#include "jrOSGPickHandler.h"

const static float csg_AmbCoef = 0.1f;
const static float csg_DiffCoef = 0.8f;
const static float csg_SpecCoef = 1.0f;

osg::Group *g_pRoot = 0;

int main(int argc, char* argv[]) {
	osg::ArgumentParser arguments(&argc, argv);

	g_pRoot = new osg::Group();
	g_pRoot->ref();

	// load model
	g_pRoot->addChild(osgDB::readNodeFiles(arguments));

	// setup viewer
	osgViewer::Viewer viewer;

	// define graphics context
	osg::GraphicsContext::Traits *pTraits = new osg::GraphicsContext::Traits();
	pTraits->x = 20;
	pTraits->y = 20;
	pTraits->width = 600;
	pTraits->height = 480;
	pTraits->windowDecoration = true;
	pTraits->doubleBuffer = true;
	pTraits->sharedContext = 0;
	osg::GraphicsContext *pGC = osg::GraphicsContext::createGraphicsContext(pTraits);

	osgGA::KeySwitchMatrixManipulator* pKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator();
	pKeyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
	pKeyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
	pKeyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
	viewer.setCameraManipulator(pKeyswitchManipulator);

	osg::Camera *pCamera = viewer.getCamera();

	pCamera->setGraphicsContext(pGC);
	pCamera->setViewport(new osg::Viewport(0, 0, pTraits->width, pTraits->height));

	// add the thread model handler -> press 'm'
	viewer.addEventHandler(new osgViewer::ThreadingHandler);

	// add the window size toggle handler -> press 'f'
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);

	// add the stats handler -> press 's'
	viewer.addEventHandler(new osgViewer::StatsHandler);

	// add the record camera path handler
	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);

	// add the LOD Scale handler
	viewer.addEventHandler(new osgViewer::LODScaleHandler);

	// add the screen capture handler -> press 'c'. look for image file in working dir($(osg)\bin)
	viewer.addEventHandler(new osgViewer::ScreenCaptureHandler);

	// add the help handler -> press 'h'
	viewer.addEventHandler(new osgViewer::HelpHandler);

	// set the scene to render
	viewer.setSceneData(g_pRoot);

	viewer.realize();

	// print out the nodes before run
	raaOSGPrintVisitor printer;
	printer.traverse(*(viewer.getScene()->getSceneData()));

	jrOSGNodeFinder finder("Body_Rotator");
	finder.traverse(*(viewer.getScene()->getSceneData()));

	jrOSGRotatorDataType* rotatorData = new jrOSGRotatorDataType(finder.getNode());
	finder.getNode()->setUserData(rotatorData);
	finder.getNode()->setUpdateCallback(new jrOSGRotateCallback);

	viewer.addEventHandler(new raaOSGSimpleEventHandler(&viewer));
	viewer.addEventHandler(new jrOSGPickHandler(&viewer));

	return viewer.run();
}

