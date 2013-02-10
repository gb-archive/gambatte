#ifndef SCOPED_PTR_H
#define SCOPED_PTR_H

#include "transfer_ptr.h"
#include "uncopyable.h"

template<class T>
class scoped_ptr : Uncopyable {
public:
	explicit scoped_ptr(T *p = 0) : p_(p) {}
	template<class U> explicit scoped_ptr(transfer_ptr<U> p) : p_(p.release()) {}
	~scoped_ptr() { defined_delete(p_); }
	T * get() const { return p_; }
	void reset(T *p = 0) { defined_delete(p_); p_ = p; }
	T & operator*() const { return *p_; }
	T * operator->() const { return p_; }

	template<class U>
	scoped_ptr & operator=(transfer_ptr<U> p) {
		reset(p.release());
		return *this;
	}

private:
	T *p_;
};

#endif