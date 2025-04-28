#include "edge.hpp"
#include <cmath>

namespace czm_face
{

    Edge::Edge(const Vec3D &start, const Vec3D &end)
        : start_(start), end_(end)
    {
    }

    double Edge::length() const
    {
        // Calculate length directly using comp array
        double dx = end_.comp[0] - start_.comp[0];
        double dy = end_.comp[1] - start_.comp[1];
        double dz = end_.comp[2] - start_.comp[2];
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    Vec3D Edge::direction() const
    {
        Vec3D diff = end_ - start_;
        double len = length();
        if (len > 0)
        {
            return diff / len;
        }
        return Vec3D(0, 0, 0);
    }

    bool Edge::operator==(const Edge &other) const
    {
        // Two edges are equal if they have the same points, regardless of order
        bool sameOrder = (start_.comp[0] == other.start_.comp[0] &&
                          start_.comp[1] == other.start_.comp[1] &&
                          start_.comp[2] == other.start_.comp[2] &&
                          end_.comp[0] == other.end_.comp[0] &&
                          end_.comp[1] == other.end_.comp[1] &&
                          end_.comp[2] == other.end_.comp[2]);

        bool reverseOrder = (start_.comp[0] == other.end_.comp[0] &&
                             start_.comp[1] == other.end_.comp[1] &&
                             start_.comp[2] == other.end_.comp[2] &&
                             end_.comp[0] == other.start_.comp[0] &&
                             end_.comp[1] == other.start_.comp[1] &&
                             end_.comp[2] == other.start_.comp[2]);

        return sameOrder || reverseOrder;
    }

} // namespace czm_face