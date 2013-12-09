#include "TabPlaneDraggerTransparent.h"
#include <osgManipulator/AntiSquish>

#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/CullFace>
#include <osg/AutoTransform>

using namespace osgManipulator;

namespace
{

osg::Node* createHandleNode(Scale2DDragger* cornerScaleDragger, float handleScaleFactor, bool twosided)
{
        osg::Vec3Array* vertices = new osg::Vec3Array(6);
        (*vertices)[0] = osg::Vec3(cornerScaleDragger->getTopLeftHandlePosition()[0],0.0,cornerScaleDragger->getTopLeftHandlePosition()[1]);
        (*vertices)[1] = osg::Vec3(cornerScaleDragger->getBottomLeftHandlePosition()[0],0.0,cornerScaleDragger->getBottomLeftHandlePosition()[1]);
        (*vertices)[2] = osg::Vec3(cornerScaleDragger->getBottomRightHandlePosition()[0],0.0,cornerScaleDragger->getBottomRightHandlePosition()[1]);
        (*vertices)[3] = osg::Vec3(cornerScaleDragger->getBottomRightHandlePosition()[0],0.0,cornerScaleDragger->getBottomRightHandlePosition()[1]);
        (*vertices)[4] = osg::Vec3(cornerScaleDragger->getTopRightHandlePosition()[0],0.0,cornerScaleDragger->getTopRightHandlePosition()[1]);
        (*vertices)[5] = osg::Vec3(cornerScaleDragger->getTopLeftHandlePosition()[0],0.0,cornerScaleDragger->getTopLeftHandlePosition()[1]);

    osg::Geometry* geometry = new osg::Geometry();
        geometry->setVertexArray(vertices);
		geometry->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, 6));

    osg::Vec3Array* normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0,1.0,0.0));
    geometry->setNormalArray(normals);
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec4Array* colors = new osg::Vec4Array(1);
	(*colors)[0].set(0.0f,1.0f,0.0f,0.0f);
	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

    osg::Geode* geode = new osg::Geode;
    geode->setName("Dragger Handle");
    geode->addDrawable(geometry);

    if (!twosided)
    {
        osg::CullFace* cullface = new osg::CullFace;
        cullface->setMode(osg::CullFace::FRONT);
        geode->getOrCreateStateSet()->setAttribute(cullface, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
        geode->getOrCreateStateSet()->setMode(GL_CULL_FACE, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    }

    geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		geode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    return geode;
}

osg::Node* createHandleScene(const osg::Vec3& pos, osg::Node* handleNode, float handleScaleFactor)
{
    osg::AutoTransform *at = new osg::AutoTransform;
    at->setPosition(pos);
    at->setPivotPoint(pos * handleScaleFactor);
    at->setAutoScaleToScreen(true);
    at->addChild(handleNode);

    AntiSquish* as = new AntiSquish;
    as->setPivot(pos);
    as->addChild(at);

    return as;
}

void createCornerScaleDraggerGeometry(Scale2DDragger* cornerScaleDragger, osg::Node* handleNode, float handleScaleFactor)
{
}

void createEdgeScaleDraggerGeometry(Scale1DDragger* horzEdgeScaleDragger, Scale1DDragger* vertEdgeScaleDragger,
                                    osg::Node* handleNode, float handleScaleFactor)
{
}

void createTranslateDraggerGeometry(Scale2DDragger* cornerScaleDragger, TranslatePlaneDraggerTransparent* translateDragger)
{
    // Create a polygon.
    {
        osg::Geode* geode = new osg::Geode;
        osg::Geometry* geometry = new osg::Geometry();
        
        osg::Vec3Array* vertices = new osg::Vec3Array(6);
        (*vertices)[0] = osg::Vec3(cornerScaleDragger->getTopLeftHandlePosition()[0],0.0,cornerScaleDragger->getTopLeftHandlePosition()[1]);
        (*vertices)[1] = osg::Vec3(cornerScaleDragger->getBottomLeftHandlePosition()[0],0.0,cornerScaleDragger->getBottomLeftHandlePosition()[1]);
        (*vertices)[2] = osg::Vec3(cornerScaleDragger->getBottomRightHandlePosition()[0],0.0,cornerScaleDragger->getBottomRightHandlePosition()[1]);
        (*vertices)[3] = osg::Vec3(cornerScaleDragger->getBottomRightHandlePosition()[0],0.0,cornerScaleDragger->getBottomRightHandlePosition()[1]);
        (*vertices)[4] = osg::Vec3(cornerScaleDragger->getTopRightHandlePosition()[0],0.0,cornerScaleDragger->getTopRightHandlePosition()[1]);
        (*vertices)[5] = osg::Vec3(cornerScaleDragger->getTopLeftHandlePosition()[0],0.0,cornerScaleDragger->getTopLeftHandlePosition()[1]);

        geometry->setVertexArray(vertices);
		geometry->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, 6));

        osg::Vec3Array* normals = new osg::Vec3Array;
        normals->push_back(osg::Vec3(0.0,1.0,0.0));
        geometry->setNormalArray(normals);
        geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec4Array* colors = new osg::Vec4Array(1);
	(*colors)[0].set(0.0f,0.0f,1.0f,0.0f);
	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

        geode->addDrawable(geometry);

        //osg::PolygonMode* polymode = new osg::PolygonMode;
		//polymode->setMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);
		//geode->getOrCreateStateSet()->setAttributeAndModes(polymode,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);

		/* is ne ? */
//		osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc;
//		blendFunc->setFunction( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//
//		geode->getOrCreateStateSet()->setAttributeAndModes( blendFunc );
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		geode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		//geometry->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

		translateDragger->getTranslate2DDraggerTransparent()->addChild(geode);
	}

}

}

