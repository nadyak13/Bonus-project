#pragma once
//#include "Predicate.hpp"
class AndPredicate;
class OrPredicate;
class NegationPredicate;
class FollowPredicate;
class EqualPredicate;
class NotEqualPredicate;
class GreaterPredicate;
class GreaterEqualPredicate;
class LessPredicate;
class LessEqualPredicate;

class Visitor {
public:
    virtual void visit(const AndPredicate &) = 0; 
    virtual void visit(const OrPredicate &) = 0;
    virtual void visit(const NegationPredicate &) = 0;
    virtual void visit(const FollowPredicate &) = 0;
    virtual void visit(const EqualPredicate &) = 0;
    virtual void visit(const NotEqualPredicate &) = 0;
    virtual void visit(const GreaterPredicate &) = 0;
    virtual void visit(const GreaterEqualPredicate &) = 0;
    virtual void visit(const LessPredicate &) = 0;
    virtual void visit(const LessEqualPredicate &) = 0;
};