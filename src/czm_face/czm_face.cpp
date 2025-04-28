#include "czm_face.hpp"
#include <stdexcept>
#include <cmath>
#include <random>

namespace czm_face
{

    std::string CzmFace::getVersion() const
    {
        return "0.1.0";
    }

    bool CzmFace::createFace(const std::vector<Vec3D> &vertices)
    {
        // Check if we have 3 or 4 vertices
        if (vertices.size() != 3 && vertices.size() != 4)
        {
            return false;
        }

        // Store vertices
        vertices_ = vertices;

        // For quadrilateral, sort vertices
        if (vertices_.size() == 4)
        {
            sortQuadVertices();
        }

        // Create edges
        createEdges();

        // Calculate face normal
        calculateNormal();

        return true;
    }

    void CzmFace::createEdges()
    {
        edges_.clear();
        for (size_t i = 0; i < vertices_.size(); ++i)
        {
            size_t next = (i + 1) % vertices_.size();
            edges_.emplace_back(vertices_[i], vertices_[next]);
        }
    }

    void CzmFace::sortQuadVertices()
    {
        if (vertices_.size() != 4)
            return;

        // Calculate face center
        Vec3D center = calculateCenter();

        // Sort vertices based on their angle with negative x-axis
        std::sort(vertices_.begin(), vertices_.end(),
                  [&center](const Vec3D &a, const Vec3D &b)
                  {
                      // Calculate vectors from center to points
                      double ax = a.comp[0] - center.comp[0];
                      double ay = a.comp[1] - center.comp[1];
                      double bx = b.comp[0] - center.comp[0];
                      double by = b.comp[1] - center.comp[1];

                      // Calculate angles with negative x-axis
                      double angleA = std::atan2(ay, -ax);
                      double angleB = std::atan2(by, -bx);

                      return angleA < angleB;
                  });
    }

    void CzmFace::calculateNormal()
    {
        if (vertices_.size() < 3)
        {
            normal_ = Vec3D(0, 0, 0);
            return;
        }

        // Calculate normal using first three vertices
        Vec3D v1 = vertices_[1] - vertices_[0];
        Vec3D v2 = vertices_[2] - vertices_[0];

        // Cross product to get normal
        normal_ = v1.cross(v2);

        // Normalize the normal vector
        double magnitude = std::sqrt(normal_.comp[0] * normal_.comp[0] +
                                     normal_.comp[1] * normal_.comp[1] +
                                     normal_.comp[2] * normal_.comp[2]);
        if (magnitude > 0)
        {
            normal_ = normal_ / magnitude;
        }
    }

    double CzmFace::calculateArea() const
    {
        if (vertices_.size() < 3)
        {
            return 0.0;
        }

        if (vertices_.size() == 3)
        {
            // Triangle area = 1/2 * |(v1-v0) × (v2-v0)|
            Vec3D v1 = vertices_[1] - vertices_[0];
            Vec3D v2 = vertices_[2] - vertices_[0];
            Vec3D cross = v1.cross(v2);
            double magnitude = std::sqrt(cross.comp[0] * cross.comp[0] +
                                         cross.comp[1] * cross.comp[1] +
                                         cross.comp[2] * cross.comp[2]);
            return 0.5 * magnitude;
        }
        else
        {
            // Quadrilateral area = sum of two triangle areas
            // First triangle: v0, v1, v2
            Vec3D v1 = vertices_[1] - vertices_[0];
            Vec3D v2 = vertices_[2] - vertices_[0];
            Vec3D cross1 = v1.cross(v2);
            double magnitude1 = std::sqrt(cross1.comp[0] * cross1.comp[0] +
                                          cross1.comp[1] * cross1.comp[1] +
                                          cross1.comp[2] * cross1.comp[2]);
            double area1 = 0.5 * magnitude1;

            // Second triangle: v0, v2, v3
            Vec3D v3 = vertices_[3] - vertices_[0];
            Vec3D cross2 = v2.cross(v3);
            double magnitude2 = std::sqrt(cross2.comp[0] * cross2.comp[0] +
                                          cross2.comp[1] * cross2.comp[1] +
                                          cross2.comp[2] * cross2.comp[2]);
            double area2 = 0.5 * magnitude2;

            return area1 + area2;
        }
    }

    double CzmFace::calculatePerimeter() const
    {
        double perimeter = 0.0;
        for (const auto &edge : edges_)
        {
            perimeter += edge.length();
        }
        return perimeter;
    }

