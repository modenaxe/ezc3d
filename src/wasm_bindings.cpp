#include <emscripten/bind.h>
#include "ezc3d/ezc3d_all.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(ezc3d_wasm) {
    // --- Matrix Bindings ---
    class_<ezc3d::Matrix>("Matrix")
        .constructor<>()
        .constructor<size_t, size_t>()
        .constructor<const ezc3d::Matrix&>()
        .function("print", &ezc3d::Matrix::print)
        .function("nbRows", &ezc3d::Matrix::nbRows)
        .function("nbCols", &ezc3d::Matrix::nbCols)
        .function("size", &ezc3d::Matrix::size)
        .function("setZeros", &ezc3d::Matrix::setZeros)
        .function("setOnes", &ezc3d::Matrix::setOnes)
        .function("setIdentity", &ezc3d::Matrix::setIdentity);

    // --- Vector3d Bindings (with Matrix inheritance) ---
    class_<ezc3d::Vector3d, base<ezc3d::Matrix>>("Vector3d")
        .constructor<>()
        .constructor<double, double, double>()
        .constructor<const ezc3d::Matrix&>()
        .function("print", &ezc3d::Vector3d::print)
        .function("x", select_overload<double() const>(&ezc3d::Vector3d::x))
        .function("set_x", select_overload<void(double)>(&ezc3d::Vector3d::x))
        .function("y", select_overload<double() const>(&ezc3d::Vector3d::y))
        .function("set_y", select_overload<void(double)>(&ezc3d::Vector3d::y))
        .function("z", select_overload<double() const>(&ezc3d::Vector3d::z))
        .function("set_z", select_overload<void(double)>(&ezc3d::Vector3d::z))
        .function("isValid", &ezc3d::Vector3d::isValid)
        .function("norm", &ezc3d::Vector3d::norm)
        .function("normalize", &ezc3d::Vector3d::normalize);

    // --- Specialized Matrix Bindings ---
    class_<ezc3d::Matrix33, base<ezc3d::Matrix>>("Matrix33")
        .constructor<>()
        .constructor<double, double, double, double, double, double, double, double, double>()
        .constructor<const ezc3d::Matrix&>();

    class_<ezc3d::Matrix44, base<ezc3d::Matrix>>("Matrix44")
        .constructor<>()
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>()
        .constructor<const ezc3d::Matrix&>();

    // --- Force Platform Bindings ---
    class_<ezc3d::Modules::ForcePlatform>("ForcePlatform")
        .function("nbFrames", &ezc3d::Modules::ForcePlatform::nbFrames)
        .function("forceUnit", &ezc3d::Modules::ForcePlatform::forceUnit)
        .function("momentUnit", &ezc3d::Modules::ForcePlatform::momentUnit)
        .function("positionUnit", &ezc3d::Modules::ForcePlatform::positionUnit)
        .function("calMatrix", &ezc3d::Modules::ForcePlatform::calMatrix)
        .function("corners", &ezc3d::Modules::ForcePlatform::corners)
        .function("origin", &ezc3d::Modules::ForcePlatform::origin)
        .function("forces", &ezc3
