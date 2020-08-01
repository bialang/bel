#include "module.hpp"

#include <bia/bsl/helper.hpp>
#include <bia/connector/connector-inl.hpp>
#include <iostream>
#include <rang.hpp>

using namespace bel::rang;

module::module(bia::gc::gc& gc) : _symbols{ _init(gc) }
{}

module::version_type module::version() const noexcept
{
	return 0;
}

bia::util::not_null<bia::member::member*> module::create(bia::gc::gc& gc)
{
	return _symbols.get();
}

void module::gc_mark_children(bool mark) const noexcept
{
	bia::gc::object::gc_mark(_symbols.get(), mark);
}

void module::register_gcables(bia::gc::gc& gc) const noexcept
{
	gc.register_gcable(_symbols.get());

	for (const auto& i : _symbols->map()) {
		gc.register_gcable(i.first.get());
		gc.register_gcable(i.second.get());
	}
}

bia::member::native::dict* module::_init(bia::gc::gc& gc)
{
	using namespace bia::bsl;

	const auto dict = gc.construct<bia::member::native::dict>().release();
	::rang::style::bold;
	put_function(gc, *dict, "print_red", +[](const char* c) {
		std::cout << ::rang::fg::red << ::rang::style::bold << c << ::rang::style::reset;
	});
	//	put_function(gc, *dict, "print", &print);
	//	put_function(gc, *dict, "read", &read_input);

	return dict;
}
