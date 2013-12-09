
#include <jni.h>
#include <android/log.h>

#include "JNIUtils.h"

#include <osgGA/TrackballManipulator>
#include <osg/Matrixf>
#include <osg/Node>

#include <string>

#include "JNIosgGUIEventHandler.h"

osg::Node* PickHandler::getOrCreateSelectionBox()
{
	if ( !_selectionBox ) {
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		geode->addDrawable( new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 1.001f)) );

		_selectionBox = new osg::MatrixTransform;
		_selectionBox->setNodeMask( 0x1 );
		_selectionBox->addChild( geode.get() );

		osg::StateSet* ss = _selectionBox->getOrCreateStateSet();

		ss->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
		ss->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE));
	}
	return _selectionBox.get();

}

bool PickHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
	if ( ea.getEventType()!=osgGA::GUIEventAdapter::RELEASE 
		|| ea.getButton()!=osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )

		return false;

	osgViewer::Viewer* viewer =	dynamic_cast<osgViewer::Viewer*>(&aa);

	if ( viewer ) {
		osg::ref_ptr<osgUtil::LineSegmentIntersector>
			intersector = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());

		osgUtil::IntersectionVisitor iv( intersector.get() );

		iv.setTraversalMask( ~0x1 );

		viewer->getCamera()->accept( iv );

		if ( intersector->containsIntersections() )	{
			osgUtil::LineSegmentIntersector::Intersection result = 
				*(intersector->getIntersections().begin());

			osg::BoundingBox bb = result.drawable->getBound();

			osg::Vec3 worldCenter = bb.center() *
				osg::computeLocalToWorld(result.nodePath);

			_selectionBox->setMatrix(
				osg::Matrix::scale(bb.xMax()-bb.xMin(),
				bb.yMax()-bb.yMin(),
				bb.zMax()-bb.zMin()) *
				osg::Matrix::translate(worldCenter) );
		}
	}
	return false;
}

osgManipulator::Dragger* createDragger(const std::string& name)
{
    osgManipulator::Dragger* dragger = 0;
    if ("TabPlaneDragger" == name)
    {
		printf("TabPlaneDragger\n");
        osgManipulator::TabPlaneDragger* d = new osgManipulator::TabPlaneDragger();
        d->setupDefaultGeometry();
        dragger = d;
    }
    else if ("TabPlaneTrackballDragger" == name)
    {
		printf("TabPlaneTrackballDragger\n");
        osgManipulator::TabPlaneTrackballDragger* d = new osgManipulator::TabPlaneTrackballDragger();
        d->setupDefaultGeometry();
        dragger = d;
    }
    else if ("TrackballDragger" == name)
    {
		printf("TrackballDragger\n");
        osgManipulator::TrackballDragger* d = new osgManipulator::TrackballDragger();
        d->setupDefaultGeometry();
        dragger = d;
    }
    else if ("Translate1DDragger" == name)
    {
		printf("Translate1DDragger\n");
        osgManipulator::Translate1DDragger* d = new osgManipulator::Translate1DDragger();
        d->setupDefaultGeometry();
        dragger = d;
    }
    else if ("Translate2DDragger" == name)
    {
		printf("Translate2DDragger\n");
        osgManipulator::Translate2DDragger* d = new osgManipulator::Translate2DDragger();
        d->setupDefaultGeometry();
        dragger = d;
    }
    else if ("TranslateAxisDragger" == name)
    {
		printf("TranslateAxisDragger\n");
        osgManipulator::TranslateAxisDragger* d = new osgManipulator::TranslateAxisDragger();
        d->setupDefaultGeometry();
        dragger = d;
    }
	else if ("ScaleAxisDragger" == name)
	{
		printf("ScaleAxisDragger\n");
		osgManipulator::ScaleAxisDragger* d = new osgManipulator::ScaleAxisDragger();
		d->setupDefaultGeometry();
		dragger = d;
	}
	else if ("TabBoxDragger" == name)
	{
		printf("TabBoxDragger\n");
        osgManipulator::TabBoxDragger* d = new osgManipulator::TabBoxDragger();
        d->setupDefaultGeometry();
		d->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		d->setPlaneColor(osg::Vec4(0,0,0,0));
        dragger = d;
	}
    else
    {
		printf("TabBoxDraggerTransparent\n");
		TabBoxDraggerTransparent* d = new TabBoxDraggerTransparent();
		d->setupDefaultGeometry();
		d->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		d->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		d->setPlaneColor(osg::Vec4(0,0,0,0));
        dragger = d;
    }

    return dragger;
}

