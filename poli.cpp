
#include <iostream>
#include <fstream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include "triangulate.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
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
        Point p = fc->vertex()->point();
        double p1x = p.x();
        double p1y = p.y();
        double p1z = p.z();
        ++fc;

        p = fc->vertex()->point();
        double p2x = p.x();
        double p2y = p.y();
        double p2z = p.z();
        ++fc;

        p = fc->vertex()->point();
        double p3x = p.x();
        double p3y = p.y();
        double p3z = p.z();
        ++fc;

        
    }

    return 0;
}

