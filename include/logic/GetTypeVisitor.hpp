#include <string>
#include "Visitor.hpp" 
//#include "Predicate.hpp"
class Predicate;

class GetTypeVisitor : public Visitor {
public:
    std::string type;
public:
    void visit(const AndPredicate &);
    void visit(const OrPredicate &);
    void visit(const NegationPredicate &);
    void visit(const FollowPredicate &);
    void visit(const EqualPredicate &);
    void visit(const NotEqualPredicate &);
    void visit(const GreaterPredicate &);
    void visit(const GreaterEqualPredicate &);
    void visit(const LessPredicate &);
    void visit(const LessEqualPredicate &);
};