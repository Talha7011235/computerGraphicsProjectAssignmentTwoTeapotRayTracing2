rtrace: main2.cpp Intersection2.cpp PolygonPatch2.cpp Ray2.cpp Light2.cpp Color2.cpp Project2IntegersForVector2.cpp Project2Vector3.cpp Matrix2.cpp Shading2.cpp ViewPort2.cpp Polygon2.cpp Sphere2.cpp NffParser2.cpp PpmFile2.cpp
	g++ -pthread -std=c++17 -O3 -o rtrace main2.cpp Intersection2.cpp PolygonPatch2.cpp Project2Vector3.cpp Ray2.cpp Light2.cpp Color2.cpp Project2IntegersForVector2.cpp Matrix2.cpp Shading2.cpp ViewPort2.cpp Polygon2.cpp Sphere2.cpp NffParser2.cpp PpmFile2.cpp

teapot: rtrace
	./rtrace teapot-3.nff teapot.ppm
	convert teapot.ppm teapot.png

stratified: rtrace
	./rtrace -s 3 teapot-3.nff stratified.ppm
	convert stratified.ppm stratified.png

dof: rtrace
	./rtrace -a 0.5 -s 3 teapot-3.nff dof.ppm
	convert dof.ppm dof.png

refract: rtrace
	./rtrace refract.nff refract.ppm
	convert refract.ppm refract.png

phong: rtrace
	./rtrace -p teapot-3.nff phong.ppm
	convert phong.ppm phong.png

clean:
	rm rtrace
