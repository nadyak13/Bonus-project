#include <memory>
#include "Visitor.hpp"
//#include "Predicate.hpp"
class Payment;
class Predicate;
class Client;


class GetResultVisitor : public Visitor {
public:
    bool result;
    std::shared_ptr<Payment> pay;
    std::shared_ptr<Client> client;
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
    bool evaluate(Predicate &, std::shared_ptr<Payment>, std::shared_ptr<Client>);
};