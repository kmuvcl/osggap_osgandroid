#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/PolygonMode>
#include <osgDB/ReadFile>
#include <osgUtil/LineSegmentIntersector>
#include <osgViewer/Viewer>

#include <osgManipulator/CommandManager>
#include <osgManipulator/TabBoxDragger>
#include <osgManipulator/TabPlaneDragger>
#include <osgManipulator/TabPlaneTrackballDragger>
#include <osgManipulator/TrackballDragger>
#include <osgManipulator/Translate1DDragger>
#include <osgManipulator/Translate2DDragger>
#include <osgManipulator/TranslateAxisDragger>
#include <osgManipulator/ScaleAxisDragger>

#include <vector>

#include "TabBoxDraggerTransparent.h"

#include <jni.h>
USE_SERIALIZER_WRAPPER_LIBRARY(osgManipulator)

class PickHandler : public osgGA::GUIEventHandler
{
public:
	osg::Node* getOrCreateSelectionBox();
	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

protected:
	osg::ref_ptr<osg::MatrixTransform> _selectionBox;
};


class PickModeHandler : public osgGA::GUIEventHandler
{
public:
	enum Modes
	{
		VIEW = 0,
		PICK
	};

	PickModeHandler():
		_mode(VIEW),
			_activeDragger(0),
			isSelect_(0)
		{
			cmdMgr = new osgManipulator::CommandManager;
		}

		osg::Group* addDraggerToScene(osg::Node* scene, const std::string& name);
		osg::Node* getSelectedNode();
		int isSelect();
		virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );

		std::vector<long> nodeAddress;

protected:
	unsigned int _mode;
	osgManipulator::Dragger* _activeDragger;
	osgManipulator::PointerInfo _pointer;
	osg::Node *selectNode;
	int isSelect_;

    // create a command manager
    osg::ref_ptr<osgManipulator::CommandManager> cmdMgr;
};
