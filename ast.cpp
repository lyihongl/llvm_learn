#include <memory>
#include <string>
#include <vector>

class ExprAST {
   public:
    virtual ~ExprAST();
};

class NumberExprAST : public ExprAST {
    double Val;

   public:
    NumberExprAST(double Val) : Val(Val) {}
};

class VariableExprAST : public ExprAST {
    std::string Name;

   public:
    VariableExprAST(const std::string& Name) : Name(Name) {}
};

class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

   public:
    BinaryExprAST(
        char op,
        std::unique_ptr<ExprAST> LHS,
        std::unique_ptr<ExprAST> RHS) : Op(Op),
                                        LHS(std::move(LHS)),
                                        RHS(std::move(RHS)) {}
};

class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

   public:
    CallExprAST(
        const std::string& Callee,
        std::vector<std::unique_ptr<ExprAST>> Args) : Callee(Callee),
                                                      Args(std::move(Args)) {}
};

class ProtoTypeAST {
    std::string Name;
    std::vector<std::string> Args;

   public:
    ProtoTypeAST(
        const std::string& name,
        std::vector<std::string> Args) : Name(name), Args(std::move(Args)) {}
    const std::string& getName() const { return Name; }
};

class FunctionAST {
    std::unique_ptr<ProtoTypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

   public:
    FunctionAST(
        std::unique_ptr<ProtoTypeAST> Proto,
        std::unique_ptr<ExprAST> Body) : Proto(std::move(Proto)),
                                         Body(std::move(Body)) {}
};