#include "OBJReader.h"

void LittleEngine::Utils::readOBJ(const char* path, Mesh &mesh)
{
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> vertexTexcoords;
	std::vector<glm::vec3> vertexNormals;

	std::vector<GLint> vertexPositionIndices;
	std::vector<GLint> vertexTexcoordIndices;
	std::vector<GLint> vertexNormalIndices;

	std::stringstream ss;
	std::ifstream file(path);


	if (!file.is_open())
	{
		throw "Error: Could not open file";
	}

	std::string line = " ";
	std::string prefix = "";


	while (std::getline(file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "v")
		{
			glm::vec3 currentVector(0.f);
			ss >> currentVector.x >> currentVector.y >> currentVector.z;
			vertexPositions.push_back(currentVector);
		}
		else if (prefix == "vt")
		{
			glm::vec2 currentVector(0.f);
			ss >> currentVector.x >> currentVector.y;
			vertexTexcoords.push_back(currentVector);
		}
		else if (prefix == "vn")
		{
			glm::vec3 currentVector(0.f);
			ss >> currentVector.x >> currentVector.y >> currentVector.z;
			vertexNormals.push_back(currentVector);
		}
		else if (prefix == "f")
		{
			GLint temp = 0;
			int counter = 0;
			int sizeFace = 0;
			std::string segment;
			std::vector < std::string> segments;

			Triangle currentTriangle = Triangle();
			Quad     currentQuad     = Quad();

			while (ss >> temp)
			{
				switch (counter)
				{
				case 0:
					vertexPositionIndices.push_back(temp - 1);
					currentTriangle.addVertexIndex(vertexPositionIndices.size() - 1);
					currentQuad.addVertexIndex(vertexPositionIndices.size() - 1);
					break;
				case 1:
					vertexTexcoordIndices.push_back(temp - 1);
					break;
				case 2:
					vertexNormalIndices.push_back(temp - 1);
					break;
				default:
					break;
				}

				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					++sizeFace;
					ss.ignore(1, ' ');
				}
				
				if (counter > 2)
				{
					counter = 0;
				}
			}
			sizeFace == 3 ? mesh.quads.push_back(currentQuad) : mesh.triangles.push_back(currentTriangle);
		}
		else
		{
			// Nothing to do here
		}		
	}

	mesh.vertices.resize(vertexPositionIndices.size(), Vertex());

	for (size_t i = 0; i < mesh.vertices.size(); ++i)
	{
		mesh.vertices[i].position	 = vertexPositions	[vertexPositionIndices[i]];
		mesh.vertices[i].texCoord	 = vertexTexcoords	[vertexTexcoordIndices[i]];
		mesh.vertices[i].normal		 = vertexNormals	[vertexNormalIndices[i]];
		mesh.vertices[i].color		 = glm::vec3(1.f);
	}
}
