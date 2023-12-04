/*
Omkar
*/

#ifndef __TranSC_CALCULATOR_HPP__
#define __TranSC_CALCULATOR_HPP__

#include "Calculator.hpp"

class TranSCCalculator : public Calculator {

public:
	TranSCCalculator(ExecutionGraph &g) : Calculator(g) {}

	/* Overrided Calculator methods */

	/* Initialize necessary matrices */
	void initCalc() override;

	/* Performs a step of the LB calculation */
	Calculator::CalculationResult doCalc() override;

	/* The calculator is informed about the removal of some events */
	void removeAfter(const VectorClock &preds) override;

	std::unique_ptr<Calculator> clone(ExecutionGraph &g) const override {
		return std::make_unique<TranSCCalculator>(g);
	}

private:
	/* Returns a list with all accesses that are accessed at least twice */
	std::vector<SAddr> getDoubleLocs() const;

	
	std::vector<Transaction> calcSCSuccs(const std::vector<Event> &fcs,
				       const Event e) const;
	std::vector<Transaction> calcSCPreds(const std::vector<Event> &fcs,
				       const Event e) const;
	std::vector<Transaction> calcRfSCSuccs(const std::vector<Event> &fcs,
					 const Event e) const;

	void addRbEdges(const std::vector<Event> &fcs,
			const std::vector<Transaction> &moAfter,
			const std::vector<Transaction> &moRfAfter,
			Calculator::GlobalTranRelation &matrix, const Event &e) const;
	void addMoRfEdges(const std::vector<Event> &fcs,
			  const std::vector<Transaction> &moAfter,
			  const std::vector<Transaction> &moRfAfter,
			  Calculator::GlobalTranRelation &matrix, const Event &e) const;
	void addSCEcosLoc(const std::vector<Event> &fcs,
			  Calculator::GlobalRelation &coMatrix,
			  Calculator::GlobalTranRelation &TranSCMatrix) const;

	void addSCEcos(const std::vector<Event> &fcs,
		       const std::vector<SAddr> &scLocs,
		       Calculator::GlobalTranRelation &matrix) const;

	void addInitEdges(const std::vector<Event> &fcs,
			  Calculator::GlobalTranRelation &matrix) const;
	void addSbHbEdges(Calculator::GlobalTranRelation &matrix) const;

	Calculator::CalculationResult addTranSCConstraints();
	void calcTranSCRelation();
};

#endif /* __TranSC_CALCULATOR_HPP__ */
