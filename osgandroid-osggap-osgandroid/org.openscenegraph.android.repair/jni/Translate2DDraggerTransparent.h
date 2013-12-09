#include <osgManipulator/Dragger>
#include <osgManipulator/Projector>

namespace osgManipulator {

/**
 * Dragger for performing 2D translation.
 */
class Translate2DDraggerTransparent : public Dragger
{
    public:

        Translate2DDraggerTransparent();

        Translate2DDraggerTransparent(const osg::Plane& plane);

        META_OSGMANIPULATOR_Object(osgManipulator,Translate2DDraggerTransparent)

        /** Handle pick events on dragger and generate TranslateInLine commands. */
        virtual bool handle(const PointerInfo& pi, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

        /** Setup default geometry for dragger. */
        void setupDefaultGeometry();

        /** Set/Get color for dragger. */
        inline void setColor(const osg::Vec4& color) { _color = color; setMaterialColor(_color,*this); }
        inline const osg::Vec4& getColor() const { return _color; }

        /** Set/Get pick color for dragger. Pick color is color of the dragger when picked.
            It gives a visual feedback to show that the dragger has been picked. */
        inline void setPickColor(const osg::Vec4& color) { _pickColor = color; }
        inline const osg::Vec4& getPickColor() const { return _pickColor; }

    protected:

        virtual ~Translate2DDraggerTransparent();

        osg::ref_ptr< PlaneProjector >  _projector;
        osg::Vec3d                      _startProjectedPoint;

        osg::Vec4                       _color;
        osg::Vec4                       _pickColor;
        //osg::ref_ptr<osg::PolygonOffset> _polygonOffset;
};


}