osg::Group* PickModeHandler::addDraggerToScene(osg::Node* scene, const std::string& name)
{
	//scene->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
	//scene->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osgManipulator::Selection* selection = new osgManipulator::Selection;
	selection->addChild(scene);

	osgManipulator::Dragger* dragger = createDragger(name);

	osg::Group* root = new osg::Group;
	root->addChild(dragger);
	root->addChild(selection);

		float scale = scene->getBound().radius() * 1.4;
		dragger->setMatrix(osg::Matrix::scale(scale, scale, scale) *
				osg::Matrix::translate(scene->getBound().center()));
		cmdMgr->connect(*dragger, *selection);

	selection->ref();
	dragger->ref();
	root->ref();

	return root;

}

osg::Node* PickModeHandler::getSelectedNode()
{
	__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","getSelectedNode");
	return selectNode;
}
int PickModeHandler::isSelect()
{
	return isSelect_;
}

bool PickModeHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
	__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","handle start");
	__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","ea: %p, aa: %p",&ea,&aa);
	osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
	if (!view) return false;

	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
		{
			__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","PUSH");
			osgUtil::LineSegmentIntersector::Intersections intersections;

			_pointer.reset();

			if (view->computeIntersections(ea.getX(),ea.getY(),intersections))
			{
				_pointer.setCamera(view->getCamera());
				_pointer.setMousePosition(ea.getX(), ea.getY());

				osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();

				//selected node
				__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","selected node");
				selectNode = dynamic_cast<osg::Node*>(hitr->nodePath[3]);
				__android_log_print(ANDROID_LOG_ERROR,"PickModeHandler","%p",selectNode);
				isSelect_ = 1;

				for(hitr;
					hitr != intersections.end();
					++hitr)
				{
					_pointer.addIntersection(hitr->nodePath, hitr->getLocalIntersectPoint());
				}

				for (osg::NodePath::iterator itr = _pointer._hitList.front().first.begin();
					itr != _pointer._hitList.front().first.end();
					++itr)
				{
					osgManipulator::Dragger* dragger = dynamic_cast<osgManipulator::Dragger*>(*itr);
					if (dragger)
					{
						dragger->handle(_pointer, ea, aa);
						_activeDragger = dragger;
						break;
					}
				}
			}
		}
	case osgGA::GUIEventAdapter::DRAG:
	case osgGA::GUIEventAdapter::RELEASE:
		{
			if (_activeDragger)
			{
				_pointer._hitIter = _pointer._hitList.begin();
				_pointer.setCamera(view->getCamera());
				//_pointer.setMousePosition(ea.getX(), ea.getY());
				_pointer.setMousePosition(ea.getX(), -ea.getY());

				_activeDragger->handle(_pointer, ea, aa);

			}
			break;
		}

	default:
		break;
	}

	if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
	{
		__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","RELEASE");
		_activeDragger = 0;
		_pointer.reset();

		isSelect_ = 0;
	}

	__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","handle end");

	return true;

}

