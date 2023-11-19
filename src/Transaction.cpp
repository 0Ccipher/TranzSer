/*
 * Omkar Tuppe
 */

#include "Transaction.hpp"

llvm::raw_ostream& operator<<(llvm::raw_ostream &s, Transaction e)
{
	return s << "(" << e.thread << ", " << e.index << ")";
}

