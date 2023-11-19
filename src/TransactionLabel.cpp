
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