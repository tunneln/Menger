#include "menger.h"

namespace {
	const int kMinLevel = 0;
	const int kMaxLevel = 4;
};

Menger::Menger(glm::vec3 min, glm::vec3 max)
{
	this->min = min;
	this->max = max;
	this->dirty_ = true;
}

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
Menger::generate_geometry(std::vector<glm::vec4>& obj_vertices,
							std::vector<glm::vec4>& vtx_normals,
							std::vector<glm::uvec3>& obj_faces) const {

	if(!this->nesting_level_) {
		generate_menger(obj_vertices, vtx_normals, obj_faces, min, max);
		return ;
	}

	std::vector<glm::vec3> computed = {this->min};
	std::vector<glm::vec3> sub_mins;

	for(int i = 1; i <= nesting_level_; i++) {
		glm::vec3 w = float(1.0f / pow(3.0f, i)) * (max - min);
		glm::vec3 x = glm::vec3(w.x, 0, 0);
		glm::vec3 y = glm::vec3(0, w.y, 0);
		glm::vec3 z = glm::vec3(0, 0, w.z);

		sub_mins = computed;

		for(glm::vec3& minvec : sub_mins) {
			computed = {minvec, (minvec + x), (minvec + 2.0f * x),
			( minvec + z), ( minvec + z + 2.0f * x), ( minvec + 2.0f * z),
			( minvec + 2.0f * z + x), ( minvec + 2.0f * z + 2.0f * x),
			( minvec + y), ( minvec + y + 2.0f * z), ( minvec + y + 2.0f * z + 2.0f * x),
			( minvec + y + 2.0f * x), ( minvec + 2.0f * y), ( minvec + 2.0f * y + x),
			( minvec + 2.0f * y + 2.0f * x), ( minvec + 2.0f * y + z), ( minvec + 2.0f * y + z + 2.0f * x),
			( minvec + 2.0f * y + 2.0f * z), ( minvec + 2.0f * y + 2.0f * z + x),
			( minvec + 2.0f * y + 2.0f * z + 2.0f * x)};
		}
	}

	glm::vec3 d = float(1.0 / pow(3.0f, nesting_level_)) * (max - min) ;
	for(auto it = computed.begin(); it != computed.end(); ++it)
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


