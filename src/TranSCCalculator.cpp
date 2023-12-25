/*
 Omkar
 */

#include "TranSCCalculator.hpp"
#include "Error.hpp"
#include "ExecutionGraph.hpp"
#include "GraphIterators.hpp"
#include "GraphTransactionIterators.hpp"
#include "WBCalculator.hpp"

std::vector<SAddr> TranSCCalculator::getDoubleLocs() const
{
	auto &g = getGraph();
	std::vector<SAddr> singles, doubles;

	for (auto i = 0u; i < g.getNumThreads(); i++) {
		for (auto j = 1u; j < g.getThreadSize(i); j++) { /* Do not consider thread inits */
			const EventLabel *lab = g.getEventLabel(Event(i, j));
			if (!llvm::isa<MemAccessLabel>(lab))
				continue;

			auto *mLab = static_cast<const MemAccessLabel *>(lab);
			if (std::find(doubles.begin(), doubles.end(),
				      mLab->getAddr()) != doubles.end())
				continue;
			if (std::find(singles.begin(), singles.end(),
				      mLab->getAddr()) != singles.end()) {
				singles.erase(std::remove(singles.begin(),
							  singles.end(),
							  mLab->getAddr()),
					      singles.end());
				doubles.push_back(mLab->getAddr());
			} else {
				singles.push_back(mLab->getAddr());
			}
		}
	}
	return doubles;
}


std::vector<Transaction> TranSCCalculator::calcSCSuccs(
					       const Event e) const
{
	auto &g = getGraph();
	const EventLabel *lab = g.getEventLabel(e);

	if (g.isRMWLoad(lab))
		return {};
	if (lab->isSC()){
		if(lab->getTransaction().isInvalid())
			return {};
		return {lab->getTransaction()};
	}
	return {};
}

std::vector<Transaction> TranSCCalculator::calcSCPreds(
					       const Event e) const
{
	auto &g = getGraph();
	const EventLabel *lab = g.getEventLabel(e);

	if (g.isRMWLoad(lab))
		return {};
	if (lab->isSC()){
		if(lab->getTransaction().isInvalid())
			return {};
		return {lab->getTransaction()};
	}
	return {};
}

std::vector<Transaction> TranSCCalculator::calcRfSCSuccs(const Event ev) const
{
	auto &g = getGraph();
	const EventLabel *lab = g.getEventLabel(ev);
	std::vector<Transaction> rfs;

	BUG_ON(!llvm::isa<WriteLabel>(lab));
	auto *wLab = static_cast<const WriteLabel *>(lab);
	for (const auto &e : wLab->getReadersList()) {
		const EventLabel *rLab = g.getEventLabel(e);
		if(wLab->getTransaction() == rLab->getTransaction() || 
					rLab->getTransaction().isInvalid()) continue;
		auto succs = calcSCSuccs( e);
		rfs.insert(rfs.end(), succs.begin(), succs.end());
	}
	return rfs;
}

void TranSCCalculator::addRbEdges(
				const std::vector<Transaction> &moAfter,
				const std::vector<Transaction> &moRfAfter,
				Calculator::GlobalTranRelation &matrix,
				const Event &ev) const
{
	auto &g = getGraph();
	const EventLabel *lab = g.getEventLabel(ev);

	BUG_ON(!llvm::isa<WriteLabel>(lab));
	auto *wLab = static_cast<const WriteLabel *>(lab);
	for (const auto &e : wLab->getReadersList()) {
		const EventLabel *rLab = g.getEventLabel(e);
		/*Already covered in mo if store and load transaction is same*/
		if(wLab->getTransaction() == rLab->getTransaction() || 
					rLab->getTransaction().isInvalid()) continue;
		auto preds = calcSCPreds( e);
		matrix.addEdgesFromTo(preds, moAfter);        /* Base/fence: Adds rb-edges (fr)*/
	}
	return;
}

void TranSCCalculator::addMoRfEdges(
				  const std::vector<Transaction> &moAfter,
				  const std::vector<Transaction> &moRfAfter,
				  Calculator::GlobalTranRelation &matrix,
				  const Event &ev) const
{
	auto &g = getGraph();
	auto preds = calcSCPreds( ev);
	auto rfs = calcRfSCSuccs( ev);

	matrix.addEdgesFromTo(preds, moAfter);        /* Base/fence:  Adds mo-edges */
	matrix.addEdgesFromTo(preds, rfs);            /* Base/fence:  Adds rf-edges (hb_loc) */
	return;
}

