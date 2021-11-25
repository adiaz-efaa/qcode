#include <pybind11/pybind11.h>

#include "date.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;
using namespace qcode::time;

PYBIND11_MODULE(qc_time, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: qc_time

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    py::class_<Date>(m, "Date", "Clase para la representación de fechas.")
            .def(py::init<int, int, long>())
            .def(py::init<const std::string &>())
            .def(py::init<long>())
            .def("day", &Date::day)
            .def("month", &Date::month)
            .def("year", &Date::year)
            .def("week_day", &Date::weekDay)
            .def("iso_format", &Date::isoFormat)
            .def("add_months", &Date::addMonths)
            .def("add_days", &Date::addDays)
            .def("day_diff", &Date::dayDiff)
            .def("excel_serial", &Date::excelSerial)
            .def("__lt__", &Date::operator<)
            .def("__le__", &Date::operator<=)
            .def("__eq__", &Date::operator==)
            .def("__ne__", &Date::operator!=)
            .def("__ge__", &Date::operator>=)
            .def("__gt__", &Date::operator>)
            .def("__sub__", &Date::operator-)
            .def("__hash__", &Date::excelSerial)
            .def("__repr__", &Date::isoFormat)
            ;

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
