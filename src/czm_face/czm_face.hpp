#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "vec3d/vec3d.h"
#include "edge.hpp"
#include "czm_point.hpp"

namespace czm_face
{

    enum class PointGenerationMethod
    {
        EDGE_ONLY,         // Only generate points on edges
        EDGE_AND_INTERIOR, // Generate points on edges and interior grid
        INTERIOR_ONLY,     // Only generate interior points
        UNIFORM_GRID       // Generate uniform grid points only
    };

    class CzmFace
    {
    public:
        CzmFace() = default;
        ~CzmFace() = default;

        // Prevent copying
        CzmFace(const CzmFace &) = delete;
        CzmFace &operator=(const CzmFace &) = delete;

        // Allow moving
        CzmFace(CzmFace &&) = default;
        CzmFace &operator=(CzmFace &&) = default;

        // Create a face from 3 or 4 vertices
        bool createFace(const std::vector<Vec3D> &vertices);

        // Get face vertices
        const std::vector<Vec3D> &getVertices() const { return vertices_; }

        // Get face edges
        const std::vector<Edge> &getEdges() const { return edges_; }

        // Get face normal
        Vec3D getNormal() const { return normal_; }

        // Calculate face area
        double calculateArea() const;

        // Calculate face center
        Vec3D calculateCenter() const;

        // Calculate face perimeter
        double calculatePerimeter() const;

        // Generate point grid on the face
        std::vector<CZM_Point> generatePointGrid(int pointsPerEdge,
                                                 PointGenerationMethod method = PointGenerationMethod::EDGE_AND_INTERIOR) const;

        // Example method
        std::string getVersion() const;

        // Generate points with equal area distribution
        std::vector<CZM_Point> generateEqualAreaPoints(int numPoints) const;

    private:
        // Calculate face normal
        void calculateNormal();

        // Sort vertices for quadrilateral face
        void sortQuadVertices();

        // Create edges from vertices
        void createEdges();

        // Generate points on edges
        std::vector<CZM_Point> generateEdgePoints(int pointsPerEdge) const;

        // Generate interior grid points
        std::vector<CZM_Point> generateInteriorGridPoints(int pointsPerEdge) const;

        // Generate uniform grid points
        std::vector<CZM_Point> generateUniformGridPoints(int pointsPerEdge) const;

        // Check if a point is inside the face
        bool isPointInside(const Vec3D &point) const;

        std::vector<Vec3D> vertices_; // Face vertices
        std::vector<Edge> edges_;     // Face edges
        Vec3D normal_;                // Face normal
    };

} // namespace czm_face