TabPlaneDraggerTransparent::TabPlaneDraggerTransparent() : _handleScaleFactor(20.0)
{
	_cornerScaleDragger = new Scale2DDragger(Scale2DDragger::SCALE_WITH_OPPOSITE_HANDLE_AS_PIVOT);
	addChild(_cornerScaleDragger.get());
	addDragger(_cornerScaleDragger.get());

	_horzEdgeScaleDragger = new Scale1DDragger(Scale1DDragger::SCALE_WITH_OPPOSITE_HANDLE_AS_PIVOT);
	addChild(_horzEdgeScaleDragger.get());
	addDragger(_horzEdgeScaleDragger.get());

	_vertEdgeScaleDragger = new Scale1DDragger(Scale1DDragger::SCALE_WITH_OPPOSITE_HANDLE_AS_PIVOT);
	addChild(_vertEdgeScaleDragger.get());
	addDragger(_vertEdgeScaleDragger.get());

	_translateDragger = new TranslatePlaneDraggerTransparent();
	_translateDragger->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 0.0f));
	addChild(_translateDragger.get());
    addDragger(_translateDragger.get());
 
    setParentDragger(getParentDragger());
}
       
TabPlaneDraggerTransparent::~TabPlaneDraggerTransparent()
{
}

bool TabPlaneDraggerTransparent::handle(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    if (ea.getButtonMask() & osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) return false;

    // Check if the dragger node is in the nodepath.
    if (!pointer.contains(this)) return false;

    // Since the translate plane and the handleNode lie on the same plane the hit could've been on either one. But we
    // need to handle the scaling draggers before the translation. Check if the node path has the scaling nodes else 
    // check for the scaling nodes in next hit.
    if (_cornerScaleDragger->handle(pointer, ea, aa))
        return true;
    if (_horzEdgeScaleDragger->handle(pointer, ea, aa))
        return true;
    if (_vertEdgeScaleDragger->handle(pointer, ea, aa))
        return true;
    
    PointerInfo nextPointer(pointer);
    nextPointer.next();
    
    while (!nextPointer.completed())
    {
        if (_cornerScaleDragger->handle(nextPointer, ea, aa))
            return true;
        if (_horzEdgeScaleDragger->handle(nextPointer, ea, aa))
            return true;
        if (_vertEdgeScaleDragger->handle(nextPointer, ea, aa))
            return true;

        nextPointer.next();
    }

    if (_translateDragger->handle(pointer, ea, aa))
        return true;

    return false;
}

void TabPlaneDraggerTransparent::setupDefaultGeometry(bool twoSidedHandle)
{
    osg::ref_ptr<osg::Node> handleNode = createHandleNode(_cornerScaleDragger.get(), _handleScaleFactor, twoSidedHandle);

    createTranslateDraggerGeometry(_cornerScaleDragger.get(), _translateDragger.get());
}


