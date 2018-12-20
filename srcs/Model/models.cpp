#include "Model.hpp"
#include "Math.hpp"

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
