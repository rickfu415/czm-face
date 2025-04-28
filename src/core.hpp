#pragma once
#include <string>
#include <vector>

namespace corecode
{
    class Core
    {
    public:
        Core() = default;
        ~Core() = default;

        // Prevent copying
        Core(const Core &) = delete;
        Core &operator=(const Core &) = delete;

        // Allow moving
        Core(Core &&) = default;
        Core &operator=(Core &&) = default;

        // Example method
        std::string getVersion() const;

    private:
        // Add private members here
    };

} // namespace corecode