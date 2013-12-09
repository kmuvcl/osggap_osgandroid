
#include "TabPlaneDraggerTransparent.h"

namespace osgManipulator {

class TabBoxDraggerTransparent : public CompositeDragger
{
    public:

        TabBoxDraggerTransparent();

        META_OSGMANIPULATOR_Object(osgManipulator,TabBoxDraggerTransparent)

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        void setPlaneColor(const osg::Vec4& color);

    protected:

        virtual ~TabBoxDraggerTransparent();

        std::vector< osg::ref_ptr< TabPlaneDraggerTransparent > > _planeDraggers;
};


}
