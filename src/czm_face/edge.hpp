#pragma once

#include "vec3d/vec3d.h"

namespace czm_face
{

    class Edge
    {
    public:
        Edge() = default;
        Edge(const Vec3D &start, const Vec3D &end);
        ~Edge() = default;

        // Prevent copying
        Edge(const Edge &) = delete;
        Edge &operator=(const Edge &) = delete;

        // Allow moving
        Edge(Edge &&) = default;
        Edge &operator=(Edge &&) = default;

        // Get start and end points
        const Vec3D &getStart() const { return start_; }
        const Vec3D &getEnd() const { return end_; }

        // Calculate edge length
        double length() const;

        // Calculate edge direction vector
        Vec3D direction() const;

        // Check if two edges are equal (same points, regardless of order)
        bool operator==(const Edge &other) const;

    private:
        Vec3D start_; // Start point
        Vec3D end_;   // End point
    };

} // namespace czm_face