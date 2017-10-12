#include "GetResultVisitor.hpp"
#include "Payment.hpp"
#include "Client.hpp"
#include "DateParser.hpp"
#include "TimeParser.hpp"
#include "Predicate.hpp"


bool GetResultVisitor::evaluate(Predicate &p, std::shared_ptr<Payment> payment, std::shared_ptr<Client> cl) {
    pay = payment;
    client = cl;
    p.accept(*this);
    return result;
}

void GetResultVisitor::visit(const AndPredicate &p) {
    GetResultVisitor v1;
    GetResultVisitor v2;
    result = v1.evaluate(*p.get_left(), pay, client) && v2.evaluate(*p.get_right(), pay, client);
}

void GetResultVisitor::visit(const OrPredicate &p) {
    GetResultVisitor v1;
    GetResultVisitor v2;
    result = v1.evaluate(*p.get_left(), pay, client) || v2.evaluate(*p.get_right(), pay, client);
}

void GetResultVisitor::visit(const NegationPredicate &p) {
    GetResultVisitor v;
    result = !v.evaluate(*p.get_right(), pay, client);
}

void GetResultVisitor::visit(const FollowPredicate &p) {
    GetResultVisitor v1;
    GetResultVisitor v2;
    result = !v1.evaluate(*p.get_left(), pay, client) || v2.evaluate(*p.get_right(), pay, client);
}

void GetResultVisitor::visit(const EqualPredicate &p) {
    if (p.get_what() == "date") {
        DateParser parser;
        Date date = parser.parse(p.get_value());
        if (date == pay->get_date()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "time") {
        TimeParser parser;
        Time time = parser.parse(p.get_value());
        if (time == pay->get_time()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "shop") {
        if (p.get_value() == pay->get_shop()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "amount") {
        double n = stod(p.get_value());
        if (n == pay->get_amount()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "balance") {
        double n = stod(p.get_value());
        if (n == client->get_balance()) {
            result = true;
        } else {
            result = false;
        }
    } 
}

void GetResultVisitor::visit(const NotEqualPredicate &p) {
    if (p.get_what() == "date") {
        DateParser parser;
 
            Date date = parser.parse(p.get_value());
            if (date != pay->get_date()) {
                result = true;
            } else {
                result = false;
            }

    } else if (p.get_what() == "time") {
        TimeParser parser;
            Time time = parser.parse(p.get_value());
            if (time != pay->get_time()) {
                result = true;
            } else {
                result = false;
            }
    } else if (p.get_what() == "shop") {
        if (p.get_value() != pay->get_shop()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "amount") {
        double n = stod(p.get_value());
        if (n != pay->get_amount()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "balance") {
        double n = stod(p.get_value());
        if (n != client->get_balance()) {
            result = true;
        } else {
            result = false;
        }
    }
}

void GetResultVisitor::visit(const GreaterPredicate &p) {
    if (p.get_what() == "date") {
        DateParser parser;
        Date date = parser.parse(p.get_value());
        if (date < pay->get_date()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "time") {
        TimeParser parser;
        Time time = parser.parse(p.get_value());
        if (time < pay->get_time()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "amount") {
        double n = stod(p.get_value());
        if (n < pay->get_amount()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "balance") {
        double n = stod(p.get_value());
        if (n < client->get_balance()) {
            result = true;
        } else {
            result = false;
        }
    }
}

void GetResultVisitor::visit(const GreaterEqualPredicate &p) {
    if (p.get_what() == "date") {
        DateParser parser;
        Date date = parser.parse(p.get_value());
        if (date <= pay->get_date()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "time") {
        TimeParser parser;
        Time time = parser.parse(p.get_value());
        if (time <= pay->get_time()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "amount") {
        double n = stod(p.get_value());
        if (n <= pay->get_amount()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "balance") {
        double n = stod(p.get_value());
        if (n <= client->get_balance()) {
            result = true;
        } else {
            result = false;
        }
    }
}
void GetResultVisitor::visit(const LessPredicate &p) {
    if (p.get_what() == "date") {
        DateParser parser;
        Date date = parser.parse(p.get_value());
        if (date > pay->get_date()) { 
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "time") {
        TimeParser parser;
        Time time = parser.parse(p.get_value());
        if (time > pay->get_time()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "amount") {
        double n = stod(p.get_value());
        if (n > pay->get_amount()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "balance") {
        double n = stod(p.get_value());
        if (n > client->get_balance()) {
            result = true;
        } else {
            result = false;
        }
    }
}
void GetResultVisitor::visit(const LessEqualPredicate &p) {
    if (p.get_what() == "date") {
        DateParser parser;
        Date date = parser.parse(p.get_value());
        if (date >= pay->get_date()) { 
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "time") {
        TimeParser parser;
        Time time = parser.parse(p.get_value());
        if (time >= pay->get_time()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "amount") {
        double n = stod(p.get_value());
        if (n >= pay->get_amount()) {
            result = true;
        } else {
            result = false;
        }
    } else if (p.get_what() == "balance") {
        double n = stod(p.get_value());
        if (n >= client->get_balance()) {
            result = true;
        } else {
            result = false;
        }
    }
}
