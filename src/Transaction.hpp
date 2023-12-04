/*
 * Omkar Tuppe
 */

#ifndef __Transaction_HPP__
#define __Transaction_HPP__
#include <llvm/ADT/Hashing.h>
#include <llvm/Support/raw_ostream.h>

struct Transaction {
	int thread;
	int index;

	Transaction() : thread(-17), index(-17) {};
	Transaction(int t, int e) : thread(t), index(e) {};

	static Transaction getInitializer() { return Transaction(0, 0); };
	static Transaction getBottom() { return Transaction(-42, -42); };
	static Transaction getInvalid() { return Transaction(-17, -17); };

	bool isInitializer() const { return *this == getInitializer(); };
	bool isBottom() const { return *this == getBottom(); };
	bool isInvalid() const { return *this == getInvalid(); };

	Transaction prev() const { return Transaction(thread, index-1); };
	Transaction next() const { return Transaction(thread, index+1); };

	bool isBetween(Transaction a, Transaction b) const {
		if (a.thread != b.thread)
			return false;
		if (this->thread != a.thread)
			return false;
		return this->index >= a.index && this->index <= b.index;
	}

	inline bool operator==(const Transaction &e) const {
		return e.index == index && e.thread == thread;
	}
	inline bool operator!=(const Transaction &e) const {
		return !(*this == e);
	}
	inline bool operator<(const Transaction &e) const {
		return (index < e.index) || (index == e.index && thread < e.thread);
	}
	inline bool operator>(const Transaction &e) const {
		return (index > e.index) || (index == e.index && thread > e.thread);
	}
	inline Transaction& operator++() {
		++index;
		return *this;
	}
	inline Transaction operator++(int) {
		auto tmp = *this;
		++index;
		return tmp;
	}
	inline Transaction& operator--() {
		--index;
		return *this;
	}
	inline Transaction operator--(int) {
		auto tmp = *this;
		--index;
		return tmp;
	}

	friend llvm::hash_code hash_value(const Transaction &e) {
		return llvm::hash_combine(e.thread, e.index);
	};
};

llvm::raw_ostream& operator<<(llvm::raw_ostream &s, Transaction e);

struct TransactionHasher {

	template <class T>
	inline void hash_combine(std::size_t& seed, const T& v)	const {
		seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
	}

	std::size_t operator()(const Transaction& e) const {
		std::size_t hash = 0;
		hash_combine(hash, e.thread);
		hash_combine(hash, e.index);
		return hash;
	}
};

#endif /* __Transaction_HPP__ */