extern "C"
{
JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_util_PickHandler_nativeCreatePickHandler(
		JNIEnv *, jclass) {
		PickHandler* picker = new PickHandler;
		picker->ref();
		return reinterpret_cast<jlong> (picker);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_util_PickHandler_nativeDisposePickHandler(
		JNIEnv *, jclass, jlong cptr) {
	PickHandler* p=  reinterpret_cast<PickHandler*>(cptr);
	p->unref();	
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_util_PickHandler_nativeGetOrCreateSelectionBox(
		JNIEnv *, jclass, jlong cptr) {
	PickHandler* p=  reinterpret_cast<PickHandler*>(cptr);
	return reinterpret_cast<jlong>(p->getOrCreateSelectionBox());	
}



JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_util_PickModeHandler_nativeCreatePickModeHandler(
		JNIEnv *, jclass) {
		PickModeHandler* picker = new PickModeHandler;
		picker->ref();
		return reinterpret_cast<jlong> (picker);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_util_PickModeHandler_nativeDisposePickModeHandler(
		JNIEnv *, jclass, jlong cptr) {
		PickModeHandler* p=  reinterpret_cast<PickModeHandler*>(cptr);
		p->unref();
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_util_PickModeHandler_nativeAddDraggerToScene(
		JNIEnv *env, jclass, jlong cptr, jlong n_cptr, jstring name) {
	PickModeHandler* p=  reinterpret_cast<PickModeHandler*>(cptr);
	osg::Node* n=  reinterpret_cast<osg::Node*>(n_cptr);
	jlong l = reinterpret_cast<jlong>(p->addDraggerToScene(n, jstring2string(env,name)));

	__android_log_print(ANDROID_LOG_ERROR,"PickModeHandler","write node address.. ");
	p->nodeAddress.push_back(l);
	__android_log_print(ANDROID_LOG_ERROR,"PickModeHandler","write node address done.. %ld",reinterpret_cast<long>(n));
//	osg::MatrixTransform* mt = new osg::MatrixTransform();
//	mt->addChild(n);
//	mt->ref();
	return l;
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_util_PickModeHandler_nativeGetSelectedNode(
		JNIEnv *, jclass, jlong cptr) {
	PickModeHandler* p=  reinterpret_cast<PickModeHandler*>(cptr);
	if(p == NULL)
		__android_log_print(ANDROID_LOG_ERROR,"PickModeHandler","PickModeHandler pointer is null");
	long l = reinterpret_cast<long>(p->getSelectedNode());

	__android_log_print(ANDROID_LOG_ERROR,"PickModeHandler","search selected node address.. %ld",l);
	int i;
	for(i=0; i<p->nodeAddress.size(); i++) {
		__android_log_print(ANDROID_LOG_ERROR,"PickModeHandler","%ld",p->nodeAddress.at(i));
		if(p->nodeAddress.at(i) == l) {
			__android_log_print(ANDROID_LOG_ERROR,"PickModeHandler","node address find.. ");
			return l;
		}
	}
	return 0;
//
//	if(l == 0)
//		__android_log_print(ANDROID_LOG_ERROR,"PickModeHandler","long is 0");

}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_util_PickModeHandler_nativeChangeScaleAndRotateSelectedNode(
		JNIEnv *env, jclass, jlong cptr, jfloat scale, jfloat degree, jint x, jint y) {
	PickModeHandler* p=  reinterpret_cast<PickModeHandler*>(cptr);

	osg::MatrixTransform *transMatForm = new osg::MatrixTransform();
	osg::Matrixd transMat;

	transMatForm = dynamic_cast<osg::MatrixTransform*>(p->getSelectedNode()->getParent(0));
	transMat = transMatForm->getMatrix();

	osg::Vec3f farFromCenter = transMatForm->getBound().center();

	osg::Matrixd tmpMat;

	tmpMat.makeTranslate(-farFromCenter.x(),-farFromCenter.y(),0);
	transMat *= tmpMat;
	tmpMat.makeScale(1+scale,1+scale,1+scale);
	transMat *= tmpMat;
	tmpMat.makeRotate(osg::DegreesToRadians(degree),0,0,1);
	transMat *= tmpMat;
	tmpMat.makeTranslate(farFromCenter.x(),farFromCenter.y(),0);
	transMat *= tmpMat;

	transMatForm->setMatrix(transMat);
}



//JNIEXPORT void JNICALL Java_org_openscenegraph_osg_util_PickModeHandler_nativeChangeScaleAndRotateSelectedNode(
//		JNIEnv *env, jclass, jlong cptr, jfloat scale, jfloat degree, jint x, jint y) {
//	PickModeHandler* p=  reinterpret_cast<PickModeHandler*>(cptr);
//
//	osg::MatrixTransform *transMatForm = new osg::MatrixTransform();
//	osg::RefMatrixf *transMat = new osg::RefMatrixf();
//
//	transMatForm = dynamic_cast<osg::MatrixTransform*>(p->getSelectedNode()->getParent(0));
//	transMat->makeScale(osg::Vec3(1+scale,1+scale,1+scale));
//	transMat->postMultRotate(osg::Quat(osg::DegreesToRadians(degree), osg::Vec3d(0,0,1)));
//	transMatForm->setMatrix(*transMat);
//
//	transMatForm->ref();
//	transMat->ref();
//}

JNIEXPORT jint JNICALL Java_org_openscenegraph_osg_util_PickModeHandler_nativeIsSelect(
		JNIEnv *env, jclass, jlong cptr) {
	__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","Java_org_openscenegraph_osg_util_PickModeHandler_nativeIsSelect");
	PickModeHandler* p=  reinterpret_cast<PickModeHandler*>(cptr);
	__android_log_print(ANDROID_LOG_INFO,"PickModeHandler","PickModeHandler* p=  reinterpret_cast<PickModeHandler*>(cptr);");

	return p->isSelect();
}




JNIEXPORT long JNICALL Java_org_openscenegraph_osg_util_TrackballManipulator_nativeCreateTrackballManipulator(JNIEnv *, jclass)
{
	osgGA::TrackballManipulator *map = new osgGA::TrackballManipulator();
	map->setCenter(osg::Vec3(0,0,0));
	map->ref();
	return reinterpret_cast<jlong> (map);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_util_TrackballManipulator_nativeDispose(JNIEnv *, jclass, jlong cptr)
{
	osgGA::TrackballManipulator* map=  reinterpret_cast<osgGA::TrackballManipulator*>(cptr);
	map->unref();
}

JNIEXPORT long JNICALL Java_org_openscenegraph_osg_util_TrackballManipulator_nativeGetMatrix(JNIEnv *, jclass, jlong cptr)
{
	osgGA::TrackballManipulator* map=  reinterpret_cast<osgGA::TrackballManipulator*>(cptr);
    osg::RefMatrixf* mat = new osg::RefMatrixf();

    mat->set(map->getInverseMatrix());

    mat->ref();
	return reinterpret_cast<jlong> (mat);
}

}
