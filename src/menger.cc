#include "menger.h"

namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

Menger::Menger(glm::vec3 min, glm::vec3 max) : min(min), max(max), dirty_(true) {}

Menger::~Menger() {}

void
Menger::set_nesting_level(int level)
{
	nesting_level_ = level;
	dirty_ = true;
}

bool
Menger::is_dirty() const
{
	return dirty_;
}

void
Menger::set_clean()
{
	dirty_ = false;
}

void
Menger::generate_geometry(std::vector<glm::vec4>& obj_vertices, std::vector<glm::vec4>& vtx_normals,
						std::vector<glm::uvec3>& obj_faces) const {

	if(!this->nesting_level_) {
        generate_menger(obj_vertices, vtx_normals, obj_faces, min, max);
        return;
    }

    std::vector<glm::vec3> mins;
    mins.push_back(this->min);

    for(int i = 1; i <= nesting_level_; i++) {
        glm::vec3 w = (max - min) * float(1.0f / pow(3.0f, i));
        glm::vec3 x = glm::vec3(w.x, 0, 0);
        glm::vec3 y = glm::vec3(0, w.y, 0);
        glm::vec3 z = glm::vec3(0, 0, w.z);

        std::vector<glm::vec3> subcube;
        subcube = mins;
        mins.clear();

        for(glm::vec3 vec : subcube) {
            mins.push_back(vec);
            mins.push_back(vec + x);
            mins.push_back(vec + 2.0f * x);
            mins.push_back(vec + z);
            mins.push_back(vec + z + 2.0f * x);
            mins.push_back(vec + 2.0f * z);
            mins.push_back(vec + 2.0f * z + x);
            mins.push_back(vec + 2.0f * z + 2.0f * x);
            mins.push_back(vec + y);
            mins.push_back(vec + y + 2.0f * z);
            mins.push_back(vec + y + 2.0f * z + 2.0f * x);
            mins.push_back(vec + y + 2.0f * x);
            mins.push_back(vec + 2.0f * y);
            mins.push_back(vec + 2.0f * y + x);
            mins.push_back(vec + 2.0f * y + 2.0f * x);
            mins.push_back(vec + 2.0f * y + z);
            mins.push_back(vec + 2.0f * y + z + 2.0f * x);
            mins.push_back(vec + 2.0f * y + 2.0f * z);
            mins.push_back(vec + 2.0f * y + 2.0f * z + x);
            mins.push_back(vec + 2.0f * y + 2.0f * z + 2.0f * x);
        }
    }

    glm::vec3 d = (max - min) * float(1.0 / pow(3.0f, nesting_level_));
    for(auto it = mins.begin(); it != mins.end(); ++it)
        generate_menger(obj_vertices, vtx_normals, obj_faces, *it, *it + d);

}

void
Menger::generate_menger(std::vector<glm::vec4> &obj_vertices, std::vector<glm::vec4> &vtx_normals,
							std::vector<glm::uvec3> &obj_faces, glm::vec3 min, glm::vec3 max) const {

	unsigned long v = obj_vertices.size();
	obj_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	obj_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));

	obj_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	obj_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	obj_vertices.push_back(glm::vec4(min.x, max.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, max.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, max.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, max.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

	obj_vertices.push_back(glm::vec4(min.x, min.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(min.x, min.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, min.y, min.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	obj_vertices.push_back(glm::vec4(max.x, min.y, max.z, 1.0f));
	vtx_normals.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

	obj_faces.push_back(glm::uvec3(v, v+ 1, v + 2));
	obj_faces.push_back(glm::uvec3(v, v + 2, v + 3));
	obj_faces.push_back(glm::uvec3(v + 4, v + 5, v + 6));
	obj_faces.push_back(glm::uvec3(v + 4, v + 6, v + 7));
	obj_faces.push_back(glm::uvec3(v + 8, v + 9, v + 10));
	obj_faces.push_back(glm::uvec3(v + 8, v + 10, v + 11));
	obj_faces.push_back(glm::uvec3(v + 12, v + 13, v + 14));
	obj_faces.push_back(glm::uvec3(v + 12, v + 14, v + 15));
	obj_faces.push_back(glm::uvec3(v + 16, v + 17, v + 18));
	obj_faces.push_back(glm::uvec3(v + 16, v + 18, v + 19));
	obj_faces.push_back(glm::uvec3(v + 20, v + 21, v + 22));
	obj_faces.push_back(glm::uvec3(v + 20, v + 22, v + 23));
}


