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
        // Added for your example: .T() (Transpose)
        .function("T", &ezc3d::Matrix::T) 
        // Allow access to elements like matrix(0, 0)
        .function("get", select_overload<double(size_t, size_t) const>(&ezc3d::Matrix::operator()));

    class_<ezc3d::Vector3d, base<ezc3d::Matrix>>("Vector3d")
        .constructor<>()
        .constructor<double, double, double>()
        .constructor<const ezc3d::Matrix&>()
        .function("print", &ezc3d::Vector3d::print)
        .function("x", select_overload<double() const>(&ezc3d::Vector3d::x))
        .function("y", select_overload<double() const>(&ezc3d::Vector3d::y))
        .function("z", select_overload<double() const>(&ezc3d::Vector3d::z))
        .function("set", &ezc3d::Vector3d::set)
        .function("set_x", select_overload<void(double)>(&ezc3d::Vector3d::x))
        .function("set_y", select_overload<void(double)>(&ezc3d::Vector3d::y))
        .function("set_z", select_overload<void(double)>(&ezc3d::Vector3d::z))
        .function("norm", &ezc3d::Vector3d::norm)
        .function("normalize", &ezc3d::Vector3d::normalize);

    // =========================================================================
    // 2. PARAMETERS HIERARCHY
    // =========================================================================
    class_<ezc3d::ParametersNS::GroupNS::Parameter>("Parameter")
        .constructor<std::string>() 
        .function("name", select_overload<const std::string& () const>(&ezc3d::ParametersNS::GroupNS::Parameter::name))
        .function("description", select_overload<const std::string& () const>(&ezc3d::ParametersNS::GroupNS::Parameter::description))
        .function("valuesAsDouble", &ezc3d::ParametersNS::GroupNS::Parameter::valuesAsDouble)
        .function("valuesAsInt", &ezc3d::ParametersNS::GroupNS::Parameter::valuesAsInt)
        .function("valuesAsString", &ezc3d::ParametersNS::GroupNS::Parameter::valuesAsString)
        .function("set", select_overload<void(const std::vector<double>&, const std::vector<size_t>&)>(&ezc3d::ParametersNS::GroupNS::Parameter::set));

    class_<ezc3d::ParametersNS::GroupNS::Group>("Group")
        .function("name", select_overload<const std::string& () const>(&ezc3d::ParametersNS::GroupNS::Group::name))
        .function("nbParameters", &ezc3d::ParametersNS::GroupNS::Group::nbParameters)
        .function("parameter", select_overload<const ezc3d::ParametersNS::GroupNS::Parameter& (size_t) const>(&ezc3d::ParametersNS::GroupNS::Group::parameter))
        .function("parameterByName", select_overload<const ezc3d::ParametersNS::GroupNS::Parameter& (const std::string &) const>(&ezc3d::ParametersNS::GroupNS::Group::parameter))
        .function("addParameter", &ezc3d::ParametersNS::GroupNS::Group::addParameter); 

    class_<ezc3d::ParametersNS::Parameters>("Parameters")
        .function("nbGroups", &ezc3d::ParametersNS::Parameters::nbGroups)
        .function("group", select_overload<const ezc3d::ParametersNS::GroupNS::Group& (size_t) const>(&ezc3d::ParametersNS::Parameters::group))
        .function("groupByName", select_overload<const ezc3d::ParametersNS::GroupNS::Group& (const std::string &) const>(&ezc3d::ParametersNS::Parameters::group));

    // =========================================================================
    // 3. DATA HIERARCHY
    // =========================================================================
    class_<ezc3d::DataNS::Points3dNS::Point>("Point")
        .constructor<>()
        .function("x", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::x))
        .function("y", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::y))
        .function("z", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::z))
        .function("residual", select_overload<double() const>(&ezc3d::DataNS::Points3dNS::Point::residual))
        .function("set_x", select_overload<void(double)>(&ezc3d::DataNS::Points3dNS::Point::x))
        .function("set_y", select_overload<void(double)>(&ezc3d::DataNS::Points3dNS::Point::y))
        .function("set_z", select_overload<void(double)>(&ezc3d::DataNS::Points3dNS::Point::z));

    class_<ezc3d::DataNS::Points3dNS::Points>("Points")
        .constructor<>()
        .function("nbPoints", select_overload<size_t() const>(&ezc3d::DataNS::Points3dNS::Points::nbPoints))
        .function("point", select_overload<const ezc3d::DataNS::Points3dNS::Point& (size_t) const>(&ezc3d::DataNS::Points3dNS::Points::point))
        .function("addPoint", select_overload<void(const ezc3d::DataNS::Points3dNS::Point&)>(&ezc3d::DataNS::Points3dNS::Points::point));

    class_<ezc3d::DataNS::AnalogsNS::Channel>("Channel")
        .constructor<>()
        .function("data", select_overload<double() const>(&ezc3d::DataNS::AnalogsNS::Channel::data))
        .function("set_data", select_overload<void(double)>(&ezc3d::DataNS::AnalogsNS::Channel::data));

    class_<ezc3d::DataNS::AnalogsNS::SubFrame>("SubFrame")
        .constructor<>()
        .function("nbChannels", select_overload<size_t() const>(&ezc3d::DataNS::AnalogsNS::SubFrame::nbChannels))
        .function("channel", select_overload<const ezc3d::DataNS::AnalogsNS::Channel& (size_t) const>(&ezc3d::DataNS::AnalogsNS::SubFrame::channel))
        .function("addChannel", select_overload<void(const ezc3d::DataNS::AnalogsNS::Channel&)>(&ezc3d::DataNS::AnalogsNS::SubFrame::channel));

    class_<ezc3d::DataNS::AnalogsNS::Analogs>("Analogs")
        .constructor<>()
        .function("nbSubframes", select_overload<size_t() const>(&ezc3d::DataNS::AnalogsNS::Analogs::nbSubframes))
        .function("subframe", select_overload<const ezc3d::DataNS::AnalogsNS::SubFrame& (size_t) const>(&ezc3d::DataNS::AnalogsNS::Analogs::subframe))
        .function("addSubframe", select_overload<void(const ezc3d::DataNS::AnalogsNS::SubFrame&)>(&ezc3d::DataNS::AnalogsNS::Analogs::subframe));

    class_<ezc3d::DataNS::Frame>("Frame")
        .constructor<>()
        .function("points", select_overload<const ezc3d::DataNS::Points3dNS::Points& () const>(&ezc3d::DataNS::Frame::points))
        .function("analogs", select_overload<const ezc3d::DataNS::AnalogsNS::Analogs& () const>(&ezc3d::DataNS::Frame::analogs))
        .function("add", select_overload<void(const ezc3d::DataNS::Points3dNS::Points&, const ezc3d::DataNS::AnalogsNS::Analogs&)>(&ezc3d::DataNS::Frame::add));

    class_<ezc3d::DataNS::Data>("Data")
        .function("nbFrames", select_overload<size_t() const>(&ezc3d::DataNS::Data::nbFrames))
        .function("frame", select_overload<const ezc3d::DataNS::Frame& (size_t) const>(&ezc3d::DataNS::Data::frame));

    // =========================================================================
    // 4. MAIN C3D CLASS
    // =========================================================================
    class_<ezc3d::c3d>("c3d")
        .constructor<>()
        .constructor<std::string>()
        .constructor<std::string, const ezc3d::Options&>() 
        .function("write", &ezc3d::c3d::write)
        .function("header", &ezc3d::c3d::header)
        .function("parameters", select_overload<const ezc3d::ParametersNS::Parameters& () const>(&ezc3d::c3d::parameters))
        .function("data", select_overload<const ezc3d::DataNS::Data& () const>(&ezc3d::c3d::data))
        .function("pointNames", &ezc3d::c3d::pointNames)
        .function("channelNames", &ezc3d::c3d::channelNames)
        .function("addParameter", select_overload<void(const std::string&, const ezc3d::ParametersNS::GroupNS::Parameter&)>(&ezc3d::c3d::parameter))
        .function("addPoint", select_overload<void(const std::string&)>(&ezc3d::c3d::point))
        .function("addAnalog", select_overload<void(const std::string&)>(&ezc3d::c3d::analog))
        .function("addFrame", select_overload<void(const ezc3d::DataNS::Frame&)>(&ezc3d::c3d::frame));

    // =========================================================================
    // 5. MODULES (Force Platforms - Updated for Example)
    // =========================================================================
    class_<ezc3d::Modules::ForcePlatform>("ForcePlatform")
        .function("nbFrames", &ezc3d::Modules::ForcePlatform::nbFrames)
        // Added: .type() needed for "Type ="
        .function("type", &ezc3d::Modules::ForcePlatform::type) 
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
    register_vector<size_t>("SizeTVector"); 
    register_vector<ezc3d::Vector3d>("Vector3dVector");
    register_vector<ezc3d::DataNS::Points3dNS::Point>("PointVector");
    register_vector<ezc3d::DataNS::Frame>("FrameVector");
    register_vector<ezc3d::Modules::ForcePlatform>("ForcePlatformVector");
}
