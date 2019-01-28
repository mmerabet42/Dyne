#include "dn/Model.hpp"
#include "dn/Math.hpp"
#include "dn/Utils.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.hpp"

dn::Model dn::Model::generatePoints(const int &p_n, const float &p_radius)
{
	dn::VertexArray vertices;
	dn::IndiceArray indices;

	for (int i = 0; i < p_n; ++i)
	{
		vertices.push_back(dn::Vertex
			{{
				dn::math::random(-p_radius, p_radius),
				dn::math::random(-p_radius, p_radius),
				dn::math::random(-p_radius, p_radius),
			}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}});
		indices.push_back((GLuint)i);
	}
	return (dn::Model(vertices, DN_POINTS, indices));
}

dn::Model dn::Model::generateGridPlane(const int &p_n, const float &p_distance)
{
	dn::VertexArray vertices;
	dn::IndiceArray indices;
	float length = (float)(p_n - 1) * p_distance;
	float startPos = length / 2.0f;
	float pos = length / -2.0f;

	for (int i = 0; i < p_n; ++i)
	{
		vertices.push_back({
			{pos, 0.f, -startPos}, {1.f, 1.f, 1.f, 0.3f}, {0.f, 0.f}, {0.f, 0.f, 0.f}
		});
		vertices.push_back({
			{pos, 0.f, startPos}, {1.f, 1.f, 1.f, 0.3f}, {0.f, 0.f}, {0.f, 0.f, 0.f}
		});

		vertices.push_back({
			{-startPos, 0.f, pos}, {1.f, 1.f, 1.f, 0.3f}, {0.f, 0.f}, {0.f, 0.f, 0.f}
		});
		vertices.push_back({
			{startPos, 0.f, pos}, {1.f, 1.f, 1.f, 0.3f}, {0.f, 0.f}, {0.f, 0.f, 0.f}
		});

		indices.push_back((i * 4) + 0);
		indices.push_back((i * 4) + 1);
		indices.push_back((i * 4) + 2);
		indices.push_back((i * 4) + 3);
		pos += p_distance;
	}
	return (dn::Model(vertices, DN_LINES, indices));
}

dn::Model dn::Model::cube({
	// FRONT FACE
	{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.25f}, {0.f, 0.f, 1.f}},
	{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.25f}, {0.f, 0.f, 1.f}},
	{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}, {0.f, 0.f, 1.f}},
	{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}, {0.f, 0.f, 1.f}},
	// BACK FACE
	{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.25f}, {0.f, 0.f, -1.f}},
	{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.25f}, {0.f, 0.f, -1.f}},
	{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}, {0.f, 0.f, -1.f}},
	{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}, {0.f, 0.f, -1.f}},
	// LEFT FACE
	{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.25f}, {-1.f, 0.f, 0.f}},
	{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.25f}, {-1.f, 0.f, 0.f}},
	{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}, {-1.f, 0.f, 0.f}},
	{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}, {-1.f, 0.f, 0.f}},
	// RIGHT FACE
	{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.25f}, {1.f, 0.f, 0.f}},
	{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.25f}, {1.f, 0.f, 0.f}},
	{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}, {1.f, 0.f, 0.f}},
	{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}, {1.f, 0.f, 0.f}},
	// TOP FACE
	{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.50f, 0.50f}, {0.f, 1.f, 0.f}},
	{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.75f, 0.50f}, {0.f, 1.f, 0.f}},
	{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.50f, 0.75f}, {0.f, 1.f, 0.f}},
	{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.75f, 0.75f}, {0.f, 1.f, 0.f}},
	// BOTTOM FACE
	{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}, {0.f, -1.f, 0.f}},
	{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}, {0.f, -1.f, 0.f}},
	{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.75f}, {0.f, -1.f, 0.f}},
	{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.75f}, {0.f, -1.f, 0.f}},
}, DN_TRIANGLES, {
	2, 1, 0, 1, 2, 3,
	6, 5, 4, 5, 6, 7,
	10, 9, 8, 9, 10, 11,
	14, 13, 12, 13, 14, 15,
	18, 17, 16, 17, 18, 19,
	22, 21, 20, 21, 22, 23
});

