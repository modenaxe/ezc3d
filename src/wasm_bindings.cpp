#include <emscripten/bind.h>
#include "ezc3d/ezc3d_all.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(ezc3d_wasm) {
    // --- Math Bindings ---
    // Note: Vector3d uses double, not float
    class_<ezc3d::Vector3d>("Vector3d")
        .function("x", select_overload<double() const>(&ezc3d::Vector3d::x))
        .function("y", select_overload<double() const>(&ezc3d::Vector3d::y))
        .function("z", select_overload<double() const>(&ezc3d::Vector3d::z));

    class_<ezc3d::Matrix>("Matrix")
        .function("nbRows", &ezc3d::Matrix::nbRows)
        .function("nbCols", &ezc3d::Matrix::nbCols);

    // --- Force Platform Bindings ---
    class_<ezc3d::Modules::ForcePlatform>("ForcePlatform")
        .function("nbFrames", &ezc3d::Modules::ForcePlatform::nbFrames)
        .function("forceUnit", &ezc3d::Modules::ForcePlatform::forceUnit)
        .function("momentUnit", &ezc3d::Modules::ForcePlatform::momentUnit)
        .function("positionUnit", &ezc3d::Modules::ForcePlatform::positionUnit)
        .function("calMatrix", &ezc3d::Modules::ForcePlatform::calMatrix)
        .function("corners", &ezc3d::Modules::ForcePlatform::corners)
        .function("origin", &ezc3d::Modules::ForcePlatform::origin)
        .function("forces", &ezc3d::Modules::ForcePlatform::forces)
        .function("moments", &ezc3d::Modules::ForcePlatform::moments)
        .function("CoP", &ezc3d::Modules::ForcePlatform::CoP)
        .function("Tz", &ezc3d::Modules::ForcePlatform::Tz);

    class_<ezc3d::Modules::ForcePlatforms>("ForcePlatforms")
        .constructor<const ezc3d::c3d&>()
        // FIXED: 'nbForcePlatforms' does not exist. Bind the vector accessor instead.
        .function("forcePlatforms", &ezc3d::Modules::ForcePlatforms::forcePlatforms)
        .function("forcePlatform", &ezc3d::Modules::ForcePlatforms::forcePlatform);

    // --- Header Bindings ---
    class_<ezc3d::Header>("Header")
        .function("nbFrames", &ezc3d::Header::nbFrames)
        .function("frameRate", select_overload<float() const>(&ezc3d::Header::frameRate))
        .function("nb3dPoints", select_overload<size_t() const>(&ezc3d::Header::nb3dPoints))
        .function("nbAnalogs", select_overload<size_t() const>(&ezc3d::Header::nbAnalogs));

    // --- Data Point Bindings ---
    // FIXED: Point::x/y/z return double, not float
    class_<ezc3d::DataNS::Points3dNS::Point>("Point")
        .function("x", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::x))
        .function("y", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::y))
        .function("z", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::z))
        .function("residual", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::residual));

    // --- Main C3D Binding ---
    class_<ezc3d::c3d>("c3d")
        .constructor<>()                 
        .constructor<std::string>()      
        .function("write", &ezc3d::c3d::write)
        .function("header", &ezc3d::c3d::header)
        .function("parameters", &ezc3d::c3d::parameters)
        .function("pointNames", &ezc3d::c3d::pointNames)
        .function("channelNames", &ezc3d::c3d::channelNames);

    // --- Vector Registrations ---
    register_vector<std::string>("StringVector");
    register_vector<ezc3d::Vector3d>("Vector3dVector");
    register_vector<ezc3d::Modules::ForcePlatform>("ForcePlatformVector");
}
