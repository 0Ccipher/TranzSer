
/*
 * Omkar Tuppe
 */

#include "TransactionLabel.hpp"

void Transactions::addStore(SAddr addr, Event store){
	stores[addr] = store;
}

void Transactions::addLoad(SAddr addr, Event load){
	reads[addr] = load;
}

bool Transactions::isLoadPresent(SAddr addr) const{
	if(reads.count(addr) == 0) return false;
	return true;
}

bool Transactions::isStorePresent(SAddr addr) const{
	if(stores.count(addr) == 0) return false;
	return true;
}

Event Transactions::getLoad(SAddr addr) const{
	if(isLoadPresent(addr))
		return reads.at(addr);
	return Event(-42,-42);
}