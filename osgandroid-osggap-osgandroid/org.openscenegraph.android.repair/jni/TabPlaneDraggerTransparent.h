#include "TranslatePlaneDraggerTransparent.h"
#include <osgManipulator/Scale2DDragger>
#include <osgManipulator/Scale1DDragger>

using namespace osgManipulator;

class TabPlaneDraggerTransparent : public CompositeDragger
{
    public:

        TabPlaneDraggerTransparent();

        META_OSGMANIPULATOR_Object(osgManipulator,TabPlaneDraggerTransparent)

        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry(bool twoSidedHandle = true);

        void setPlaneColor(const osg::Vec4& color) { _translateDragger->setColor(color); }

    protected:

        virtual ~TabPlaneDraggerTransparent();

        osg::ref_ptr< TranslatePlaneDraggerTransparent >   _translateDragger;
        osg::ref_ptr< Scale2DDragger >          _cornerScaleDragger;
        osg::ref_ptr< Scale1DDragger >          _horzEdgeScaleDragger;
        osg::ref_ptr< Scale1DDragger >          _vertEdgeScaleDragger;

        float                                   _handleScaleFactor;
};
