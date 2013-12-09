

#include "TranslatePlaneDraggerTransparent.h"

#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/CullFace>
#include <osg/AutoTransform>

using namespace osgManipulator;

TranslatePlaneDraggerTransparent::TranslatePlaneDraggerTransparent() : _usingTranslate1DDragger(false)
{
    _Translate2DDraggerTransparent = new Translate2DDraggerTransparent();
    _Translate2DDraggerTransparent->setColor(osg::Vec4(0.0f, 0.0f, 0.0f, 0.0f));
	//_Translate2DDraggerTransparent->
    addChild(_Translate2DDraggerTransparent.get());
    addDragger(_Translate2DDraggerTransparent.get());

    _translate1DDragger = new Translate1DDragger(osg::Vec3(0.0f,0.0f,0.0f),osg::Vec3(0.0f,1.0f,0.0f));
    _translate1DDragger->setCheckForNodeInNodePath(false);
    addChild(_translate1DDragger.get());
    addDragger(_translate1DDragger.get());

    setParentDragger(getParentDragger());
}
       
TranslatePlaneDraggerTransparent::~TranslatePlaneDraggerTransparent()
{
}

bool TranslatePlaneDraggerTransparent::handle(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    // Check if the dragger node is in the nodepath.
    if (!pointer.contains(this)) return false;

    if ((ea.getButtonMask() & osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON) &&
        ea.getEventType() == osgGA::GUIEventAdapter::PUSH)
        _usingTranslate1DDragger = true;

    bool handled = false;
    if (_usingTranslate1DDragger)
    {
        if (_translate1DDragger->handle(pointer, ea, aa))
            handled = true;
    }
    else
    {
        if (_Translate2DDraggerTransparent->handle(pointer, ea, aa))
            handled = true;
    }

    if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
        _usingTranslate1DDragger = false;

    return handled;
}

void TranslatePlaneDraggerTransparent::setupDefaultGeometry()
{
    // Create a polygon.
    {
        osg::Geode* geode = new osg::Geode;
        osg::Geometry* geometry = new osg::Geometry();

        osg::Vec3Array* vertices = new osg::Vec3Array(6);
        (*vertices)[0] = osg::Vec3(-0.5,0.0,0.5);
        (*vertices)[1] = osg::Vec3(-0.5,0.0,-0.5);
        (*vertices)[2] = osg::Vec3(0.5,0.0,-0.5);
        (*vertices)[3] = osg::Vec3(0.5,0.0,-0.5);
        (*vertices)[4] = osg::Vec3(0.5,0.0,0.5);
        (*vertices)[5] = osg::Vec3(-0.5,0.0,0.5);
		
        geometry->setVertexArray(vertices);
		geometry->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, 6));

        osg::Vec3Array* normals = new osg::Vec3Array;
        normals->push_back(osg::Vec3(0.0,1.0,0.0));
        geometry->setNormalArray(normals);
        geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

        geode->addDrawable(geometry);

        //osg::PolygonMode* polymode = new osg::PolygonMode;
		//polymode->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);
		//geode->getOrCreateStateSet()->setAttributeAndModes(polymode,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);

		geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

		/* is nessesary? */
//		osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
//		blendFunc->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//
//		geode->getOrCreateStateSet()->setAttributeAndModes( blendFunc );
		geode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		_Translate2DDraggerTransparent->addChild(geode);

	}
}