/*
 * addSCEcosLoc - Helper function that calculates a part of TranSC_base and TranSC_fence
 *
 * For TranSC_base and TranSC_fence, it adds co, rb, and hb_loc edges. The
 * procedure for co and rb is straightforward: at each point, we only
 * need to keep a list of all the co-after writes that are either SC,
 * or can reach an SC fence. For hb_loc, however, we only consider
 * rf-edges because the other cases are implicitly covered (sb, co, etc).
 *
 * For TranSC_fence only, it adds (co;rf)- and (rb;rf)-edges. Simple cases like
 * co, rf, and rb are covered by TranSC_base, and all other combinations with
 * more than one step either do not compose, or lead to an already added
 * single-step relation (e.g, (rf;rb) => co, (rb;co) => rb)
 */
void TranSCCalculator::addSCEcosLoc( SAddr loc,
				 Calculator::GlobalRelation &coMatrix,
				 Calculator::GlobalTranRelation &TranSCMatrix) const
{
	auto &g = getGraph();
	// auto &stores = coMatrix.getElems();
	/* Collect all SC events/transactions (except for RMW loads) */
	auto accesses = g.getSCEventsTransactions();
	/*All Transactions*/
	auto &sctrans = accesses.second; 
	for(auto i = 0u; i < sctrans.size(); i++) {
		/*
		 * Calculate which of the stores are co-after the current
		 * write, and then collect co-after and (co;rf)-after SC successors
		 */
		std::vector<Transaction> coAfter,coRfAfter;
		const Transactions *trani = g.getTransaction(sctrans[i]);
		if(!trani->getFinishedStatus()) continue;
		if(!trani->isStorePresent(loc)) continue;
		Event storei = trani->getStore(loc);
		for(auto j = 0u; j < sctrans.size(); j++){
			if(i==j) continue;
			const Transactions *tranj = g.getTransaction(sctrans[j]);
			//check if it's current transactions
			if(!tranj->getFinishedStatus()) continue;
			if(!tranj->isStorePresent(loc)) continue;
			Event storej = tranj->getStore(loc);
			if (coMatrix(storei,storej)){
				auto succs = calcSCSuccs( storej);
				coAfter.insert(coAfter.end(), succs.begin(), succs.end());

			}

		}
		/* Then, add the proper edges to TranSC using co-after and (co;rf)-after successors */
		addRbEdges( coAfter, coRfAfter, TranSCMatrix, storei); // (fr)
		addMoRfEdges( coAfter, coRfAfter, TranSCMatrix, storei); //(co-rf)
	}
}

/*
 * Adds sb as well as [Esc];sb_(<>loc);hb;sb_(<>loc);[Esc] edges. The first
 * part of this function is common for TranSC_base and TranSC_fence, while the second
 * part of this function is not triggered for fences (these edges are covered in
 * addSCEcos()).
 */
void TranSCCalculator::addSbHbEdges(Calculator::GlobalTranRelation &matrix) const
{
	auto &g = getGraph();
	auto &hbRelation = g.getGlobalRelation(ExecutionGraph::RelationId::hb);

	auto accesses = g.getSCEventsTransactions();
	auto &sctrans = accesses.second;
	for(auto i = 0u; i < sctrans.size(); i++){
		for(auto j = 0u; j < sctrans.size(); j++){
			if(i==j)
				continue;
			const Transactions *trani = g.getTransaction(sctrans[i]);
			const Transactions *tranj = g.getTransaction(sctrans[j]);

			/* Add sb-edges (po)*/
			if(trani->getThread() == tranj->getThread()){
				if(trani->getIndex() < tranj->getIndex())
					matrix.addEdge(i,j);
				continue;
			}
		}
	}
	return;
}

void TranSCCalculator::addInitEdges(
				  Calculator::GlobalTranRelation &matrix) const
{
	auto &g = getGraph();
	auto accesses = g.getSCEventsTransactions();
	auto &sctrans = accesses.second;
	/*Get transactionList and explore each transaction per thread*/
	for (auto i = 0u; i < g.getNumThreads(5); i++) {
		for (auto j = 0u; j < g.getThreadTranSize(i); j++) {
			const Transactions *tr = g.getTransaction(Transaction(i,j));
			auto loads = tr->getLoads();
			if(loads.empty()) continue;
			for(auto ev:loads){
				const EventLabel *lab = g.getEventLabel(ev);
				if(!llvm::isa<ReadLabel>(lab)) abort();
				BUG_ON(!llvm::isa<ReadLabel>(lab));
				auto *rLab = static_cast<const ReadLabel *>(lab);
				if (!rLab->getRf().isInitializer())
					continue;
				/*fr edges*/
				// auto preds = calcSCPreds( rLab->getPos());
				for (const auto &w : stores(g, rLab->getAddr())) {
					/* Can be casted to WriteLabel by construction */
					auto *wLab = g.getWriteLabel(w);
					/*If same transaction or not a part of a transaction- do nothing*/
					if(wLab->getTransaction() == Transaction(i,j) || wLab->getTransaction().isInvalid())
						continue;
					auto wSuccs = calcSCSuccs( w);
					matrix.addEdgesFromTo({Transaction(i,j)}, wSuccs); /* Adds rb-edges (fr)*/
				}
			}
		}
	}
	return;
}

