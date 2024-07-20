
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/polygon_mesh_processing.h>
#include "triangulate.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
namespace PMP = CGAL::Polygon_mesh_processing;

void my_triangulate_faces(Polyhedron& poly) {
    PMP::triangulate_faces(poly);
}

