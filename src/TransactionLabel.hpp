/*
 * Omkar Tuppe
 */

#ifndef __TransactionLabel_HPP__
#define __TransactionLabel_HPP__

#include "Event.hpp"
#include "Transaction.hpp"
#include "EventAttr.hpp"
#include "value_ptr.hpp"
#include "DepView.hpp"
#include "InterpreterEnumAPI.hpp"
#include "ModuleID.hpp"
#include "NameInfo.hpp"
#include "MemAccess.hpp"
#include "SAddr.hpp"
#include "SExpr.hpp"
#include "SVal.hpp"
#include "View.hpp"
#include <llvm/IR/Instructions.h> /* For AtomicOrdering in older LLVMs */
#include <llvm/Support/Casting.h>
#include <llvm/Support/raw_ostream.h>

class Transactions{

public:
	using StoreMap = std::unordered_map<SAddr, Event>;
	using LoadMap = std::unordered_map<SAddr, Event>;
	Transactions(unsigned int s, Transaction tr, Event be) : stamp(s), position(tr), beginEvent(be) {}
	Transactions(Transaction tr, Event be)
		: stamp(0), position(tr) , beginEvent(be) {}

	/* Getter/setter for the stamp in an execution graph*/
	unsigned int getStamp() const { return stamp; }
	void setStamp(unsigned int s) { stamp = s; }

	/* Returns the position in the execution graph (thread, index) */
	Transaction getPos() const { return position; }

	/* Returns the index within a thread */
	int getIndex() const { return position.index; }

	/* Returns the thread of this transaction in the execution graph */
	int getThread() const { return position.thread; }

	/* Returns the beginEvent of this transaction in the execution graph */
	Event getBeginEvent() const { return beginEvent; }

	/* Add the store*/
	void addStore(SAddr addr, Event store) {stores[addr] = store;};
	bool isStorePresent(SAddr addr) const;
	Event getStore(SAddr addr) const;
	std::vector<Event> getStores() const;
	StoreMap getLocStores() const;

	/* Add the load*/
	void addLoad(SAddr addr, Event load) {reads[addr] = load;};
	bool isLoadPresent(SAddr addr) const;
	Event getLoad(SAddr addr) const;
	std::vector<Event> getLoads() const;

	void setFinishedStatus(bool value) {finshedExecution = value};
	bool getFinishedStatus(){return finshedExecution;}

	/* Methods that get/set the vector clocks for this label. */
	const View& getHbView() const { return hbView; }
	const View& getPorfView() const { return porfView; }
	const DepView& getPPoView() const { return ppoView; }
	const DepView& getPPoRfView() const { return pporfView; }

	void updateHbView(const View &v) { hbView.update(v); };
	void updatePorfView(const View &v) { porfView.update(v); };
	void updatePPoView(const View &v) { ppoView.update(v); };
	void updatePPoRfView(const DepView &v) { pporfView.update(v); };

	void setHbView(View &&v) { hbView = std::move(v); }
	void setPorfView(View &&v) { porfView = std::move(v); }
	void setPPoView(DepView &&v) { ppoView = std::move(v); }
	void setPPoRfView(DepView &&v) { pporfView = std::move(v); }

	virtual ~Transactions() = default;

	friend llvm::raw_ostream& operator<<(llvm::raw_ostream& rhs,
					     const Transactions &tr);

private:
	
	/* The stamp of this transaction in the execution graph */
	unsigned int stamp;

	/* Position of the beging event label of this transaction within the execution graph (thread, index) */
	const Transaction position;

	/* Position of the beging event label of this transaction within the execution graph (thread, index) */
	const Event beginEvent;

	/*Latest stores of this Transaction */
	
	StoreMap stores;

	/*Loades of this Transaction */
	
	LoadMap reads;

	/* Executed transaction?*/

	bool finshedExecution;
	
	/* Events that are hb-before this label */
	View hbView;

	/* Events that are (po U rf)-before this label */
	View porfView;

	/* Events that are (ppo U rf)*;ppo-before this label */
	DepView ppoView;

	/* Events that are (ppo U rf)*-before this label */
	DepView pporfView;
};

#endif /* __TransactionLabel_HPP__ */
