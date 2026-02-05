#include <emscripten/bind.h>
#include "ezc3d/ezc3d_all.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(ezc3d_wasm) {

    // =========================================================================
    // 1. OPTIONS & MATH CORE
    // =========================================================================
    class_<ezc3d::Options>("Options")
        .constructor<bool, bool>()
        .constructor<>()
        .property("ignoreBadFormatting", &ezc3d::Options::getIgnoreBadFormatting)
        .property("keepParametersTrailingSpaces", &ezc3d::Options::getKeepParametersTrailingSpaces);

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

    class_<ezc3d::Matrix33, base<ezc3d::Matrix>>("Matrix33")
        .constructor<>()
        .constructor<double, double, double, double, double, double, double, double, double>()
        .constructor<const ezc3d::Matrix&>();

    class_<ezc3d::Matrix44, base<ezc3d::Matrix>>("Matrix44")
        .constructor<>()
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>()
        .constructor<const ezc3d::Matrix&>();

    // =========================================================================
    // 2. PARAMETERS HIERARCHY
    // =========================================================================
    class_<ezc3d::ParametersNS::GroupNS::Parameter>("Parameter")
        .function("name", select_overload<const std::string& () const>(&ezc3d::ParametersNS::GroupNS::Parameter::name))
        .function("description", select_overload<const std::string& () const>(&ezc3d::ParametersNS::GroupNS::Parameter::description))
        .function("isLocked", &ezc3d::ParametersNS::GroupNS::Parameter::isLocked)
        .function("valuesAsString", &ezc3d::ParametersNS::GroupNS::Parameter::valuesAsString)
        .function("valuesAsDouble", &ezc3d::ParametersNS::GroupNS::Parameter::valuesAsDouble)
        .function("valuesAsInt", &ezc3d::ParametersNS::GroupNS::Parameter::valuesAsInt);

    class_<ezc3d::ParametersNS::GroupNS::Group>("Group")
        .function("name", select_overload<const std::string& () const>(&ezc3d::ParametersNS::GroupNS::Group::name))
        .function("description", select_overload<const std::string& () const>(&ezc3d::ParametersNS::GroupNS::Group::description))
        .function("isLocked", &ezc3d::ParametersNS::GroupNS::Group::isLocked)
        .function("nbParameters", &ezc3d::ParametersNS::GroupNS::Group::nbParameters)
        .function("parameter", select_overload<const ezc3d::ParametersNS::GroupNS::Parameter& (size_t) const>(&ezc3d::ParametersNS::GroupNS::Group::parameter))
        .function("parameterByName", select_overload<const ezc3d::ParametersNS::GroupNS::Parameter& (const std::string &) const>(&ezc3d::ParametersNS::GroupNS::Group::parameter))
        .function("isParameter", &ezc3d::ParametersNS::GroupNS::Group::isParameter);

    class_<ezc3d::ParametersNS::Parameters>("Parameters")
        .function("nbGroups", &ezc3d::ParametersNS::Parameters::nbGroups)
        .function("isGroup", &ezc3d::ParametersNS::Parameters::isGroup)
        .function("group", select_overload<const ezc3d::ParametersNS::GroupNS::Group& (size_t) const>(&ezc3d::ParametersNS::Parameters::group))
        .function("groupByName", select_overload<const ezc3d::ParametersNS::GroupNS::Group& (const std::string &) const>(&ezc3d::ParametersNS::Parameters::group));

    // =========================================================================
    // 3. DATA HIERARCHY (Corrected Namespaces and Overloads)
    // =========================================================================
    class_<ezc3d::DataNS::Points3dNS::Point>("Point")
        .function("x", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::x))
        .function("y", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::y))
        .function("z", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::z))
        .function("residual", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::residual));

    class_<ezc3d::DataNS::Points3dNS::Points>("Points")
        .function("nbPoints", select_overload<size_t() const>(&ezc3d::DataNS::Points3dNS::Points::nbPoints))
        .function("point", select_overload<const ezc3d::DataNS::Points3dNS::Point& (size_t) const>(&ezc3d::DataNS::Points3dNS::Points::point));

    class_<ezc3d::DataNS::AnalogsNS::Channel>("Channel")
        .function("data", select_overload<double() const>(&ezc3d::DataNS::AnalogsNS::Channel::data));

    class_<ezc3d::DataNS::AnalogsNS::SubFrame>("SubFrame")
        .function("nbChannels", select_overload<size_t() const>(&ezc3d::DataNS::AnalogsNS::SubFrame::nbChannels))
        .function("channel", select_overload<const ezc3d::DataNS::AnalogsNS::Channel& (size_t) const>(&ezc3d::DataNS::AnalogsNS::SubFrame::channel));

    class_<ezc3d::DataNS::AnalogsNS::Analogs>("Analogs")
        .function("nbSubframes", select_overload<size_t() const>(&ezc3d::DataNS::AnalogsNS::Analogs::nbSubframes))
        .function("subframe", select_overload<const ezc3d::DataNS::AnalogsNS::SubFrame& (size_t) const>(&ezc3d::DataNS::AnalogsNS::Analogs::subframe));

    class_<ezc3d::DataNS::Frame>("Frame")
        .function("points", &ezc3d::DataNS::Frame::points)
        .function("analogs", &ezc3d::DataNS::Frame::analogs);

    class_<ezc3d::Data>("Data")
        .function("nbFrames", select_overload<size_t() const>(&ezc3d::Data::nbFrames))
        .function("frame", select_overload<const ezc3d::DataNS::Frame& (size_t) const>(&ezc3d::Data::frame));

    // =========================================================================
    // 4. MAIN CLASSES
    // =========================================================================
    class_<ezc3d::Header>("Header")
        .function("nbFrames", &ezc3d::Header::nbFrames)
        .function("frameRate", select_overload<float() const>(&ezc3d::Header::frameRate))
        .function("set_frameRate", select_overload<void(float)>(&ezc3d::Header::frameRate))
        .function("nb3dPoints", select_overload<size_t() const>(&ezc3d::Header::nb3dPoints))
        .function("nbAnalogs", select_overload<size_t() const>(&ezc3d::Header::nbAnalogs))
        .function("nbAnalogByFrame", select_overload<size_t() const>(&ezc3d::Header::nbAnalogByFrame))
        .function("firstFrame", select_overload<size_t() const>(&ezc3d::Header::firstFrame))
        .function("lastFrame", select_overload<size_t() const>(&ezc3d::Header::lastFrame));

    class_<ezc3d::c3d>("c3d")
        .constructor<>()
        .constructor<std::string>()
        .constructor<std::string, const ezc3d::Options&>() 
        .function("write", &ezc3d::c3d::write)
        .function("header", &ezc3d::c3d::header)
        .function("parameters", select_overload<const ezc3d::ParametersNS::Parameters& () const>(&ezc3d::c3d::parameters))
        .function("data", &ezc3d::c3d::data)
        .function("pointNames", &ezc3d::c3d::pointNames)
        .function("channelNames", &ezc3d::c3d::channelNames);

    // =========================================================================
    // 5. MODULES (Force Platforms)
    // =========================================================================
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
        .function("forcePlatforms", &ezc3d::Modules::ForcePlatforms::forcePlatforms)
        .function("forcePlatform", &ezc3d::Modules::ForcePlatforms::forcePlatform);

    // =========================================================================
    // 6. VECTOR REGISTRATIONS
    // =========================================================================
    register_vector<std::string>("StringVector");
    register_vector<double>("DoubleVector");
    register_vector<int>("IntVector");
    register_vector<ezc3d::Vector3d>("Vector3dVector");
    register_vector<ezc3d::Modules::ForcePlatform>("ForcePlatformVector");
    register_vector<ezc3d::DataNS::Points3dNS::Point>("PointVector");
}
