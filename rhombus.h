#ifndef D_RHOMBUS_H 
#define D_RHOMBUS_H 1

#include "figure.h"
#include "builder.h"

struct rhombus : figure {
	rhombus(const std::array<vertex, 4>& vertices);

	void setColor(std::vector<int> color) override;

	void render(const sdl::renderer& renderer) const override;

	void save(std::ostream& os) const override;


	bool isPointInside(vertex v) const override;

private:
	std::vector<int> color_;
	std::array<vertex, 4> vertices_;

};

struct rhombus_builder : builder {
	std::unique_ptr<figure> add_vertex(const vertex& v) override;

	std::string getType();
private:
	int32_t n_ = 0;
	std::array<vertex, 4> vertices_;

};


#endif // !D_RHOMBUS_H 