void TranSCCalculator::addSCEcos(
			      const std::vector<SAddr> &scLocs,
			      Calculator::GlobalTranRelation &matrix) const
{
	auto &g = getGraph();
	auto &coRelation = g.getPerLocRelation(ExecutionGraph::RelationId::co);

	for (auto loc : scLocs)
		addSCEcosLoc( loc , coRelation[loc], matrix);
	return;
}

void TranSCCalculator::calcTranSCRelation()
{
	auto &g = getGraph();
	auto &TranSCRelation = g.getGlobalTranRelation(ExecutionGraph::RelationId::TranSC);

	/* Collect all SC events (except for RMW loads) */
	auto accesses = g.getSCEventsTransactions();
	/*All events(mem)*/
	auto &scs = accesses.first;
	/*All Transactions*/
	auto &sctrans = accesses.second; 
	std::vector<Event> fcs;

	/* If there are no SC events, it is a valid execution */
	if (scs.empty())
		return;

	/* Add edges from the initializer write (special case) */
	addInitEdges( TranSCRelation);
	/* Add sb and sb_(<>loc);hb;sb_(<>loc) edges (+ Fsc;hb;Fsc) */
	addSbHbEdges(TranSCRelation);

	/*
	 * Collect memory locations with more than one SC accesses
	 * and add the rest of TranSC_base and TranSC_fence
	 */
	addSCEcos( getDoubleLocs(), TranSCRelation);
	TranSCRelation.transClosure();
	addSbHbEdges(TranSCRelation);
	return;
}

Calculator::CalculationResult TranSCCalculator::addTranSCConstraints()
{
	auto &g = getGraph();
	auto &coRelation = g.getPerLocRelation(ExecutionGraph::RelationId::co);
	auto &TranSCRelation = g.getGlobalTranRelation(ExecutionGraph::RelationId::TranSC);
	Calculator::CalculationResult result;

	// if (auto *wbCoh = llvm::dyn_cast<WBCalculator>(
	// 	    g.getCoherenceCalculator())) {
	// 	for (auto &coLoc : coRelation)
	// 		result |= wbCoh->calcWbRelation(coLoc.first, coLoc.second,
	// 						TranSCRelation, [&](Event e)
	// 						{ return g.getEventLabel(e)->isSC() &&
	// 							 !g.isRMWLoad(e); });
	// }
	return result;
}

void TranSCCalculator::initCalc()
{
	auto &g = getGraph();
	auto &TranSCRelation = g.getGlobalTranRelation(ExecutionGraph::RelationId::TranSC);

	/* Collect all SC events (except for RMW loads) */
	auto accesses = getGraph().getSCEventsTransactions();
	TranSCRelation = Calculator::GlobalTranRelation(accesses.second);
	return;
}

Calculator::CalculationResult TranSCCalculator::doCalc()
{
	auto &g = getGraph();
	auto &hbRelation = g.getGlobalRelation(ExecutionGraph::RelationId::hb);
	auto &TranSCRelation = g.getGlobalTranRelation(ExecutionGraph::RelationId::TranSC);
	auto &coRelation = g.getPerLocRelation(ExecutionGraph::RelationId::co);

	hbRelation.transClosure();
	if (!hbRelation.isIrreflexive())
		return Calculator::CalculationResult(false, false);
	calcTranSCRelation();
	if (!TranSCRelation.isIrreflexive())
		return Calculator::CalculationResult(false, false);

	auto result = addTranSCConstraints();
	if (!result.cons)
		return Calculator::CalculationResult(result.changed, false);
	for (auto &coLoc : coRelation)
		coLoc.second.transClosure();

	/* Check that co is acyclic */
	for (auto &coLoc : coRelation) {
		if (!coLoc.second.isIrreflexive())
		return Calculator::CalculationResult(result.changed, false);
	}
	return Calculator::CalculationResult(result.changed, true);
}

void TranSCCalculator::removeAfter(const VectorClock &preds)
{
	/* We do not track anything specific for TranSC */
	return;
}
