
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include "precompilado.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
namespace PMP = CGAL::Polygon_mesh_processing;

void my_triangulate_faces(Polyhedron& poly) {
    PMP::triangulate_faces(poly);
}

void my_orient(Polyhedron& poly) {
    PMP::orient(poly);
}

