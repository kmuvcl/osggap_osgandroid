#include "Translate2DDraggerTransparent.h"
#include <osgManipulator/Translate1DDragger>

namespace osgManipulator {

class TranslatePlaneDraggerTransparent : public CompositeDragger
{
    public:

        TranslatePlaneDraggerTransparent();

        META_OSGMANIPULATOR_Object(osgManipulator,TranslatePlaneDraggerTransparent)

        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        inline void setColor(const osg::Vec4& color) { if (_Translate2DDraggerTransparent.valid()) _Translate2DDraggerTransparent->setColor(color); }

        Translate1DDragger* getTranslate1DDragger() { return _translate1DDragger.get(); }
        Translate2DDraggerTransparent* getTranslate2DDraggerTransparent() { return _Translate2DDraggerTransparent.get(); }

    protected:

        virtual ~TranslatePlaneDraggerTransparent();

        osg::ref_ptr< Translate2DDraggerTransparent >      _Translate2DDraggerTransparent;
        osg::ref_ptr< Translate1DDragger >      _translate1DDragger;
        bool                                    _usingTranslate1DDragger;
};


}
