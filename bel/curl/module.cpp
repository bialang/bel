#include "module.hpp"

#include <bia/bsl/helper.hpp>
#include <bia/connector/connector-inl.hpp>
#include <bia/creator/creator.hpp>
#include <bia/gc/temporary_token.hpp>
#include <curl/curl.h>
#include <sstream>

using namespace bel::curl;

inline std::string get(const char* url)
{
	if (auto curl = curl_easy_init()) {
		std::stringstream out;

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(
		    curl, CURLOPT_WRITEFUNCTION, +[](char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
			    auto& out = *static_cast<std::stringstream*>(userdata);

			    out.write(ptr, nmemb);

			    return nmemb;
		    });
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		return out.str();
	}

	return "";
}

module::module(bia::gc::gc& gc) : _symbols{ _init(gc) }
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

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

	const auto dict  = gc.construct<bia::member::native::dict>().release();
	const auto token = gc.activate_temporarily();

	put_function(gc, *dict, "get", &get);
	put_gcable(gc, *dict, "version", bia::creator::create(curl_version()));

	return dict;
}
