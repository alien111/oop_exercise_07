#include "brokenLine.h"

brokenLine::brokenLine(const std::vector<vertex>& vertices) : vertices_(vertices) {}

void brokenLine::setColor(std::vector<int> color) {
	for (int i = 0; i < 3; i++) {
		color_.push_back(color[i]);
	}
}
	
void brokenLine::render(const sdl::renderer& renderer) const {
	renderer.set_color(color_[0], color_[1], color_[2]);
	for (int32_t i = 0; i < vertices_.size() - 1; ++i) {
		renderer.draw_line(vertices_[i].x, vertices_[i].y, 
			vertices_[(i + 1)].x, vertices_[(i + 1)].y);
	}
}

void brokenLine::save(std::ostream& os) const {
	os << "brokenLine\n";
	os << vertices_.size() << '\n';
	for (int32_t i = 0; i < vertices_.size(); ++i) {
		os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
	}
	os << color_[0] << ' ' << color_[1] << ' ' << color_[2] << '\n';
}


bool brokenLine::isPointInside(vertex v) const {
	return false;
}

std::unique_ptr<figure> brokenLine_builder::add_vertex(const vertex& v) {
	if (v.x != -1 && v.y != -1) {
		vertices_.push_back(v);
		return nullptr;
	}
		
	return std::make_unique<brokenLine>(vertices_);
}

std::string brokenLine_builder::getType() {
	return "brokenLine";
}
