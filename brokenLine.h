#ifndef D_BROKENLINE_H
#define D_BROKENLINE_H 1

#include "figure.h"
#include "builder.h"


struct brokenLine : figure {

	brokenLine(const std::vector<vertex>& vertices);

	void setColor(std::vector<int> color) override;
	
	void render(const sdl::renderer& renderer) const override;
	void save(std::ostream& os) const override;


	bool isPointInside(vertex v) const override;

private:
	std::vector<int> color_;
	std::vector<vertex> vertices_;


};

struct brokenLine_builder : builder {
	std::unique_ptr<figure> add_vertex(const vertex& v) override;

	std::string getType();
private:
	
	std::vector<vertex> vertices_;

};

#endif