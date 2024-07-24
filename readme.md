
# Proyecto semestral de geometría computacional

Este proyecto lo elaboré utilizando el paquete de CGAL de los repositorios 
de Debian 12 con todas sus dependencias, para instalarlos desde Debian solo
debería ser necesario utilizar el siguiente comando:
```bash
sudo apt install libcgal-dev
```

Para poder compilar se debe crear un directorio con el cache de CMake y desde
ahí correr `make`:
```bash
mkdir build
cd build
cmake ..
make
```

Para correr la tarea se debe pasar un archivo con formato `.off` con la descripción
de una maya poligonal cerrada, varios ejemplos se pueden encontrar en 
[ésta página](https://people.sc.fsu.edu/~jburkardt/data/off/off.html):
```bash
./poli ./ubicación/de/archivo.off
```


