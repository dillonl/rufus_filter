#ifndef SRC_UTILS_NONCOPYABLE_HPP
#define SRC_UTILS_NONCOPYABLE_HPP

namespace rufus
{

	//  Private copy constructor and copy assignment ensure classes derived from
	//  class noncopyable cannot be copied.

	//  Contributed by Dave Abrahams

	namespace noncopyable_  // protection from unintended ADL
	{
		  class noncopyable
		  {
		  protected:
			  constexpr noncopyable() = default;
			  ~noncopyable() = default;
		  private:  // emphasize the following members are private
			  noncopyable( const noncopyable& );
			  noncopyable& operator=( const noncopyable& );
		  };
	}

	typedef noncopyable_::noncopyable noncopyable;

} // namespace boost

#endif  // SRC_UTILS_NONCOPYABLE_HPP
