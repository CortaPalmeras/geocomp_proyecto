
#include <iostream>
#include <fstream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/IO/OFF.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_3> Surface_mesh;
typedef Surface_mesh::Vertex_index Vertex_index;
typedef Surface_mesh::Face_index Face_index;

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
    Surface_mesh mesh;
    if (!CGAL::IO::read_OFF(input, mesh)) {
        std::cerr << "Not a valid OFF file." << std::endl;
        return 1;
    }

    std::cout << "cantidad de caras: " << mesh.faces().size() << std::endl;

    // Global counter for coordinates
    double global_x = 0.0, global_y = 0.0, global_z = 0.0;

    // Iterate over all faces and add the coordinates of its points
    for (const Face_index& fi : mesh.faces()) {
        for (const Vertex_index& vi : CGAL::vertices_around_face(mesh.halfedge(fi), mesh)) {
            const auto& point = mesh.point(vi);
            global_x += point.x();
            global_y += point.y();
            global_z += point.z();
        }
    }

    // Print the global counter
    std::cout << "Global coordinates sum: (" << global_x << ", " << global_y << ", " << global_z << ")" << std::endl;

    return 0;
}

