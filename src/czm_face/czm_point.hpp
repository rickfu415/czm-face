#pragma once

#include "vec3d/vec3d.h"
#include "edge.hpp"

namespace czm_face
{

    enum class PointType
    {
        EDGE_POINT,    // Point on edge
        INTERIOR_POINT // Point inside face
    };

    class CZM_Point
    {
    public:
        CZM_Point() = default;
        CZM_Point(const Vec3D &position, PointType type);
        ~CZM_Point() = default;

        // Allow copying
        CZM_Point(const CZM_Point &) = default;
        CZM_Point &operator=(const CZM_Point &) = default;

        // Allow moving
        CZM_Point(CZM_Point &&) = default;
        CZM_Point &operator=(CZM_Point &&) = default;

        // Get point position
        const Vec3D &getPosition() const { return position_; }

        // Get point type
        PointType getType() const { return type_; }

        // Set associated edge (for edge points)
        void setEdge(const Edge *edge) { edge_ = edge; }

        // Get associated edge (for edge points)
        const Edge *getEdge() const { return edge_; }

    private:
        Vec3D position_;             // Point position
        PointType type_;             // Point type (edge or interior)
        const Edge *edge_ = nullptr; // Associated edge (for edge points)
    };

} // namespace czm_face