    Vec3D CzmFace::calculateCenter() const
    {
        if (vertices_.size() < 3)
        {
            return Vec3D(0, 0, 0);
        }

        if (vertices_.size() == 3)
        {
            // Triangle center = (v0 + v1 + v2) / 3
            return (vertices_[0] + vertices_[1] + vertices_[2]) / 3.0;
        }
        else
        {
            // Quadrilateral center = (v0 + v1 + v2 + v3) / 4
            return (vertices_[0] + vertices_[1] + vertices_[2] + vertices_[3]) / 4.0;
        }
    }

    std::vector<CZM_Point> CzmFace::generatePointGrid(int pointsPerEdge, PointGenerationMethod method) const
    {
        std::vector<CZM_Point> points;

        switch (method)
        {
        case PointGenerationMethod::EDGE_ONLY:
            return generateEdgePoints(pointsPerEdge);

        case PointGenerationMethod::INTERIOR_ONLY:
            return generateInteriorGridPoints(pointsPerEdge);

        case PointGenerationMethod::UNIFORM_GRID:
            return generateUniformGridPoints(pointsPerEdge);

        case PointGenerationMethod::EDGE_AND_INTERIOR:
        default:
            auto edgePoints = generateEdgePoints(pointsPerEdge);
            auto interiorPoints = generateInteriorGridPoints(pointsPerEdge);
            points.insert(points.end(), edgePoints.begin(), edgePoints.end());
            points.insert(points.end(), interiorPoints.begin(), interiorPoints.end());
            return points;
        }
    }

    std::vector<CZM_Point> CzmFace::generateEdgePoints(int pointsPerEdge) const
    {
        std::vector<CZM_Point> points;
        for (const auto &edge : edges_)
        {
            Vec3D start = edge.getStart();
            Vec3D end = edge.getEnd();

            for (int i = 0; i < pointsPerEdge; ++i)
            {
                double t = static_cast<double>(i) / (pointsPerEdge - 1);
                Vec3D position;
                position.comp[0] = start.comp[0] + (end.comp[0] - start.comp[0]) * t;
                position.comp[1] = start.comp[1] + (end.comp[1] - start.comp[1]) * t;
                position.comp[2] = start.comp[2] + (end.comp[2] - start.comp[2]) * t;

                CZM_Point point(position, PointType::EDGE_POINT);
                point.setEdge(&edge);
                points.push_back(std::move(point));
            }
        }
        return points;
    }

    std::vector<CZM_Point> CzmFace::generateInteriorGridPoints(int pointsPerEdge) const
    {
        std::vector<CZM_Point> points;

        // Calculate total area
        double totalArea = calculateArea();

        // Calculate number of interior points based on edge points
        // For a square, if we have n points per edge, we want (n-2)^2 interior points
        int numInteriorPoints = (pointsPerEdge - 2) * (pointsPerEdge - 2);

        // Calculate area per point
        double areaPerPoint = totalArea / numInteriorPoints;

        // Calculate grid spacing based on area per point
        double spacing = std::sqrt(areaPerPoint);

        // Calculate bounding box
        double minX = vertices_[0].comp[0], maxX = vertices_[0].comp[0];
        double minY = vertices_[0].comp[1], maxY = vertices_[0].comp[1];
        double minZ = vertices_[0].comp[2], maxZ = vertices_[0].comp[2];

        for (const auto &v : vertices_)
        {
            minX = std::min(minX, v.comp[0]);
            maxX = std::max(maxX, v.comp[0]);
            minY = std::min(minY, v.comp[1]);
            maxY = std::max(maxY, v.comp[1]);
            minZ = std::min(minZ, v.comp[2]);
            maxZ = std::max(maxZ, v.comp[2]);
        }

        // Calculate number of points in each direction
        int numPointsX = static_cast<int>(std::ceil((maxX - minX) / spacing));
        int numPointsY = static_cast<int>(std::ceil((maxY - minY) / spacing));

        // Adjust spacing to ensure exact number of points
        double spacingX = (maxX - minX) / (numPointsX - 1);
        double spacingY = (maxY - minY) / (numPointsY - 1);

        // Generate interior grid points
        for (int i = 1; i < numPointsX - 1; ++i)
        {
            for (int j = 1; j < numPointsY - 1; ++j)
            {
                Vec3D point(minX + i * spacingX, minY + j * spacingY, minZ);
                if (isPointInside(point))
                {
                    CZM_Point interiorPoint(point, PointType::INTERIOR_POINT);
                    points.push_back(std::move(interiorPoint));
                }
            }
        }

        return points;
    }

