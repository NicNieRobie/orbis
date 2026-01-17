#pragma once

#include "orbis/math/types.hpp"

#include <variant>

namespace orbis {
    using UniformValue = std::variant<
        int,
        float,
        math::Vec3,
        math::Vec4,
        math::Mat4
    >;
}
