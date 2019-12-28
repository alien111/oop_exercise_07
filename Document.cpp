#include "Document.h"


void Document::addFigure(std::unique_ptr<figure> fig) {
	figures.emplace_back(std::move(fig));
	
	commandStack.push(std::make_unique<CommandAdd>(figures.size() - 1, this));

}
void Document::removeFigure(int id) {
	//commandStack.push(std::make_unique<remove_command>(remove_command(this, std::move(figures[id]), id)));
	//figures.pop_back();

	commandStack.push(std::make_unique<CommandRemove>(id, figures[id], this));
	figures.erase(figures.begin() + id);

}
void Document::undo() {
	if (commandStack.size()) {

		commandStack.top() -> undo();

		commandStack.pop();
	
	}
}

void Document::removeByClick(vertex v) {
	std::vector<int> toDelete;
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i] -> isPointInside(v)) {
			toDelete.push_back(i);
			//std::string type_ = active_builder -> getType();

			commandStack.push(std::make_unique<CommandRemove>(i, figures[i], this));
						

		}
	}

	for (int i = 0; i < toDelete.size(); i++) {
		figures.erase(figures.begin() + toDelete[i] - i);
	}
}

void Document::render(const sdl::renderer& renderer) {
	for (const std::shared_ptr<figure>& figure : figures) {
		figure -> render(renderer);
	}
}

void Document::Save(std::ofstream& os) {
	for (const std::shared_ptr<figure>& figure : figures) {
		figure -> save(os);
	}
}

void Document::Load(std::ifstream& is) {

	figures.clear();

	while ( ! commandStack.empty() )
	{
    	commandStack.pop();
	}
	
	std::string type;

	while(std::getline(is, type)) {
		if (type == "rectangle") {
			std::array<vertex, 4> vrt;
			for (int i = 0; i < 4; i++) {
				is >> vrt[i];
			}
			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}
			std::unique_ptr<figure> rect = std::make_unique<rectangle>(vrt);
			rect -> setColor(colorTmp);
			figures.emplace_back(std::move(rect));
		} else if (type == "rhombus") {
			std::array<vertex, 4> vrt;
			for (int i = 0; i < 4; i++) {
				is >> vrt[i];
			}
			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}
			std::unique_ptr<figure> rhom = std::make_unique<rhombus>(vrt);
			rhom -> setColor(colorTmp);
			figures.emplace_back(std::move(rhom));
		} else if (type == "trapezoid") {
			std::array<vertex, 4> vrt;
			for (int i = 0; i < 4; i++) {
				is >> vrt[i];
			}
			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}
			std::unique_ptr<figure> trap = std::make_unique<trapezoid>(vrt);
			trap -> setColor(colorTmp);
			figures.emplace_back(std::move(trap));
		} else if (type == "polygon") {
			int sz;
			is >> sz;
			std::vector<vertex> vrt(sz);
						
			for (int i = 0; i < sz; i++) {
				is >> vrt[i];
			}
			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}
			std::unique_ptr<figure> poly = std::make_unique<polygon>(vrt);
			poly -> setColor(colorTmp);
			figures.emplace_back(std::move(poly));
		} else if (type == "brokenLine") {
			int sz;
			is >> sz;
			std::vector<vertex> vrt(sz);
					
			for (int i = 0; i < sz; i++) {
				is >> vrt[i];
			}
			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}
			std::unique_ptr<figure> bl = std::make_unique<brokenLine>(vrt);
			bl -> setColor(colorTmp);
			figures.emplace_back(std::move(bl));
		} else if (type == "circle") {
			std::vector<vertex> vrt(2);
			is >> vrt[0] >> vrt[1];

			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}

			std::unique_ptr<figure> crcl = std::make_unique<circle>(vrt);
			crcl -> setColor(colorTmp);
			figures.emplace_back(std::move(crcl));
		}
			
	}

}

void Document::clear() {

	while ( ! commandStack.empty() )
	{
    	commandStack.pop();
	}

	figures.clear();

}