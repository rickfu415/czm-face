#include "core.hpp"
#include "czm_face/czm_face.hpp"
#include <iostream>
#include <iomanip>

void testCzmFace()
{
    std::cout << "\nTesting CzmFace functionality:\n";

    // Create a triangle face
    std::vector<Vec3D> triangleVertices = {
        Vec3D(0, 0, 0),
        Vec3D(1, 0, 0),
        Vec3D(0, 1, 0)};

    czm_face::CzmFace triangleFace;
    if (triangleFace.createFace(triangleVertices))
    {
        std::cout << "Triangle face created successfully\n";
        std::cout << "Area: " << triangleFace.calculateArea() << std::endl;
        std::cout << "Perimeter: " << triangleFace.calculatePerimeter() << std::endl;
        Vec3D center = triangleFace.calculateCenter();
        std::cout << "Center: (" << center.comp[0] << ", "
                  << center.comp[1] << ", "
                  << center.comp[2] << ")" << std::endl;
        Vec3D normal = triangleFace.getNormal();
        std::cout << "Normal: (" << normal.comp[0] << ", "
                  << normal.comp[1] << ", "
                  << normal.comp[2] << ")" << std::endl;

        // Generate points on edges
        int pointsPerEdge = 7;
        auto points = triangleFace.generatePointGrid(pointsPerEdge);

        std::cout << "\nGenerated " << points.size() << " points ("
                  << pointsPerEdge << " points per edge):\n";
        std::cout << std::fixed << std::setprecision(3);
        for (size_t i = 0; i < points.size(); ++i)
        {
            const auto &point = points[i];
            const Vec3D &pos = point.getPosition();
            std::cout << "Point " << i + 1 << " at ("
                      << std::setw(6) << pos.comp[0] << ", "
                      << std::setw(6) << pos.comp[1] << ", "
                      << std::setw(6) << pos.comp[2] << ") - ";
            if (point.getType() == czm_face::PointType::EDGE_POINT)
            {
                const auto *edge = point.getEdge();
                std::cout << "Edge point (edge length: " << edge->length() << ")";
            }
            else
            {
                std::cout << "Interior point";
            }
            std::cout << std::endl;
        }
    }

    // Create a quadrilateral face with unordered vertices
    std::vector<Vec3D> quadVertices = {
        Vec3D(1, 1, 0), // top-right
        Vec3D(0, 0, 0), // bottom-left
        Vec3D(0, 1, 0), // top-left
        Vec3D(1, 0, 0)  // bottom-right
    };

    std::cout << "\nOriginal quadrilateral vertices order:\n";
    for (const auto &v : quadVertices)
    {
        std::cout << "(" << v.comp[0] << ", " << v.comp[1] << ", " << v.comp[2] << ") ";
    }
    std::cout << std::endl;

    czm_face::CzmFace quadFace;
    if (quadFace.createFace(quadVertices))
    {
        std::cout << "\nQuadrilateral face created successfully\n";
        std::cout << "Sorted vertices order:\n";
        for (const auto &v : quadFace.getVertices())
        {
            std::cout << "(" << v.comp[0] << ", " << v.comp[1] << ", " << v.comp[2] << ") ";
        }
        std::cout << std::endl;

        std::cout << "Area: " << quadFace.calculateArea() << std::endl;
        std::cout << "Perimeter: " << quadFace.calculatePerimeter() << std::endl;
        Vec3D center = quadFace.calculateCenter();
        std::cout << "Center: (" << center.comp[0] << ", "
                  << center.comp[1] << ", "
                  << center.comp[2] << ")" << std::endl;
        Vec3D normal = quadFace.getNormal();
        std::cout << "Normal: (" << normal.comp[0] << ", "
                  << normal.comp[1] << ", "
                  << normal.comp[2] << ")" << std::endl;

        // Generate points on edges
        int pointsPerEdge = 7;
        auto points = quadFace.generatePointGrid(pointsPerEdge);

        std::cout << "\nGenerated " << points.size() << " points ("
                  << pointsPerEdge << " points per edge):\n";
        std::cout << std::fixed << std::setprecision(3);
        for (size_t i = 0; i < points.size(); ++i)
        {
            const auto &point = points[i];
            const Vec3D &pos = point.getPosition();
            std::cout << "Point " << i + 1 << " at ("
                      << std::setw(6) << pos.comp[0] << ", "
                      << std::setw(6) << pos.comp[1] << ", "
                      << std::setw(6) << pos.comp[2] << ") - ";
            if (point.getType() == czm_face::PointType::EDGE_POINT)
            {
                const auto *edge = point.getEdge();
                std::cout << "Edge point (edge length: " << edge->length() << ")";
            }
            else
            {
                std::cout << "Interior point";
            }
            std::cout << std::endl;
        }
    }
}

