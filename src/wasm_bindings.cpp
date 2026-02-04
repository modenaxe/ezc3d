#include <emscripten/bind.h>
#include "ezc3d/ezc3d_all.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(ezc3d_wasm) {
    // --- 1. Math Bindings ---
    // Required for force/moment vectors
    class_<ezc3d::Vector3d>("Vector3d")
        .function("x", &ezc3d::Vector3d::x)
        .function("y", &ezc3d::Vector3d::y)
        .function("z", &ezc3d::Vector3d::z);

    class_<ezc3d::Matrix>("Matrix")
        .function("nbRows", &ezc3d::Matrix::nbRows)
        .function("nbCols", &ezc3d::Matrix::nbCols)
        .function("operator()", &ezc3d::Matrix::operator());

    // --- 2. Force Platform Filter Bindings ---
    // Wraps the computed platform data
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
        .function("nbPlatforms", &ezc3d::Modules::ForcePlatforms::nbPlatforms)
        .function("forcePlatform", &ezc3d::Modules::ForcePlatforms::forcePlatform);

    // --- 3. Core C3D Output Bindings ---
    class_<ezc3d::Header>("Header")
        .function("nbFrames", &ezc3d::Header::nbFrames)
        .function("frameRate", &ezc3d::Header::frameRate)
        .function("nb3dPoints", &ezc3d::Header::nb3dPoints)
        .function("nbAnalogs", &ezc3d::Header::nbAnalogs);

    class_<ezc3d::DataNS::Points3dNS::Point>("Point")
        .function("x", &ezc3d::DataNS::Points3dNS::Point::x)
        .function("y", &ezc3d::DataNS::Points3dNS::Point::y)
        .function("z", &ezc3d::DataNS::Points3dNS::Point::z);

    class_<ezc3d::c3d>("c3d")
        .constructor<std::string>()
        .function("header", &ezc3d::c3d::header)
        .function("pointNames", &ezc3d::c3d::pointNames)
        .function("channelNames", &ezc3d::c3d::channelNames);

    // --- 4. Vector Registrations ---
    // Essential for returning arrays of objects to JS
    register_vector<std::string>("StringVector");
    register_vector<ezc3d::Vector3d>("Vector3dVector");
}
