
#include <iostream>
#include <fstream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Point_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include "precompilado.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Kernel::Vector_3 Vector;
typedef Kernel::Point_3 Point;
typedef Polyhedron::Facet_iterator Facet_iterator;
typedef Polyhedron::Halfedge_around_facet_circulator Facet_circulator;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input.off>" << std::endl;
        return 1;
    }

    // Open the OFF file
    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Cannot open file " << argv[1] << std::endl;
        return 1;
    }

    // Read the mesh from the OFF file
    Polyhedron poly;
    input >> poly;

    if (!input) {
        std::cerr << "Not a valid OFF file." << std::endl;
        return 1;
    }

    std::cout << "cantidad de caras: " << poly.size_of_facets() << std::endl;

    my_triangulate_faces(poly);

    std::cout << "cantidad de caras: " << poly.size_of_facets() << std::endl;

    // Global counter for coordinates
    double resultado = 0;

    // Iterate over all faces and add the coordinates of its points
    for (Facet_iterator fi = poly.facets_begin(); fi != poly.facets_end(); ++fi) {
        Facet_circulator fc = fi->facet_begin();
        Point p1 = fc->vertex()->point();
        Point p2 = (++fc)->vertex()->point();
        Point p3 = (++fc)->vertex()->point();

        Vector u = p2 - p1;
        Vector v = p3 - p1;
        Vector n = CGAL::cross_product(u, v);

        resultado += n.x() * (p1.x() * 3.0 + u.x() + v.x()) / 6;
    }
    
    std::cout << "Volumen del polihedro: " << resultado << std::endl;

    return 0;
}

