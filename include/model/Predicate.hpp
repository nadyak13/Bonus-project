#include <string>
#include <memory>
//#include "GetTypeVisitor.hpp"
//#include "GetResultVisitor.hpp"
#include "Visitor.hpp"


class Predicate {
public: 
    virtual void accept(Visitor &) = 0;
    virtual int get_number() const = 0;
    virtual std::shared_ptr<Predicate> get_left() const = 0;
    virtual std::shared_ptr<Predicate> get_right() const = 0;
    virtual std::string get_what() const = 0;
    virtual std::string get_value() const = 0;
};


class BinaryPredicate : public Predicate {
public:
    virtual std::shared_ptr<Predicate> get_left() const = 0;
    virtual std::shared_ptr<Predicate> get_right() const = 0;
    std::string get_what() const;
    std::string get_value() const;
    virtual int get_number() const = 0;
};

class SubjectPredicate : public Predicate {
public:
    virtual std::string get_what() const = 0;
    virtual std::string get_value() const = 0;
    std::shared_ptr<Predicate> get_left() const;
    std::shared_ptr<Predicate> get_right() const;
    virtual int get_number() const = 0;
};


class AndPredicate : public BinaryPredicate {
    std::shared_ptr<Predicate> left, right;
    int number;
public:
    void accept(Visitor &);
    AndPredicate(std::shared_ptr<Predicate>, std::shared_ptr<Predicate>, int);
    std::shared_ptr<Predicate> get_left() const;
    std::shared_ptr<Predicate> get_right() const;
    int get_number() const;
};

class OrPredicate : public BinaryPredicate {
    std::shared_ptr<Predicate> left, right;
    int number;
public:
    OrPredicate(std::shared_ptr<Predicate>, std::shared_ptr<Predicate>, int);
    void accept(Visitor &);
    std::shared_ptr<Predicate> get_left() const;
    std::shared_ptr<Predicate> get_right() const;
    int get_number() const;
};

class NegationPredicate : public BinaryPredicate {
    std::shared_ptr<Predicate> left;
    std::shared_ptr<Predicate> right;
    int number;
public:
    NegationPredicate(std::shared_ptr<Predicate>, int);
    void accept(Visitor &);
    std::shared_ptr<Predicate> get_left() const;
    std::shared_ptr<Predicate> get_right() const;
    int get_number() const;
};

class FollowPredicate : public BinaryPredicate {
    std::shared_ptr<Predicate> left;
    std::shared_ptr<Predicate> right;
    int number;
public:
    FollowPredicate(std::shared_ptr<Predicate>, std::shared_ptr<Predicate>, int);
    void accept(Visitor &);
    std::shared_ptr<Predicate> get_left() const;
    std::shared_ptr<Predicate> get_right() const;
    int get_number() const;
};


class EqualPredicate : public SubjectPredicate {
    std::string what;
    std::string value;
    int number;
public:
    EqualPredicate(std::string, std::string, int);
    void accept(Visitor &);
    std::string get_what() const;
    std::string get_value() const;
    int get_number() const;
};

class LessPredicate : public SubjectPredicate {
    std::string what;
    std::string value;
    int number;
public:
    LessPredicate(std::string, std::string, int);
    void accept(Visitor &);
    std::string get_what() const;
    std::string get_value() const;
    int get_number() const;
};

class GreaterPredicate : public SubjectPredicate {
    std::string what;
    std::string value;
    int number;
public:
    GreaterPredicate(std::string, std::string, int);
    void accept(Visitor &);
    std::string get_what() const;
    std::string get_value() const;
    int get_number() const;
};

class GreaterEqualPredicate : public SubjectPredicate {
    std::string what;
    std::string value;
    int number;
public:
    GreaterEqualPredicate(std::string, std::string, int);
    void accept(Visitor &);
    std::string get_what() const;
    std::string get_value() const;
    int get_number() const;
};

class LessEqualPredicate : public SubjectPredicate {
    std::string what;
    std::string value;
    int number;
public:
    LessEqualPredicate(std::string, std::string, int);
    void accept(Visitor &);
    std::string get_what() const;
    std::string get_value() const;
    int get_number() const;
};

class NotEqualPredicate : public SubjectPredicate {
    std::string what;
    std::string value;
    int number;
public:
    NotEqualPredicate(std::string, std::string, int);
    void accept(Visitor &);
    std::string get_what() const;
    std::string get_value() const;
    int get_number() const;
};