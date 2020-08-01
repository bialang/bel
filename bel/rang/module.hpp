#ifndef BEL_RANG_MODULE_HPP_
#define BEL_RANG_MODULE_HPP_

#include <bia/bvm/module/module.hpp>
#include <bia/gc/object/pointer.hpp>
#include <bia/member/native/dict.hpp>

namespace bel {
namespace rang {

class module : public bia::bvm::module::module
{
public:
	module(bia::gc::gc& gc);
	version_type version() const noexcept override;
	bia::util::not_null<bia::member::member*> create(bia::gc::gc& gc) override;
	void gc_mark_children(bool mark) const noexcept override;

protected:
	void register_gcables(bia::gc::gc& gc) const noexcept override;

private:
	bia::gc::object::immutable_pointer<bia::member::native::dict> _symbols;

	static bia::member::native::dict* _init(bia::gc::gc& gc);
};

} // namespace rang
} // namespace bel

#endif
