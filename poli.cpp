
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Point_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include <fstream>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Kernel::Vector_3 Vector;
typedef Kernel::Point_3 Point;
typedef Polyhedron::Facet_iterator Facet_iterator;
typedef Polyhedron::Halfedge_around_facet_circulator Facet_circulator;
namespace PMP = CGAL::Polygon_mesh_processing;

double cuad(double a_1, double a_2, double b_1, double b_2) {
    return -((pow(a_2, 2) - pow(a_1, 2)) * (b_2 - b_1) * (b_2 + b_1)) / 4;
}

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

    PMP::orient(poly);

    PMP::triangulate_faces(poly);

    double volumen = 0;

    double centro_x = 0;
    double centro_y = 0;
    double centro_z = 0;

    double inercia_xx = 0;
    double inercia_yy = 0;
    double inercia_zz = 0;

    double inercia_xy = 0;
    double inercia_xz = 0;
    double inercia_yz = 0;

    for (Facet_iterator fi = poly.facets_begin(); fi != poly.facets_end(); ++fi) {
        Facet_circulator fc = fi->facet_begin();
        Point p1 = fc->vertex()->point();
        Point p2 = (++fc)->vertex()->point();
        Point p3 = (++fc)->vertex()->point();

        Vector u = p2 - p1;
        Vector v = p3 - p1;
        Vector n = CGAL::cross_product(u, v);

        using std::pow;

        volumen += n.x() * (p1.x() * 3.0 + u.x() + v.x()) / 6;

        centro_x += n.x() *
            (pow(v.x(), 2) + (u.x() + 4 * p1.x()) * v.x() + pow(u.x(), 2) +
            4 * p1.x() * u.x() + 6 * pow(p1.x(), 2)) /
            24;

        centro_y += n.y() *
            (pow(v.y(), 2) + (u.y() + 4 * p1.y()) * v.y() + pow(u.y(), 2) +
            4 * p1.y() * u.y() + 6 * pow(p1.y(), 2)) /
            24;

        centro_z += n.z() *
            (pow(v.z(), 2) + (u.z() + 4 * p1.z()) * v.z() + pow(u.z(), 2) +
            4 * p1.z() * u.z() + 6 * pow(p1.z(), 2)) /
            24;

        double inercia_x =
            n.x() * (pow(v.x(), 3) + (u.x() + 5 * p1.x()) * pow(v.x(), 2) +
            (pow(u.x(), 2) + 5 * p1.x() * u.x() + 10 * pow(p1.x(), 2)) * v.x() + pow(u.x(), 3) +
            5 * p1.x() * pow(u.x(), 2) + 10 * pow(p1.x(), 2) * u.x() + 10 * pow(p1.x(), 3)) / 60;

        double inercia_y =
            n.y() * (pow(v.y(), 3) + (u.y() + 5 * p1.y()) * pow(v.y(), 2) +
            (pow(u.y(), 2) + 5 * p1.y() * u.y() + 10 * pow(p1.y(), 2)) * v.y() + pow(u.y(), 3) +
            5 * p1.y() * pow(u.y(), 2) + 10 * pow(p1.y(), 2) * u.y() + 10 * pow(p1.y(), 3)) / 60;

        double inercia_z =
            n.z() * (pow(v.z(), 3) + (u.z() + 5 * p1.z()) * pow(v.z(), 2) +
            (pow(u.z(), 2) + 5 * p1.z() * u.z() + 10 * pow(p1.z(), 2)) * v.z() + pow(u.z(), 3) +
            5 * p1.z() * pow(u.z(), 2) + 10 * pow(p1.z(), 2) * u.z() + 10 * pow(p1.z(), 3)) / 60;

        inercia_xx += inercia_y + inercia_z;
        inercia_yy += inercia_x + inercia_z;
        inercia_zz += inercia_x + inercia_y;


        inercia_xy -=
            n.x() * ((3 * pow(v.x(), 2) + (2 * u.x() + 10 * p1.x()) * v.x() + pow(u.x(), 2) +
            5 * p1.x() * u.x() + 10 * pow(p1.x(), 2)) * v.y() + (u.y() + 5 * p1.y()) * pow(v.x(), 2) +
            ((2 * u.x() + 5 * p1.x()) * u.y() + 5 * p1.y() * u.x() + 20 * p1.x() * p1.y()) * v.x() +
            (3 * pow(u.x(), 2) + 10 * p1.x() * u.x() + 10 * pow(p1.x(), 2)) * u.y() +
            5 * p1.y() * pow(u.x(), 2) + 20 * p1.x() * p1.y() * u.x() + 30 * pow(p1.x(), 2) * p1.y()) / 120;

        inercia_xz -=
            n.x() * ((3 * pow(v.x(), 2) + (2 * u.x() + 10 * p1.x()) * v.x() + pow(u.x(), 2) +
            5 * p1.x() * u.x() + 10 * pow(p1.x(), 2)) * v.z() + (u.z() + 5 * p1.z()) * pow(v.x(), 2) +
            ((2 * u.x() + 5 * p1.x()) * u.z() + 5 * p1.z() * u.x() + 20 * p1.x() * p1.z()) * v.x() +
            (3 * pow(u.x(), 2) + 10 * p1.x() * u.x() + 10 * pow(p1.x(), 2)) * u.z() +
            5 * p1.z() * pow(u.x(), 2) + 20 * p1.x() * p1.z() * u.x() + 30 * pow(p1.x(), 2) * p1.z()) / 120;

        inercia_yz -=
            n.y() * ((3 * pow(v.y(), 2) + (2 * u.y() + 10 * p1.y()) * v.y() + pow(u.y(), 2) +
            5 * p1.y() * u.y() + 10 * pow(p1.y(), 2)) * v.z() + (u.z() + 5 * p1.z()) * pow(v.y(), 2) +
            ((2 * u.y() + 5 * p1.y()) * u.z() + 5 * p1.z() * u.y() + 20 * p1.y() * p1.z()) * v.y() +
            (3 * pow(u.y(), 2) + 10 * p1.y() * u.y() + 10 * pow(p1.y(), 2)) * u.z() +
            5 * p1.z() * pow(u.y(), 2) + 20 * p1.y() * p1.z() * u.y() + 30 * pow(p1.y(), 2) * p1.z()) / 120;
    }

    centro_x /= volumen;
    centro_y /= volumen;
    centro_z /= volumen;

    // Teorema de Steiner
    inercia_xx -= volumen * (pow(centro_y, 2) + pow(centro_z, 2));
    inercia_yy -= volumen * (pow(centro_x, 2) + pow(centro_z, 2));
    inercia_zz -= volumen * (pow(centro_x, 2) + pow(centro_y, 2));

    inercia_xy += volumen * centro_x * centro_y;
    inercia_xz += volumen * centro_x * centro_z;
    inercia_yz += volumen * centro_y * centro_z;

    std::cout << "Volumen del polihedro: " << volumen << std::endl;

    std::cout << "Centro de masas: (" << centro_x << ", " << centro_y << ", " << centro_z << ")"
              << std::endl;

    std::cout << "Tensor de inercia:" << std::endl;
    std::cout << "    " << inercia_xx << "  " << inercia_xy << "  " << inercia_xz << std::endl;
    std::cout << "    " << inercia_xy << "  " << inercia_yy << "  " << inercia_yz << std::endl;
    std::cout << "    " << inercia_xz << "  " << inercia_yz << "  " << inercia_zz << std::endl;

    return 0;
}
