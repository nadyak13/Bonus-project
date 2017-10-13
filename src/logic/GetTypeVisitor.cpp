#include "GetTypeVisitor.hpp"

void GetTypeVisitor::visit(const AndPredicate &p) {
    type = "&&";
}

void GetTypeVisitor::visit(const OrPredicate &p) {
    type = "||";
}

void GetTypeVisitor::visit(const NegationPredicate &p) {
    type = "!";
}

void GetTypeVisitor::visit(const FollowPredicate &p) {
    type = "->";
}

void GetTypeVisitor::visit(const EqualPredicate &p) {
    type = "==";
}

void GetTypeVisitor::visit(const NotEqualPredicate &p) {
    type = "!=";
}

void GetTypeVisitor::visit(const GreaterPredicate &p) {
    type = ">";
}

void GetTypeVisitor::visit(const GreaterEqualPredicate &p) {
    type = ">=";
}

void GetTypeVisitor::visit(const LessPredicate &p) {
    type = "<";
}

void GetTypeVisitor::visit(const LessEqualPredicate &p) {
    type = "<=";
}