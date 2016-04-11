#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Vertex.h"
#include "Triangle.h"
#include "Image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

int main(int argc, char **argv)
{
   if(argc != 6) {
      printf("\nIncorrect Number of Arguments. Correct format of input is ./{executable name} {input object file name} {output .png file name} {width} {height} {color mode}\n");
      printf("And example of a correct input is: ./Assignment1 bunny.obj output.png 512 512 1\n\n");
      return 0;
   }
   // OBJ filename
   string meshName(argv[1]);
   string fileName(argv[2]);
   int width = atoi(argv[3]);
   int height = atoi(argv[4]);
   // int colorMode = atoi(argv[5]);
   auto image = make_shared<Image>(width, height);

   // triangle buffer
   vector<unsigned int> triBuf;
   // position buffer
   vector<float> posBuf;
   vector<float> zBuf(width * height, -.5 * numeric_limits<float>::max());
   // Some obj files contain material information.
   // We'll ignore them for this assignment.
   vector<tinyobj::shape_t> shapes; // geometry
   vector<tinyobj::material_t> objMaterials; // material
   string errStr;
   bool rc = tinyobj::LoadObj(shapes, objMaterials, errStr, meshName.c_str());

   if(!rc) {
      cerr << errStr << endl;
   } else {
      posBuf = shapes[0].mesh.positions;
      triBuf = shapes[0].mesh.indices;
   }
   cout << meshName << endl;
   cout << "Number of vertices: " << posBuf.size()/3 << endl;
   cout << "Number of triangles: " << triBuf.size()/3 << endl;

   vector<Triangle> triangles;

   float scale, tx, ty;
   float deltaX, deltaY;
   float maxX, maxY, minX, minY, minZ, maxZ;

   minX = 0;
   minY = 0;
   minZ = 0;
   maxX = 0;
   maxY = 0;
   maxZ = 0;

   for (int i = 0; i < posBuf.size(); i+=3) {
      if (i == 0) {
         minX = posBuf.at(i);
         maxX = posBuf.at(i);
         minY = posBuf.at(i + 1);
         maxY = posBuf.at(i + 1);
         minZ = posBuf.at(i + 2);
         maxZ = posBuf.at(i + 2);
      }
      minX = fmin(minX, posBuf.at(i));
      minY = fmin(minY, posBuf.at(i + 1));
      minZ = fmin(minZ, posBuf.at(i + 2));

      maxX = fmax(maxX, posBuf.at(i));
      maxY = fmax(maxY, posBuf.at(i + 1));
      maxZ = fmax(maxZ, posBuf.at(i + 2));
   }

   deltaX = maxX - minX;
   deltaY = maxY - minY;

   scale = min((float)height / (float)deltaY, (float)width / (float)deltaX);
   tx = .5 * (float)width - ((.5 * (float)(minX + maxX)) * scale);
   ty = .5 * (float)height - ((.5 * (float)(minY + maxY)) * scale);

   for (int i = 0; i < triBuf.size(); i+=3) {
      int posV1, posV2, posV3;
      posV1 = 3 * triBuf.at(i);
      posV2 = 3 * triBuf.at(i + 1);
      posV3 = 3 * triBuf.at(i + 2);

      float v1x, v1y, v2x, v2y, v3x, v3y;

      v1x = scale * posBuf.at(posV1) + tx;
      v1y = scale * posBuf.at(posV1 + 1) + ty;
      v2x = scale * posBuf.at(posV2) + tx;
      v2y = scale * posBuf.at(posV2 + 1) + ty;
      v3x = scale * posBuf.at(posV3) + tx;
      v3y = scale * posBuf.at(posV3 + 1) + ty;

      Vertex v1 = Vertex(v1x, v1y, posBuf.at(posV1 + 2), 255, 0, 0);
      Vertex v2 = Vertex(v2x, v2y, posBuf.at(posV2 + 2), 255, 0, 0);
      Vertex v3 = Vertex(v3x, v3y, posBuf.at(posV3 + 2), 255, 0, 0);

      Triangle tri = Triangle(v1, v2, v3);
      triangles.push_back(tri);
   }

   for (int k = 0; k < 1000; k += 100) {
      image->setPixel(0, k, 255, 255,255);
      image->setPixel(k, 0, 255, 255,255);
   }   

   for (int i = 0; i < triangles.size(); i++) {
      float xMinBox = triangles.at(i).xMin;
      float xMaxBox = triangles.at(i).xMax;
      float yMinBox = triangles.at(i).yMin;
      float yMaxBox = triangles.at(i).yMax; 

      Vertex v1 = triangles.at(i).getV1();
		Vertex v2 = triangles.at(i).getV2();
		Vertex v3 = triangles.at(i).getV3();

      float z1, z2, z3, zRatio, zValue, zMax, zMin;
      z1 = triangles.at(i).getV1().getZ();
      z2 = triangles.at(i).getV2().getZ();
      z3 = triangles.at(i).getV3().getZ();
      zMin = fmin(z1, fmin(z2, z3));
      zMax = fmax(z1, fmax(z2, z3));

      float areaTotal;
      Triangle triangle = Triangle(v1, v2, v3);
		triangle.setArea();
		areaTotal = triangle.getArea();

      for(int y = yMinBox; y < yMaxBox; y++) {
         for(int x = xMinBox; x < xMaxBox; x++) {
            Vertex p = Vertex(x, y, 0, 255, 0, 0);
				Triangle tri1 = Triangle(p, v2, v3);
				Triangle tri2 = Triangle(v1, p, v3);
				Triangle tri3 = Triangle(v1, v2, p);

            image->setPixel(500, 800, 255, 255 ,255);

				tri1.setArea();
				tri2.setArea();
				tri3.setArea();

				float a, b, c;


				a = tri1.getArea()/areaTotal;
				b = tri2.getArea()/areaTotal;
				c = tri3.getArea()/areaTotal;

            zValue = a * z1 + b * z2 + c * z3;
            zRatio = (zValue - zMin) / (zMax - zMin);
					
				if (a >= -0.01 && a <= 1.01) {
					if (b >= -0.01 && b <= 1.01) {
						if (c >= -0.0 && c <= 1.01) {
                     if (zBuf.at(width * y + x) < zValue) {
						      image->setPixel(x, y, 255 * zRatio, 0, 0);
                        zBuf.at(width * y + x) = zValue;
                     }
						}
					}
				}
         }
     }
   }

   image->writeToFile(fileName);
   return 0;
}
