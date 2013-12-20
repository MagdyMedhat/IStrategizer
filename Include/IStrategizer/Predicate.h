#ifndef PREDICATE_H
#define PREDICATE_H

#include <cassert>

namespace IStrategizer
{
	class BasePredicate
	{
	public:
		virtual bool Equals( const BasePredicate* p_other) = 0;
		virtual bool operator()() = 0;
		virtual bool Call() = 0;
	};

	template<class TReciever>
	class Predicate : public BasePredicate
	{
	private:
		typedef bool (TReciever::*PTF)();
		PTF         m_ptr2Func;
		TReciever*  m_ptr2Object;

	public:
		Predicate(TReciever* p_ptr2Object, PTF p_ptr2Func)
		{
			m_ptr2Func      = p_ptr2Func;
			m_ptr2Object    = p_ptr2Object;
		}

		bool Equals(const BasePredicate* p_other)
		{
			const Predicate<TReciever>* other;

			other = static_cast<const Predicate<TReciever>*>(p_other);

			assert(other != nullptr);
			assert(m_ptr2Object != nullptr);

			return other->m_ptr2Object == m_ptr2Object && other->m_ptr2Func == m_ptr2Func;
		}

		virtual bool operator()()
		{
			assert(m_ptr2Object != nullptr);
			return (m_ptr2Object->*m_ptr2Func)();
		}

		virtual bool Call()
		{
			assert(m_ptr2Object != nullptr);
			return (m_ptr2Object->*m_ptr2Func)();
		}
	};
}

#endif // PREDICATE_H