
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

Event Transactions::getStore(SAddr addr) const{
	if(isStorePresent(addr))
		return stores.at(addr);
	return Event(-42,-42);
}

std::vector<Event> Transactions::getLoads() const{
	std::vector<Event> loads;
	for(auto ele:reads){
		loads.push_back(ele.second);
	}
	return loads;
}

std::vector<Event> Transactions::getStores() const{
	std::vector<Event> writes;
	for(auto ele:stores){
		writes.push_back(ele.second);
	}
	return writes;
}
