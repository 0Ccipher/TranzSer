/*
 * GenMC -- Generic Model Checking.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you can access it online at
 * http://www.gnu.org/licenses/gpl-3.0.html.
 *
 * Author: Michalis Kokologiannakis <michalis@mpi-sws.org>
 */

#include "MOCalculator.hpp"
#include "ExecutionGraph.hpp"
#include "GraphIterators.hpp"
#include <vector>

CoherenceCalculator::const_store_iterator
MOCalculator::succ_begin(SAddr addr, Event store) const
{
	auto offset = getStoreOffset(addr, store);
	return store_begin(addr) + (offset + 1);
}

CoherenceCalculator::const_store_iterator
MOCalculator::succ_end(SAddr addr, Event store) const
{
	return store_end(addr);
}

CoherenceCalculator::const_store_iterator
MOCalculator::pred_begin(SAddr addr, Event store) const
{
	return store_begin(addr);
}

CoherenceCalculator::const_store_iterator
MOCalculator::pred_end(SAddr addr, Event store) const
{
	auto offset = getStoreOffset(addr, store);
	return store_begin(addr) + (offset >= 0 ? offset : 0);
}

void MOCalculator::trackCoherenceAtLoc(SAddr addr)
{
	stores[addr];
}

int MOCalculator::getStoreOffset(SAddr addr, Event e) const
{
	BUG_ON(stores.count(addr) == 0);

	if (e == Event::getInitializer())
		return -1;

	auto oIt = std::find(store_begin(addr), store_end(addr), e);
	if(oIt == store_end(addr)) abort();
	BUG_ON(oIt == store_end(addr));
	return std::distance(store_begin(addr), oIt);
}

std::pair<int, int>
MOCalculator::getPossiblePlacings(SAddr addr, Event store, bool isRMW)
{
	const auto &g = getGraph();

	/* If it is an RMW store, there is only one possible position in MO */
	if (isRMW) {
		if (auto *rLab = llvm::dyn_cast<ReadLabel>(g.getEventLabel(store.prev()))) {
			auto offset = getStoreOffset(addr, rLab->getRf()) + 1;
			return std::make_pair(offset, offset);
		}
		BUG();
	}

	/* Otherwise, we calculate the full range and add the store */
	auto rangeBegin = splitLocMOBefore(addr, store);
	auto rangeEnd = (supportsOutOfOrder()) ? splitLocMOAfter(addr, store) :
		getStoresToLoc(addr).size();
	return std::make_pair(rangeBegin, rangeEnd);

}

void MOCalculator::addStoreToLoc(SAddr addr, Event store, int offset)
{
	if (offset == -1)
		stores[addr].push_back(store);
	else
		stores[addr].insert(store_begin(addr) + offset, store);
}

//newscdpor
void MOCalculator::removeAllStores(Transaction tr)
{
	const auto &g = getGraph();
	auto *trans = g.getTransaction(tr);
	for (auto it = begin(); it != end(); it++) {
		it->second.erase(std::remove_if(it->second.begin(), it->second.end(),
				[&](Event &e)
				{ 
					auto *lab = g.getWriteLabel(e);
					if(!lab->getTransaction().isInvalid()) {
						if(lab->getTransaction() == tr 	
								&& !trans->isRevisitedStore(lab->getAddr())){
							WARN("**Removed from mo write("+std::__cxx11::to_string(lab->getPos().thread)
									+","+std::__cxx11::to_string(lab->getPos().index)+")**\n");
							return true;
						}
							
					}
						
					return false;
				}),
				it->second.end());

	}
}

void MOCalculator::removeStore(SAddr addr, Event store){
	if(stores.count(addr) == 0) return;
	auto it = std::find(stores[addr].begin() , stores[addr].end() , store);
	if(it == stores[addr].end()) return;
	stores[addr].erase(it);
}

void MOCalculator::addStoreToLocAfter(SAddr addr, Event store, Event pred)
{
	int offset = getStoreOffset(addr, pred);
	addStoreToLoc(addr, store, offset + 1);
}

bool MOCalculator::isCoMaximal(SAddr addr, Event store)
{
	auto &locMO = stores[addr];
	return (store.isInitializer() && locMO.empty()) ||
	       (!store.isInitializer() && !locMO.empty() && store == locMO.back());
}

bool MOCalculator::isCachedCoMaximal(SAddr addr, Event store)
{
	return isCoMaximal(addr, store);
}

