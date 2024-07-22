
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
        std::cerr << "Uso: " << argv[0] << " <input.off>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error al abrir archivo" << argv[1] << std::endl;
        return 1;
    }

    Polyhedron poly;
    input >> poly;

    if (!input) {
        std::cerr << "Archivo OFF no valido." << std::endl;
        return 1;
    }

    if (!CGAL::is_closed(poly)) {
        std::cerr << "La maya poligonal no está cerrada." << std::endl;
        return 1;
    }

    my_orient(poly);

    my_triangulate_faces(poly);

    double volumen = 0;

    double centro_x = 0;
    double centro_y = 0;
    double centro_z = 0;

    for (Facet_iterator fi = poly.facets_begin(); fi != poly.facets_end(); ++fi) {
        Facet_circulator fc = fi->facet_begin();
        Point p1 = fc->vertex()->point();
        Point p2 = (++fc)->vertex()->point();
        Point p3 = (++fc)->vertex()->point();

        Vector u = p2 - p1;
        Vector v = p3 - p1;
        Vector n = CGAL::cross_product(u, v);

        volumen += n.x() * (p1.x() * 3.0 + u.x() + v.x()) / 6;

        centro_x += n.x() * (std::pow(v.x(), 2) 
            + (u.x() + 4 * p1.x()) * v.x()
            + std::pow(u.x(), 2)
            + 4 * p1.x() * u.x()
            + 6 * std::pow(p1.x(), 2)) / 24;

        centro_y += n.y() * (std::pow(v.y(), 2) 
           + (u.y() + 4 * p1.y()) * v.y()
            + std::pow(u.y(), 2)
            + 4 * p1.y() * u.y()
            + 6 * std::pow(p1.y(), 2)) / 24;

        centro_z += n.z() * (std::pow(v.z(), 2) 
            + (u.z() + 4 * p1.z()) * v.z()
            + std::pow(u.z(), 2)
            + 4 * p1.z() * u.z()
            + 6 * std::pow(p1.z(), 2)) / 24;
    }

    double inercia_xx = 0;

    for (Facet_iterator fi = poly.facets_begin(); fi != poly.facets_end(); ++fi) {
        Facet_circulator fc = fi->facet_begin();

        Point p1 = fc->vertex()->point();
        Point p2 = (++fc)->vertex()->point();
        Point p3 = (++fc)->vertex()->point();

        Vector u = p2 - p1;
        Vector v = p3 - p1;
        Vector n = CGAL::cross_product(u, v);

        inercia_xx = n.y() * (std::pow(p3.y(),2)
            + (p2.y() + p1.y() - 4 * centro_y) * p3.y()
            + std::pow(p2.y(),2) 
            + (p1.y() - 4 * centro_y) * p2.y() 
            + std::pow(p1.y(),2) - 4 * centro_y* p1.y() 
            + 6 * std::pow(centro_y,2)) / 12;

        /*inercia_xx += n.y() * (std::pow(v.y(),3)*/
        /*    + (u.y() + 5 * p1.y()) * std::pow(v.y(),2)*/
        /*    + (std::pow(u.y(),2) + 5 * p1.y() * u.y()*/
        /*    + 10 * std::pow(p1.y(),2)) * v.y() */
        /*    + std::pow(u.y(),3) */
        /*    + 5 * p1.y() * std::pow(u.y(),2)*/
        /*    + 10 * std::pow(p1.y(),2) * u.y() */
        /*    + 10 * std::pow(p1.y(),3)) / 60;*/
        /**/
        /*inercia_xx += n.z() * (std::pow(v.z(),3)*/
        /*    + (u.z() + 5 * p1.z()) * std::pow(v.z(),2)*/
        /*    + (std::pow(u.z(),2) + 5 * p1.z() * u.z()*/
        /*    + 10 * std::pow(p1.z(),2)) * v.z() */
        /*    + std::pow(u.z(),3) */
        /*    + 5 * p1.z() * std::pow(u.z(),2)*/
        /*    + 10 * std::pow(p1.z(),2) * u.z() */
        /*    + 10 * std::pow(p1.z(),3)) / 60;*/
    }
    
    std::cout << "Volumen del polihedro: " << volumen << std::endl;

    std::cout << "Centro de masas: (" << centro_x / volumen << ", " << 
        centro_y / volumen << ", " << centro_z / volumen << ")" << std::endl;

    std::cout << "Momento de inercia en el eje X: " << inercia_xx << std::endl;


    return 0;
}

