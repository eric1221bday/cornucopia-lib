#include "SimpleAPI.h"
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace CornuPy
{
std::vector<Cornu::BasicPrimitive> fit(const py::array_t<double, py::array::c_style | py::array::forcecast> points_np, const Cornu::Parameters &parameters)
{
    auto pts_np = points_np.unchecked<2>();

    if (pts_np.shape(1) != 2)
    {
        throw std::runtime_error("only 2 points needed, x, y");
    }
    std::vector<Cornu::Point> points(points_np.shape()[0]);
    std::memcpy(&points[0], pts_np.data(0, 0), pts_np.nbytes());

    for (auto const& pt: points) {
        std::cout << pt.x << ", " << pt.y << std::endl;
    }
    auto primitives = Cornu::fit(points, parameters);

    return primitives;
}
} // namespace CornuPy

PYBIND11_MODULE(CornucopiaPy, m)
{
    m.def("fit", &CornuPy::fit, "the fit function from");
    py::class_<Cornu::BasicPrimitive> prim(m, "BasicPrimitive");
    prim.def_readwrite("type", &Cornu::BasicPrimitive::type)
        .def_readwrite("length", &Cornu::BasicPrimitive::length)
        .def_readwrite("start_angle", &Cornu::BasicPrimitive::startAngle)
        .def_readwrite("start_curvature", &Cornu::BasicPrimitive::startCurvature)
        .def_readwrite("curvature_derivative", &Cornu::BasicPrimitive::curvatureDerivative)
        .def_readwrite("start", &Cornu::BasicPrimitive::start)
        .def("eval", &Cornu::BasicPrimitive::eval);

    py::class_<Cornu::Point>(m, "Point")
        .def(py::init<>())
        .def_readwrite("x", &Cornu::Point::x)
        .def_readwrite("y", &Cornu::Point::y);

    py::class_<Cornu::Parameters> params(m, "Parameters");
    params.def(py::init<Cornu::Parameters::Preset>());

    py::enum_<Cornu::Parameters::Preset>(params, "Preset")
        .value("DEFAULT", Cornu::Parameters::Preset::DEFAULT)
        .value("ACCURATE", Cornu::Parameters::Preset::ACCURATE)
        .export_values();

    py::enum_<Cornu::BasicPrimitive::PrimitiveType>(prim, "PrimitiveType")
        .value("ARC", Cornu::BasicPrimitive::PrimitiveType::ARC)
        .value("CLOTHOID", Cornu::BasicPrimitive::PrimitiveType::CLOTHOID)
        .value("LINE", Cornu::BasicPrimitive::PrimitiveType::LINE);
}