void MOCalculator::changeStoreOffset(SAddr addr, Event store, int newOffset)
{
	auto &locMO = stores[addr];

	locMO.erase(std::find(store_begin(addr), store_end(addr), store));
	locMO.insert(store_begin(addr) + newOffset, store);
}

int MOCalculator::splitLocMOBefore(SAddr addr, Event e)
{
	const auto &g = getGraph();
	auto rit = std::find_if(store_rbegin(addr), store_rend(addr), [&](const Event &s){
		return g.isWriteRfBefore(s, e.prev());
	});
	return (rit == store_rend(addr)) ? 0 : std::distance(rit, store_rend(addr));
}

int MOCalculator::splitLocMOAfterHb(SAddr addr, const Event read)
{
	const auto &g = getGraph();

	auto initRfs = g.getInitRfsAtLoc(addr);
	if (std::any_of(initRfs.begin(), initRfs.end(), [&read,&g](const Event &rf){
		return g.getEventLabel(rf)->getHbView().contains(read);
	}))
		return 0;

	auto it = std::find_if(store_begin(addr), store_end(addr), [&](const Event &s){
		return g.isHbOptRfBefore(read, s);
	});
	if (it == store_end(addr))
		return std::distance(store_begin(addr), store_end(addr));
	return (g.getEventLabel(*it)->getHbView().contains(read)) ?
		std::distance(store_begin(addr), it) : std::distance(store_begin(addr), it) + 1;
}

int MOCalculator::splitLocMOAfter(SAddr addr, const Event e)
{
	const auto &g = getGraph();
	auto it = std::find_if(store_begin(addr), store_end(addr), [&](const Event &s){
		return g.isHbOptRfBefore(e, s);
	});
	return (it == store_end(addr)) ? std::distance(store_begin(addr), store_end(addr)) :
		std::distance(store_begin(addr), it);
}

std::vector<Event>
MOCalculator::getCoherentStores(SAddr addr, Event read)
{
	auto &g = getGraph();
	std::vector<Event> stores;

	/*
	 * If there are no stores (rf?;hb)-before the current event
	 * then we can read read from all concurrent stores and the
	 * initializer store. Otherwise, we can read from all concurrent
	 * stores and the mo-latest of the (rf?;hb)-before stores.
	 */
	auto begO = splitLocMOBefore(addr, read);
	if (begO == 0)
		stores.push_back(Event::getInitializer());
	else
		stores.push_back(*(store_begin(addr) + begO - 1));

	/*
	 * If the model supports out-of-order execution we have to also
	 * account for the possibility the read is hb-before some other
	 * store, or some read that reads from a store.
	 */
	auto endO = (supportsOutOfOrder()) ? splitLocMOAfterHb(addr, read) :
		std::distance(store_begin(addr), store_end(addr));
	stores.insert(stores.end(), store_begin(addr) + begO, store_begin(addr) + endO);
	return stores;
}

std::vector<Event>
MOCalculator::getMOOptRfAfter(const WriteLabel *sLab)
{
	std::vector<Event> after;

	std::for_each(succ_begin(sLab->getAddr(), sLab->getPos()),
		      succ_end(sLab->getAddr(), sLab->getPos()), [&](const Event &w){
			      auto *wLab = getGraph().getWriteLabel(w);
			      after.push_back(wLab->getPos());
			      after.insert(after.end(), wLab->readers_begin(), wLab->readers_end());
	});
	return after;
}

std::vector<Event>
MOCalculator::getMOInvOptRfAfter(const WriteLabel *sLab)
{
	std::vector<Event> after;

	/* First, add (mo;rf?)-before */
	std::for_each(pred_begin(sLab->getAddr(), sLab->getPos()),
		      pred_end(sLab->getAddr(), sLab->getPos()), [&](const Event &w){
			      auto *wLab = getGraph().getWriteLabel(w);
			      after.push_back(wLab->getPos());
			      after.insert(after.end(), wLab->readers_begin(), wLab->readers_end());
	});

	/* Then, we add the reader list for the initializer */
	auto initRfs = getGraph().getInitRfsAtLoc(sLab->getAddr());
	after.insert(after.end(), initRfs.begin(), initRfs.end());
	return after;
}