    std::vector<CZM_Point> CzmFace::generateUniformGridPoints(int pointsPerEdge) const
    {
        std::vector<CZM_Point> points;

        // Calculate bounding box
        double minX = vertices_[0].comp[0], maxX = vertices_[0].comp[0];
        double minY = vertices_[0].comp[1], maxY = vertices_[0].comp[1];
        double minZ = vertices_[0].comp[2], maxZ = vertices_[0].comp[2];

        for (const auto &v : vertices_)
        {
            minX = std::min(minX, v.comp[0]);
            maxX = std::max(maxX, v.comp[0]);
            minY = std::min(minY, v.comp[1]);
            maxY = std::max(maxY, v.comp[1]);
            minZ = std::min(minZ, v.comp[2]);
            maxZ = std::max(maxZ, v.comp[2]);
        }

        // Calculate grid spacing based on edge length
        double edgeLength = edges_[0].length();
        double spacing = edgeLength / (pointsPerEdge - 1);

        // Generate uniform grid points
        for (double x = minX; x <= maxX; x += spacing)
        {
            for (double y = minY; y <= maxY; y += spacing)
            {
                Vec3D point(x, y, minZ);
                if (isPointInside(point))
                {
                    CZM_Point gridPoint(point, PointType::INTERIOR_POINT);
                    points.push_back(std::move(gridPoint));
                }
            }
        }

        return points;
    }

    std::vector<CZM_Point> CzmFace::generateEqualAreaPoints(int numPoints) const
    {
        std::vector<CZM_Point> points;
        if (vertices_.size() < 3 || numPoints <= 0)
            return points;

        // Calculate total area
        double totalArea = calculateArea();
        double areaPerPoint = totalArea / numPoints;

        // Calculate bounding box
        double minX = vertices_[0].comp[0], maxX = vertices_[0].comp[0];
        double minY = vertices_[0].comp[1], maxY = vertices_[0].comp[1];
        double minZ = vertices_[0].comp[2], maxZ = vertices_[0].comp[2];

        for (const auto &v : vertices_)
        {
            minX = std::min(minX, v.comp[0]);
            maxX = std::max(maxX, v.comp[0]);
            minY = std::min(minY, v.comp[1]);
            maxY = std::max(maxY, v.comp[1]);
            minZ = std::min(minZ, v.comp[2]);
            maxZ = std::max(maxZ, v.comp[2]);
        }

        // Calculate initial grid spacing based on area per point
        double spacing = std::sqrt(areaPerPoint);

        // Calculate number of points in each direction
        int numPointsX = static_cast<int>(std::ceil((maxX - minX) / spacing));
        int numPointsY = static_cast<int>(std::ceil((maxY - minY) / spacing));

        // Adjust spacing to ensure exact number of points
        double spacingX = (maxX - minX) / (numPointsX - 1);
        double spacingY = (maxY - minY) / (numPointsY - 1);

        // Generate initial grid points
        std::vector<Vec3D> initialPoints;
        for (int i = 0; i < numPointsX; ++i)
        {
            for (int j = 0; j < numPointsY; ++j)
            {
                Vec3D point(minX + i * spacingX, minY + j * spacingY, minZ);
                if (isPointInside(point))
                {
                    initialPoints.push_back(point);
                }
            }
        }

        // If we have too many points, randomly select the desired number
        if (initialPoints.size() > numPoints)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::shuffle(initialPoints.begin(), initialPoints.end(), gen);
            initialPoints.resize(numPoints);
        }

        // Convert to CZM_Points
        for (const auto &point : initialPoints)
        {
            points.emplace_back(point, PointType::INTERIOR_POINT);
        }

        return points;
    }

    bool CzmFace::isPointInside(const Vec3D &point) const
    {
        if (vertices_.size() < 3)
            return false;

        // Project point onto face plane
        Vec3D toPoint = point - vertices_[0];
        double dot = toPoint.dot(normal_);
        Vec3D projectedPoint;
        projectedPoint.comp[0] = point.comp[0] - normal_.comp[0] * dot;
        projectedPoint.comp[1] = point.comp[1] - normal_.comp[1] * dot;
        projectedPoint.comp[2] = point.comp[2] - normal_.comp[2] * dot;

        // Check if point is inside using ray casting
        int intersections = 0;
        for (const auto &edge : edges_)
        {
            Vec3D edgeStart = edge.getStart();
            Vec3D edgeEnd = edge.getEnd();

            // Check if ray intersects edge
            if ((edgeStart.comp[1] > projectedPoint.comp[1]) != (edgeEnd.comp[1] > projectedPoint.comp[1]))
            {
                double x = (edgeEnd.comp[0] - edgeStart.comp[0]) *
                               (projectedPoint.comp[1] - edgeStart.comp[1]) /
                               (edgeEnd.comp[1] - edgeStart.comp[1]) +
                           edgeStart.comp[0];
                if (projectedPoint.comp[0] < x)
                {
                    intersections++;
                }
            }
        }

        return (intersections % 2) == 1;
    }

} // namespace czm_face