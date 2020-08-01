#include "bel/curl/module.hpp"
#include "bel/rang/module.hpp"

#include <bia/bia.hpp>

int main(int argc, char** argv)
{
	bia::engine engine;

	engine.use_bsl({ argv, argv + argc });
	engine.module<bel::rang::module>("rang", engine.gc());
	engine.module<bel::curl::module>("curl", engine.gc());

	std::stringstream s;
	s << R"(
		import rang
		import curl
		import io

		rang.print_red(curl.get("http://example.com/"))
		io.print(curl.version)
	)";
	engine.execute(s);
}
