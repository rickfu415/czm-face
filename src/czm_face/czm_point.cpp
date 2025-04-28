#include "czm_point.hpp"

namespace czm_face
{

    CZM_Point::CZM_Point(const Vec3D &position, PointType type)
        : position_(position), type_(type)
    {
    }

} // namespace czm_face