#include <bia/bia.hpp>
#include "bel/rang/module.hpp"

int main()
{
	bia::engine engine;

	engine.module<bel::rang::module>("rang", engine.gc());

	std::stringstream s;
	s<<R"(import rang; rang.print_red("hihi\n"))";
	engine.execute(s);
}