//newscdpor
std::vector<Event>
MOCalculator::getConsistentLoadRevisits(const Transactions *trans)
{
	const auto &g = getGraph();
	auto ls = g.getConsistentRevisitable(trans);

	auto stores = trans->getStoresWithAddr();
	/* If this store is po- and mo-maximal then we are done */
	if (!supportsOutOfOrder() && std::all_of( stores.begin() , stores.end() , 
				[&](std::pair<SAddr,Event> &s) {
						auto *sLab = getGraph().getWriteLabel(s.second);
						return isCoMaximal(sLab->getAddr(), sLab->getPos());
				}) )
		return ls;

	/* First, we have to exclude (mo;rf?;hb?;sb)-after reads */
	// auto optRfs = getMOOptRfAfter(sLab);
	std::vector<Event> moOptRfAfter;
	for(auto store: stores){
		std::for_each(succ_begin(store.first, store.second),
		      succ_end(store.first, store.second), [&](const Event &w){
			      auto *wLab = g.getWriteLabel(w);
			      moOptRfAfter.push_back(wLab->getPos());
			      moOptRfAfter.insert(moOptRfAfter.end(), wLab->readers_begin(), wLab->readers_end());
		});
	}
	
	ls.erase(std::remove_if(ls.begin(), ls.end(), [&](Event e)
				{ 
					const View &before = g.getHbPoBefore(e);
				  	return std::any_of(moOptRfAfter.begin(), moOptRfAfter.end(),
					 	[&](Event ev){ return before.contains(ev); });
				}), ls.end());

	/* If out-of-order event addition is not supported, then we are done
	 * due to po-maximality */
	if (!supportsOutOfOrder())
		return ls;
	//TODO: See if there is need for futher optimization as in getCoherentRevisits()
	return ls;
}

//newscdpor
void
MOCalculator::setAddedMaxFalse(const WriteLabel *sLab)
{
	/* Sets maximal=false for the MO-successor of this sLab */
	std::for_each(succ_begin(sLab->getAddr(), sLab->getPos()),
		         succ_end(sLab->getAddr(), sLab->getPos()), [&](const Event &w){
			      auto *wLab = getGraph().getWriteLabel(w);
				//   if(wLab->getStamp() < sLab->getStamp())
			      	wLab->setAddedMax(false);
				//   if(wLab->getStamp() > sLab->getStamp())
			    //   	wLab->setAddedMax(true);
	});
}

std::vector<Event>
MOCalculator::getCoherentRevisits(const WriteLabel *sLab)
{
	const auto &g = getGraph();
	auto ls = g.getRevisitable(sLab);

	/* If this store is po- and mo-maximal then we are done */
	if (!supportsOutOfOrder() && isCoMaximal(sLab->getAddr(), sLab->getPos()))
		return ls;

	/* First, we have to exclude (mo;rf?;hb?;sb)-after reads */
	auto optRfs = getMOOptRfAfter(sLab);
	ls.erase(std::remove_if(ls.begin(), ls.end(), [&](Event e)
				{ const View &before = g.getHbPoBefore(e);
				  return std::any_of(optRfs.begin(), optRfs.end(),
					 [&](Event ev)
					 { return before.contains(ev); });
				}), ls.end());

	/* If out-of-order event addition is not supported, then we are done
	 * due to po-maximality */
	if (!supportsOutOfOrder())
		return ls;

	/* Otherwise, we also have to exclude hb-before loads */
	ls.erase(std::remove_if(ls.begin(), ls.end(), [&](Event e)
		{ return g.getEventLabel(sLab->getPos())->getHbView().contains(e); }),
		ls.end());

	/* ...and also exclude (mo^-1; rf?; (hb^-1)?; sb^-1)-after reads in
	 * the resulting graph */
	auto &before = g.getPPoRfBefore(sLab->getPos());
	auto moInvOptRfs = getMOInvOptRfAfter(sLab);
	ls.erase(std::remove_if(ls.begin(), ls.end(), [&](Event e)
				{ auto *eLab = g.getEventLabel(e);
				  auto v = g.getDepViewFromStamp(eLab->getStamp());
				  v.update(before);
				  return std::any_of(moInvOptRfs.begin(),
						     moInvOptRfs.end(),
						     [&](Event ev)
						     { return v.contains(ev) &&
						       g.getHbPoBefore(ev).contains(e); });
				}),
		 ls.end());

	return ls;
}

