/*
Omkar
 */

#ifndef __GRAPHTransaction_ITERATORS_HPP__
#define __GRAPHTransaction_ITERATORS_HPP__

#include "config.h"
#include "ExecutionGraph.hpp"
#include "CoherenceCalculator.hpp"
#include <iterator>
#include <llvm/ADT/iterator_range.h>

/*
 * Helper iterators for ExecutionGraphs
 */

/*******************************************************************************
 **                         TransactionsIterator Class
 ******************************************************************************/

/*
 * This class implements some helper iterators for ExecutionGraph.
 * A bit ugly, but easily tunable, and deals with UP containers
 */
template<typename ThreadTranT, typename ThreadTranItT, typename TransactionsT, typename TransactionsItT>
class TransactionsIterator {

protected:
	ThreadTranT *threads;
	ThreadTranItT thread;
	TransactionsItT transaction;

public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = TransactionsT;
	using difference_type = signed;
	using pointer = TransactionsT *;
	using reference = TransactionsT &;


	/*** Constructors/destructor ***/
	TransactionsIterator() = default;

	template<typename A, typename B, typename C, typename D>
	TransactionsIterator(const TransactionsIterator<A,B,C,D> &LI)
		: threads(LI.threads), thread(LI.thread), transaction(LI.transaction) {}

	template<typename A, typename B, typename C, typename D>
	TransactionsIterator(TransactionsIterator<A,B,C,D> &LI)
		: threads(LI.threads), thread(LI.thread), transaction(LI.transaction) {}

	/* tran_begin() constructor */
	template<typename G>
	TransactionsIterator(G &g) : threads(&g.getTransactionList()), thread(g.tran_begin()) {
		if (thread != threads->end()) {
			transaction = thread->begin();
			advanceThreadTran();
		}
	}

	/* end() constructor -- dummy parameter */
	template<typename G>
	TransactionsIterator(G &g, bool) : threads(&g.getTransactionList()), thread(g.tran_end()) {}


	/*** Operators ***/
	inline pointer operator*() const { return &**transaction; }
	inline pointer operator->() const { return operator*(); }

	inline bool operator==(const TransactionsIterator &other) const {
		return thread == other.thread &&
		       (thread == threads->end() || transaction == other.transaction);
	}
	inline bool operator!=(const TransactionsIterator& other) const {
		return !operator==(other);
	}

	TransactionsIterator& operator++() {
		++transaction;
		advanceThreadTran();
		return *this;
	}
	inline TransactionsIterator operator++(int) {
		auto tmp = *this; ++*this; return tmp;
	}

	TransactionsIterator& operator--() {
		while (thread == threads->end() || transaction == thread->tran_begin()) {
			--thread;
			transaction = thread->tran_end();
		}
		--transaction;
		return *this;
	}
	inline TransactionsIterator operator--(int) {
		auto tmp = *this; --*this; return tmp;
	}

private:
	/* Checks whether we have reached the end of a thread, and appropriately
	 * advances the thread and transaction iterators. Does nothing if that is not the case. */
	inline void advanceThreadTran() {
		while (transaction == thread->end()) {
			++thread;
			if (thread == threads->end())
				break;
			transaction = thread->begin();
		}
	}

};

/*******************************************************************************
 **                         transaction-iteration utilities
 ******************************************************************************/

using transaction_iterator = TransactionsIterator<ExecutionGraph::TransactionList,
				     ExecutionGraph::tran_iterator,
				     Transactions,
				     ExecutionGraph::TransactionsPerThread::iterator>;
using const_transaction_iterator = TransactionsIterator<const ExecutionGraph::TransactionList,
					   ExecutionGraph::const_tran_iterator,
					   const Transactions,
					   ExecutionGraph::TransactionsPerThread::const_iterator>;

using transaction_range = llvm::iterator_range<transaction_iterator>;
using const_transaction_range = llvm::iterator_range<const_transaction_iterator>;

inline transaction_iterator transaction_begin(ExecutionGraph *G) { return transaction_iterator(*G); }
inline transaction_iterator transaction_begin(ExecutionGraph &G) { return transaction_iterator(G); }
inline const_transaction_iterator transaction_begin(const ExecutionGraph *G)
{
	return const_transaction_iterator(*G);
}
inline const_transaction_iterator transaction_begin(const ExecutionGraph &G)
{
	return const_transaction_iterator(G);
}

inline transaction_iterator transaction_end(ExecutionGraph *G) { return transaction_iterator(*G, true); }
inline transaction_iterator transaction_end(ExecutionGraph &G)   { return transaction_iterator(G, true); }
inline const_transaction_iterator transaction_end(const ExecutionGraph *G)
{
	return const_transaction_iterator(*G, true);
}
inline const_transaction_iterator transaction_end(const ExecutionGraph &G)
{
	return const_transaction_iterator(G, true);
}

inline transaction_range alltransactions(ExecutionGraph *G) { return transaction_range(transaction_begin(G), transaction_end(G)); }
inline transaction_range alltransactions(ExecutionGraph &G) { return transaction_range(transaction_begin(G), transaction_end(G)); }
inline const_transaction_range alltransactions(const ExecutionGraph *G) {
	return const_transaction_range(transaction_begin(G), transaction_end(G));
}
inline const_transaction_range alltransactions(const ExecutionGraph &G) {
	return const_transaction_range(transaction_begin(G), transaction_end(G));
}


// /*******************************************************************************
//  **                         store-iteration utilities
//  ******************************************************************************/

// using const_store_iterator = CoherenceCalculator::const_store_iterator;
// using const_reverse_store_iterator = CoherenceCalculator::const_reverse_store_iterator;

// using store_range = llvm::iterator_range<const_store_iterator>;

// inline const_store_iterator store_begin(const ExecutionGraph &G, SAddr addr)
// {
// 	return G.getCoherenceCalculator()->store_begin(addr);
// }
// inline const_store_iterator store_begin(const ExecutionGraph *G, SAddr addr)
// {
// 	return store_begin(*G, addr);
// }
// inline const_reverse_store_iterator store_rbegin(const ExecutionGraph &G, SAddr addr)
// {
// 	return G.getCoherenceCalculator()->store_rbegin(addr);
// }

// inline const_reverse_store_iterator store_rbegin(const ExecutionGraph *G, SAddr addr)
// {
// 	return store_rbegin(*G, addr);
// }

// inline const_store_iterator store_end(const ExecutionGraph &G, SAddr addr)
// {
// 	return G.getCoherenceCalculator()->store_end(addr);
// }
// inline const_store_iterator store_end(const ExecutionGraph *G, SAddr addr)
// {
// 	return store_end(*G, addr);
// }
// inline const_reverse_store_iterator store_rend(const ExecutionGraph &G, SAddr addr)
// {
// 	return G.getCoherenceCalculator()->store_rend(addr);
// }
// inline const_reverse_store_iterator store_rend(const ExecutionGraph *G, SAddr addr)
// {
// 	return store_rend(*G, addr);
// }

// inline store_range stores(const ExecutionGraph &G, SAddr addr)
// {
// 	return store_range(store_begin(G, addr), store_end(G, addr));
// }
// inline store_range stores(const ExecutionGraph *G, SAddr addr) { return stores(*G, addr); }

#endif /* __GRAPHTransaction_ITERATORS_HPP__ */