dn::Model dn::Model::cubeEdges({
	// FRONT FACE
	{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
	{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
	{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
	{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
	// BACK FACE
	{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
	{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
	{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
	{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
}, DN_LINE_STRIP, {
	0, 1, 3, 2, 0, 4, 6, 2, 3, 7, 6, 4, 5, 1, 5, 7
});

dn::Model dn::Model::loadObj(const std::string &p_path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	dn::VertexArray vertices;
	dn::IndiceArray indices;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, p_path.c_str()))
		std::cout << warn + err << std::endl;

	for (const auto &shape : shapes)
	{
		for (const auto &index : shape.mesh.indices)
		{
			dn::Vertex vertex;

			vertex.position[0] = attrib.vertices[3 * index.vertex_index + 0];
			vertex.position[1] = attrib.vertices[3 * index.vertex_index + 1];
			vertex.position[2] = attrib.vertices[3 * index.vertex_index + 2];

			vertex.tex[0] = attrib.texcoords[2 * index.texcoord_index + 0];
			vertex.tex[1] = 1.0f - attrib.texcoords[2 * index.texcoord_index + 1];

			vertex.color[0] = 1.f;
			vertex.color[1] = 1.f;
			vertex.color[2] = 1.f;

			vertex.normal[0] = 0.f;
			vertex.normal[1] = 0.f;
			vertex.normal[2] = 0.f;

			vertices.push_back(vertex);
			indices.push_back(indices.size());
		}
	}
	return (dn::Model(vertices, DN_TRIANGLES, indices));
}

static dn::Vertex createVertex(const std::vector<std::string> &p_attrs,
							const std::vector<glm::vec3> &p_v_h,
							const std::vector<glm::vec3> &p_vn_h,
							const std::vector<glm::vec2> &p_vt_h)
{
	int v_i = std::stoi(p_attrs[0]) - 1;
	int vt_i = -1;
	if (!p_attrs[1].empty())
		vt_i = std::stoi(p_attrs[1]) - 1;
	int vn_i = -1;
	if (p_attrs.size() > 2 && !p_attrs[2].empty())
		vn_i = std::stoi(p_attrs[2]) - 1;
	dn::Vertex result;
	result.position[0] = p_v_h[v_i].x;
	result.position[1] = p_v_h[v_i].y;
	result.position[2] = p_v_h[v_i].z;
	result.tex[0] = (vt_i == -1 ? 0.0f : p_vt_h[vt_i].x);
	result.tex[1] = (vt_i == -1 ? 0.0f : p_vt_h[vt_i].y);
	result.normal[0] = (vn_i == -1 ? 0.0f : p_vn_h[vn_i].x);
	result.normal[1] = (vn_i == -1 ? 0.0f : p_vn_h[vn_i].y);
	result.normal[2] = (vn_i == -1 ? 0.0f : p_vn_h[vn_i].z);
	result.color[0] = 1.0f;
	result.color[1] = 1.0f;
	result.color[1] = 1.0f;
	return (result);
}

// Parse a .obj file
dn::Model dn::Model::parse(const std::string &p_path)
{
	// Opening the file
	std::ifstream file(p_path);
	// If the file failed to open, an empty model is returned
	if (!file.is_open())
		return (dn::Model({}, DN_POINTS, {}));

	dn::VertexArray vertices;
	dn::IndiceArray indices;

	std::vector<glm::vec3> v_h, vn_h;
	std::vector<glm::vec2> vt_h;

	int i = 0;
	// Read line by line, and store the current line in `line'
	std::string line;
	while (std::getline(file, line))
	{
		// Split the line using the space as a delimiter
		std::vector<std::string> tokens = dn::split(line, ' ');
		if (tokens.empty())
			continue ;
		// If vertex position attribute
		if (tokens[0] == "v")
		{
			// Push in the in the 'v_h' list, std::stof is a function for converting strings to floats
			glm::vec3 v(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
			v_h.push_back(v);
		}
		// If texture coordinate attribute
		else if (tokens[0] == "vt")
		{
			// Push in the 'vt_h' list
			glm::vec2 v(std::stof(tokens[1]), std::stof(tokens[2]));
			vt_h.push_back(v);
		}
		// If normal attribute
		else if (tokens[0] == "vn")
		{
			 // Push in the 'vn_h' list
			glm::vec3 v(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
			vn_h.push_back(v);
		}
		// If face attribute
		else if (tokens[0] == "f")
		{
			// A face is, in fact, a triangle, and a triangle is defined by three vertices
			// The face, actually connects the vertices, texture coordinates and normals
			std::vector<std::string> attrs1 = dn::split(tokens[1], '/', true);
			// Three vertices that are seperated by a space and each attribute is seperated by a '/'
			std::vector<std::string> attrs2 = dn::split(tokens[2], '/', true);
			// There are 3 vertices, so 3 splits
			std::vector<std::string> attrs3 = dn::split(tokens[3], '/', true);

			indices.push_back(i++);
			indices.push_back(i++);
			indices.push_back(i++);

			vertices.push_back(createVertex(attrs1, v_h, vn_h, vt_h));
			vertices.push_back(createVertex(attrs2, v_h, vn_h, vt_h));
			vertices.push_back(createVertex(attrs3, v_h, vn_h, vt_h));
		}
	}

	// Close the file
	file.close();
	// And return the generated model
	return (dn::Model(vertices, DN_TRIANGLES, indices));
}