#ifdef ENABLE_GENMC_DEBUG
std::vector<std::pair<Event, Event> >
MOCalculator::saveCoherenceStatus(const std::vector<std::unique_ptr<EventLabel> > &labs,
				  const ReadLabel *rLab) const
{
	auto before = getGraph().getPredsView(rLab->getPos());
	std::vector<std::pair<Event, Event> > pairs;

	for (const auto &lab : labs) {
		/* Only store MO pairs for write labels */
		if (!llvm::isa<WriteLabel>(lab.get()))
			continue;

		BUG_ON(before->contains(lab->getPos()));
		auto *wLab = static_cast<const WriteLabel *>(lab.get());
		auto moPos = std::find(store_begin(wLab->getAddr()), store_end(wLab->getAddr()), wLab->getPos());

		/* This store must definitely be in this location's MO */
		BUG_ON(moPos == store_end(wLab->getAddr()));

		/* We need to find the previous MO store that is in before or
		 * in the vector for which we are getting the predecessors */
		decltype(store_rbegin(wLab->getAddr())) predPos(moPos);
		auto predFound = false;
		for (auto rit = predPos; rit != store_rend(wLab->getAddr()); ++rit) {
			if (before->contains(*rit) ||
			    std::find_if(labs.begin(), labs.end(),
					 [&](const std::unique_ptr<EventLabel> &lab)
					 { return lab->getPos() == *rit; })
			    != labs.end()) {
				pairs.push_back(std::make_pair(*moPos, *rit));
				predFound = true;
				break;
			}
		}
		/* If there is not predecessor in the vector or in before,
		 * then INIT is the only valid predecessor */
		if (!predFound)
			pairs.push_back(std::make_pair(*moPos, Event::getInitializer()));
	}
	return pairs;
}
#endif

bool MOCalculator::isCoBeforeSavedPrefix(const BackwardRevisit &r, const EventLabel *lab)
{
	auto *mLab = llvm::dyn_cast<MemAccessLabel>(lab);
	if (!mLab)
		return false;

	auto &g = getGraph();
        auto v = g.getRevisitView(r);
	auto w = llvm::isa<ReadLabel>(mLab) ? llvm::dyn_cast<ReadLabel>(mLab)->getRf() : mLab->getPos();
	return any_of(succ_begin(mLab->getAddr(), w),
		      succ_end(mLab->getAddr(), w), [&](const Event &s){
			      auto *sLab = g.getEventLabel(s);
			      return v->contains(sLab->getPos()) &&
				     mLab->getIndex() > sLab->getPPoRfView()[mLab->getThread()] &&
				     sLab->getPos() != r.getRev();
		      });
}

bool MOCalculator::coherenceSuccRemainInGraph(const BackwardRevisit &r)
{
	auto &g = getGraph();
	auto *wLab = g.getWriteLabel(r.getRev());
	if (g.isRMWStore(wLab))
		return true;

	auto succIt = succ_begin(wLab->getAddr(), wLab->getPos());
	auto succE = succ_end(wLab->getAddr(), wLab->getPos());
	if (succIt == succE)
		return true;

	return g.getRevisitView(r)->contains(*succIt);
}

bool MOCalculator::wasAddedMaximally(const EventLabel *lab)
{
	if (auto *mLab = llvm::dyn_cast<MemAccessLabel>(lab))
		return mLab->wasAddedMax();
	if (auto *oLab = llvm::dyn_cast<OptionalLabel>(lab))
		return !oLab->isExpanded();
	return true;
}

bool MOCalculator::inMaximalPath(const BackwardRevisit &r)
{
	if (!coherenceSuccRemainInGraph(r))
		return false;

	auto &g = getGraph();
    auto v = g.getRevisitView(r);

	for (const auto *lab : labels(g)) {
		if ((lab->getPos() != r.getPos() && v->contains(lab->getPos())) ||
		    g.prefixContainsSameLoc(r, lab) ||
		    g.isOptBlockedRead(lab))
			continue;

		if (isCoBeforeSavedPrefix(r, lab))
			return false;
		if (g.hasBeenRevisitedByDeleted(r, lab))
			return false;
		if (!wasAddedMaximally(lab))
			return false;
	}
	return true;
}

