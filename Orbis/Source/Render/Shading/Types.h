#pragma once

#include "Math/Types.h"

#include <variant>

namespace Orbis {
    using UniformValue = std::variant<
        int,
        float,
        Math::Vec3,
        Math::Vec4,
        Math::Mat4
    >;
}
