#include "Model.hpp"
#include "Math.hpp"
#include "utils.hpp"
#include <fstream>
#include <array>

static dn::Vertex createVertex(const std::vector<std::string> &p_attrs,
							const std::vector<std::array<float, 3>> &p_v_h,
							const std::vector<std::array<float, 3>> &p_vn_h,
							const std::vector<std::array<float, 2>> &p_vt_h)
{
	int v_i = std::stoi(p_attrs[0]) - 1;
	int vt_i = -1;
	if (!p_attrs[1].empty())
		vt_i = std::stoi(p_attrs[1]) - 1;
	int vn_i = -1;
	if (p_attrs.size() > 2)
		vn_i = std::stoi(p_attrs[2]) - 1;
/*	std::cout << "VERTEX>>>>>>>>>>>>>\n";
	std::cout << "\tPosition>>> " << p_v_h[v_i][0] << ", " << p_v_h[v_i][1] << ", " << p_v_h[v_i][2] << std::endl;
	if (vt_i != -1)
		std::cout << "\tTexture>>>  " << p_vt_h[vt_i][0] << ", " << p_vt_h[vt_i][1] << std::endl;
	std::cout << "\tNormal>>>   " << p_vn_h[vn_i][0] << ", " << p_vn_h[vn_i][1] << ", " << p_vn_h[vn_i][2] << std::endl;
*/	return (dn::Vertex{
		{p_v_h[v_i][0], p_v_h[v_i][1], p_v_h[v_i][2]},
		{1.f, 1.f, 1.f, 1.f},
		{(vt_i == -1 ? 0.0f : p_vt_h[vt_i][0]), (vt_i == -1 ? 0.0f : p_vt_h[vt_i][1])},
		{(vn_i == -1 ? 0.0f : p_vn_h[vn_i][0]), (vn_i == -1 ? 0.0f : p_vn_h[vn_i][1]), (vn_i == -1 ? 0.0f : p_vn_h[vn_i][2])}
	});
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

	std::vector<std::array<float, 3>> v_h, vn_h;
	std::vector<std::array<float, 2>> vt_h;

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
			// Push in the in the 'v_h' list, std::stof is a function for converting strings to floats
			v_h.push_back({std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])});
		// If texture coordinate attribute
		else if (tokens[0] == "vt")
			// Push in the 'vt_h' list
			vt_h.push_back({std::stof(tokens[1]), std::stof(tokens[2])});
		// If normal attribute
		else if (tokens[0] == "vn")
			 // Push in the 'vn_h' list
			vn_h.push_back({std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])});
		// If face attribute
		else if (tokens[0] == "f")
		{
			// A face is, in fact, a triangle, and a triangle is defined by three vertices
			// The face, actually connects the vertices, texture coordinates and normals
			std::vector<std::string> attrs1 = dn::split(tokens[1], '/', true);
			// Three vertices that are seperated by a space and the attributes are seperated by a '/'
			std::vector<std::string> attrs2 = dn::split(tokens[2], '/', true);
			// There are three vertices, so 3 splits
			std::vector<std::string> attrs3 = dn::split(tokens[3], '/', true);

			indices.push_back(std::stoi(attrs1[0]) - 1);
			indices.push_back(std::stoi(attrs2[0]) - 1);
			indices.push_back(std::stoi(attrs3[0]) - 1);

			vertices.push_back(createVertex(attrs1, v_h, vn_h, vt_h));
			vertices.push_back(createVertex(attrs2, v_h, vn_h, vt_h));
			vertices.push_back(createVertex(attrs3, v_h, vn_h, vt_h));
		}
	}
	// Close the file
	file.close();
	// And return the generated model
	return (dn::Model(vertices, DN_LINES, indices));
}

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
			}, {1.f, 1.f, 1.f, 1.f}});
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
		vertices.push_back({{pos, 0.f, -startPos}, {1.f, 1.f, 1.f, 0.3f}, {0.f, 0.f}});
		vertices.push_back({{pos, 0.f, startPos}, {1.f, 1.f, 1.f, 0.3f}, {0.f, 0.f}});

		vertices.push_back({{-startPos, 0.f, pos}, {1.f, 1.f, 1.f, 0.3f}, {0.f, 0.f}});
		vertices.push_back({{startPos, 0.f, pos}, {1.f, 1.f, 1.f, 0.3f}, {0.f, 0.f}});

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
	{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.25f}},
	{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.25f}},
	{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}},
	{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}},
	// BACK FACE
	{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.25f}},
	{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.25f}},
	{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}},
	{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}},
	// LEFT FACE
	{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.25f}},
	{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.25f}},
	{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}},
	{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}},
	// RIGHT FACE
	{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.25f}},
	{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.25f}},
	{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}},
	{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}},
	// TOP FACE
	{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.50f, 0.50f}},
	{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.75f, 0.50f}},
	{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.50f, 0.75f}},
	{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.75f, 0.75f}},
	// BOTTOM FACE
	{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.50f}},
	{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.50f}},
	{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.75f}},
	{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.25f, 0.75f}},
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
	{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
	{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
	{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
	{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
	// BACK FACE
	{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
	{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
	{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
	{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
}, DN_LINE_STRIP, {
	0, 1, 3, 2, 0, 4, 6, 2, 3, 7, 6, 4, 5, 1, 5, 7
});