//newscdpor
bool MOCalculator::inMaximalPathTr(const TransactionBackwardRevisit &r)
{
	WARN("inMaximalPathTr Read ("+ std::__cxx11::to_string(r.getPos().thread)+
		","+std::__cxx11::to_string(r.getPos().index) +")\n");
	auto &g = getGraph();
	auto preds = g.getRevisitViewTr(r);
	
	auto *trans = g.getTransaction(r.getTransaction());
	auto *revLab = g.getEventLabel(r.getPos());
	BUG_ON(revLab->getTransaction().isInvalid());
	auto *rTrans = g.getTransaction(revLab->getTransaction());
	/*mo-succ of all writes from r.Transaction should be in the updated graph */
	auto stores = trans->getStoresWithAddr();
	if(std::any_of(stores.begin() , stores.end(), 
				[&](std::pair<SAddr,Event> &store) {
					auto *wLab = g.getWriteLabel(store.second);
					auto succIt = succ_begin(wLab->getAddr(), wLab->getPos());
					auto succE = succ_end(wLab->getAddr(), wLab->getPos());
					if (!(succIt == succE) && !(preds->contains(*succIt)))
						return true;
					return false;
				})) {
		WARN("there exists a Mo succ, which is not in graph \n");
		return false;
	}
		
	for (const auto *lab : labels(g)) {
		if ((lab->getPos() != r.getPos() && preds->contains(lab->getPos())) || g.isOptBlockedRead(lab)) {
			continue;
		}
		std::vector<Event> moSuccs;
		/*isCoBeforeSavedPrefix(r, lab)*/
		if(auto *mLab = llvm::dyn_cast<MemAccessLabel>(lab)) {
			auto w = llvm::isa<ReadLabel>(mLab) ? llvm::dyn_cast<ReadLabel>(mLab)->getRf() : mLab->getPos();
			if(any_of(succ_begin(mLab->getAddr(), w), succ_end(mLab->getAddr(), w), 
					[&](const Event &s){
						auto *sLab = g.getEventLabel(s);
						if(sLab->getTransaction().isInvalid())
							return false;
						/*S belongs to a transaction. Add s to succ list*/
						moSuccs.push_back(s);

						auto *sTran = g.getTransaction(sLab->getTransaction());
						auto *eLab = g.getEventLabel(sTran->getEndEvent());
						auto eLabPoRfView = eLab->getPorfView();
						bool flag = preds->contains(sLab->getPos()) &&
							preds->contains(eLab->getPos()) &&
							sLab->getTransaction() != trans->getPos() &&
							mLab->getIndex() > sLab->getPPoRfView()[mLab->getThread()] &&
							mLab->getIndex() > eLab->getPPoRfView()[mLab->getThread()];
						if(flag) {
							WARN("isCoBeforeSavedPrefix check(RF-for read) event("
								+ std::__cxx11::to_string(w.thread)+","+
								std::__cxx11::to_string(w.index) +") 1 \n");
							/*Check if this mLab-event belongs to same transaction as rLab and
							* sTran(succs of mLab) also has write on some read in trans before rLab
							*/
							if(mLab->getTransaction().isInvalid()) return false;
							if(mLab->getTransaction() == revLab->getTransaction()){
								for(auto ev : rTrans->getLoadsWithAddr()){
									if(ev.second.index < r.getPos().index) {
										if(sTran->isStorePresent(ev.first))
											return false;
										for(auto we : moSuccs){
											if(we != sLab->getPos() && eLabPoRfView.contains(we)){
												auto *weTrans = g.getTransaction(g.getEventLabel(we)->getTransaction());
												if(weTrans->isStorePresent(ev.first))
													return false;
											}
										}
									}
										
								}
							}
								
							WARN("isCoBeforeSavedPrefix check(RF-for read) event("+ 
								std::__cxx11::to_string(w.thread)+","+std::__cxx11::to_string(w.index)
									+") 2 \n");
							WARN("isCoBeforeSavedPrefix succ event("+ 
								std::__cxx11::to_string(sLab->getPos().thread)+","+
								std::__cxx11::to_string(sLab->getPos().index) +")\n");
							return true;
						}
						return false;
						}) ) {
				WARN("`CoBeforeSavedPrefix(RF-for read) event("+ 
					std::__cxx11::to_string(lab->getPos().thread)+","+
					std::__cxx11::to_string(lab->getPos().index) +")`\n");
				return false;
			}
		

		}
		/*hasBeenRevisitedByDeleted(r,lab)*/
		auto *rLab = llvm::dyn_cast<ReadLabel>(lab);
		if (rLab){
			auto *rfLab = g.getEventLabel(rLab->getRf());
			if( !preds->contains(rfLab->getPos()) && rfLab->getStamp() > lab->getStamp() ) {
				WARN("`hasBeenRevisitedByDeleted for read("+ std::__cxx11::to_string(lab->getPos().thread)
					+","+std::__cxx11::to_string(lab->getPos().index) +")`\n");
				return false;
			}
		}
		if (!wasAddedMaximally(lab)) {
			WARN("`Not AddedMaximally event("+ std::__cxx11::to_string(lab->getPos().thread)+","
				+std::__cxx11::to_string(lab->getPos().index) +")` 1 \n");
			/* If lab.trans = BRevisit read.trans, then its okay lab to be not-maximal if all the 
			mo-succ transaction(and their por-rf before transaction) contain writes on the same location 
			as some read ev \in BRevisit read.trans.
			And the mo-succ write.stamp < lab.stamp.
			This check is mainly needed if lab is writeLabel (for reads, this issue may not arise; still check it)
			*/
			if(auto *mLab = llvm::dyn_cast<MemAccessLabel>(lab)){
				auto w = llvm::isa<ReadLabel>(mLab) ? llvm::dyn_cast<ReadLabel>(mLab)->getRf()
								 : mLab->getPos();
				if(mLab->getTransaction().isInvalid()) continue;
				if(mLab->getTransaction() == revLab->getTransaction()){
					if(std::all_of(succ_begin(mLab->getAddr(), w), succ_end(mLab->getAddr(), w),
						[&](const Event &s){
							auto *sLab = g.getWriteLabel(s);
							if(sLab->getStamp() > mLab->getStamp())
								return true;
							if(sLab->getTransaction().isInvalid())
								return true;
							auto *sTran = g.getTransaction(sLab->getTransaction());
							auto *eLab = g.getEventLabel(sTran->getEndEvent());
							auto eLabPoRfView = eLab->getPorfView();
							for(auto ev : rTrans->getLoadsWithAddr()){
								if(ev.second.index < r.getPos().index) {
									if(sTran->isStorePresent(ev.first))
										return true;
									for(auto we : moSuccs){
										if(we != sLab->getPos() && eLabPoRfView.contains(we)) {
											auto *weTrans = g.getTransaction(g.getEventLabel(we)->getTransaction());
											if(weTrans->isStorePresent(ev.first))
												return true;
										}
									}
								}		
							}
							return false;
						} )) {
							continue;
					}
				}

			}
			WARN("`Not AddedMaximally event("+ std::__cxx11::to_string(lab->getPos().thread)+","
				+std::__cxx11::to_string(lab->getPos().index) +")` 2 \n");
			return false;
		}
	}
	return true;
}

