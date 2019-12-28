#include "polygon.h"

polygon::polygon(const std::vector<vertex>& vertices) : vertices_(vertices) {}

std::string polygon::getType() {
	return "polygon";
}

void polygon::setColor(std::vector<int> color) {
	for (int i = 0; i < 3; i++) {
		color_.push_back(color[i]);
	}
}
	
void polygon::render(const sdl::renderer& renderer) const {
	renderer.set_color(color_[0], color_[1], color_[2]);
	for (int32_t i = 0; i < vertices_.size() - 1; ++i) {
		renderer.draw_line(vertices_[i].x, vertices_[i].y,
			vertices_[(i + 1)].x, vertices_[(i + 1)].y);
	}
	renderer.draw_line(vertices_[vertices_.size() - 1].x, vertices_[vertices_.size() - 1].y, vertices_[0].x, vertices_[0].y);
}

void polygon::save(std::ostream& os) const {
	os << "polygon\n";
	os << vertices_.size() << '\n';
	for (int32_t i = 0; i < vertices_.size(); ++i) {
		os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
	}
	os << color_[0] << ' ' << color_[1] << ' ' << color_[2] << '\n';
}


bool polygon::isPointInside(vertex v) const {
	int x = v.x;
	int y = v.y;
	int i1, i2, n, N, S, S1, S2, S3;
	bool flag;
  	N = vertices_.size();
  	for (n = 0; n < N; n++) {
   		flag = false;
   		i1 = n < N-1 ? n + 1 : 0;
   		while (flag == false) {
    		i2 = i1 + 1;
    		if (i2 >= N)
      			i2 = 0;
    		if (i2 == (n < N-1 ? n + 1 : 0))
      			break;
   	 		S = abs (vertices_[i1].x * (vertices_[i2].y - vertices_[n ].y) + vertices_[i2].x * (vertices_[n ].y - vertices_[i1].y) + vertices_[n].x  * (vertices_[i1].y - vertices_[i2].y));
    		S1 = abs (vertices_[i1].x * (vertices_[i2].y - y) + vertices_[i2].x * (y       - vertices_[i1].y) + x       * (vertices_[i1].y - vertices_[i2].y));
    		S2 = abs (vertices_[n ].x * (vertices_[i2].y - y) + vertices_[i2].x * (y       - vertices_[n ].y) + x       * (vertices_[n ].y - vertices_[i2].y));
    		S3 = abs (vertices_[i1].x * (vertices_[n ].y - y) + vertices_[n ].x * (y       - vertices_[i1].y) + x       * (vertices_[i1].y - vertices_[n ].y));
   			if (S == S1 + S2 + S3) {
     			flag = true;
     			break;
    		}
    		i1 = i1 + 1;
    		if (i1 >= N)
     			i1 = 0;
   		}
   		if (flag == false)
     		break;
  	}
  	return flag;
}


std::unique_ptr<figure> polygon_builder::add_vertex(const vertex& v) {
	if (v.x != -1 && v.y != -1) {
		vertices_.push_back(v);
		return nullptr;
	}
		
	return std::make_unique<polygon>(vertices_);
}

std::string polygon_builder::getType() {
	return "polygon";
}