void testPointGeneration()
{
    std::cout << "\nTesting Point Generation Methods:\n";

    // Create a square face
    std::vector<Vec3D> squareVertices = {
        Vec3D(0, 0, 0), // bottom-left
        Vec3D(1, 0, 0), // bottom-right
        Vec3D(1, 1, 0), // top-right
        Vec3D(0, 1, 0)  // top-left
    };

    czm_face::CzmFace squareFace;
    if (squareFace.createFace(squareVertices))
    {
        std::cout << "Square face created successfully\n";
        std::cout << "Area: " << squareFace.calculateArea() << std::endl;
        std::cout << "Perimeter: " << squareFace.calculatePerimeter() << std::endl;

        // Test different point generation methods
        int pointsPerEdge = 5;
        std::cout << "\nTesting with " << pointsPerEdge << " points per edge:\n";

        // 1. Edge only points
        auto edgePoints = squareFace.generatePointGrid(pointsPerEdge,
                                                       czm_face::PointGenerationMethod::EDGE_ONLY);
        std::cout << "\n1. Edge Only Points (" << edgePoints.size() << " points):\n";
        std::cout << std::fixed << std::setprecision(3);
        for (size_t i = 0; i < edgePoints.size(); ++i)
        {
            const auto &point = edgePoints[i];
            const Vec3D &pos = point.getPosition();
            std::cout << "Point " << i + 1 << " at ("
                      << std::setw(6) << pos.comp[0] << ", "
                      << std::setw(6) << pos.comp[1] << ", "
                      << std::setw(6) << pos.comp[2] << ") - ";
            if (point.getType() == czm_face::PointType::EDGE_POINT)
            {
                const auto *edge = point.getEdge();
                std::cout << "Edge point (edge length: " << edge->length() << ")";
            }
            else
            {
                std::cout << "Interior point";
            }
            std::cout << std::endl;
        }

        // 2. Interior only points
        auto interiorPoints = squareFace.generatePointGrid(pointsPerEdge,
                                                           czm_face::PointGenerationMethod::INTERIOR_ONLY);
        std::cout << "\n2. Interior Only Points (" << interiorPoints.size() << " points):\n";
        for (size_t i = 0; i < interiorPoints.size(); ++i)
        {
            const auto &point = interiorPoints[i];
            const Vec3D &pos = point.getPosition();
            std::cout << "Point " << i + 1 << " at ("
                      << std::setw(6) << pos.comp[0] << ", "
                      << std::setw(6) << pos.comp[1] << ", "
                      << std::setw(6) << pos.comp[2] << ") - ";
            if (point.getType() == czm_face::PointType::EDGE_POINT)
            {
                const auto *edge = point.getEdge();
                std::cout << "Edge point (edge length: " << edge->length() << ")";
            }
            else
            {
                std::cout << "Interior point";
            }
            std::cout << std::endl;
        }

        // 3. Uniform grid points
        auto uniformPoints = squareFace.generatePointGrid(pointsPerEdge,
                                                          czm_face::PointGenerationMethod::UNIFORM_GRID);
        std::cout << "\n3. Uniform Grid Points (" << uniformPoints.size() << " points):\n";
        for (size_t i = 0; i < uniformPoints.size(); ++i)
        {
            const auto &point = uniformPoints[i];
            const Vec3D &pos = point.getPosition();
            std::cout << "Point " << i + 1 << " at ("
                      << std::setw(6) << pos.comp[0] << ", "
                      << std::setw(6) << pos.comp[1] << ", "
                      << std::setw(6) << pos.comp[2] << ") - ";
            if (point.getType() == czm_face::PointType::EDGE_POINT)
            {
                const auto *edge = point.getEdge();
                std::cout << "Edge point (edge length: " << edge->length() << ")";
            }
            else
            {
                std::cout << "Interior point";
            }
            std::cout << std::endl;
        }

        // 4. Edge and interior points
        auto allPoints = squareFace.generatePointGrid(pointsPerEdge,
                                                      czm_face::PointGenerationMethod::EDGE_AND_INTERIOR);
        std::cout << "\n4. Edge and Interior Points (" << allPoints.size() << " points):\n";
        for (size_t i = 0; i < allPoints.size(); ++i)
        {
            const auto &point = allPoints[i];
            const Vec3D &pos = point.getPosition();
            std::cout << "Point " << i + 1 << " at ("
                      << std::setw(6) << pos.comp[0] << ", "
                      << std::setw(6) << pos.comp[1] << ", "
                      << std::setw(6) << pos.comp[2] << ") - ";
            if (point.getType() == czm_face::PointType::EDGE_POINT)
            {
                const auto *edge = point.getEdge();
                std::cout << "Edge point (edge length: " << edge->length() << ")";
            }
            else
            {
                std::cout << "Interior point";
            }
            std::cout << std::endl;
        }

        // 5. Equal area points
        int numEqualAreaPoints = 16; // Example: 4x4 grid
        auto equalAreaPoints = squareFace.generateEqualAreaPoints(numEqualAreaPoints);
        std::cout << "\n5. Equal Area Points (" << equalAreaPoints.size() << " points):\n";
        for (size_t i = 0; i < equalAreaPoints.size(); ++i)
        {
            const auto &point = equalAreaPoints[i];
            const Vec3D &pos = point.getPosition();
            std::cout << "Point " << i + 1 << " at ("
                      << std::setw(6) << pos.comp[0] << ", "
                      << std::setw(6) << pos.comp[1] << ", "
                      << std::setw(6) << pos.comp[2] << ") - Interior point\n";
        }
    }
}

int main()
{
    corecode::Core core;
    std::cout << "CoreCodeRD Version: " << core.getVersion() << std::endl;

    // Run CzmFace tests
    testCzmFace();

    // Run point generation tests
    testPointGeneration();

    return 0;
}