void MOCalculator::initCalc()
{
	auto &gm = getGraph();
	auto &coRelation = gm.getPerLocRelation(ExecutionGraph::RelationId::co);

	coRelation.clear();
	for (auto locIt = begin(); locIt != end(); locIt++) {
		coRelation[locIt->first] = GlobalRelation(getStoresToLoc(locIt->first));
		if (locIt->second.empty())
			continue;
		for (auto sIt = locIt->second.begin(); sIt != locIt->second.end() - 1; sIt++)
			coRelation[locIt->first].addEdge(*sIt, *(sIt + 1));
		coRelation[locIt->first].transClosure();
	}
	return;
}

Calculator::CalculationResult MOCalculator::doCalc()
{
	auto &gm = getGraph();
	auto &coRelation = gm.getPerLocRelation(ExecutionGraph::RelationId::co);

	for (auto locIt = begin(); locIt != end(); locIt++) {
		if (!coRelation[locIt->first].isIrreflexive())
			return Calculator::CalculationResult(false, false);
	}
	return Calculator::CalculationResult(false, true);
}

void MOCalculator::removeAfter(const VectorClock &preds)
{
	auto &g = getGraph();
	VSet<SAddr> keep;

	/* Check which locations should be kept */
	for (auto i = 0u; i < preds.size(); i++) {
		for (auto j = 0u; j <= preds[i]; j++) {
			auto *lab = g.getEventLabel(Event(i, j));
			if (auto *mLab = llvm::dyn_cast<MemAccessLabel>(lab))
				keep.insert(mLab->getAddr());
		}
	}

	for (auto it = begin(); it != end(); /* empty */) {
		it->second.erase(std::remove_if(it->second.begin(), it->second.end(),
						[&](Event &e)
						{ return !preds.contains(e); }),
				 it->second.end());

		/* Should we keep this memory location lying around? */
		if (!keep.count(it->first)) {
			BUG_ON(!it->second.empty());
			it = stores.erase(it);
		} else {
			++it;
		}
	}
}

bool MOCalculator::locContains(SAddr addr, Event e) const
{
	BUG_ON(stores.count(addr) == 0);
	return e == Event::getInitializer() ||
		std::any_of(store_begin(addr), store_end(addr),
			    [&e](Event s){ return s == e; });
}
